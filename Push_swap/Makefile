# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/27 12:09:53 by ybouhaik          #+#    #+#              #
#    Updated: 2024/07/26 22:04:02 by ybouhaik         ###   ########.fr        #
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

NAME				:= push_swap
cc 					:= gcc
flags 				:= -g -Wall -Wextra -Werror
SRCS 				:= src/push_swap.c src/parsing.c src/errors.c src/utils.c src/swap.c  src/rotate.c\
						src/algorithm.c src/set_pos_and_index.c src/rotate_reverse.c src/init_stacks.c\
						src/cost_change.c src/mvts_stack_a.c src/mvts_stack_b.c src/two_and_three_nodes.c src/free.c src/fill_stack.c src/list_utils.c src/push.c src/get_costs.c
OBJS 				:=$(SRCS:.c=.o)
INCL				:= include/push_swap.h

all:utils $(NAME)

bonus: $(NAME_BONUS)

%.o: %.c $(INCL)
	@gcc $(FLAGS) -c $< -o $@
	@echo " $(BLUE)COMPILING $(YELLOW)$(ITALIC) $^ $(CYAN) to $(YELLOW)$(ITALIC)$@\n"

$(NAME):$(OBJS)
	@echo "\n $(BLUE)---------------------------------------------\n"
	@echo " $(CYAN)LINKING$(YELLOW)$(ITALIC) $(SRCS) libft.a $(CYAN) to $(YELLOW)$(ITALIC) $(NAME)\n"
	@make -C libft
	@mv libft/libft.a .
	@$(cc) $(flags) $(OBJS) libft.a -o $(NAME)
	@echo "$(MAGENTA)$(ITALIC)Push-swap compiled!$(RESET)"

clean:
	@rm -f $(FDF_OBJS)
	@echo "$(YELLOW)Cleaning...$(RESET)"
	@$(MAKE) -C libft clean
	@rm -f src/*.o
	@rm -f libft.a
	
fclean:clean
	@/bin/rm -f $(NAME)
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

.PHONY: all clean fclean re
