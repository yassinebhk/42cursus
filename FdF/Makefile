# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yassine <yassine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 20:35:03 by ybouhaik          #+#    #+#              #
#    Updated: 2024/02/26 13:27:28 by yassine          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc 
CFLAGS = -Werror -Wextra -Wall -g #gcc main.c ... libmlx42.a -Iinclude -ldl -lglfw -pthread -lm
FT_PRINTF_DIR = libs/ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
GET_NEXT_LINE_DIR = libs/get_next_line
GET_NEXT_LINE = $(GET_NEXT_LINE_DIR)/getnextline.a
MLX42_DIR = libs/MLX42
MLX42 = $(MLX42_DIR)/libmlx42.a
INCLUDES = -I . -I include -I $(FT_PRINTF_DIR) -I $(GET_NEXT_LINE_DIR) -I $(MLX42_DIR)

# COMMON_SRCS
FDF_SRCS = src/main.c
FDF_OBJS = $(FDF_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(FDF_OBJS) $(FT_PRINTF) $(GET_NEXT_LINE) $(MLX42)
	$(CC) $(CFLAGS) $(INCLUDES) $(FDF_OBJS) $(FT_PRINTF) $(GET_NEXT_LINE) $(MLX42) -o $(NAME)

$(FT_PRINTF):
	@$(MAKE) -C $(FT_PRINTF_DIR)

$(GET_NEXT_LINE):
	@$(MAKE) -C $(GET_NEXT_LINE_DIR)

$(MLX42):
	@$(MAKE) -C $(MLX42_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(FDF_OBJS)
	@$(MAKE) -C $(FT_PRINTF_DIR) clean
	@$(MAKE) -C $(GET_NEXT_LINE_DIR) clean
	@$(MAKE) -C $(MLX42_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(FT_PRINTF_DIR) fclean
	@$(MAKE) -C $(GET_NEXT_LINE_DIR) fclean
	@$(MAKE) -C $(MLX42_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
