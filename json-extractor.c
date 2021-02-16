#include "json-actor.c"
#include "json-scanf.h"

static char*
print_token(jsmntype_t type)
{
  switch (type) {
    case JSMN_UNDEFINED:  return "undefined";
    case JSMN_OBJECT:     return "object";
    case JSMN_ARRAY:      return "array";
    case JSMN_STRING:     return "string";
    case JSMN_PRIMITIVE:  return "primitive";
    default:              ERR("Unknown JSMN_XXXX type encountered (code: %d)", type);
  }
  return NULL; // avoid warning
}

static int keycmp(char *json, jsmntok_t *tok, struct sized_buffer *key)
{
  if (tok->type == JSMN_STRING
      && key->size == tok->end - tok->start
      && STRNEQ(json + tok->start, key->start, key->size))
  {
    return 0;
  }
  return -1;
}

static char * copy_over_string (size_t * new_size, char * str, size_t len)
{
  char * new_str = NULL;
  if (json_unescape_string(&new_str, new_size, str, len)) {
    return new_str;
  }
  else {
    // ill formed string
    char * p = NULL;
    asprintf(&p, "cannot unescape an ill-formed-string %.*s", (int)len, str);
    *new_size = strlen(p) + 1;
    return p;
  }
}

struct e_info {
  char * pos;
  jsmntok_t *tok;
  int n_toks;
  struct existence * E;
};



static int extract_str (struct action * v, int i, struct e_info * info)
{
  jsmntok_t * t = info->tok;
  ASSERT_S (JSMN_STRING == t[i].type, "expecect string");

  size_t new_size = 0;
  int len = t[i].end - t[i].start;
  char * json = info->pos;
  char * escaped = copy_over_string(&new_size, json + t[i].start, len);

  switch(v->mem_size.tag)
  {
    case SIZE_ZERO: {
      char **p = (char **) v->operand;
      int len = t[i].end - t[i].start + 1;
      *p = malloc(len);
      int ret = snprintf(*p, len, "%.*s", len - 1, escaped);
      ASSERT_S(ret < len, "out-of-bounds write");
      break;
    }
    case SIZE_FIXED:
    case SIZE_PARAMETERIZED:
    {
      int ret = snprintf((char *) v->operand, v->mem_size.size,
                         "%.*s", t[i].end - t[i].start, escaped);
      ASSERT_S((size_t) ret < v->mem_size.size, "out-of-bounds write");
      break;
    }
    case SIZE_UNKNOWN:
    {
      // we have to allow this potential oob write as
      // we don't know the buffer size of recipient.
      sprintf((char *) v->operand, "%.*s", (int)new_size, escaped);
      break;
    }
  }
  if (escaped != json + t[i].start)
    free(escaped);
  return 0;
}

static int extract_scalar (struct action * a, int i, struct e_info * info)
{
  jsmntok_t * t = info->tok;
  char * json = info->pos, * end;
  ASSERT_S(t[i].type == JSMN_PRIMITIVE, "Not a primitive");

  switch(a->_.builtin)
  {
    case B_INT:
      if ('n' == json[t[i].start])
        *(int *) a->operand = 0;
      else {
        *(int *) a->operand = (int) strtol(json + t[i].start, &end, 10);
        if (end != json + t[i].end) goto type_error;
        break;
      }
    case B_BOOL:
      switch (json[t[i].start]) {
        case 't': *(bool *)a->operand = true; break;
        case 'f': *(bool *)a->operand = false; break;
        default: goto type_error;
      }
      break;
    case B_LONG_LONG:
      if ('n' == json[t[i].start])
        *(long long *) a->operand = 0;
      else {
        *(long long *) a->operand = strtoll(json + t[i].start, &end, 10);
        if (end != json + t[i].end) goto type_error;
      }
      break;
    case B_FLOAT:
      if ('n' == json[t[i].start])
        *(float *) a->operand = 0;
      else {
        *(float *) a->operand = strtof(json + t[i].start, &end);
        if (end != json + t[i].end) goto type_error;
      }
      break;
    case B_DOUBLE:
      if ('n' == json[t[i].start])
        *(double *) a->operand = 0;
      else {
        *(double *) a->operand = strtod(json + t[i].start, &end);
        if (end != json + t[i].end) goto type_error;
      }
      break;
    default:
      ERR("unexpected");
  }
type_error:
  return 0;
}

