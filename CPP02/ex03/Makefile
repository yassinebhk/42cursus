# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 23:31:51 by ybouhaik          #+#    #+#              #
#    Updated: 2024/09/11 00:13:18 by ybouhaik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLACK   = \033[30;1m
RED     = \033[31;1m
GREEN   = \033[32;1m
YELLOW  = \033[33;1m
BLUE    = \033[34;1m
MAGENTA = \033[35;1m
CYAN    = \033[36;1m
WHITE   = \033[37;1m
GRAY 	= \033[0;90m

BRIGHT_BLACK   = \033[90;1m
BRIGHT_RED     = \033[91;1m
BRIGHT_GREEN   = \033[92;1m
BRIGHT_YELLOW  = \033[93;1m
BRIGHT_BLUE    = \033[94;1m
BRIGHT_MAGENTA = \033[95;1m
BRIGHT_CYAN    = \033[96;1m
BRIGHT_WHITE   = \033[97;1m

UNDERLINE = \033[4m
REVERSE   = \033[7m
HIDDEN    = \033[8m
ITALIC    = \033[3m
CROSSED   = \033[9m

NAME = bsp
FLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = Fixed.cpp main.cpp Point.cpp bsp.cpp
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