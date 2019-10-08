## Part 7

Each call to `foo` in the loop of `main` will use the exact same
memory addresses to store `foo`'s local variables on the stack. In
particular, the same memory cell will be used to store `i` in all
calls to `foo`. Assuming that the value of that memory cell is `0` the
first time `foo` is called, then for *n > 1*, the value of `i` at the
start of the *n*-th call to `foo` will be the value of `i` at the end
of the *n-1*-th call, which is *n-1*.

Note that there are many possible reasons why the program may print a
different sequence of values. First, the initial value stored in `i`
does not have to be 0, but can be any other value. One can
e.g. simulate this behavior with a slightly modified version of the
code:
   
```c
void foo() {
  int i;
  printf("%d ", i++);
}

void bar() {
  int i = 5;
}

int main() {
  int j = 1;
  bar();
  while (j <= 10) {
    foo();
    j = j + 1;
  }
}
```
   
In this case, the program will likely print the sequence 
`5 6 7 8 9 10 11 12 13 14`.

Another reason, why the program may print a different sequence is
due to compiler optimizations. Note that the incremented value of
`i` is never read in `foo`. So the compiler is allowed to eliminate
the increment operation from the code. For instance, compiling the
code with GCC and optimization level `-O2` yields an executable that
prints the sequence `0 0 0 0 0 0 0 0 0 0` on a Linux machine.

## Part 8

1. The problem with the code is that the call `foo(n2)` frees
   the `Node` value on the heap pointed to by `n2->next`. This struct
   value is also pointed to by `n1`. Hence, after the call to `foo`,
   `n1` is a dangling pointer. The assignment `n1->data = 42`
   dereferences this dangling pointer, which is unsafe and means that
   the program has undefined behavior according to the semantics of
   C. In particular, the program may crash at this point because
   it tries to access an invalid pointer.
   
   Now why does the program likely proceed without crashing and print
   the value 42? The reason for this is that the call `create(3,
   NULL)` allocates a new `Node` value on the heap. The underlying
   implementation of the memory allocation mechanism will likely reuse
   the memory that has just been freed when deallocating
   `n1->data`. Thus, after `n3` has been initialized, both `n3` and
   `n2` will point to the same memory address. In this case, after the
   call to `create`, `n1` will again point to valid memory and the
   assignment `n1->data = 42` will proceed without problems. Since
   `n1` and `n3` are aliased, the update of the `data` field of the
   `Node` value through `n1` will also be observable through `n3`
   which is why `n3->data` will be `42` when the print statement
   executes.
   
   Note that this behavior is by no means guaranteed. It depends on
   the specific implementation details of the memory allocator as well
   as other extraneous circumstances that are outside of the control
   of the programmer. For instance, if `main` were to be executed
   concurrently with other threads, then an allocation request of
   another thread may be interleaved between the calls to `foo` and
   `create` causing `create` to use fresh memory rather than reuse the
   memory of `n2->next` that was just freed.

2. Since in this case the call to `create` happens before the deletion
   of `n2->next`, `n2->next` is still allocated when the new `Node`
   value is allocated inside of `create`. Thus, the memory used for
   this allocation is guaranteed to be different from the one pointed
   to by `n2->next`. Hence, after the calls to `create` and `foo`,
   `n1` and `n3` will definitely not be aliased. It follows that if
   the assignment `n1->data` proceeds without crashing, then
   `n3->data` will likely still hold the initial value `3` assigned in
   `create`. Thus, the program will likely print `3` in this case. I
   say "likely" here because `n1` is still dangling after `foo`
   returns. Hence, the behavior of the assignment to `n1->data` is
   still undefined and could, at least in theory, change the value of
   `n3->data` arbitrarily (among other things).
