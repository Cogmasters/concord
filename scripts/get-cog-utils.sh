#!/bin/bash
set -e
set -o pipefail

mypath=$(dirname $(readlink -f $0))
url="https://raw.githubusercontent.com/Cogmasters/cog-utils/master"

list="README.md
debug.h
jsmn.h
json-actor-boxed.c
json-actor-boxed.h
json-actor.c
json-actor.h
json-string.c
specs-gen.c
log.c
logconf.c
logconf.h
log.h
ntl.c
ntl.h
cog-utils.c
cog-utils.h
greatest.h
uthash.h
clock.h
"

mkdir -p $mypath/../cog-utils
pushd $mypath/../cog-utils
for i in $list; do
    echo "getting $i"
    echo "$url/$i"
    wget $url/$i -O $i
done
popd
