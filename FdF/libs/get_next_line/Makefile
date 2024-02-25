# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/24 18:03:25 by ybouhaik          #+#    #+#              #
#    Updated: 2024/02/25 17:43:45 by ybouhaik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = getnextline.a

SRCS = get_next_line.c get_next_line_utils.c

BONUS_SRCS = get_next_line_bonus.c get_next_line_utils_bonus.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

clean:
	rm -f *.o

fclean: clean 
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
