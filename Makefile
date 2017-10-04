NAME = libcstruct.a

SRCS = $(wildcard ./srcs/*.c)

OBJ	= $(SRCS:.c=.o)
INC	= -I ./includes
#FLAGS	= -Wall -Werror -Wextra -Ofast
FLAGS	= -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $< $(INC)

clean: 
	rm -rf */*.o
	rm -rf */*.o.test

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all test clean
