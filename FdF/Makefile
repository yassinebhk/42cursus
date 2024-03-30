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

framework			:= -framework OpenGL -framework AppKit
NAME				:= fdf
NAME_BONUS				:= fdf_bonus
cc 					:= gcc
flags 				:= -g -O3 -Wall -Wextra -Werror
SRCS 				:= src/main.c\
	   					src/draw.c\
	   					src/parsing.c\
	   					src/utils.c \
	   					src/hooks.c src/menu.c src/project.c src/utils2.c
SRCS_BONUS 			:= src/main_bonus.c\
	   					src/draw_bonus.c\
	   					src/parsing_bonus.c\
	   					src/utils_bonus.c \
	   					src/hooks_bonus.c src/menu_bonus.c src/project_bonus.c src/utils2_bonus.c
OBJS 				:=$(SRCS:.c=.o)
OBJS_BONUS 			:=$(SRCS_BONUS:.c=.o)
INCL				:= include/fdf.h


GREY=$'\x1b[30m
GREEN=$'\x1b[32m
YELLOW=$'\x1b[33m
BLUE=$'\x1b[34m
PURPLE=$'\x1b[35m
CYAN=$'\x1b[36m
WHITE=$'\x1b[37m


all:utils $(NAME)

bonus: $(NAME_BONUS)

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
	@$(cc) $(flags) $(OBJS) -framework OpenGL -framework AppKit libmlx.a libft.a libftprintf.a getnextline.a -o $(NAME)
	@echo "$(MAGENTA)$(ITALIC)FdF compiled!$(RESET)"

%.o: %.c $(INCL)
	@gcc $(FLAGS) -c $< -o $@
	@echo " $(CYAN)COMPILING $(YELLOW) $^ $(CYAN) to $(YELLOW)$@\n"

$(NAME_BONUS):$(OBJS_BONUS) utils
	@echo " \n$(BLUE)---------------------------------------------\n"
	@echo " $(CYAN)LINKING$(YELLOW) $(OBJS_BONUS) libft.a $(CYAN) to $(YELLOW) $(NAME_BONUS)\n"
	@make -C libs/ft_printf
	@make -C libs/ft_printf/libft
	@make -C libs/get_next_line
	@make -C minilibx
	@mv libs/ft_printf/libftprintf.a .
	@mv libs/get_next_line/getnextline.a .
	@mv libs/ft_printf/libft/libft.a .
	@mv minilibx/libmlx.a .
	@$(cc) $(flags) $(OBJS_BONUS) -framework OpenGL -framework AppKit libmlx.a libft.a libftprintf.a getnextline.a -o $(NAME_BONUS)
	@echo "$(MAGENTA)$(ITALIC)FdF compiled!$(RESET)"

clean:
	rm -f $(FDF_OBJS)
	@echo "$(YELLOW)Cleaning...$(RESET)"
	@$(MAKE) -C libs/ft_printf clean
	@$(MAKE) -C libs/get_next_line clean
	@$(MAKE) -C minilibx clean
	@rm -f src/*.o
	@rm -f libft.a libftprintf.a getnextline.a libmlx.a
	

fclean:clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(NAME_BONUS)
	@echo "$(GREEN)$(INVERT)Completed$(RESET)"

re:fclean all

norm:
	@echo "$(BLUE)$(DIM)FT_PRINTF$(RESET)"
	@norminette libs/ft_printf/*.c libs/ft_printf/*.h
	@echo "$(GREEN)Completed!$(RESET)"
	@echo
	@echo "$(BLUE)$(DIM)LIBFT$(RESET)"
	@norminette libs/ft_printf/libft/*.c libs/ft_printf/libft/*.h
	@echo "$(GREEN)Completed!$(RESET)"
	@echo
	@echo "$(BLUE)$(DIM)GNL$(RESET)"
	@norminette libs/get_next_line/*.c libs/get_next_line/*.h
	@echo "$(GREEN)Completed!$(RESET)"
	@echo
	@echo "$(BLUE)$(DIM)SRC$(RESET)"
	@norminette src/*.c include/$(NAME).h
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