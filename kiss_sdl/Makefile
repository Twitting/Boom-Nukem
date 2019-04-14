C = gcc

NAME = libkisssdl.a

CFILES = kiss_draw.c \
		kiss_general.c \
		kiss_posix.c \
		kiss_widgets.c 

OFILES	= $(CFILES:%.c=%.o)

INCLUDE = -I ./ -I ../includes/frameworks/SDL2.framework/Versions/A/Headers -I ../includes/frameworks/SDL2_image.framework/Versions/A/Headers  \
-F ~/Library/Frameworks/ -I ../includes/frameworks/SDL2_ttf.framework/Versions/A/Headers

all: $(NAME)

%.o: %.c
	gcc $(INCLUDE) -o $@ -c $<

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all