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
				src/_signal.c \
				src/_check.c \
				src/_token01.c \
				src/_token02.c \
				src/_token03.c \
				src/_lst01.c \
				src/_lst02.c \
				src/_utils.c \
				src/__display.c 
				
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