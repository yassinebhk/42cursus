# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yassine <yassine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 11:41:20 by ybouhaik          #+#    #+#              #
#    Updated: 2024/04/07 23:35:34 by yassine          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
		ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
		ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_substr.c \
		ft_strtrim.c ft_split.c ft_strjoin.c ft_substr.c ft_itoa.c ft_strmapi.c \
		ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_round.c ft_atof.c \
		ft_aux.c ft_putnbr_base.c get_next_line_utils_bonus.c get_next_line_bonus.c ft_printf.c ft_putchar2_fd.c ft_putstr2_fd.c

SRCS2 = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS2 = $(SRCS2:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJS)
	@ar -rcs  $(NAME) $(OBJS)

bonus: $(OBJS) $(OBJS2)
	@ar -rcs  $(NAME) $(OBJS2)
clean:
	@rm -f $(OBJS) $(OBJS2)

fclean: clean 
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
