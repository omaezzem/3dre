# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/27 09:42:39 by omaezzem          #+#    #+#              #
#    Updated: 2025/12/09 13:02:11 by omaezzem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #

NAME    = cub3D

NAME_BONUS = 

CC      = cc

CFLAGS  = -Wall -Wextra -Werror

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

SRCS    = cub.c  init_mlx.c utils/ft_split.c utils/ft_strjoin.c utils/utils.c parsing/pars.c get_next_line/get_next_line_utils.c get_next_line/get_next_line.c\
				errors/failed_msg.c ray_casting/ray.c utils/ft_strcmp.c utils/ft_strlen.c parsing/parc2.c parsing/parc3.c parsing/parc4.c parsing/parc5.c parsing/parc6.c\
				parsing/parc7.c   parsing/parc8.c utils/ft_atoi.c ray_casting/intersections_check.c

OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(OBJS) $(MLX_LIB) -lXext -lX11 -lm -lz -o $@

%.o: %.c get_next_line/get_next_line.h cub.h1
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C $(MLX_DIR) clean 2>/dev/null || true

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re