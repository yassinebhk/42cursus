# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/05 19:40:05 by ybouhaik          #+#    #+#              #
#    Updated: 2024/08/11 15:39:15 by ybouhaik         ###   ########.fr        #
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

NAME 	= philo
cc		= gcc
flags	= -Wall -Wextra -Werror -pthread -g -Iinclude -fsanitize=address
SRCS	= src/main.c src/parsing.c src/utils.c src/init_table.c src/init_philo.c \
			src/routine.c src/clean.c src/protect_args.c

OBJS	= $(SRCS:.c=.o)
INC		= include/philo.h

all: $(NAME)

%.o: %.c $(INCL)
	@gcc $(flags) -c $< -o $@
	@echo " $(BLUE)COMPILING $(YELLOW)$(ITALIC) $^ $(CYAN) to $(YELLOW)$(ITALIC)$@\n"

$(NAME):$(OBJS)
	@echo "\n $(BLUE)---------------------------------------------\n"
	@$(cc) $(flags) $(OBJS) -o $(NAME)
	@echo "$(MAGENTA)$(ITALIC)Philosophers compiled!$(RESET)"

clean:
	@rm -f $(OBJS)
	@echo "$(YELLOW)Cleaning...$(RESET)"
	@rm -f src/*.o
	@rm -f *.a
	
fclean: clean
	@/bin/rm -f $(NAME)
	@echo "$(GREEN)$(INVERT)Completed$(RESET)"

re: fclean all

norm:
	@echo "$(BLUE)$(DIM)SRC$(RESET)"
	@norminette src/*.c
	@echo "$(BLUE)$(DIM)Include$(RESET)"
	@norminette include/*.h
	@echo "$(GREEN)Completed!$(RESET)"

.PHONY: all clean fclean re