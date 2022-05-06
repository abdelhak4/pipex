NAME = pipex
SRCS = pipex.c \
	ft_child.c ft_child2.c libft/libft.a \
	pipex_utils.c

CFLAGS = -Wall -Werror -Wextra #-fsanitize=address

.SILENT: OTHERS = cd libft && make && cd ..

all : $(NAME)

$(NAME) : $(SRCS)
	$(OTHERS)
	cc $(CFLAGS) $(SRCS) -o $(NAME)
clean :
	cd libft && make clean && cd ..
fclean : clean
	rm -f $(NAME)
re : fclean all
.PHONY: clean all clean re fclean