programparts/learn_c
====
    C language programming examples.

##Overview:
    This repository includes functions for general purposes.

    Boyer Moore search method      ...string matching
    Gauss Jordan iteration method  ...solve simultaneous linear equations
    Power method                   ...search largest eigenvalue
    Least square method            ...get approximate curve
    Quick sort                     ...sorting algolithm
    etc.

##Description:
    this repository made up with 2 folders: lib and src folder.
    The formar one includes source files and header files for functions.
    The latter one has main functions to test functions or stand alone program.

##Usage:
    You can use these functions in your projects.

##Install:
    use make to build in folders under src.
    use gcc to build standalone programs under src.

##Feature:
    cording rules:

    1. Use data types defined in <stdint.h>.
       This is for portability.

       Some of data type has different length in different CPU.
       For example, 8 bit microchips like PIC16F877 has 8bit integer,
    thought my PC has 32bit integer.
    This rule prevents potential probrems caused by datasize, such as
    unexpected overflow.

    2. Give comment for all fuctions.
       This is for maintainability.

       It is necessary for proper use of these funcions.
    The comment must be the same in source file and header file.

    3. function arguments patterns should follow the rules below
       This is for usability.

    a. VO format naming is prefered.
    a. pointer for array must be xxx[], not xxx*
    b. the order of arguments is <data pointer> <solution poiter>
       <initial consitions> <other conditions>.
