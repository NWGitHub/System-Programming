CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude
BIN_DIR = bin

all: $(BIN_DIR)/fork_exec_lab

solution: $(BIN_DIR)/fork_exec_lab_solution

check: all
	./scripts/check.sh

grade: all
	./scripts/grade.sh

$(BIN_DIR)/fork_exec_lab: src/fork_exec_lab.c include/fork_exec_lab.h
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/fork_exec_lab_solution: solutions/fork_exec_lab_solution.c include/fork_exec_lab.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(BIN_DIR)/fork_exec_lab $(BIN_DIR)/fork_exec_lab_solution

.PHONY: all solution check grade clean