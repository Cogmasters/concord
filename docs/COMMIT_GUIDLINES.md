# Easy Commit

This section explains how to submit changes and pull requests the easy
   and cleanest way without causing any merge conflicts.

## Setup  .cee-contributor
1. fork this repo to your personal account. Please DO NOT submit any changes to
this fork from your git command line

2. run the following command
```
git clone https://github.com/cee-studio/orca.git
cd orca
cp bots/bot.config .cee-contributor
```
It is important that you clone from this repo, NOT from your fork.


3. add replace "YOUR-GITHUB-USERNAME" and "YOUR-PERSONAL-ACCESS-TOKEN"
   with your github username and your personal access token (which can
   be obtained thru this
   [link](https://docs.github.com/en/github/authenticating-to-github/creating-a-personal-access-token))

## Build the test-git2.exe
1. run
```
cd orca
make all test
```
Copy test-git2.exe to your bin folder and make that folder searchable in PATH


## Usage
Run the following command that will automatically do the following
1. sync up your personal fork
2. create a branch in your fork
3. submit a commit to the branch
4. create a pull request

Assume your changes are in the orca folder, you can run the following commands:
```
./test/test-git2.exe -m "you commit comments"  files
```
