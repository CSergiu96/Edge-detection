EXE = soble

SRCS = main.c sobel.c file_operations.c
OBJS = $(SRCS:.c=.o)

INCDIR=./inc/
SRCDIR=./src/
OBJDIR=./bin/

ARQUIVE = libsobel.a

FLAGS = 
		-std=c99 
		-g 
		-lm
		-Wall
		-Werror
		-Wextra

all: $(OBJS) archive
	gcc $(OBJS) -o $(EXE) $(FLAGS)

.c.o:
	gcc -c $< -o $@ $(FLAGS)

archive:
	ar rcs $(ARQUIVE) $(OBJS)

clean:
	rm $(OBJS) $(ARQUIVE) $(EXE)6