# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maxgarci <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/28 18:51:22 by maxgarci          #+#    #+#              #
#    Updated: 2025/02/24 10:45:31 by maxgarci         ###   ########.fr        #
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

CC 					:= cc
CFLAGS 				:= -g -Wall -Wextra -Werror 
INCLUDES 			:= -I./include -I./libft #-fsanitize=address
LIBRARIES			:= -lreadline 

LIBFT_PATH			:= libft/
LIBFT				:= $(LIBFT_PATH)libft.a

SRC_PATH			:= src/
SRC 				:= main.c print_error.c env_vars.c builts.c echo.c \
						cd.c free.c list_utils.c list_utils_two.c pwd.c export.c \
						unset.c print_lists.c export_two.c exit.c cd_update.c \
						count_pipes.c parsing.c export_utils.c \
						translate_str.c invalid_character.c init_node.c \
						process_command.c node_creation.c execute_one_command.c \
						execute_commands.c delete_backslash.c signals.c expand.c \
						expand_utils.c heredoc.c

SRCS				:= $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH			:= obj/
OBJ 				:= $(SRC:.c=.o)
OBJS				:= $(addprefix $(OBJ_PATH), $(OBJ))

INCL				:= include/minishell.h

all: $(LIBFT) $(NAME)

#bonus: $(NAME_BONUS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo " $(BLUE)COMPILING $(YELLOW)$(ITALIC) $^ $(CYAN) to $(YELLOW)$(ITALIC)$@\n"

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJS): $(OBJ_PATH)

$(LIBFT):
	@echo "Libft being created . . ."
	@make -C $(LIBFT_PATH)
	@echo "Libft created!✅"

$(NAME): $(OBJS)
	@echo "\n $(BLUE)---------------------------------------------\n"
	@echo " $(CYAN)LINKING$(YELLOW)$(ITALIC) $(SRCS) libft.a $(CYAN) to $(YELLOW)$(ITALIC) $(NAME)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME) $(LIBRARIES)
	@echo "$(MAGENTA)$(ITALIC)Minishell compiled!✅$(RESET)"

clean:
	@echo "$(YELLOW)Removing object files . . .$(RESET)"
	@make clean -C $(LIBFT_PATH)
	@rm -rf $(OBJ_PATH)
	
fclean:clean
	@echo "$(YELLOW)Removing minishell . . ."
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@echo "$(GREEN)$(INVERT)Completed$(RESET)"

re:fclean all

norm:
	@echo "$(BLUE)$(DIM)LIBFT$(RESET)"
	@norminette libft/*.c libft/*.h
	@echo "$(GREEN)Completed!$(RESET)"
	@echo
	@echo "$(BLUE)$(DIM)SRC$(RESET)"
	@norminette $(SRCS) $(INCL)
	@echo "$(GREEN)Completed!$(RESET)"

.PHONY: all clean fclean re
