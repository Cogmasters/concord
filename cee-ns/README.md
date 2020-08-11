# A single file C++ library to provide similar productivity of C++ STL
It's basically C with C++'s namespace.  It does not intend to replicate C++ STL

## How to use it ?

1. Download the two files;
```
  wget https://raw.githubusercontent.com/cee-studio/orca/master/cee-cc/release/cee.h
  wget https://raw.githubusercontent.com/cee-studio/orca/master/cee-cc/release/cee.cc
```
2. Add them to your source folder


## Usage Examples

**string**
```
  #include "cee.h"
 
  using namespace cee;

  str::data * s, * s1, * s2;
  
  s = str::mk("the number ten: %d", 10);
  printf("%s\n", (char *)s);
  
  s1 = str::mk("the number ten point three: %.1f", 10.3);
  printf("%s\n", (char *)e);
  
  s2 = str::mk("%s, %s", s, s1);
  printf("%s\n", (char *)s2);

  // delete strings
  del(s);
  del(s1);
  del(s2);
```

**vector**
```
  #include "cee.h"
 
  using namespace cee;

  vect::data *v;
  
  v = vect::mk(1);
  v = vect::append(v, str::mk("1"));
  v = vect::append(v, str::mk("2"));
  v = vect::append(v, str::mk("3"));
  
  printf("v.count %u\n", vect::count(v));
  for (int i = 0; i < vect::count(v); i++) {
    printf ("%d:%s\n", i, (char *)v->e[i]);
  }

  // delete vector
  del(v);
```

**set**
```
  #include "cee.h"

  using namespace cee;

  set::data * st = set::mk((cmp_fun)strcmp);
  printf ("st: %p\n", st);
  set::add(st, "a");
  set::add(st, "aabc");
  char * p = (char *)set::find(st, "aabc");
  printf ("%s\n", p);

  // delete set 
  del(st);
```

**map**
```
  #include "cee.h"

  using namespace cee;

  map::data * mp = map::mk((cmp_fun)strcmp);  
  map::add(mp, str::mk("1"), box::from_i32(10));
  map::add(mp, str::mk("2"), box::from_i32(20));
  map::add(mp, str::mk("3"), box::from_i32(30));
  
  void * t = map::find(mp, "1");
  printf ("found value %u\n", (uintptr_t)t);
  
  vect::data * keys = map::keys(mp);
  for (int i = 0; i < vect::count(keys); i++) {
    printf ("[%d] key:%s\n", i, (char *)keys->e[i]);
  }
 
  // delete map
  del(mp);
```

**stack**
```
  #include "cee.h"

  using namespace;

  stack::data * sp = stack::mk_e(dp_noop, 100);
  stack::push(sp, "1");
  stack::push(sp, "2");
  stack::push(sp, "3");
  printf ("%s\n", stack::top(sp, 0));

  // delete stack, optional
  del(stack);
```

**free any memory blocks of `struct cee_*`**

any memory blocks pointed by a `cee struct` can be freed with `cee_del` like the following:
```
   #include "cee.h"

   using namespace cee;

   str::data * s = ..;
   del(s);

   vect::data * v = ..;
   del(v);

   map::data * m = ..;
   del(m);

   stack::data * sp = ..;
   del(sp);
```

## How to test/develop it ?

### Using https://cee.studio cloud IDE
1. click [https://cee.studio/?bucket=orca&name=cee-cc](https://cee.studio/?bucket=orca&name=cee-cc)
2. clone to my account
3. click Start
4. run it Terminal

All memory access violations will be detected and reproted. 


### Using your computer

```
git clone https://github.com/cee-studio/orca.git
cd orca/cee-cc
make
./a.out
```

## Rationale

[DESIGN](./DESIGN.md)


## Contirubtion are welcome

Please oin our discord [https://discord.gg/nBUqrWf](https://discord.gg/nBUqrWf)