static int apply_action (struct value * v, int idx, struct e_info * info)
{
  jsmntok_t * t = info->tok;
  char * json = info->pos;
  ASSERT_S(V_ACTION == v->tag, "expect an action");

  struct action * a = &v->_.action;
  if (ACT_BUILT_IN == v->_.action.tag) {
    switch (a->_.builtin) {
      case B_STRING:
        extract_str(a, idx, info);
        break;
      case B_TOKEN: {
        struct sized_buffer *tk = a->operand;
        tk->start = json + t[idx].start;
        tk->size = t[idx].end - t[idx].start;
        break;
      }
      default:
        if (a->_.builtin < B_STRING)
          extract_scalar(a, idx, info);
        else
          ERR("unexpected case %d\n", a->_.builtin);
        break;
    }
  }
  else if (ACT_FORMAT_STRING == a->tag) {
    ERR("not supported yet");
  }
  else {
    if (t[idx].type == JSMN_PRIMITIVE
        && (STRNEQ(json + t[idx].start, "null", 4))) {
      //es->is_applied = false;
    }
    else if (0 == t[idx].size
             && (t[idx].type == JSMN_OBJECT || t[idx].type == JSMN_ARRAY)) {
    }
    else {
      int (*f)(char *, size_t, void *);
      f = a->_.user_def;
      int ret = (*f)(json + t[idx].start, t[idx].end - t[idx].start, a->operand);
      if (0 == ret);
      //es->is_applied = false;
    }
  }
  return 0;
}

static int
extract_object_value (struct composite_value * cv, int parent, struct e_info *);
static int
extract_array_value (struct composite_value * cv, int parent, struct e_info *);

static int
extract_value (struct value * v, int val_idx, struct e_info * info)
{
  switch (v->tag) {
    case V_ACTION:
      apply_action(v, val_idx, info);
      break;
    case V_COMPOSITE_VALUE:
      if (v->_.cv->is_object)
        extract_object_value(v->_.cv, val_idx, info);
      else
        extract_array_value(v->_.cv, val_idx, info);
      break;
    case V_PRIMITIVE:
      break;
    case V_STRING_LITERAL:
      break;
  }
  return 0;
}

static int
extract_access_path (
  int val_idx,
  struct access_path_value *apv,
  struct access_path *curr_path,
  struct e_info * info)
{
  char * json = info->pos;
  jsmntok_t * t = info->tok;

  char *end = 0;
  int i = val_idx, ic;
  if (curr_path)
  {
    switch (t[val_idx].type) {
      case JSMN_OBJECT:
        for (ic = i + 1; t[ic].start < t[i].end; ic++) {
          if (i != t[ic].parent)
            continue;

          // top level key within t[i]
          if (0 == keycmp(json, &t[ic], &curr_path->key))
            return extract_access_path(ic+1, apv, curr_path->next, info);
        }
        return 0;
      case JSMN_ARRAY:
      {
        char *end;
        int index = strtol(curr_path->key.start, &end, 10);
        ASSERT_S(*end == 0, "Index is not a number");
        ASSERT_S(index >= 0, "Index is not zero or positive");
        ASSERT_S(index < t[i].size, "Index is out-of-bound");

        ic = i + 1; // the first child of i;
        return extract_access_path(ic + index, apv, curr_path->next, info);
      }
      default:
        ERR("Patch match error (not an Object or Array)");
    }
    return 0;
  }
  struct value * v = &apv->value;
  return extract_value(v, val_idx, info);
}

static void
print_tok (char * json, jsmntok_t * tok, int i) {
  D_PRINT("[%u][p:%d][size:%d]%s (%.*s)\n",
          i, tok[i].parent,
          tok[i].size, print_token(tok[i].type),
          (int)(tok[i].end - tok[i].start), json + tok[i].start);
}
static int
extract_object_value (
  struct composite_value * cv,
  int parent,
  struct e_info * info)
{
  char * json = info->pos;
  jsmntok_t * t = info->tok;

