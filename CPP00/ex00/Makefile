# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/25 21:42:58 by ybouhaik          #+#    #+#              #
#    Updated: 2024/08/25 22:37:38 by ybouhaik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
MAGENTA = \033[35;1m
YELLOW  = \033[33;1m
GREEN   = \033[32;1m
WHITE   = \033[37;1m
RESET   = \033[0m
BLUE    = \033[34;1m

NAME = megaphone
FLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = megaphone.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

%.o: %.cpp
	@g++ $(FLAGS) -c $< -o $@
	@echo " $(BLUE)COMPILING $(YELLOW) $< $(CYAN) to $(YELLOW) $@\n"

$(NAME): $(OBJS)
	@echo "\n $(BLUE)---------------------------------------------\n"
	@echo " $(CYAN)LINKING$(YELLOW) $(OBJS) $(CYAN) to $(YELLOW) $(NAME)\n"
	@g++ $(OBJS) -o $(NAME)
	@echo "$(MAGENTA) $(NAME) compiled!$(RESET)"

clean:
	@echo "$(YELLOW)Cleaning...$(RESET)"
	@rm -f $(OBJS)

fclean: clean
	@echo "$(YELLOW)Cleaning executable...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)Completed$(RESET)"

re: fclean all

.PHONY: all clean fclean re
