#ifndef ORCA_JSON_H
#define ORCA_JSON_H
#ifndef ORCA_JSON_AMALGAMATION
#include "cee.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#endif

#define MAX_JSON_DEPTH 500

namespace cee {
  namespace json {
    
struct null {};
struct undefined {};

enum type {
  type_is_undefined,	///< Undefined value
  type_is_null,	      ///< null value
  type_is_boolean,	  ///< boolean value
  type_is_number,	    ///< numeric value
  type_is_string,	    ///< string value
  type_is_object,	    ///< object value 
  type_is_array	      ///< array value
};

struct data {
	enum type t;
  union {
    struct singleton::data * null;
    struct singleton::data * undefined;
    struct singleton::data * boolean;
    struct box::data       * number;
    struct str::data       * string;
    struct vect::data      * array;
    struct map::data       * object;
  } value;
};

enum format {
  compact = 0,
  readable = 1
};

extern enum type type  (json::data *);
extern bool is_undefined (json::data *);
extern bool is_null (json::data *);
extern bool to_bool (json::data *);

extern json::data * find (json::data *, char *);
extern json::data * get(json::data *, char *, json::data * def);

extern bool save (json::data *, FILE *, int how);
extern json::data * load_from_file (FILE *, bool force_eof, int * error_at_line);
extern json::data * load_from_buffer (int size, char *, int line);
extern int cmp (json::data *, json::data *);

extern vect::data * to_array (json::data *);
extern map::data * to_object (json::data *);
extern box::data * to_number (json::data *);
extern str::data * to_string (json::data *);

extern json::data * mk_true();
extern json::data * mk_false();
extern json::data * mk_undefined ();
extern json::data * mk_null ();
extern json::data * mk_object();
extern json::data * mk_number (double d);
extern json::data * mk_string(str::data * s);
extern json::data * mk_array(int s);

extern void object_set (json::data *, char *, json::data *);
extern void object_set_bool (json::data *, char *, bool);
extern void object_set_string (json::data *, char *, char *);
extern void object_set_number (json::data *, char *, double);

extern void array_append (json::data *, json::data *);
extern void array_append_bool (json::data *, bool);
extern void array_append_string (json::data *, char *);
extern void array_append_number (json::data *, double);

extern size_t snprint (char * buf, size_t size, json::data *, enum format);

extern bool parse(char * buf, uintptr_t len, json::data **out, bool force_eof,
                  int *error_at_line);
    
  }
}

#endif // ORCA_JSON_H