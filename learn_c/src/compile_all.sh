#!/bin/sh

for i in `ls *.c`;\
do\
    gcc ${i} -o `echo ${i} | sed 's/\.c/\.exe/g'`\
    && ls `echo ${i} | sed 's/\.c/\.out/g'`;\
done
