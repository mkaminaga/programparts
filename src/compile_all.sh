#!/bin/sh

for i in `ls *.c`;\
do\
    gcc ${i} -o `echo ${i} | sed 's/\.c/\.out/g'`\
    && ls `echo ${i} | sed 's/\.c/\.out/g'`;\
done
