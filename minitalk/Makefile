# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yassine <yassine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/01 14:20:25 by ybouhaik          #+#    #+#              #
#    Updated: 2024/04/05 15:14:12 by yassine          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
MAGENTA = \033[35;1m
RESET   = \033[0m
GRAY 	= \033[0;90m
CYAN    = \033[37;1m
BOLD	= \033[1m
RED		= \033[31;1m
GREY	= $'\x1b[30m
GREEN	= $'\x1b[32m
YELLOW	= $'\x1b[33m
BLUE	= $'\x1b[34m
PURPLE	= $'\x1b[35m
CYAN	= $'\x1b[36m
WHITE	= $'\x1b[37m

# Styles
RESET	= \033[0m
BOLD	= \033[1m
DIM		= \033[2m
ITALIC	= \033[3m
UNDER	= \033[4m
INVERT	= \033[7m
DASH	= \033[9m

NAME_SERVER					    := server
NAME_CLIENT					    := client
NAME_SERVER_BONUS				:= server_bonus
NAME_CLIENT_BONUS				:= client_bonus
cc 								:= gcc
flags 							:= -g -Wall -Wextra -Werror
SRCS_CLIENT 					:= src/client.c 
SRCS_SERVER 					:= src/server.c
SRCS_CLIENT_BONUS 				:= src/client_bonus.c 
SRCS_SERVER_BONUS				:= src/server_bonus.c
OBJS_SERVER					    := $(SRCS_SERVER:.c=.o)
OBJS_CLIENT					    := $(SRCS_CLIENT:.c=.o)
OBJS_SERVER_BONUS				:= $(SRCS_SERVER_BONUS:.c=.o)
OBJS_CLIENT_BONUS				:= $(SRCS_CLIENT_BONUS:.c=.o)
INCL							:= include/.h

all: $(NAME_SERVER) $(NAME_CLIENT)
bonus: $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

%.o: %.c $(INCL)
	@gcc $(FLAGS) -c $< -o $@
	@echo " $(CYAN)COMPILING $(YELLOW) $^ $(CYAN) to $(YELLOW)$@\n"

$(NAME_SERVER):$(OBJS_SERVER)
	@echo "\n $(BLUE)---------------------------------------------\n"
	@echo " $(CYAN)LINKING$(YELLOW) $(SRCS_SERVER) libft.a $(CYAN) to $(YELLOW) $(NAME_SERVER)\n"
	@make -C libft
	@mv libft/libft.a .
	@$(cc) $(flags) $(OBJS_SERVER) libft.a -o $(NAME_SERVER)
	@echo "$(MAGENTA)$(ITALIC) compiled!$(RESET)"

$(NAME_CLIENT):$(OBJS_CLIENT)
	@echo " \n$(BLUE)---------------------------------------------\n"
	@echo " $(CYAN)LINKING$(YELLOW) $(SRCS_CLIENT) libft.a $(CYAN) to $(YELLOW) $(NAME_CLIENT)\n"
	@make -C libft
	@mv libft/libft.a .
	@$(cc) $(flags) $(OBJS_CLIENT) libft.a -o $(NAME_CLIENT)
	@echo "$(MAGENTA)$(ITALIC) compiled!$(RESET)"

$(NAME_SERVER_BONUS):$(OBJS_SERVER_BONUS)
	@echo " \n$(BLUE)---------------------------------------------\n"
	@echo " $(CYAN)LINKING$(YELLOW) $(SRCS_SERVER_BONUS) libft.a $(CYAN) to $(YELLOW) $(NAME_SERVER_BONUS)\n"
	@make -C libft
	@mv libft/libft.a .
	@$(cc) $(flags) $(OBJS_SERVER_BONUS) libft.a -o $(NAME_SERVER_BONUS)
	@echo "$(MAGENTA)$(ITALIC) compiled!$(RESET)"

$(NAME_CLIENT_BONUS):$(OBJS_CLIENT_BONUS)
	@echo " \n$(BLUE)---------------------------------------------\n"
	@echo " $(CYAN)LINKING$(YELLOW) $(SRCS_CLIENT_BONUS) libft.a $(CYAN) to $(YELLOW) $(NAME_CLIENT_BONUS)\n"
	@make -C libft
	@mv libft/libft.a .
	@$(cc) $(flags) $(OBJS_CLIENT_BONUS) libft.a -o $(NAME_CLIENT_BONUS)
	@echo "$(MAGENTA)$(ITALIC) compiled!$(RESET)"

clean:
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER)
	@echo "$(YELLOW)Cleaning...$(RESET)"
	@$(MAKE) -C libft clean
	@rm -f src/*.o
	@rm -f libft.a
	

fclean:clean
	@/bin/rm -f $(NAME_CLIENT)
	@/bin/rm -f $(NAME_SERVER)
	@/bin/rm -f $(NAME_CLIENT_BONUS)
	@/bin/rm -f $(NAME_SERVER_BONUS)
	@echo "$(GREEN)$(INVERT)Completed$(RESET)"

re:fclean all


norm:
	@echo "$(RED)$(BOLD)NORMINETTE$(RESET)"
	@echo "$(BLUE)$(DIM)LIBFT$(RESET)"
	@norminette libft/*.c libft/*.h
	@echo "$(GREEN)Completed!$(RESET)"
	@echo
	@echo "$(BLUE)$(DIM)SRC$(RESET)"
	@norminette src/*.c include/*.h
	@echo "$(GREEN)Completed!$(RESET)"

.PHONY: all utils clean fclean re
