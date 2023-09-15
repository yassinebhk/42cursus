# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 11:41:20 by ybouhaik          #+#    #+#              #
#    Updated: 2023/09/13 11:41:24 by ybouhaik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_substr.c ft_strtrim.c ft_split.c ft_strjoin.c ft_substr.c 
#ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

SRCS2 = 

OBJS = $(SRCS:.c=.o)
OBJS2 = $(SRCS2:.c=.o)
CFLAGS = -Wall -Wextra -Werror

NAME = libft

.PHONY: clean fclean bonus re

all: $(NAME)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJS)
	gcc $(CFLAGS) $(OBJS) -o $(NAME)

bonus:
	gcc $(CFLAGS) $(OBJS2) -o $(NAME)
clean:
	rm -f $(OBJS)

fclean: clean 
	rm -f $(NAME)
