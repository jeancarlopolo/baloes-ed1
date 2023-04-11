# Name of the project
objects = ted

# .c files
C_SOURCE=$(wildcard **/*.c) $(wildcard *.c)

# .h files
H_SOURCE=$(wildcard **/*.h) $(wildcard *.h)

# Object files
OBJ=$(C_SOURCE:.c=.o)

# Libraries
LIBS= -lm

# Compiler
CC=gcc

# Aluno: Jean Carlo Polo
ALUNO = jeancp

# Flags for compiler
CC_FLAGS=-ggdb -O0 -std=c99 -fstack-protector-all -Werror=implicit-function-declaration

LINKER_FLAGS = -O0

#
# Compilation and linking
#
all: $(objects)

$(objects): $(OBJ)
	$(CC) -o $(objects) $(LINKER_FLAGS) $(OBJ) $(LIBS)

%.o: %.c 
	$(CC) -c $(CC_FLAGS) $< -o $@ 

main.o: main.c $(H_SOURCE)
	$(CC) -o $@ $< -c $(CC_FLAGS)

clean:
	rm -rf **/*.o $(objects) *~
	rm -rf *.o $(objects) *~

pack: $(objects)
	rm -f ../$(ALUNO).zip
	echo $(ALUNO)
	date >> .entrega
	cd ..; zip $(ALUNO).zip -r LEIA-ME.txt src/ -x "*.o" "*.geo" "*.qry" "src/ted"

.PRECIOUS: %.o