# Easy Commit

This section explains how to submit commits and pull requests the easy
   and cleanest way without causing any merge conflicts.

### Setup
1. fork this repo to your personal account. Please DO NOT submit any commit to
this fork from your git command line

2. run the following command
```
git clone https://github.com/cee-studio/orca.git
cd orca
cp bots/bot.config .cee-contributor
```

3. add replace "YOUR-GITHUB-USERNAME" and "YOUR-PERSONAL-ACCESS-TOKEN"
   with your github username and your personal access token (which can
   be obtained thru this
   [link](https://docs.github.com/en/github/authenticating-to-github/creating-a-personal-access-token))

5. run
```
make all test
```


### Usage
Run the following command that will automatically do the following
1. sync up your personal fork
2. create a branch in your fork
3. submit a commit to the branch
4. create a pull request

```
./test/test-git2.exe -m "you commit comments"  files
```
