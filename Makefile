NAME		=	minishell

RED			=	\033[0;31m
GRN			= 	\033[0;32m
YLW			=	\033[0;33m
BLU			= 	\033[0;36m
DFT			= 	\033[0;37m

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
RLFLAGS		=	-L /Users/jrim/.brew/opt/readline/lib -I /Users/jrim/.brew/opt/readline/include -lreadline
AR			=	ar rcs
RM			=	rm -f

LIB_DIR		=	./libft/
LIB_NAME	=	libft.a
LIBS		=	$(addprefix $(LIB_DIR), $(LIB_NAME))

SRC			=	src/minishell.c \
				src/utils/_display.c \
				src/utils/env01.c \
				src/utils/env02.c \
				src/utils/error.c \
				src/utils/signal.c \
				src/utils/string.c \
				src/parser/check.c \
				src/parser/token01.c \
				src/parser/token02.c \
				src/parser/token03.c \
				src/lst/strlst.c \
				src/lst/envlst.c \
				src/lst/toklst.c \
				src/executor/executor.c \
				src/executor/cmd_utils.c \
				src/executor/redirection.c \
				src/executor/check_files.c \
				src/executor/heredoc.c \
				src/executor/wait.c \
				src/executor/error.c \
				src/executor/double_join.c \
				src/builtin/builtin.c \
				src/builtin/_cd.c \
				src/builtin/_echo.c \
				src/builtin/_env.c \
				src/builtin/_exit.c \
				src/builtin/_pwd.c \
				src/builtin/_unset.c \
				src/builtin/_export.c
				
OBJ			=	$(SRC:.c=.o)

all : $(NAME) 

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I /Users/jrim/.brew/opt/readline/include

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