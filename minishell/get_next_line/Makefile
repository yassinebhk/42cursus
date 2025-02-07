# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maxgarci <maxgarci@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 13:07:20 by maxgarci          #+#    #+#              #
#    Updated: 2025/01/22 14:32:28 by maxgarci         ###   ########.fr        #
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

NAME				:= get_next_line.a

CC 					:= cc
CFLAGS 				:= -g -Wall -Wextra -Werror 

SRCS 				:= get_next_line_bonus.c get_next_line_utils_bonus.c

OBJ_PATH			:= obj/
OBJ 				:= $(SRCS:.c=.o)
OBJS				:= $(addprefix $(OBJ_PATH), $(OBJ))

INCL				:= get_next_line_bonus.h

all: $(NAME)

$(OBJ_PATH)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo " $(BLUE)COMPILING $(YELLOW)$(ITALIC) $^ $(CYAN) to $(YELLOW)$(ITALIC)$@\n"

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJS): $(OBJ_PATH)

$(NAME): $(OBJS)
	@echo "\n $(BLUE)---------------------------------------------\n"
	@ar -rcs $(NAME) $(OBJS)
	@echo "$(MAGENTA)$(ITALIC)get_next_line compiled!✅$(RESET)"

clean:
	@echo "$(YELLOW)Removing object files . . .$(RESET)"
	@rm -rf $(OBJ_PATH)
	
fclean:clean
	@echo "$(YELLOW)Removing get_next_line. . ."
	@rm -f $(NAME)
	@echo "$(GREEN)$(INVERT)Completed$(RESET)"

re:fclean all

.PHONY: all clean fclean re
