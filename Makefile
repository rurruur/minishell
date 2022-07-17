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
				src/utils/_display.c \
				src/utils/error.c \
				src/utils/signal.c \
				src/utils/utils_env.c \
				src/utils/utils_str.c \
				src/parser/check.c \
				src/parser/token01.c \
				src/parser/token02.c \
				src/parser/token03.c \
				src/lst/lst01.c \
				src/lst/lst02.c \
				src/lst/lst_free.c \
				src/executor/executor.c \
				src/executor/cmd_utils.c \
				src/executor/redirection.c \
				src/built_in/builtin.c \
				src/built_in/_cd.c \
				src/built_in/_echo.c \
				src/built_in/_env.c \
				src/built_in/_exit.c \
				src/built_in/_pwd.c \
				src/built_in/_unset.c \
				src/built_in/_export.c
				
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