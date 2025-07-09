# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 19:33:31 by tmuranak          #+#    #+#              #
#    Updated: 2024/05/05 13:47:32 by tmuranak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAG = -Wextra -Werror -Wall
BSCSRC = \
ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isspace.c\
ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c \
ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
ft_substr.c ft_tolower.c ft_toupper.c
BNSSRC = \
ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
MINESRC = \
	  ft_streq.c
NAME = libft.a


SOURCES = $(BSCSRC) $(MINESRC)
ifdef BONUS_FLAG
	SOURCES += $(BNSSRC)
endif
OBJ = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME):$(OBJ)
	ar -rcs $@ $^

bonus:
	@make BONUS_FLAG=1

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -f $(BSCSRC:.c=.o) $(BNSSRC:.c=.o)

fclean: clean
	rm -f $(NAME)

re: fclean
	make
