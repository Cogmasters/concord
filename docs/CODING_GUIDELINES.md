# CODING GUIDELINES

In order to keep the code concise and easy to read, there are a few rules to follow. Feel free to use these coding guidelines outside of this project.

## Naming

Try using an organized naming scheme for your new functions and variable names. It doesn't necessarily mean that you should use the same as in other places of the code. The names should be logical, understandable and be named according to what they're used for. File-local functions should be made static. We require lowercase names for all of our symbols (functions, variables names, etc).

## Line Width

Try to use lines that are at most 80 characters long. This is an amount of text that is easy to fit in most monitors. Don't be afraid to break a long function into many lines.

## Indentation

We use always two spaces for identation for each new open brace, never TABs. If readability becomes an issue, your better judgment should tell you whether you need more or less identation. For compactness and readability, this is the preferred identation style:

```c
for (int i=0; i < n; ++i) {
  if (something) {
    ...
  }
  else if (something_else) {
    ...
  } 
  else {
    ...
  }
}
```
Use your surrounding code as a guide.

## Braces

In if/while/do/for expressions, we write the open brace on the same line as the keyword and we then set the closing brace on the same indentation level as the initial keyword. Like this:

```c
if (age < 40) {
  ...
}
```

You may omit the braces if they would contain only a one-line statement:

```c
if (!x) continue;
```
OR
```c
if (!x)
  continue;
```

For functions, the opening brace should be on a separate line:

```c
int main(int argc, char *argv[])
{
  return 0;
}
```

## 'else' on the following line

When adding an else clause to a conditional expression using braces, we add it on a new line after the closing brace like this:

```c
if (age < 40) {
  ...
}
else {
  ...
}
```

## Space before parentheses

When writing expressions using if/while/do/for, there should be no space between the keyword and the open parenthesis like this:

```c
while (1) {
  ...
}
```

## No typedefed structs

Use structs by all means, but do not typedef them. Use the `struct` syntax to identify them:

```c
struct something {
   void *valid;
   size_t way_to_write;
};
struct something instance;
```
Not okay:
```c
typedef struct {
   void *wrong;
   size_t way_to_write;
} something;
something instance;
```

## Conditional Statements

### Nesting

To keep the code away from deep nesting, one should always check for false conditions.

Instead of checking only for true, like so:

```c
if (IS_PAIR(a)) {
  if (IS_BASE_TWO(a)) {
    if (a > 100) {
      for (int i=0; i < a; ++i) {
        ...
      }
    }
  }
}
```

We can achieve a code with better flow and minimal nesting by checking for false conditions instead as follows:

```c
if (!IS_PAIR(a)) return;
if (!IS_BASE_TWO(a)) return;
if (a <= 100) return;

for (int i=0; i < a; ++i) {
  ...
}
```

### Switch vs Else If

If you are in a situation where a variable can assume many values that are known at compile time, then use switch. As a general rule, using switch is always preferrable as it makes your intents clearer and the code easier to read. Remember to always include the `default` case even if you assume that it will never be used (in which case it will be a valuable tool for covering potential errors).

And remember to always explicitly comment your fall throughs.

Try to keep your switch statement(s) similar to the following format:

```c
  switch (a) {
  case 0:
      ...
      break;
  case 1:
      ...
      break;
  case 2:
      ...
  /* fall through */
  case 3: case 4: case 5:
      ...
      break;
  default:
      ...
      break;
  }
```
## Conditional Compilation
Conditional compilations are discouraged in this project.  It makes code harder to read and test. 
Please only use the portable C/C++ features in the implementation.

## Importing

### Include guards in header files/files for importing

When making files for importing, add `#ifndef` and `#define` at the beginning of the file with a specified tag and `#endif` at the end disallows double declarations. The tag is normally the name of the file in uppercase, with dots and spaces represented as underscores.

For example, a file called `test.h` should have:

```c
#ifndef TEST_H
#define TEST_H

// the code goes here

#endif // TEST_H
```

Don't use `pragam once` which is not supported by all C/C++ compilers

## Miscellaneous
For subjects that are not covered here, we follow [Linux kernel coding style](https://www.kernel.org/doc/html/v4.10/process/coding-style.html#linux-kernel-coding-style)

## Commit and Merge
To avoid creating redundant merge commits, the following methods are recommanded:
* [How to avoid merge commits from git pull when pushing to remote](https://stackoverflow.com/questions/30052104/how-to-avoid-merge-commits-from-git-pull-when-pushing-to-remote)
