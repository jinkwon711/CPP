#!/bin/bash

target="a.out"

n=-1
f="mission failure..."

#test0
let n++
read -r -d '' tc[n] << EOM
1
an
me
EOM
result[n]="an"

#test1
let n++
read -r -d '' tc[n] << EOM
1
an
em
EOM
result[n]="an"

#test2
let n++
read -r -d '' tc[n] << EOM
1
an
emz
EOM
result[n]=$f

#test3
let n++
read -r -d '' tc[n] << EOM
1
an
me me
EOM
result[n]="an an"

#test4
let n++
read -r -d '' tc[n] << EOM
1
an
em me
EOM
result[n]=$f

#test5
let n++
read -r -d '' tc[n] << EOM
2
an
kn
em me
EOM
result[n]=$f

#test6
let n++
read -r -d '' tc[n] << EOM
3
man
kna
nap
yem mek
EOM
result[n]="man nap"

#test7
let n++
read -r -d '' tc[n] << EOM
6
an
the
open
escape
lighter
umbrella
late me gufbtoom
EOM
result[n]="open an umbrella"

#test8
let n++
read -r -d '' tc[n] << EOM
6
an
the
open
escape
lighter
umbrella
xxxx yy zzzzzzzz
EOM
result[n]=$f

#test9
let n++
read -r -d '' tc[n] << EOM
6
an
the
open
escape
lighter
umbrella
late me m gufbtoom
EOM
result[n]=$f

#test10
let n++
read -r -d '' tc[n] << EOM
5
abc
bcd
cde
ooi
pkkj
yui uio iop
EOM
result[n]="abc bcd cde"

# test 11
let n++
read -r -d '' tc[n] << EOM
7
an
the
open
escape
lighter
asshole
umbrella
late me gufbtoom piiklot
EOM
result[n]="open an umbrella asshole"


for i in $(seq 0 $n)
do
    echo "${tc[$i]}" > input.txt
    ./"${target}" < input.txt > output.txt

    line=$(<output.txt)
    if [ "${result[$i]}" = "$line" ]
    then
        echo "pass"
    else
        echo "fail : test$i"
        echo "expected output : ${result[$i]}, your output : $line"
    fi
done
