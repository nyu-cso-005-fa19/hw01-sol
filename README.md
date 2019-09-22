# Homework 1 (90 Points)

The deadline for Homework 1 is Monday, October 7, 8pm. The late
submission deadline is Monday, October 14, 8pm.

## Getting the code template

Before you perform the next steps, you first need to create your own
private copy of this git repository. To do so, click on the link
provided in the announcement of this homework assignment on
Piazza. After clicking on the link, you will receive an email from
GitHub, when your copy of the repository is ready. It will be
available at
`https://github.com/nyu-cso-005-fa19/hw01-<YOUR-GITHUB-USERNAME>`.  
Note that this may take a few minutes.

* Open a browser at `https://github.com/nyu-cso-005-fa19/hw01-<YOUR-GITHUB-USERNAME>` with your Github username inserted at the appropriate place in the URL.
* Choose a place on your computer for your homework assignments to reside and open a terminal to that location.
* Execute the following git command: <br/>
  ```git clone https://github.com/nyu-sco-005-fa19/hw01-<YOUR-GITHUB-USERNAME>.git```<br/>
  ```cd hw01```

Put your answers to parts 7 and 8 into the text file `solution.md`.

## Submitting your solution

Once you have completed the assignment, you can submit your solution
by pushing the modified code template to GitHub. This can be done by
opening a terminal in the project's root directory and executing the
following commands in the :

```bash
git add .
git commit -m "solution"
git push
```

You can replace "solution" by a more meaningful commit message.

Refresh your browser window pointing at
```
https://github.com/nyu-cso-005-fa19/hw01-<YOUR-GITHUB-USERNAME>/
```
and double-check that your solution has been uploaded correctly.

You can resubmit an updated solution anytime by reexecuting the above
git commands. Though, please remember the rules for submitting
solutions after the homework deadline has passed.


## Part 1-6: C Programming (80 Points)

Complete the programming tasks specified in the files
`src/part[1-6].c`.

* Test each part individually by executing
  
  ```bash
  make build/part1
  build/part1
  ```
  and similarly for the other parts.
  
* You can also test all parts by executing `./grade` (this requires a
  working Python installation).

We encourage you to write your own supplementary testing code.

## Part 7: Local variables and Stack (4 Points)

Consider the following simple C program (see also the file `src/part7.c`):

```c
#include <stdio.h>

void foo() {
  int i;
  printf("%d ", i++);
}

int main() {
  int j = 1;
  while (j <= 10) {
    foo();
    j = j + 1;
  }
}
```

This program is erroneous: the local variable `i` in `foo` is not
initialized before it is used, which according to the C standard,
causes the program to have undefined behavior. Nevertheless, for many
C compilers and architectures, this program will consistently print
the sequence `0 1 2 3 4 5 6 7 8 9` when it is executed. 

Use your knowledge about how local variables such as `i` in `foo` are
stored on the stack to explain this behavior.

## Part 8: Dynamic Memory Allocation (6 Points)

Consider the following C program (see also `src/part8.c`)

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct list_node Node;

struct list_node {
  int data;
  Node* next;
};

void foo(Node* n) {
  free(n->next);
}

Node* create(int x, Node* n) {
  Node* n1 = malloc(sizeof(Node));
  n1->data = x;
  n1->next = n;
  
  return n1;
}

int main() {
  Node* n1 = create(1, NULL);
  Node* n2 = create(2, n1);
  
  foo(n2);
  Node* n3 = create(3, NULL);
  
  n1->data = 42;
  
  printf("%d\n", n3->data);
  free(n2);
  free(n3);
 
  return 0;
}
```

1. This program contains a problem related to dynamic memory
   allocation that will likely make the program crash. However, the
   program may just as likely not crash and instead consistently print
   the value 42. Explain what is going on.
   
1. What happens if the two lines

   ```c++
   foo(n2);
   Node* n3 = create(3, NULL);
   ```
   
   are swapped?
