# Contributing to the Concord project

This document intention is to provide guidelines on how to best contribute to the Concord project.

## Learning Concord

### Join the Community

Skip over to our [Discord Server](https://discord.gg/Y7Xa6MA82v), we will be more than happy to assist you!

### License and copyright

When contributing with code, you agree to put your changes and new code under the same license Concord is already using unless stated and agreed otherwise.

When changing existing source code, you do not alter the copyright of the original file(s). The copyright will still be owned by the original creator(s) or those who have been assigned copyright by the original author(s).

### What To Read

Source code, the [project outline](PROJECT_OUTLINE.md) and [internals](INTERNALS.md).

## Write a good patch

### Code Style

When writing C code, follow the [coding guidelines](CODING_GUIDELINES.md) already established in the project. Consistency makes code easier to read, and mistakes less likely to happen.

### Non-clobbering All Over

When you write new functionality or fix bugs, it is important that you don't fiddle all over the source files and functions. Remember that it is likely that other people have done changes in the same source files as you have and possibly even in the same functions. If you bring completely new functionality, try writing it in a new source file. If you fix bugs, try to fix one bug at a time and send them as separate patches.

### Patch Against Recent Source 

Please try to get the latest available sources to make your patches against. It makes the lives of the developers so much easier.

### Documentation

Writing docs is dead boring and one of the big problems with many open source projects. But someone's gotta do it! Please get yourself familiarized with [Doxygen syntax](https://www.doxygen.nl/manual/docblocks.html) and use the surrounding code as a guide when documenting your patch. Once the patch is approved a automated [workflow](.github/workflows/gh_pages.yml) will automatically updated our documentation with your changes. If you wish to patch how the documentation is generated and rendered, please head to [concord-docs](https://github.com/Cogmasters/concord-docs) and submit your changes there.

### Test Cases

Thorougly test your patch before sending a PR for approval. If you are implementing a missing feature to one of our wrapped APIs, you can write or update one of the example bots from `examples/` folder, alternatively, you can write a test to the `test/` folder.

## Sharing Your Changes

### Semantic Commit Messages

For organization purposes we standardize how our commits are staged.
This section is copied from [link](https://gist.github.com/joshbuchea/6f47e86d2510bce28f8e7f42ae84c716) 
to save you a click.

See how a minor change to your commit message style can make you a better programmer.

Format: `<type>(<scope>): <subject>`

`<scope>` is optional

#### Example

```
feat: add hat wobble
^--^  ^------------^
|     |
|     +-> Summary in present tense.
|
+-------> Type: chore, docs, feat, fix, refactor, style, or test.
```

More Examples:

- `feat`: (new feature for the user, not a new feature for build script)
- `fix`: (bug fix for the user, not a fix to a build script)
- `docs`: (changes to the documentation)
- `style`: (formatting, missing semi colons, etc; no production code change)
- `refactor`: (refactoring production code, eg. renaming a variable)
- `test`: (adding missing tests, refactoring tests; no production code change)
- `chore`: (updating grunt tasks etc; no production code change)
- `wip`: (work in progress)

References:

- https://www.conventionalcommits.org/
- https://seesparkbox.com/foundry/semantic_commit_messages
- http://karma-runner.github.io/1.0/dev/git-commit-msg.html
