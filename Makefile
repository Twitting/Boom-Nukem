# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: twitting <twitting@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 14:23:06 by twitting          #+#    #+#              #
#    Updated: 2019/03/05 15:12:19 by twitting         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem
SRC = ./src/*.c
SRC2 = ./libft/libft.a
OBJECTS = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror
FLAGS2 = -I libft -Iincludes -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers -I ~/Library/Frameworks/SDL2_image.framework/Versions/A/Headers
SDL = -F ~/Library/Frameworks/ -framework SDL2 -framework SDL2_image
FLAGS_LINUX = -I ./includes/  -lXext -lX11 -lm -lpthread

all: $(NAME)

linux:
	make re -C libft/
	sudo gcc $(FLAGS) $(SRC) $(SRC2) $(FLAGS_LINUX) -o $(NAME)

$(NAME): $(OBJECTS)
	make -C libft/
	gcc -g $(FLAGS) $(SDL) $(FLAGS2) $(OBJECTS) $(SRC2) -o $(NAME)

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
