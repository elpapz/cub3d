# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acanelas <acanelas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/11 03:18:07 by acanelas          #+#    #+#              #
#    Updated: 2023/10/11 03:24:13 by acanelas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	srcs/check_input.c \
		srcs/check_n_get_map.c \
		srcs/inicialize.c \
		srcs/main.c \

NAME = cub3d
RM = rm -rf
LIBFT = ./libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(CCMLX) -o $(NAME)

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re