# CODING GUIDELINES

In order to keep the code concise and easy to read, there are a few rules to follow. Feel free to use this coding guidelines outside of this project. (This is still a work in progress)

## Line Width

Try to use lines that are at most 80 characters long. This is an amount of text that is easy to fit in most monitors. Don't be afraid to break a long function into many lines.

## Indentation

Overall we will stick with two space identation. But if readability becomes an issue, your better judgment should tell you wether you need more or less identation. For compactness and readability this is the preferred identation style:

```c
for (int i=0; i < n; ++i) {
  if (something) {
    //do something
  }
  else if (something_else) {
    //do something else
  } 
  else {
    //this is it
  }
}
```
Use your surrounding code as a guide.

## Conditional Statements

### Nesting

To keep the code away from deep nesting one should always check for false conditions.

Instead of checking only for true, like so:

```c
if (IS_PAIR(a)) {
  if (IS_BASE_TWO(a)) {
    if (a > 100) {
      for (int i=0; i < a; ++i) {
        //do something
      }
    }
  }
}
```

We can achieve a code with better flow and minimal nesting by checking for false conditions, as follows:

```c
if (!IS_PAIR(a)) return;
if (!IS_BASE_TWO(a)) return;
if (a <= 100) return;

for (int i=0; i < a; ++i) {
  //do something
}
```

### Switch vs Else If

If you are in a situation where a variable can assume many values that are known at compile time, then use switch. As a general rule, using switch is always preferrable as it makes your intents clearer and the code easier to read. Remember to always include the `default` case even if you assume that it will never be used (in which case it will be a valuable tool for covering potential errors).

And remember to always explicitly comment your fall throughs.

Try to keep your switch statement similar to the following format:

```c
  switch (a) {
  case 0:
      //do something
      break;
  case 1:
      //do another thing
      break;
  case 2:
      //do something else
  /* fall through */
  case 3:
      //the other thing
      break;
  default:
      ERROR("This shouldn't happen."); //leave this statement out if you are planning on using default
      break;
  }
```

## Importing

### Include guards in header files/files for importing

When making files for importing, adding `#ifndef` and `#define` in the beginning of the file with a specified tag and `#endif` at the end disallows double declarations. The tag is normally the name of the file in uppercase, with dots and spaces represented as underscores.

For example, a file called `test.h` should have:

```c
#ifndef TEST_H
#define TEST_H

//put code here

#endif // TEST_H
```


## Commit and Merge
To avoid creating redundant merge commits the following methods are recommanded:
https://stackoverflow.com/questions/30052104/how-to-avoid-merge-commits-from-git-pull-when-pushing-to-remote
