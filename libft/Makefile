# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkerob <vkerob@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 14:11:42 by vkerob            #+#    #+#              #
#    Updated: 2024/08/02 15:34:48 by vkerob           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = clang

CFLAGS = -Wall -Wextra -Werror -fPIC

NAME = libft.a

SRC = ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isascii.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_is_plus_or_minus.c \
		ft_free_tab.c \
		ft_isspace.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memset.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strjoin_free.c \
		ft_strlcat.c \
		ft_substr.c \
		ft_memcpy.c \
		ft_itoa.c \
		ft_strtrim.c \
		ft_memmove.c \
		ft_strmapi.c \
		ft_split.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		get_next_line/get_next_line_bonus.c \
		get_next_line/get_next_line_utils_bonus.c \
		ft_printf/ft_printf.c \
		ft_printf/ft_putchar_ct.c \
		ft_printf/ft_putstr_ct.c \
		ft_printf/ft_putnbr_ct_1.c \
		ft_printf/ft_putnbr_ct_2.c \
		ft_printf/ft_adress.c \
		ft_printf/ft_strlen.c 

OBJ = $(SRC:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) 

all : $(NAME)

$(NAME) : $(OBJ)
	ar -rc  $(NAME) $(OBJ)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
