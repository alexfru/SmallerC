# Smaller C Preprocessor

## Table of contents

[What is Smaller C Preprocessor?](#what-is-smaller-c-preprocessor)

[What features does Smaller C Preprocessor have?](#what-features-does-smaller-c-preprocessor-have)

[How do I compile Smaller C Preprocessor?](#how-do-i-compile-smaller-c-preprocessor)

## What is Smaller C Preprocessor?

Smaller C preprocessor (smlrpp) is a version of ucpp adapted for use with
Smaller C (ucpp 1.3.2 was used as the basis).

## What features does Smaller C Preprocessor have?

smlrpp (ucpp) is a C preprocessor compliant to ISO-C99. For more information
please see the language standard and/or the ucpp documentation.

## How do I compile Smaller C Preprocessor?

Something like this:

> gcc -Wall -O2 -o smlrpp -DSTAND_ALONE -DUCPP_CONFIG arith.c assert.c cpp.c eval.c lexer.c macro.c mem.c nhash.c

or

> smlrcc -Wall -win -o smlrpp.exe -DSTAND_ALONE -DUCPP_CONFIG arith.c assert.c cpp.c eval.c lexer.c macro.c mem.c nhash.c

