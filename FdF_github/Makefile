# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yassine <yassine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 20:35:03 by ybouhaik          #+#    #+#              #
#    Updated: 2024/03/24 00:25:17 by yassine          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
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

# Styles
RESET	= \033[0m
BOLD	= \033[1m
DIM		= \033[2m
ITALIC	= \033[3m
UNDER	= \033[4m
INVERT	= \033[7m
DASH	= \033[9m

NAME = fdf
CC = gcc
CFLAGS = -Werror -Wextra -Wall
FT_PRINTF_DIR = libs/ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
GET_NEXT_LINE_DIR = libs/get_next_line
GET_NEXT_LINE = $(GET_NEXT_LINE_DIR)/getnextline.a
MLX42_DIR = libs/MLX42
MLX42 = $(MLX42_DIR)/libmlx42.a
LIBS	:= -ldl -lglfw -L /opt/homebrew/Cellar/glfw/3.3.6/lib/ -pthread -lm $(MLX42_DIR)/libmlx42.a #-framework Cocoa -framework OpenGL -framework IOKit
INCLUDES = -I . -I include -I $(FT_PRINTF_DIR) -I $(GET_NEXT_LINE_DIR) -I $(MLX42_DIR)/include/MLX42 #/Users/ybouhaik/Documents/FdF/libs/MLX42/include/MLX42/

# COMMON_SRCS
# FDF_SRCS = src/fdf.c src/draw.c src/hooks.c 
FDF_SRCS = src/main.c src/read_file.c
FDF_OBJS = $(FDF_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(FDF_OBJS) $(FT_PRINTF) $(GET_NEXT_LINE) $(MLX42)
	@clear
	@echo
	@$(CC) $(CFLAGS) $(FDF_OBJS) $(FT_PRINTF) $(GET_NEXT_LINE) $(MLX42) $(LIBS) $(INCLUDES) -o $(NAME) 
	@echo "$(BLUE)Compiling FDF...$(RESET)"
	@echo "$(GREEN)$(BOLD)COMPLETED$(RESET)"
	@echo "$(MAGENTA)$(ITALIC)FdF compiled!$(RESET)"
	
$(FT_PRINTF):
	@$(MAKE) -C $(FT_PRINTF_DIR)

$(GET_NEXT_LINE):
	@$(MAKE) -C $(GET_NEXT_LINE_DIR)

$(MLX42):
	@$(MAKE) -C $(MLX42_DIR)

%.o: %.c
	@echo "$(BLUE)Compiling: $(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(FDF_OBJS)
	@echo "$(YELLOW)Cleaning...$(RESET)"
	@$(MAKE) -C $(FT_PRINTF_DIR) clean
	@$(MAKE) -C $(GET_NEXT_LINE_DIR) clean
	@$(MAKE) -C $(MLX42_DIR) clean
	


fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(FT_PRINTF_DIR) fclean
	@$(MAKE) -C $(GET_NEXT_LINE_DIR) fclean
	@echo "$(GREEN)$(INVERT)Completed$(RESET)"
re: fclean all

norm:
	@echo "$(BLUE)$(DIM)FT_PRINTF$(RESET)"
	@norminette $(FT_PRINTF_DIR)/*.c $(FT_PRINTF_DIR)/*.h
	@echo "$(GREEN)Completed!$(RESET)"
	@echo
	@echo "$(BLUE)$(DIM)LIBFT$(RESET)"
	@norminette $(FT_PRINTF_DIR)/LIBFT/*.c $(FT_PRINTF_DIR)/LIBFT/*.h
	@echo "$(GREEN)Completed!$(RESET)"
	@echo
	@echo "$(BLUE)$(DIM)SRC$(RESET)"
	@norminette $(FDF_SRCS) include/$(NAME).h
	@echo "$(GREEN)Completed!$(RESET)"
ascii:
	@echo "$(MAGENTA)$(BOLD)"
	@echo "                                            "
	@echo " #########      #########         ######### "
	@echo " ##             ##      ##        ##        "
	@echo " ##             ##       ##       ##        "
	@echo " #########      ##        ##      ######### "
	@echo " ##             ##       ##       ##        "
	@echo " ##             ##      ##        ##        "
	@echo " ##             ##     ##         ##        "
	@echo "                #######                     "
	@echo "                                            "
	@echo "$(RESET)"

.PHONY: all clean fclean re
