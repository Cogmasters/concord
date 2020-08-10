#ifndef ORCA_JSON_H
#define ORCA_JSON_H
#ifndef ORCA_JSON_AMALGAMATION
#include "cee.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#endif

#define MAX_JSON_DEPTH 500

struct json_null {};
struct json_undefined {};

enum json_type {
  is_undefined,	///< Undefined value
  is_null,	///< null value
  is_boolean,	///< boolean value
  is_number,	///< numeric value
  is_string,	///< string value
  is_object,	///< object value 
  is_array	///< array value
};

struct json {
	enum json_type t;
  union {
    struct cee_singleton * null;
    struct cee_singleton * undefined;
    struct cee_singleton * boolean;
    struct cee_box       * number;
    struct cee_str       * string;
    struct cee_vect      * array;
    struct cee_map       * object;
  } value;
};

enum json_format {
  compact = 0,
  readable = 1
};

extern enum json_type json_type  (struct json *);
extern bool json_is_undefined (struct json *);
extern bool json_is_null (struct json *);
extern bool json_to_bool (struct json *);

extern struct json * json_find (struct json *, char *);
extern struct json * json_get(struct json *, char *, struct json * def);

extern bool json_save (struct json *, FILE *, int how);
extern struct json * json_load_from_file (FILE *, bool force_eof, int * error_at_line);
extern struct json * json_load_from_buffer (int size, char *, int line);
extern int json_cmp (struct json *, struct json *);

extern struct cee_vect * json_to_array (struct json *);
extern struct cee_map * json_to_object (struct json *);
extern struct cee_box * json_to_number (struct json *);
extern struct cee_str * json_to_string (struct json *);

extern struct json * json_true();
extern struct json * json_false();
extern struct json * json_undefined ();
extern struct json * json_null ();
extern struct json * json_object();
extern struct json * json_number (double d);
extern struct json * json_string(struct cee_str * s);
extern struct json * json_array(int s);

extern void json_object_set (struct json *, char *, struct json *);
extern void json_object_set_bool (struct json *, char *, bool);
extern void json_object_set_string (struct json *, char *, char *);
extern void json_object_set_number (struct json *, char *, double);

extern void json_array_append (struct json *, struct json *);
extern void json_array_append_bool (struct json *, bool);
extern void json_array_append_string (struct json *, char *);
extern void json_array_append_number (struct json *, double);

extern size_t json_snprintf(char * buf, size_t size, struct json *, 
                                 enum json_format);

extern bool json_parse(char * buf, uintptr_t len, 
                       struct json **out, bool force_eof,
                       int *error_at_line);

#endif // ORCA_JSON_H