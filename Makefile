
NAME = wolf3d

SRC_SUP = my_sdl
SRC_PATH = src
SRC_NAME =  main.c
		   
OBJ_PATH = .objects
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

INC_PATH = includes
INC_NAME = wolf3d.h
INC = $(addprefix $(INC_PATH)/,$(INC_NAME))

CPPFLAGS = -I $(INC_PATH)
LDFLAGS = -O3 -lpthread -L libft
LDLIBS = -lft

SDL = -lft -F /Library/Frameworks/ -L sdl2/2.0.10/lib/ -lSDL2 -L sdl2_image/2.0.5/lib/ -lSDL2_image
PATH_TO_SDL = ./


CC = gcc -g
CFLAGS = -Wall -Wextra


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

.PHONY: all clean fclean re

all: libft.a $(NAME)
	@printf "$(BLUE)> $(NAME) : $(YELLOW)Project ready !$(END)\n"

$(NAME): $(OBJ)
	@$(CC) $(LDFLAGS) $(SDL) $(LDLIBS) $^ -o $@
	@printf "\n$(BLUE)> $@ : $(GREEN)Success !$(END)\n\n"

libft.a:
	@make -C ./libft/


$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC)
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/$(SRC_SUP)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@printf "\r$(YELLOW)$(BOLD)[COMPILE] $(END) $(<:.c=)..."

clean:
	@make -C libft clean
	@rm -rf $(OBJ_PATH)
	@printf "$(BLUE)> Deleted : $(RED)$(OBJ_PATH)$(END)\n"

fclean: clean
	@make -C libft fclean
	@rm -rf $(NAME)
	@printf "$(BLUE)> Deleted : $(RED)$(NAME)$(END)\n"

re: fclean all

norme:
	norminette $(SRC_PATH) $(INC_PATH)
