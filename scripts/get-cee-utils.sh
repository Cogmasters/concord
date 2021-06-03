#!/bin/bash
mypath=$(dirname $(readlink -f $0))
url="https://raw.githubusercontent.com/cee-studio/cee-utils/master"

wget $url/scripts/get-cee-utils.sh -O ${mypath}/get-cee-utils.sh
chmod +x ${mypath}/get-cee-utils.sh

list="debug.h
cee-sqlite3.h
cee-sqlite3.c
jsmn.h
json-actor-boxed.c
json-actor-boxed.h
json-actor.c
json-actor.h
json-parser.c
json-printf.c
json-scanf.c
json-scanf.h
json-string.c
json-struct.c
log.c
logconf.c
logconf.h
log.h
ntl.c
ntl.h
orka-utils.c
orka-utils.h
utarray.h
url-encode.h
hmac.h
hmac.c
teeny-sha1.c
cee-data-sizes.h
sha.h
sha1.c
utf8.h
uthash.h
utlist.h
utringbuffer.h
utstack.h
utstring.h"

mkdir -p $mypath/../cee-utils
pushd $mypath/../cee-utils
for i in $list; do
    echo "getting $i"
    echo "$url/$i"
    wget $url/$i -O $i
done
popd
