#!/bin/sh

while [ $# -ne 0 ]; do
	case $1 in
		"--unstage")
			unstage="Y"
			;;
		"--help")
			echo "Usage: $0 [--unstage]"
			exit 1
			;;
		*)
			echo "Usage: $0 [--unstage]"
			exit 1
			;;
	esac
	shift
done

for i in $(git status -s | awk '{ print $2'}); do
  diffuse $i
  if [ -z "unstage" ]; then
    read -p "STAGE   '$i' ? y/[n]:" ans
    if [ "$ans" = "y" ] || [ "$ans" = "Y" ]; then
      echo "git add $i"
      git add $i
    fi
  else
    read -p "UNSTAGE   '$i' ? y/[n]:" ans
    if [ "$ans" = "y" ] || [ "$ans" = "Y" ]; then
      echo "git reset HEAD $i"
      git reset HEAD $i
    fi
  fi
done
