NAME	=	gnl.a

RED		=	\033[0;31m
GRN		= 	\033[0;32m
YLW		=	\033[0;33m
BLU		= 	\033[0;36m
DFT		= 	\033[0;37m

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
AR		=	ar rcs
RM		=	rm -f

SRC		=	get_next_line.c\
			get_next_line_utils.c\
				
OBJ		=	$(SRC:.c=.o)

all : $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo "$(NAME) is $(GRN)ready$(DFT)"

clean :
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)

re : clean all

PHONY	: all clean fclean re bonus