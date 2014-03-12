# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/09/30 11:03:46 by rfrey             #+#    #+#              #
#    Updated: 2014/03/12 21:47:09 by gbersac          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= cc
CFLAGS			= -Wall -Werror -Wextra -O3 -g
NAME			= RT
PATH_OBJ		= obj
PATH_SRC		= src
PATH_INC		= inc
PATH_LIBFT		= libft
LIBFT			= libft.a
PATH_LIBFT_INC	= $(PATH_LIBFT)/includes
SRC				= debug.c main.c load_file.c render.c parse.c parse2.c \
					sphere.c cam.c light.c image.c handle.c free.c vector1.c \
					vector2.c render2.c plan.c rotate_cam.c

OBJ				= $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))
MLX				= -L /usr/X11/lib -lmlx -lXext -lX11

all : $(NAME)

$(NAME) : $(PATH_LIBFT)/$(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(PATH_LIBFT)/$(LIBFT) -o $@ $(MLX)
	@echo " done !"

$(PATH_OBJ)/%.o : $(addprefix $(PATH_SRC)/, %.c)
	@echo -n .
	@mkdir -p $(PATH_OBJ)
	@$(CC) $(CFLAGS) -o $@ -c $< -I $(PATH_INC)/ -I $(PATH_LIBFT_INC)/

$(PATH_LIBFT)/$(LIBFT) : $(PATH_LIBFT)/Makefile
	@cd $(PATH_LIBFT)/ && $(MAKE)

clean :
	@rm -f $(OBJ)
	@cd $(PATH_LIBFT) && $(MAKE) $@

fclean : clean
	@rm -f $(NAME)
	@rm -f $(PATH_LIBFT)/$(LIBFT)

re : fclean all

.PHONY: clean fclean
