# truth-tables

A program to generate truth tables from boolean expressions.
Homework assignment for the course of Computer Architecture and Organization (EIF205) II Semester of 2023, at Universidad Nacional de Costa Rica (UNA).

## table of contents
- [truth-tables](#truth-tables)
  - [table of contents](#table-of-contents)
  - [Output example](#output-example)
  - [Bugs and Issues](#bugs-and-issues)
  - [Representation of the binary tree](#representation-of-the-binary-tree)
    - [How I thought it](#how-i-thought-it)
    - [Expected subtree](#expected-subtree)
    - [How it's being generated](#how-its-being-generated)
    - [Actual subtree](#actual-subtree)
  - [How to run](#how-to-run)
    - [Building the project](#building-the-project)
    - [Compiling the project](#compiling-the-project)
  - [Tools needed](#tools-needed)

## Output example
```
Tree:
xy' -> x 0 y 0 ' 0 
x'y -> x 0 y 0 ' 0 
Variables: xy
+-------------------------------------------------+
| x       | y       | xy'     | x'y     | xy'+x'y |
+-------------------------------------------------+
| 0       | 0       | 0       | 0       | 0       |
| 0       | 1       | 0       | 0       | 0       |
| 1       | 0       | 0       | 0       | 0       |
| 1       | 1       | 0       | 0       | 0       |
+-------------------------------------------------+
```

Where the expression is printed as a binary tree, in postfix notation.

Overall, the program is not working correctly.

## Bugs and Issues
1. It needs a function to parse the expression into [Reverse Polish Notation (RPN)](https://en.wikipedia.org/wiki/Reverse_Polish_notation)

For example:
```
xy'+ x'y to xy' * x'y * +
```

2. The binary tree used for evaluating the expression is not 
setting the is_negated flag correctly, for the negated variables.
This is causing the program to not evaluate the expression correctly.

## Representation of the binary tree
### How I thought it
Consider the expression `xy'`, it's represented as:

`xy' -> x 0 y 1 * 0`

The first is the left child node `(x 0)`, the second is the right child `(y 1)`, and the third is the parent node `(* 0)`.

### Expected subtree
The tree must be:

```
    *
   / \
  x   y' -> The ' is set in node field as is_negated: bool = true,
            but it's not setting the is_negated flag correctly.
```

### How it's being generated
Consider the same expression `xy'`, it's wrongly represented in the actual program as:

`xy' -> x 0 y 0 ' 0 `

The first is the left child node `(x 0)`, the second is the right child `(y 0)`, and the third is the parent node `(' 0)`. In this case, the parent node is the negation, that's a bug. It should be `(* 0)`, because the expression is `x * y'`.

### Actual subtree
Actually being generated as:

```
    '
   / \
  x   y
```




## How to run

### Building the project
```bash
cmake -S . -B build
```

### Compiling the project
```bash
./build/truth-tables
```

## Tools needed
- CMake (version 3.5)
- C++ Compiler (e.g., GCC, Clang, MSVC)