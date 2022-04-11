NAME = pipex
SRCS = pipex.c \
	ft_child.c ft_child2.c libft/libft.a

CFLAGS = -Wall -Werror -Wextra

OTHERS = cd libft && make && cd ..

all : $(NAME)

$(NAME) : $(SRCS)
	$(OTHERS)
	cc -fsanitize=address $(SRCS) -o $(NAME)
clean :
	cd libft && make clean && cd ..
fclean : clean
	rm -f $(NAME)
re : fclean all
.PHONY: clean all clean re fclean