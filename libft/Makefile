#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naali <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/09 11:18:25 by naali             #+#    #+#              #
#    Updated: 2019/12/11 02:12:23 by nabih            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	libft.a

AR			=	ar

ARFLAGS		=	rcs

CC			=	gcc

LIBPATH		=

CFLAGS		+= -I ./
CFLAGS		+= -Wall -Wextra -Werror

SRC			=	ft_atoi.c			ft_bzero.c			ft_isalnum.c		ft_isalpha.c		ft_isascii.c	\
				ft_isdigit.c		ft_isprint.c		ft_memccpy.c		ft_memchr.c			ft_memcmp.c		\
				ft_memcpy.c			ft_memmove.c		ft_memset.c			ft_strcat.c			ft_strchr.c		\
				ft_strcmp.c			ft_strcpy.c			ft_strdup.c			ft_strlcat.c		ft_strlen.c		\
				ft_strncat.c		ft_strncmp.c		ft_strncpy.c		ft_strnstr.c		ft_strrchr.c	\
				ft_strstr.c			ft_tolower.c		ft_toupper.c		ft_memalloc.c		ft_memdel.c		\
				ft_strnew.c			ft_strdel.c			ft_strclr.c			ft_striter.c		ft_striteri.c	\
				ft_strmap.c			ft_strmapi.c		ft_strequ.c			ft_strnequ.c		ft_strsub.c		\
				ft_strjoin.c		ft_strtrim.c		ft_strsplit.c		ft_itoa.c			ft_putchar.c	\
				ft_putstr.c			ft_putendl.c		ft_putnbr.c			ft_putchar_fd.c		ft_putstr_fd.c	\
				ft_putendl_fd.c		ft_putnbr_fd.c		ft_lstnew.c			ft_lstdelone.c		ft_lstdel.c		\
				ft_lstadd.c			ft_lstiter.c		ft_lstmap.c			ft_lstlast.c		ft_lstfind.c	\
				ft_lstsize.c		ft_lstfindsize.c	get_next_line.c		ft_tabcpy.c			ft_swap.c		\
				ft_lstadd_bot.c		ft_lstadd_top.c		ft_square_rec.c		ft_lstdel_contentsize.c

SRCSDIR		=	.

OBJ			=	$(SRC:.c=.o)

all			:	$(NAME)


$(NAME):		$(OBJ) $(LIBPATH)libft.h $(LIBPATH)get_next_line.h
				@$(AR) $(ARFLAGS) $(NAME) $(OBJ)

%.o			:	$(SRCSDIR)/%.c
				@$(CC) -o $@ -c $< $(CFLAGS)

clean		:
				@rm -rf $(OBJ)

fclean		:	clean
				@rm -rf $(NAME)

re			:	fclean all
