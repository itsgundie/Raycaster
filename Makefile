#    PROJECT    #
NAME = wolf3d

#    DIRECTORIES    #
SRC_DIR = ./src/
LIB_DIR = ./libft/
OBJ_DIR = ./obj/
SRC_INC_DIR = ./includes/
LIB_INC_DIR = ./libft/includes
SDL_INC_DIR = ./SDL/inc
SDL_F_DIR = ./SDL/framework

#    FLAGS    #
CFLGS = -Wl -rpath $(SDL_F_DIR) -F $(SDL_F_DIR) -framework SDL2 -framework SDL2_mixer -framework SDL2_image -framework SDL2_ttf
WFLGS = -Wall -Wextra -Werror
CFLGS_DBG = -g
LFLGS = -L$(LIB_DIR) -lft
CC = gcc

#    LIBFT    #
LIBFT = $(LIB_DIR)/libft.a

#    SOURCES AND HEADERS    #
HEADER = includes/wolf3d.h
TEXTHEADER =

SRC_FILES = main.c \
			parse.c \
			create2dmap.c \
			blood_from_ears.c \
			preparation.c \
			destroy_everything.c \
			put_in.c \
			render_minimap.c \

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:%.c=%.o))

#    INCLUDES    #
INCL = -I $(SDL_INC_DIR) -I $(SRC_INC_DIR) -I $(LIB_INC_DIR)

#    RULES    #
.PHONY: all clean fclean re

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) $(TEXTHEADER)
	$(CC) -c $< -o $@ -I $(SRC_INC_DIR) $(INCL) $(CFLGS_DBG)

$(LIBFT):
	@$(MAKE) -C $(LIB_DIR)

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT) $(HEADER) $(TEXTHEADER)
	$(CC) $(CFLGS) $(WFLGS) -o $(NAME) $(INCL) $(LFLGS) $(OBJS) $(CFLGS_DBG)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(SHADER_FRAG)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

#build:
	#gcc -g -std=c99 ./src/*.c -I SDL/inc/ -L ./SDL/lib/ -lSDL2 -o raycaster

run:
	./wolf3d map

#clean:
	#rm raycaster