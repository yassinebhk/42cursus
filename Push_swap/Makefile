# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yassine <yassine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/27 12:09:53 by ybouhaik          #+#    #+#              #
#    Updated: 2024/04/30 12:36:58 by yassine          ###   ########.fr        #
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
GREY=$'\x1b[30m
GREEN=$'\x1b[32m
YELLOW=$'\x1b[33m
BLUE=$'\x1b[34m
PURPLE=$'\x1b[35m
CYAN=$'\x1b[36m
WHITE=$'\x1b[37m

NAME				:= push_swap
NAME_BONUS			:= push_swap_bonus
cc 					:= gcc
flags 				:= -g -Wall -Wextra -Werror
SRCS 				:= src/push_swap.c src/parsing.c src/errors.c src/utils.c src/swap.c  src/rotate.c\
						src/set_pos_and_index.c src/rotate_reverse.c src/init_stacks.c src/free.c src/fill_stack.c src/list_utils.c src/push.c 
SRCS_BONUS 			:= src/push_swap.c
OBJS 				:=$(SRCS:.c=.o)
OBJS_BONUS 			:=$(SRCS_BONUS:.c=.o)
INCL				:= include/push_swap.h

all:utils $(NAME)

bonus: $(NAME_BONUS)

%.o: %.c $(INCL)
	@gcc $(FLAGS) -c $< -o $@
	@echo " $(CYAN)COMPILING $(YELLOW) $^ $(CYAN) to $(YELLOW)$@\n"

$(NAME):$(OBJS) utils
	@echo "\n $(BLUE)---------------------------------------------\n"
	@echo " $(CYAN)LINKING$(YELLOW) $(SRCS) libft.a $(CYAN) to $(YELLOW) $(NAME)\n"
	@make -C libft
	@mv libft/libft.a .
	@$(cc) $(flags) $(OBJS) libft.a -o $(NAME)
	@echo "$(MAGENTA)$(ITALIC)Push-swap compiled!$(RESET)"

$(NAME_BONUS):$(OBJS_BONUS) utils
	@echo "\n $(BLUE)---------------------------------------------\n"
	@echo " $(CYAN)LINKING$(YELLOW) $(SRCS_BONUS) libft.a $(CYAN) to $(YELLOW) $(NAME_BONUS)\n"
	@make -C libft
	@mv libft/libft.a .
	@$(cc) $(flags) $(OBJS_BONUS) libft.a -o $(NAME_BONUS)
	@echo "$(MAGENTA)$(ITALIC)Push-swap compiled!$(RESET)"

clean:
	rm -f $(FDF_OBJS)
	@echo "$(YELLOW)Cleaning...$(RESET)"
	@$(MAKE) -C libft clean
	@rm -f src/*.o
	@rm -f libft.a
	
fclean:clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(NAME_BONUS)
	@echo "$(GREEN)$(INVERT)Completed$(RESET)"

re:fclean all

norm:
	@echo "$(BLUE)$(DIM)LIBFT$(RESET)"
	@norminette libft/*.c libft/*.h
	@echo "$(GREEN)Completed!$(RESET)"
	@echo
	@echo "$(BLUE)$(DIM)SRC$(RESET)"
	@norminette src/*.c include/$(NAME).h
	@echo "$(GREEN)Completed!$(RESET)"

.PHONY: all utils clean fclean re
