NAME		=	minishell

RED			=	\033[0;31m
GRN			= 	\033[0;32m
YLW			=	\033[0;33m
BLU			= 	\033[0;36m
DFT			= 	\033[0;37m

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
RLFLAGS		=	-L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include -lreadline
AR			=	ar rcs
RM			=	rm -f

LIB_DIR		=	./libft/
LIB_NAME	=	libft.a
LIBS		=	$(addprefix $(LIB_DIR), $(LIB_NAME))
GNL_DIR		=	./gnl/
GNL_NAME	=	gnl.a
GNLS		=	$(addprefix $(GNL_DIR), $(GNL_NAME))

SRC			=	src/
				
OBJ			=	$(SRC:.c=.o)

all : $(NAME) 

%.o : %.c
	@$(CC) $(CFLAGS) $(RLFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	@$(MAKE) -C $(LIB_DIR)
	@$(MAKE) -C $(GNL_DIR)
	@$(CC) -o $(NAME) $(OBJ) $(LIBS) $(GNLS) $(RLFLAGS)
	@echo "$(NAME) is $(GRN)ready$(DFT)"

clean :
	@$(MAKE) -C $(LIB_DIR) clean
	@$(MAKE) -C $(GNL_DIR) clean
	@$(RM) $(OBJ)
	@echo "$(RED)cleaned$(DFT)"

fclean : 
	@$(MAKE) clean
	@$(MAKE) -C $(LIB_DIR) fclean
	@$(MAKE) -C $(GNL_DIR) fclean
	@$(RM) $(NAME)
	@echo "$(RED)fcleaned$(DFT)"

re : fclean all

PHONY	: all clean fclean re