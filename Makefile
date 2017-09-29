# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/04 15:56:40 by gmichaud          #+#    #+#              #
#    Updated: 2017/09/29 17:22:29 by gmichaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC_NAME = main.c error.c display.c init_params.c fill_map.c update_img.c \
			matrices_calc.c inputs.c inputs2.c put_params.c \
			quit.c init_vector.c matrices.c mtx_op.c projection.c \
			ndc_conv.c win_scale.c vec_op.c rasterize.c rasterize2.c \
			put_pixel.c sort.c

SRC_PATH = src

OBJ_PATH = obj

INC_PATH = -I./includes -I./libft/includes -I./minilibx_macos

LIBS = -lft -lmlx -lm -framework OpenGL -framework Appkit

LIB_PATH = -L./libft -L./minilibx_macos

CC = clang

CFLAGS = -Wall -Wextra -Werror

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	make -C ./minilibx_macos
	$(CC) $(CFLAGS) $^ -o $@ $(LIB_PATH) $(LIBS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) -c -o $@ $< $(INC_PATH)

clean:
	/bin/rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	make -C ./libft clean
	make -C ./minilibx_macos clean

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f ./libft/libft.a
	/bin/rm -f ./minilibx_macos/libmlx.a

re: fclean $(NAME)
