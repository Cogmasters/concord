#!/bin/bash
set -e
set -o pipefail

mypath=$(dirname $(readlink -f $0))
url="https://raw.githubusercontent.com/cee-studio/cee-utils/master"

list="README.md
debug.h
jsmn.h
json-actor-boxed.c
json-actor-boxed.h
json-actor.c
json-actor.h
json-parser.c
json-string.c
json-struct.c
log.c
logconf.c
logconf.h
log.h
ntl.c
ntl.h
cee-utils.c
cee-utils.h
greatest.h
uthash.h
cee-data-sizes.h
clock.h
"

mkdir -p $mypath/../cee-utils
pushd $mypath/../cee-utils
for i in $list; do
    echo "getting $i"
    echo "$url/$i"
    wget $url/$i -O $i
done
popd
