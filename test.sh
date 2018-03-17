#!/bin/bash

executable1="partition"
executable2="checker"

make $executable1
make $executable2

./$executable1 $1 $2 $3
./$executable2 $1 $2 $3