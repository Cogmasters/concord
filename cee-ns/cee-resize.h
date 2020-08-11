static struct S(header) * S(resize)(struct S(header) * h, size_t s) 
{
  struct S(header) * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
    	ret = (struct S(header) *)realloc(h, s);
      ret->cs.mem_block_size = s;
      break;
    case resize_with_malloc:
    	ret = (struct S(header) *)malloc(s);
    	memcpy(ret, h, h->cs.mem_block_size);
      ret->cs.mem_block_size = s;
      break;
    case resize_with_identity:
      ret = h;
      break;
  }
  return ret;
}