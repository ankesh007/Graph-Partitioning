#!/bin/bash

executable1="partition"
executable2="checker"

rm $executable1
rm $executable2

make part
make check

./$executable1 $1 $2 $3
./$executable2 $1 $2 $3