  int key_idx = parent + 1, val_idx = parent + 2;
  struct access_path_value *p;
  int nkeys = 0;
  while (1) {
    if (t[key_idx].type != JSMN_STRING) {
      print_tok(json, t, key_idx);
    }
    ASSERT_S(t[key_idx].type == JSMN_STRING, "Not a key"); // make sure it's a key
    ASSERT_S(t[key_idx].parent == parent, "Token is not at top level"); // make sure it's at the toplevel

    for (size_t i = 0; i < cv->_.pairs.size; i++) {
      p = cv->_.pairs.pos + i;
      if (0 == keycmp(json, &t[key_idx], &p->path.key))
        extract_access_path(val_idx, p, p->path.next, info);
    }

    nkeys ++;
    if (nkeys < t[parent].size) {
      // find the next toplevel key
      key_idx = val_idx + 1;
      while (t[key_idx].end < t[val_idx].end && t[key_idx].end < t[parent].end) {
        print_tok(json, t, key_idx);
        key_idx ++;
      }
    }
    else
      break;
  }
}

static struct value * is_list_extraction (struct composite_value * cv)
{
  struct value * v = cv->_.elements.pos;
  if (1 == cv->_.elements.size
      && V_ACTION == v->tag
      && ACT_BUILT_IN == v->_.action.tag
      && B_LIST == v->_.action._.builtin) {
    return v;
  }

  return NULL;
}

static int
extract_array_value (
  struct composite_value * cv,
  int parent,
  struct e_info * info)
{
  jsmntok_t * t = info->tok;
  int n_toks = info->n_toks;

  struct sized_buffer **token_array = NULL;
  int * children;

  int n = t[parent].size;

  struct value * v = is_list_extraction(cv);

  if (v)
    token_array = (struct sized_buffer **)
      ntl_malloc(n, sizeof(struct sized_buffer));
  else
    children = malloc(n * sizeof(int));

  int idx, ic;
  for (idx = 0, ic = parent + 1; ic < n_toks && idx < n; ic++) {
    if (t[ic].parent != parent)
      continue;

    if (v) {
      token_array[idx]->start = info->pos + t[ic].start;
      token_array[idx]->size = t[ic].end - t[ic].start;
    }
    else {
      children[idx] = ic;
    }
    ++idx;
  }

  if (v) {
    *(struct sized_buffer ***)v->_.action.operand = token_array;
    return 1;
  }

  for (size_t i = 0; i < cv->_.elements.size && i < n; i++) {
    v = cv->_.elements.pos + i;
    extract_value(v, children[i], info);
  }

  free(children);
  return 0;
}

int
json_extract_va_list (char * json, size_t size, char * extractor, va_list ap)
{
  struct stack stack = { .array = {0}, .top = 0, .actor = EXTRACTOR };
  struct operand_addrs rec = { 0 };
  struct composite_value cv;

  prepare_actor(&stack, &rec, &cv, json, size, extractor, ap);
  struct e_info info = { .pos = json, .E = NULL };

  //calculate how many tokens are needed
  jsmn_parser parser;
  jsmn_init(&parser);
  jsmntok_t * tok = NULL;
  int num_tok = jsmn_parse(&parser, json, size, NULL, 0);
  D_PRINT("# of tokens = %d", num_tok);
  if (num_tok < 0) {
    D_PRINT("Failed to parse JSON: %.*s", (int)size, json);
    D_PRINT("Returned token number: %d", num_tok);
    goto cleanup;
  }

  tok = malloc(sizeof(jsmntok_t) * num_tok);
  jsmn_init(&parser);
  num_tok = jsmn_parse(&parser, json, size, tok, num_tok);

  /* Assume the top-level element is an object */
  if (num_tok < 1 || !(tok[0].type == JSMN_OBJECT || tok[0].type == JSMN_ARRAY))
  {
    D_PRINT("Object or array expected");
    goto cleanup;
  }

  for (int i = 0; i < num_tok; i++) {
    print_tok(json, tok, i);
  }

  info.n_toks = num_tok;
  info.tok = tok;
  switch (tok[0].type)
  {
    case JSMN_OBJECT:
      ASSERT_S(cv.is_object, "Cannot extract array from json object\n");
      extract_object_value(&cv, 0, &info);
      break;
    case JSMN_ARRAY:
      ASSERT_S(!cv.is_object, "Cannot extract object from json array\n");
      extract_array_value(&cv, 0, &info);
      break;
    default:
      ERR("Unexpected toplevel token %s\n", print_token(tok[0].type));
      goto cleanup;
  }

  cleanup:
  return 0;
}

int json_extract (char * json, size_t size, char * extractor, ...)
{
  va_list ap;
  va_start(ap, extractor);
  size_t used_bytes = json_extract_va_list(json, size, extractor, ap);
  va_end(ap);
  return used_bytes;
}
