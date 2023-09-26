# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alumno <alumno@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/24 18:03:25 by ybouhaik          #+#    #+#              #
#    Updated: 2023/09/26 00:04:06 by alumno           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_printf.c ft_putnbr_base.c

OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJS)
	make -C Libft
	mv Libft/libft.a Ft_printf
	ar -rcs  $(NAME) $(OBJS)

clean:
	rm -f *.o
	rm -f Libft/*.o

fclean: clean 
	rm -f $(NAME)
	rm -f libft.a

re: fclean all

.PHONY: all clean fclean re
