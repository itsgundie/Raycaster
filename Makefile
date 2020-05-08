#    PROJECT    #
NAME = wolf3d

#    DIRECTORIES    #
SRC_DIR = ./src/
LIB_DIR = ./libft/
OBJ_DIR = ./obj/
SRC_INC_DIR = ./includes/
LIB_INC_DIR = ./libft/includes
SDL_F_DIR	= ./SDL/framework
SDL_INC_DIR = ./SDL/include

#    FLAGS    #
CFLGS = -Wl -rpath $(SDL_F_DIR) -F $(SDL_F_DIR) -framework SDL2 -framework SDL2_mixer -framework SDL2_image -framework SDL2_ttf
WFLGS = -Wall -Wextra -Werror
CFLGS_DBG = -g
LFLGS = -L$(LIB_DIR) -lft
CC = gcc

#    LIBFT    #
LIBFT = $(LIB_DIR)/libft.a

#    SOURCES AND HEADERS    #
HEADER = includes/wolf3d.h includes/vec3.h
SRC_FILES = background.c \
			events.c \
			init.c \
			main.c \
			move.c \
			parse.c \
			ray.c \
			render.c \
			textures.c \
			update.c \

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:%.c=%.o))

#    INCLUDES    #
INCL = -I $(SDL_INC_DIR) -I $(SRC_INC_DIR) -I $(LIB_INC_DIR)

#    RULES    #
.PHONY: all clean fclean re

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) -c $< -o $@ -I $(SRC_INC_DIR) $(INCL) $(CFLGS_DBG) -Ofast

$(LIBFT):
	@echo "${LBLUE}########## COMPILE LIBFT.A ##########${RESTORE}"
	@$(MAKE) -C $(LIB_DIR)

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT) $(HEADER)
	$(CC) $(CFLGS) $(WFLGS) -o $(NAME) $(INCL) $(LFLGS) $(OBJS) $(CFLGS_DBG) -Ofast

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(SHADER_FRAG)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

$(OBJ_DIR):
	@echo "${PURPLE}########## CREATE OBJ DIRECTORY ##########${RESTORE}"
	@mkdir -p $(OBJ_DIR)
#	COLORS	#
RESTORE = \033[0m

RED = \033[00;31m
GREEN = \033[00;32m
YELLOW = \033[00;33m
BLUE = \033[00;34m
PURPLE = \033[00;35m
CYAN = \033[00;36m
LIGHTGRAY = \033[00;37m

LRED = \033[01;31m
LGREEN = \033[01;32m
LYELLOW = \033[01;33m
LBLUE = \033[01;34m
LPURPLE = \033[01;35m
LCYAN = \033[01;36m
WHITE = \033[01;37m