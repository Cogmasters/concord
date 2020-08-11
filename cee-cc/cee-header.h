#undef DATA_OFFSET
#undef FIND_HEADER
#define DATA_OFFSET (__builtin_offsetof(struct S(header), _))
#define FIND_HEADER(p)  (struct S(header) *)((void *)((char *)(p) - DATA_OFFSET))
#define ZERO_CEE_SECT(s)  do{ memset(s, 0, sizeof(struct cee::sect)); } while(0);