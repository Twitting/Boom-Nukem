# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: twitting <twitting@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 14:23:06 by twitting          #+#    #+#              #
#    Updated: 2019/03/06 15:30:23 by twitting         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem
SRC = ./src/main.c \
		./src/map_test.c \
		./src/vector_funcs.c
SRC2 = ./libft/libft.a
OBJECTS = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror
FLAGS2 = -I libft -I includes/ -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers -I ~/Library/Frameworks/SDL2_image.framework/Versions/A/Headers
SDL = -F ~/Library/Frameworks/ -framework SDL2 -framework SDL2_image
FLAGS_LINUX = -I ./includes/  -lXext -lX11 -lm -lpthread -lft

all: $(NAME)

linux:
	make re -C libft/
	sudo gcc $(FLAGS) $(SRC) $(SRC2) $(FLAGS_LINUX) -o $(NAME)

$(NAME): $(OBJECTS)
	make -C libft/
	gcc $(FLAGS) $(SDL) $(FLAGS2) $(OBJECTS) $(SRC2) -o $(NAME)

%.o: %.c
	gcc $(FLAGS) -I includes -I libft -c $< -o $@

clean:
	make clean -C libft/
	/bin/rm -f $(OBJECTS)

fclean: clean
	make fclean -C libft/
	/bin/rm -f $(NAME)

re: fclean all

re_linux: fclean linux
