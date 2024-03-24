# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yassine <yassine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/24 18:03:25 by ybouhaik          #+#    #+#              #
#    Updated: 2024/03/23 22:49:57 by yassine          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_printf.c ft_putnbr_base.c ft_aux.c

OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJS)
	@make -C libft
	@mv libft/libft.a $(NAME)
	@ar -rcs $(NAME) $(OBJS)

clean:
	@rm -f *.o
	@rm -f Libft/*.o

fclean: clean 
	rm -f $(NAME)
	rm -f libft.a

re: fclean all

.PHONY: all clean fclean re
