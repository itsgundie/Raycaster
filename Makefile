.PHONY: all clean fclean re

GREY=$ \x1b[30m
RED=$ \x1b[31m
GREEN=$ \x1b[32m
YELLOW=$ \x1b[33m
BLUE=$ \x1b[34m
PINK=$ \x1b[35m
CYAN=$ \x1b[36m
WHITE=$ \x1b[37m

END=$ \x1b[0m
BOLD=$ \x1b[1m
UNDER=$ \x1b[4m
SUR=$ \x1b[7m

NAME = wolf3d

CC = clang -g

CC_FLAGS = 

SDL_INC = -I /SDL/inc/
SDL_LIB = -L SDL/lib/ -l SDL2 -L SDL/lib/ -l SDL2_image
SDL = $(SDL_INC) $(SDL_LIB)


SRC_PATH = ./src/

SRC_FILES =	main.c \
		parse.c \
		init.c \
		events.c \
		background.c \
		render.c \
		ray.c	\
		move.c	\
		update.c \
		textures.c
		
SRC = $(addprefix $(SRC_PATH), $(SRC_FILES))

OBJ_PATH = ./objects/

OBJ_FILES = $(SRC_FILES: .c=.o)

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

INC_PATH = ./includes/

INC_FILES = wolf3d.h

INC = $(addprefix $(INC_PATH), $(INC_FILES))

LIBFT = ./libft/libft.a


all: $(NAME)
	@printf "$(BLUE)> $(NAME) : $(YELLOW)Project ready !$(END)\n"

$(LIBFT):
	@make -C libft/

$(NAME): $(LIBFT)
	$(CC) $(SRC) $(LIBFT) -o $(NAME) -I $(INC) $(SDL)
	@printf "\n$(BLUE)> $@ : $(GREEN)Success !$(END)\n\n"


clean:
	@make -C libft/ clean
	@printf "$(BLUE)> Deleted : $(RED)$(OBJ_PATH)$(END)\n"

fclean: clean
	@make -C libft fclean
	@rm $(NAME)
	@printf "$(BLUE)> Deleted : $(RED)$(NAME) -[-_-]- $(END)\n"

re: fclean all

norme:
	norminette $(SRC) $(INC)

run:
	./wolf3d petite


# ALL: LIBFT NAME
# 	@printf "$(BLUE)> $(NAME) : $(YELLOW)Project ready !$(END)\n"

# LIBFT:
# 	@make -C ./libft/

# NAME: $(OBJ)
# 	@$(CC) $(CC_FLAGS) -I $(INC) $(SDL) $(OBJ) -o $(NAME) 
# 	@printf "\n$(BLUE)> $@ : $(GREEN)Success !$(END)\n\n"

# $(OBJ_PATH)$(OBJ_FILES): $(SRC_PATH)$(SRC_FILES)
# 	@mkdir -p $(OBJ_PATH)
# 	@$(CC) -c $(INC) -o $@ $< $(CC_FLAGS) 
# 	@printf "\r$(YELLOW)$(BOLD)[COMPILE] $(END) $(<:.c=)..."



# SRC_SUP = my_sdl
# SRC_PATH = src
# SRC_NAME =  main.c \
# 			parse.c \
# 			init.c \
# 			background.c \
# 			events.c \
# 			ray.c \
# 			render.c
		   
# OBJ_PATH = .objects
# OBJ_NAME = $(SRC_NAME:.c=.o)
# OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

# INC_PATH = includes
# INC_NAME = wolf3d.h
# INC = $(addprefix $(INC_PATH)/,$(INC_NAME))

# CPPFLAGS = -I $(INC_PATH)
# LDFLAGS = -O3 -lpthread -L libft
# LDLIBS = -lft

# SDL = -lft -F /Library/Frameworks/ -L sdl2/2.0.10/lib/ -lSDL2 -L sdl2_image/2.0.5/lib/ -lSDL2_image
# PATH_TO_SDL = ./


# CC = gcc -g
# CFLAGS = -Wall -Wextra