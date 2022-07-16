NAME		=	minishell

RED			=	\033[0;31m
GRN			= 	\033[0;32m
YLW			=	\033[0;33m
BLU			= 	\033[0;36m
DFT			= 	\033[0;37m

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
RLFLAGS		=	-L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include -lreadline
#RLFLAGS		=	-L /Users/jrim/.brew/opt/readline/lib -I /Users/jrim/.brew/opt/readline/include -lreadline
AR			=	ar rcs
RM			=	rm -f

LIB_DIR		=	./libft/
LIB_NAME	=	libft.a
LIBS		=	$(addprefix $(LIB_DIR), $(LIB_NAME))

SRC			=	src/minishell.c \
				src/parser/_signal.c \
				src/parser/_check.c \
				src/parser/_token01.c \
				src/parser/_token02.c \
				src/parser/_token03.c \
				src/parser/_env.c \
				src/parser/_lst01.c \
				src/parser/_lst02.c \
				src/parser/_free.c \
				src/parser/_error.c \
				src/parser/_utils.c \
				src/parser/__display.c \
				src/executor/executor.c \
				src/executor/cmd_utils.c \
				src/executor/redirection.c \
				src/built_in/built_in.c \
				src/built_in/cd.c \
				src/built_in/echo.c \
				src/built_in/env.c \
				src/built_in/exit.c \
				src/built_in/pwd.c \
				src/built_in/unset.c
				
OBJ			=	$(SRC:.c=.o)

all : $(NAME) 

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I /opt/homebrew/opt/readline/include
#/Users/jrim/.brew/opt/readline/include
#/opt/homebrew/opt/readline/include

$(NAME) : $(OBJ)
	@$(MAKE) -C $(LIB_DIR)
	@$(CC) -o $(NAME) $(OBJ) $(LIBS) $(RLFLAGS)
	@echo "$(NAME) is $(GRN)ready$(DFT)"

clean :
	@$(MAKE) -C $(LIB_DIR) clean
	@$(RM) $(OBJ)
	@echo "$(RED)cleaned$(DFT)"

fclean : 
	@$(MAKE) clean
	@$(MAKE) -C $(LIB_DIR) fclean
	@$(RM) $(NAME)
	@echo "$(RED)fcleaned$(DFT)"

re : 
	@$(MAKE) fclean
	@$(MAKE) all

PHONY	: all clean fclean re