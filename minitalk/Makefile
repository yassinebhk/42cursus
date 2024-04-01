# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/01 14:20:25 by ybouhaik          #+#    #+#              #
#    Updated: 2024/04/01 14:20:27 by ybouhaik         ###   ########.fr        #
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

NAME_SERVIDOR				:= servidor
NAME_CLIENTE				:= cliente
#NAME_SERVIDOR_BONUS				:= servidor_bonus
#NAME_CLIENTE_BONUS				:= cliente_bonus
cc 					:= gcc
flags 				:= -g -Wall -Wextra -Werror
SRCS_CLIENTE 				:= src/cliente.c 
SRCS_SERVIDOR 				:= src/servidor.c
#SRCS_BONUS 			:= src/cliente_bonus.c src/servidor_bonus.c
OBJS_SERVIDOR				:= $(SRCS_SERVIDOR:.c=.o)
OBJS_CLIENTE				:= $(SRCS_CLIENTE:.c=.o)
#OBJS_BONUS 			:=$(SRCS_BONUS:.c=.o)
INCL				:= include/.h

all: $(NAME_SERVIDOR) $(NAME_CLIENTE)

#bonus: $(NAME_SERVIDOR_BONUS) $(NAME_CLIENTE_BONUS)

%.o: %.c $(INCL)
	@gcc $(FLAGS) -c $< -o $@
	@echo " $(CYAN)COMPILING $(YELLOW) $^ $(CYAN) to $(YELLOW)$@\n"

$(NAME_SERVIDOR):$(OBJS_SERVIDOR)
	@echo " \n$(BLUE)---------------------------------------------\n"
	@echo " $(CYAN)LINKING$(YELLOW) $(SRCS_SERVIDOR) libft.a $(CYAN) to $(YELLOW) $(NAME_SERVIDOR)\n"
	@make -C libft
	@mv libft/libft.a .
	@$(cc) $(flags) $(OBJS_SERVIDOR) libft.a -o $(NAME_SERVIDOR)
	@echo "$(MAGENTA)$(ITALIC) compiled!$(RESET)"

$(NAME_CLIENTE):$(OBJS_CLIENTE)
	@echo " \n$(BLUE)---------------------------------------------\n"
	@echo " $(CYAN)LINKING$(YELLOW) $(SRCS_CLIENTE) libft.a $(CYAN) to $(YELLOW) $(NAME_CLIENTE)\n"
	@make -C libft
	@mv libft/libft.a .
	@$(cc) $(flags) $(OBJS_CLIENTE) libft.a -o $(NAME_CLIENTE)
	@echo "$(MAGENTA)$(ITALIC) compiled!$(RESET)"

# $(NAME_SERVIDOR_BONUS):$(OBJS_BONUS)
# 	@echo " \n$(BLUE)---------------------------------------------\n"
# 	@echo " $(CYAN)LINKING$(YELLOW) $(OBJS_BONUS) libft.a $(CYAN) to $(YELLOW) $(NAME_SERVIDOR_BONUS)\n"
# 	@make -C libft
# 	@mv libft/libft.a .
# 	@$(cc) $(flags) $(OBJS_BONUS) libft.a -o $(NAME_SERVIDOR_BONUS)
# 	@echo "$(MAGENTA)$(ITALIC) compiled!$(RESET)"

# $(NAME_CLIENTE_BONUS):$(OBJS_BONUS)
# 	@echo " \n$(BLUE)---------------------------------------------\n"
# 	@echo " $(CYAN)LINKING$(YELLOW) $(OBJS_BONUS) libft.a $(CYAN) to $(YELLOW) $(NAME_CLIENTE_BONUS)\n"
# 	@make -C libft
# 	@mv libft/libft.a .
# 	@$(cc) $(flags) $(OBJS_BONUS) libft.a -o $(NAME_CLIENTE_BONUS)
# 	@echo "$(MAGENTA)$(ITALIC) compiled!$(RESET)"

clean:
	rm -f $(OBJS_CLIENTE) $(OBJS_SERVIDOR)
	@echo "$(YELLOW)Cleaning...$(RESET)"
	@$(MAKE) -C libft clean
	@rm -f src/*.o
	@rm -f libft.a
	

fclean:clean
	@/bin/rm -f $(NAME_CLIENTE)
	@/bin/rm -f $(NAME_SERVIDOR)
	@echo "$(GREEN)$(INVERT)Completed$(RESET)"

re:fclean all

# @/bin/rm -f $(NAME_CLIENTE_BONUS)
# @/bin/rm -f $(NAME_SERVIDOR_BONUS)

norm:
	@echo "$(RED)$(BOLD)NORMINETTE$(RESET)"
	@echo "$(BLUE)$(DIM)LIBFT$(RESET)"
	@norminette libft/*.c libft/*.h
	@echo "$(GREEN)Completed!$(RESET)"
	@echo
	@echo "$(BLUE)$(DIM)SRC$(RESET)"
	@norminette src/*.c include/$(NAME).h
	@echo "$(GREEN)Completed!$(RESET)"

ascii:
	@echo "$(MAGENTA)$(BOLD)"
	@echo "                                            "
	@echo " #########      #########         ######### "
	@echo " ##             ##      ##        ##        "
	@echo " ##             ##       ##       ##        "
	@echo " #########      ##        ##      ######### "
	@echo " ##             ##       ##       ##        "
	@echo " ##             ##      ##        ##        "
	@echo " ##             ##     ##         ##        "
	@echo " ##             #######           ##        "
	@echo "                                            "
	@echo "$(RESET)"


.PHONY: all utils clean fclean re
