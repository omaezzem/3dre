# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/27 09:42:39 by omaezzem          #+#    #+#              #
#    Updated: 2025/12/22 16:18:44 by omaezzem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  	= cub3D

NAME_BONUS =

CC 		= cc

CFLAGS 	= -Wall -Wextra -Werror

SRCS 	= cub.c  init_mlx.c utils/ft_split.c utils/ft_strjoin.c utils/utils.c parsing/pars.c get_next_line/get_next_line_utils.c get_next_line/get_next_line.c\
				errors/failed_msg.c ray_casting/ray.c utils/ft_strcmp.c utils/ft_strlen.c parsing/parc2.c parsing/parc3.c parsing/parc4.c parsing/parc5.c parsing/parc6.c\
				parsing/parc7.c parsing/parc8.c utils/ft_atoi.c parsing/parc9.c ray_casting/intersections_check.c ray_casting/ray.c ray_casting/textures.c ray_casting/utils_tex_ray.c\
				utils/ft_isdigit.c 
all: $(NAME)

OBJS	= $(SRCS:.c=.o)
BOBJS   = $(BSRC:.c=.o)

$(NAME) : $(OBJS)
	@$(CC) -lmlx -framework OpenGL -framework AppKit  $^ -o $@

%.o: %.c get_next_line/get_next_line.h cub.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS) : $(BOBJS)
	@$(CC) -lmlx -framework OpenGL -framework AppKit  $^ -o $@

clean:
	@rm -f $(OBJS) $(BOBJS)

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)

re: fclean all
