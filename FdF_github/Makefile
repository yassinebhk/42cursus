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

framework= -framework OpenGL -framework AppKit
NAME=fdf
cc = gcc
flags = -Wall -Wextra -Werror
SRCS = src/main.c\
	   src/draw.c\
	   src/parsing.c\
	   src/utils.c \
	   src/hooks.c src/menu.c src/project.c src/utils2.c
OBJS =$(SRCS:.c=.o)
INCL= include/fdf.h

GREY=$'\x1b[30m
GREEN=$'\x1b[32m
YELLOW=$'\x1b[33m
BLUE=$'\x1b[34m
PURPLE=$'\x1b[35m
CYAN=$'\x1b[36m
WHITE=$'\x1b[37m


all:utils $(NAME)

%.o: %.c $(INCL)
	@gcc $(FLAGS) -c $< -o $@
	@echo " $(CYAN)COMPILING $(YELLOW) $^ $(CYAN) to $(YELLOW)$@\n"

$(NAME):$(OBJS) utils
	@echo " \n$(BLUE)---------------------------------------------\n"
	@echo " $(CYAN)LINKING$(YELLOW) $(OBJS) libft.a $(CYAN) to $(YELLOW) $(NAME)\n"
	@make -C libs/ft_printf
	@make -C libs/ft_printf/libft
	@make -C libs/get_next_line
	@make -C minilibx
	@mv libs/ft_printf/libftprintf.a .
	@mv libs/get_next_line/getnextline.a .
	@mv libs/ft_printf/libft/libft.a .
	@mv minilibx/libmlx.a .
	@$(cc) $(flags) $(OBJS) $(framework) libmlx.a libft.a libftprintf.a getnextline.a -o $(NAME)
	@echo "$(MAGENTA)$(ITALIC)FdF compiled!$(RESET)"

clean:
	rm -f $(FDF_OBJS)
	@echo "$(YELLOW)Cleaning...$(RESET)"
	@$(MAKE) -C libs/ft_printf clean
	@$(MAKE) -C libs/get_next_line clean
	@$(MAKE) -C minilibx clean
	@rm -f src/*.o
	@rm -f *.a
	

fclean:clean
	@/bin/rm -f $(NAME)
	@echo "$(GREEN)$(INVERT)Completed$(RESET)"

re:fclean all

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
	@echo " ##             #######           ##        "
	@echo "                                            "
	@echo "$(RESET)"


.PHONY: all utils clean fclean re