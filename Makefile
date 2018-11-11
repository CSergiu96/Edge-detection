NAME = sobel

CC = @gcc

SRC = 	main.c 			\
		sobel.c 		\
		file.c

SRCS = $(addprefix $(SRCD),$(SRC))
OBJS = $(addprefix $(OBJD),$(SRC:.c=.o))

INCD = inc/
SRCD = src/
OBJD = tmp/
LIBD = lib/
BIND = bin/

EXE = $(BIND)$(NAME)
ARC = $(LIBD)libsobel.a

FLAGS = -std=c99  	\
		-g  		\
		-lm 		\
		-Wall 		\
		-Werror 	\
		-Wextra 	

$(OBJD)%.o:$(SRCD)%.c
	@echo -e "\e[32mCompiling $<"
	$(CC) $(FLAGS) -I $(INCD) -o $@ -c $<

$(EXE):$(OBJS)
	@echo -e "\e[1m\e[36mLinking objects...\e[0m"
	$(CC) $(OBJS) -o $(EXE)
	@echo -e "\e[1m\e[36mLibrary created in : $(LIBD) \e[0m" 
	@ar rcs $(ARC) $(OBJS)

all: dirs $(EXE) 
	 @echo -e "\e[1m\e[36mExecutable created in : $(BIND) \e[0m" 

dirs:
	@echo -e "\e[1m\e[36mPreparing directories...\e[0m"
	@mkdir -p $(OBJD)
	@mkdir -p $(LIBD)
	@mkdir -p $(BIND)

clean:
	@rm -rf $(OBJD) $(LIBD) $(BIND)

re: clean all