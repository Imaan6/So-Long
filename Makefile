CC = gcc -lmlx -framework OpenGL -framework AppKit
NAME = so_long
FLAGS = -Wall -Wextra -Werror
SRC = so_long.c ft_split.c get_next_line.c get_next_line_utils.c utilities.c utilities_continued.c ft_printf.c ft_putaddress.c ft_puthexalow.c ft_puthexaup.c ft_putnbr.c ft_putstr.c
OBJSRC = $(SRC)

all : $(NAME)

$(NAME): $(OBJSRC)
	$(CC) $(FLAGS)  $(OBJSRC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf $(NAME)

re: fclean all