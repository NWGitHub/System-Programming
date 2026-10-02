# System Programming Lab: fork() and Program Address Space

## 1. Learning Objectives
By the end of this lab, you should be able to:
- create a child process with `fork()`
- explain what parts of program memory are copied on `fork()`
- wait for a child process with `waitpid()`
- report child exit status correctly
- handle system call failures safely

## 2. Repository Layout
- `src/`: source files for this lab
- `include/`: headers and function prototypes
- `scripts/`: helper scripts for grading or local checks
- `tests/`: notes about the visible checks
- `samples/`: sample command arguments

## 3. What You Need To Implement
Complete the TODO sections in `src/fork_exec_lab.c`.

Required behavior:
1. create exactly one child process with `fork()`
2. initialize values as:
	- global: `100`
	- heap: `200`
	- stack: `300`
3. in the child, add `7` to each value and print the child snapshot
4. child exits with status `(global + heap + stack) % 256`
5. in the parent, wait for the specific child with `waitpid()`
6. print child exit status and parent snapshot
7. print `parent: address-space=isolated` when parent values remain unchanged
5. return a non-zero exit code on failure

Rules:
- do not change the function signatures in `include/fork_exec_lab.h`
- keep the output labels `parent:` and `child:`
- check every system call return value

## 4. Build
```bash
make
```

## 5. Run
```bash
./bin/fork_exec_lab
```

Expected successful run shape:
```text
parent: start g=100 h=200 s=300
child: g=107 h=207 s=307 sum=621
parent: child-exit=109
parent: g=100 h=200 s=300
parent: address-space=isolated
```

The parent output after `waitpid()` must appear only after the child exits.

## 6. Test
```bash
./scripts/test.sh
```

## 7. Deadline
- due date: set by instructor
- late policy: set by instructor

## 8. Grading Hooks
For local grading and future Classroom automation:

```bash
make check
make grade
```

## 9. Grading Rubric
- correctness: 50%
- process control and exit handling: 20%
- error handling: 15%
- build hygiene and warnings: 15%

## 10. Submission Checklist
- builds with no warnings
- visible checks pass
- no extra debug output remains
- all TODOs are replaced with working code

## 11. Academic Integrity
- write your own solution
- do not copy code from another student
- discussion of concepts is allowed, sharing code is not

## 12. Instructor Materials
- instructor solution source: `solutions/fork_exec_lab_solution.c`
- keep solution files outside the student-facing template repository when publishing to Classroom