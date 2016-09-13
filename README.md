# 4th
## Overview
A small Forth implementation.

## Build the executeable
Run `make` from the root of the repository

## Start the interpreter/compiler
From the root of the repository - `./4th`

## Load predefined composures and execute words
The `4th.conf` file is interpreted prior to the REPL running.  Any composures created in `4th.conf` are avaiable in the REL and any words outside of a composure are executed.

## Exit the interpreter/compiler
`bye`

## Builtin Words

**Stack Worlds**

`dot` **(a --)**
Remove the top of the data stack and display it.

`drop` **( a -- )**
Remove the top of the data stack.

`dup` **( a -- a a )**
Duplicate the data stack top.

`over` **( a b -- a b a )**
Duplicate the top-1 (second element) of the data stack and put it on the top.

`swap` **( a b -- b a )**
Duplicate the top of the data stack.

`rot` **( a b c -- b c a )**
Rotate the top 3 elements of the data stack to the left.

**Output Words**

`.s` **( -- )**
Displays the contents of the data stack.

`read` **( -- a)**
Reads a word from stdin and puts it on the data stack.

`emit` **(char -- )**
Displays the character

**Arithemtic Words**

`+` **( n1 n2 -- n3 )**
Adds n1+n2

`-` **( n1 n2 -- n3 )**
Subtracts n1-n2

`*` **( n1 n2 -- n3 )**
Multiply n1\*N2

`mod` **( n1 n2 -- n3 )**
Remainder of n1/n2

**Memory Words**

`variable` **( -- ) name**
Defines a variable

`!` **( n adr  -- )**
Stores a number at adr

`@` **( adr  --  n )**
Fetches a number from adr

**Composing Words**

`:` **( -- sys )    name**
Starts the compilation of a new colon definition

`;` **( -- )**
Finishes the compilation of a colon definition

**Return Stack Words**

`>r` **( n -- )**
Moves a number to the return stack

`r>` **( -- n )**
Moves a number from the return stack to the data stack

`r@`  **( -- n )**
Copies the top of the return stack to the data stack

**Lifecycle Management Words**

`execute`  **( acf -- )**
Executes the word whose compilation address is on the stack

`compile`  **( -- )**
Compiles next word at run time

`run` **( adr -- )**
Compiles and executes the string pointed to by the address

