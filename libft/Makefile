# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amargy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/26 17:53:17 by amargy            #+#    #+#              #
#    Updated: 2019/05/15 14:50:44 by amargy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
FLAGS = -O3 -c
INCLUDES = -I $(HEADERS_DIRECTORY)
HEADERS_LIST = 	libft.h 	\
				ft_printf.h \

HEADERS_DIRECTORY = ./
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))
LIBFT_SOURCES_DIRECTORY = ./
PRINTF_SOURCES_DIRECTORY = ./ft_printf/

SOURCES_LIST = ft_memset.c 							\
	   	ft_bzero.c 									\
		ft_error.c									\
	   	ft_memcpy.c 								\
	   	ft_memccpy.c 								\
	   	ft_memmove.c 								\
	   	ft_memchr.c 								\
	   	ft_memcmp.c 								\
	   	ft_strlen.c 								\
	   	ft_strdup.c 								\
	   	ft_strcpy.c 								\
	   	ft_strncpy.c 								\
	   	ft_strcat.c 								\
	   	ft_strncat.c 								\
	   	ft_strlcat.c 								\
	   	ft_strchr.c 								\
	   	ft_strrchr.c 								\
	   	ft_strstr.c 								\
	   	ft_strnstr.c 								\
	   	ft_strcmp.c 								\
	   	ft_strncmp.c 								\
	   	ft_atoi.c 									\
	   	ft_isalpha.c 								\
	   	ft_isdigit.c 								\
	   	ft_isalnum.c 								\
	   	ft_isascii.c 								\
	   	ft_isprint.c 								\
	   	ft_toupper.c 								\
	   	ft_tolower.c 								\
	   	ft_memalloc.c 								\
	   	ft_memdel.c 								\
	   	ft_strnew.c 								\
	   	ft_strdel.c 								\
	   	ft_strclr.c 								\
	   	ft_striter.c 								\
	   	ft_striteri.c 								\
	   	ft_strmap.c 								\
	   	ft_strmapi.c 								\
	   	ft_strequ.c 								\
	   	ft_strnequ.c 								\
	   	ft_strsub.c 								\
	   	ft_strjoin.c 								\
	   	ft_strtrim.c 								\
	   	ft_strtrim.c 								\
	   	ft_strsplit.c 								\
	   	ft_itoa.c 									\
	   	ft_putchar.c 								\
	   	ft_putstr.c 								\
	   	ft_putendl.c 								\
	   	ft_putnbr.c 								\
	   	ft_putchar_fd.c 							\
	   	ft_putstr_fd.c 								\
	   	ft_putendl_fd.c 							\
	   	ft_putnbr_fd.c 								\
	   	ft_lstnew.c 								\
	   	ft_lstdelone.c 								\
	   	ft_lstdel.c 								\
	   	ft_lstadd.c 								\
	   	ft_lstiter.c 								\
	   	ft_lstmap.c 								\
	   	get_next_line.c 							\
		ft_printf.c 								\
		parser.c 									\
		f_divf.c 									\
		f_double.c 									\
		f_format_float.c 							\
		f_long.c 									\
		f_multf.c 									\
		f_round.c 									\
		f_ten_pow.c 								\
		f_write_flo.c 								\
		preparation.c 								\
		flags_sp_s_o_p_cl.c 						\
		flags_unk_c_h_sh_po.c 						\
		flags_x_u_i_l.c 							\
		width_prec.c 								\
		plus_minus_zero_space_sharp.c				\
		cast.c 										\
		buffer_print.c 								\
		dioux.c 									\
		preprint_processing.c 						\

SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))
OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY)%.o : $(LIBFT_SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) $(INCLUDES) $< -o $@

$(OBJECTS_DIRECTORY)%.o : $(PRINTF_SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) $(INCLUDES) $< -o $@

clean:
	@rm -rf $(OBJECTS_DIRECTORY)

fclean: clean
	@rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all