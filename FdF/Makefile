# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 20:35:03 by ybouhaik          #+#    #+#              #
#    Updated: 2024/02/25 19:19:52 by ybouhaik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
CFLAGS = -Werror -Wextra -Wall -g
FT_PRINTF_DIR = libs/ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
GET_NEXT_LINE_DIR = libs/get_next_line
GET_NEXT_LINE = $(GET_NEXT_LINE_DIR)/getnextline.a
MINILIBX_DIR = libs/minilibx_macos
MINILIBX = $(MINILIBX_DIR)/libmlx.a
INCLUDES = -I . -I include -I $(FT_PRINTF_DIR) -I $(GET_NEXT_LINE_DIR) -I $(MINILIBX_DIR)

# COMMON_SRCS
FDF_SRCS = src/main.c
FDF_OBJS = $(FDF_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(FDF_OBJS) $(FT_PRINTF) $(GET_NEXT_LINE) $(MINILIBX)
	$(CC) $(CFLAGS) $(INCLUDES) $(FDF_OBJS) $(FT_PRINTF) $(GET_NEXT_LINE) $(MINILIBX) -o $(NAME)

$(FT_PRINTF):
	@$(MAKE) -C $(FT_PRINTF_DIR)

$(GET_NEXT_LINE):
	@$(MAKE) -C $(GET_NEXT_LINE_DIR)

$(MINILIBX):
	@$(MAKE) -C $(MINILIBX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(FDF_OBJS)
	@$(MAKE) -C $(FT_PRINTF_DIR) clean
	@$(MAKE) -C $(GET_NEXT_LINE_DIR) clean
	@$(MAKE) -C $(MINILIBX_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(FT_PRINTF_DIR) fclean
	@$(MAKE) -C $(GET_NEXT_LINE_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
