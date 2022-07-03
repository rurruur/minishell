NAME	=	libft.a

RED		=	\033[0;31m
GRN		= 	\033[0;32m
YLW		=	\033[0;33m
BLU		= 	\033[0;36m
DFT		= 	\033[0;37m

CC 		= 	gcc
CFLAGS	=	-Wall -Wextra -Werror

SRC 	= 	ft_isalpha.c\
			ft_isdigit.c\
			ft_isalnum.c\
			ft_isascii.c\
			ft_isprint.c\
			ft_toupper.c\
			ft_tolower.c\
			ft_strlen.c\
			ft_strlcpy.c\
			ft_strlcat.c\
			ft_strncmp.c\
			ft_strchr.c\
			ft_strrchr.c\
			ft_strnstr.c\
			ft_strdup.c\
			ft_bzero.c\
			ft_memset.c\
			ft_memcpy.c\
			ft_memmove.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_atoi.c\
			ft_calloc.c\
			ft_strmapi.c\
			ft_striteri.c\
			ft_putchar_fd.c\
			ft_putstr_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
			ft_substr.c\
			ft_strjoin.c\
			ft_strtrim.c\
			ft_split.c\
			ft_itoa.c\

OBJ 	= 	$(SRC:.c=.o)

BONUS 	= 	ft_lstnew.c\
			ft_lstadd_front.c\
			ft_lstsize.c\
			ft_lstlast.c\
			ft_lstadd_back.c\
			ft_lstdelone.c\
			ft_lstclear.c\
			ft_lstiter.c\
			ft_lstmap.c

BNS_OBJ = 	$(BONUS:.c=.o)

all: $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo "$(NAME) is $(GRN)ready$(DFT)"

clean:
	@rm -f $(OBJ) $(BNS_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

bonus: $(OBJ) $(BNS_OBJ)
	@ar rc $(NAME) $(OBJ) $(BNS_OBJ)

PHONY: all clean fclean re bonus
