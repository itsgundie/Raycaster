#    PROJECT    #
NAME = wolf3d

OS = $(shell uname)

ifeq ($(OS), Linux)

#    DIRECTORIES    #
SRC_DIR = ./src/
LIB_DIR = ./libft/
OBJ_DIR = ./obj/
SRC_INC_DIR = includes/
LIB_INC_DIR = libft/includes/
SDL_INC_DIR = SDL2_Linux/include/

#    FLAGS    #
WFLGS = -g -Wall -Wextra -Werror
CFLGS_DBG =
LFLGS = -g -lm -L $(LIB_DIR) -lft -L SDL_Linux/lib/ -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
CC = gcc

#    LIBFT    #
LIBFT = $(LIB_DIR)/libft.a

#    SOURCES AND HEADERS    #
HEADER = includes/wolf3d.h

SRC_FILES = main.c \
			parse.c \
			create2dmap.c \
			blood_from_ears.c \
			preparation.c \
			destroy_everything.c \
			put_in.c \
			render_minimap.c \
			ray.c \
			render.c \
			draw.c \
			calculations.c \
			rays_calc.c

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:%.c=%.o))

#    INCLUDES    #
INCL = -I $(SDL_INC_DIR) -I $(SRC_INC_DIR) -I $(LIB_INC_DIR)

#    RULES    #
.PHONY: all clean fclean re

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) -c $< -o $@ $(INCL) $(LFLGS)

$(LIBFT):
	@$(MAKE) -C $(LIB_DIR)

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT) $(HEADER)
	$(CC) $(WFLGS) -o $(NAME) $(OBJS) $(INCL) $(LFLGS)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

run:
	./wolf3d map


else

#    DIRECTORIES    #
SRC_DIR = ./src/
LIB_DIR = ./libft/
OBJ_DIR = ./obj/
SRC_INC_DIR = ./includes/
LIB_INC_DIR = ./libft/includes
SDL_MAIN_INC = ./SDL/framework/SDL2.framework/Headers/
SDL_IMAGE_INC = ./SDL/framework/SDL2_image.framework/Headers/
SDL_MIXER_INC = ./SDL/framework/SDL2_mixer.framework/Headers/
SDL_TTF_INC = ./SDL/framework/SDL2_ttf.framework/Headers/
SDL_INC = -I SDL/inc/ -I $(SDL_MAIN_INC) -I $(SDL_IMAGE_INC) -I $(SDL_MIXER_INC) -I $(SDL_TTF_INC)
SDL_F_DIR = ./SDL/framework

#    FLAGS    #
CFLGS =  -g -Wl -rpath $(SDL_F_DIR) -F $(SDL_F_DIR) -framework SDL2 -framework SDL2_mixer -framework SDL2_image  -framework SDL2_ttf
WFLGS = -Wall -Wextra -Werror -g
CFLGS_DBG = -g
LFLGS = -g -lm -L$(LIB_DIR) -lft
CC = clang -g

#    LIBFT    #
LIBFT = $(LIB_DIR)/libft.a

#    SOURCES AND HEADERS    #
HEADER = includes/wolf3d.h

SRC_FILES = main.c \
			parse.c \
			create2dmap.c \
			blood_from_ears.c \
			preparation.c \
			destroy_everything.c \
			put_in.c \
			render_minimap.c \
			ray.c \
			render.c \
			draw.c \
			calculations.c \
			rays_calc.c \

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:%.c=%.o))

#    INCLUDES    #
INCL = $(SDL_INC) -I $(SRC_INC_DIR) -I $(LIB_INC_DIR)

#    RULES    #
.PHONY: all clean fclean re

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) -c $< -o $@ $(INCL) $(LFLAGS)

$(LIBFT):
	@$(MAKE) -C $(LIB_DIR)

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT) $(HEADER)
	$(CC) $(OBJS) $(WFLGS) -o $(NAME) $(INCL) $(LFLGS) $(CFLGS)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

run:
	./wolf3d map

#clean:
	#rm raycaster

endif
