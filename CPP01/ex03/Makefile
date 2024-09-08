# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 23:31:51 by ybouhaik          #+#    #+#              #
#    Updated: 2024/09/05 21:29:00 by ybouhaik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
MAGENTA  = \033[35;1m
YELLOW   = \033[33;1m
GREEN    = \033[32;1m
WHITE    = \033[37;1m
RESET    = \033[0m
GRAY     = \033[0;90m
BLUE     = \033[34;1m
CYAN     = \033[37;1m
BOLD     = \033[1m
RED      = \033[31;1m

NAME = weapon
FLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = Weapon.cpp HumanA.cpp HumanB.cpp main.cpp
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