CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror 
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

CFILES = lista.c pruebas_alumno.c main.c testing.c
HFILES = lista.h pruebas_alumno.h testing.h
EXEC_S = main
PADRON = 102103


build: $(CFILES)
	$(CC) $(CFLAGS) -o $(EXEC_S) $(CFILES)

run: build
	./$(EXEC_S)

valgrind: build
	valgrind $(VFLAGS) ./$(EXEC_S)

gdb: build
	gdb $(GDBFLAGS) ./$(EXEC_S)

runtime: build
	time ./$(EXEC_S)

clean:
	rm -f *.o $(EXEC_S)

zip:
	zip $(PADRON).zip $(CFILES) $(HFILES)

entregar: build
	$(MAKE) run; test $$? -eq 0
	$(MAKE) valgrind; test $$? -eq 0
	$(MAKE) clean
	zip $(PADRON).zip $(CFILES) $(HFILES)
	@echo "Perfecto, no falla ni pierde memoria"
	@echo "El zip esta listo para entregar"

party:
	@curl http://parrot.live

batman:
	@echo "        _==/          |     |          \==_        "
	@echo "      /XX/            |\___/|            \XX\      "
	@echo "    /XXXX\            |XXXXX|            /XXXX\    "
	@echo "   |XXXXXX\_         _XXXXXXX_         _/XXXXXX|   "
	@echo "  XXXXXXXXXXXxxxxxxxXXXXXXXXXXXxxxxxxxXXXXXXXXXXX  "
	@echo " |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX| "
	@echo " XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX "
	@echo " |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX| "
	@echo "  XXXXXX/^^^^^\XXXXXXXXXXXXXXXXXXXXX/^^^^^\XXXXXX  "
	@echo "   |XXX|       \XXX/^^\XXXXX/^^\XXX/       |XXX|   "
	@echo "     \XX\       \X/    \XXX/    \X/       /XX/     "
	@echo "         \              \X/             /          "
	@echo "                        \/                         "

