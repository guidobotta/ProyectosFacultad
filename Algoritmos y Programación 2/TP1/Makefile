CC = gcc
CFLAGS = -g -Wall -Wconversion -Wno-sign-conversion -Werror 
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

CFILES_DC = dc.c pila.c strutil.c
HFILES_DC = pila.h strutil.h
EXEC_S_DC = dc

CFILES_GREP = grep.c cola.c
HFILES_GREP = cola.h
EXEC_S_GREP = grep

build_dc: $(CFILES_DC)
	$(CC) $(CFLAGS) -o $(EXEC_S_DC) $(CFILES_DC)

run_dc: build_dc
	./$(EXEC_S_DC)

valgrind_dc: build_dc
	valgrind $(VFLAGS) ./$(EXEC_S_DC)

gdb_dc: build_dc
	gdb $(GDBFLAGS) ./$(EXEC_S_DC)

build_grep: $(CFILES_GREP)
	$(CC) $(CFLAGS) -o $(EXEC_S_GREP) $(CFILES_GREP)

run_grep: build_grep
	./$(EXEC_S_GREP)

valgrind_grep: build_grep
	valgrind $(VFLAGS) ./$(EXEC_S_GREP)

gdb_grep: build_grep
	gdb $(GDBFLAGS) ./$(EXEC_S_GREP)