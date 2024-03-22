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

MAGENTA = \033[35;1m
YELLOW  = \033[33;1m
GREEN   = \033[32;1m
WHITE   = \033[37;1m
RESET   = \033[0m
GRAY 	= \033[0;90m
BLUE    = \033[34;1m
CYAN    = \033[37;1m
BOLD	= \033[1m
RED		= \033[31;1m

NAME = fdf
CC = gcc
CFLAGS = -Werror -Wextra -Wall
FT_PRINTF_DIR = libs/ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
GET_NEXT_LINE_DIR = libs/get_next_line
GET_NEXT_LINE = $(GET_NEXT_LINE_DIR)/getnextline.a
MLX42_DIR = libs/MLX42
MLX42 = $(MLX42_DIR)/libmlx42.a
LIBS	:= -ldl -lglfw3 -L "/Users/ybouhaik/.brew/opt/glfw/lib/" -pthread -lm $(MLX42_DIR)/libmlx42.a -framework Cocoa -framework OpenGL -framework IOKit
INCLUDES = -I . -I include -I $(FT_PRINTF_DIR) -I $(GET_NEXT_LINE_DIR) -I $(MLX42_DIR)/include/MLX42 #/Users/ybouhaik/Documents/FdF/libs/MLX42/include/MLX42/

# COMMON_SRCS
FDF_SRCS = src/main.c
FDF_OBJS = $(FDF_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(FDF_OBJS) $(FT_PRINTF) $(GET_NEXT_LINE) $(MLX42)
	@echo
	@$(CC) $(CFLAGS) $(FDF_OBJS) $(FT_PRINTF) $(GET_NEXT_LINE) $(MLX42) $(LIBS) $(INCLUDES) -o $(NAME) 
	@echo "$(BLUE)Compiling FDF...$(RESET)"
	@echo "$(GREEN)COMPLETED$(RESET)"
	@echo "$(BLUE)./fdf...$(RESET)"
	./fdf
	@echo "$(MAGENTA)FdF compiled!$(RESET)"
	
$(FT_PRINTF):
	@$(MAKE) -C $(FT_PRINTF_DIR)

$(GET_NEXT_LINE):
	@$(MAKE) -C $(GET_NEXT_LINE_DIR)

$(MINILIBX):
	@$(MAKE) -C $(MLX42_DIR)

%.o: %.c
	@echo "$(BLUE)Compiling: $(RESET)"
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

re: fclean all

.PHONY: all clean fclean re
