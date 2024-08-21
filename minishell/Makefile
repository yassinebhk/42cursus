# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/14 14:45:07 by ybouhaik          #+#    #+#              #
#    Updated: 2024/08/21 21:12:44 by maxgarci         ###   ########.fr        #
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

NAME				:= minishell
cc 					:= gcc
flags 				:= -g -Wall -Wextra -Werror -Iinclude -Ilibft #-fsanitize=address
SRCS 				:= src/main.c src/print_error.c src/env_vars.c src/builts.c src/echo.c \
						src/cd.c src/free.c src/list_utils.c src/list_utils_two.c src/pwd.c src/export.c \
						src/unset.c src/print_lists.c src/export_two.c src/exit.c src/cd_update.c
OBJS 				:=$(SRCS:.c=.o)
INCL				:= include/minishell.h

all: $(NAME)

#bonus: $(NAME_BONUS)

%.o: %.c $(INCL)
	@gcc $(flags) -c $< -o $@
	@echo " $(BLUE)COMPILING $(YELLOW)$(ITALIC) $^ $(CYAN) to $(YELLOW)$(ITALIC)$@\n"

$(NAME):$(OBJS)
	@echo "\n $(BLUE)---------------------------------------------\n"
	@echo " $(CYAN)LINKING$(YELLOW)$(ITALIC) $(SRCS) libft.a $(CYAN) to $(YELLOW)$(ITALIC) $(NAME)\n"
	@make -C libft
	@mv libft/libft.a .
	@$(cc) $(flags) $(OBJS) libft.a -lreadline -o $(NAME)
	@echo "$(MAGENTA)$(ITALIC) minishell compiled!$(RESET)"

clean:
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
