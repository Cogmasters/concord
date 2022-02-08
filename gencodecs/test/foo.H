ENUM_BEGIN(foo_types)
    ENUMERATOR(FOO_A, = 1)
    ENUMERATOR(FOO_B, BLANK)
    ENUMERATOR_LAST(FOO_C, = 10)
ENUM_END

STRUCT_BEGIN(foo)
  COND_WRITE(this->id != NULL)
    FIELD_PTR(char, *, id)
  COND_END
  COND_WRITE(this->name != NULL)
    FIELD_PTR(char, *, name)
  COND_END
  COND_WRITE(this->b != 0)
    FIELD(int, b, 5)
  COND_END
  COND_WRITE(this->child != NULL)
    FIELD_STRUCT_PTR(foo, *, child)
  COND_END
STRUCT_END

LIST_BEGIN(bars)
    LISTTYPE_STRUCT(bars)
LIST_END

LIST_BEGIN(integers)
    LISTTYPE_PRIMITIVE(int)
LIST_END
