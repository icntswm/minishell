# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/26 17:38:29 by fkenned           #+#    #+#              #
#    Updated: 2021/11/12 18:11:44 by fkenned          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re bonus

SRCS	=	ft_atoi.c		\
            ft_bzero.c		\
            ft_calloc.c		\
            ft_isalnum.c	\
            ft_isalpha.c	\
			ft_isascii.c	\
			ft_isdigit.c	\
			ft_isprint.c	\
			ft_memccpy.c	\
			ft_memchr.c		\
			ft_memcmp.c		\
			ft_memcpy.c		\
			ft_memmove.c	\
			ft_memset.c		\
			ft_strchr.c		\
			ft_strdup.c		\
			ft_strlen.c		\
			ft_strlcat.c	\
			ft_strlcpy.c	\
			ft_strnstr.c	\
			ft_strncmp.c	\
			ft_strrchr.c	\
			ft_tolower.c	\
			ft_toupper.c	\
			ft_substr.c		\
			ft_strjoin.c	\
			ft_strtrim.c	\
			ft_putchar_fd.c	\
			ft_putstr_fd.c	\
			ft_putendl_fd.c	\
			ft_putnbr_fd.c	\
			ft_strmapi.c	\
			ft_itoa.c		\
			ft_split.c		
	
B_SRCS	=	ft_lstnew.c		\
			ft_lstadd_front.c	\
			ft_lstsize.c	\
			ft_lstlast.c	\
			ft_lstadd_back.c	\
			ft_lstdelone.c	\
			ft_lstiter.c

OBJS	=	${SRCS:.c=.o}

L_HEAD	=	libft.h

B_OBJS	=	${B_SRCS:.c=.o}

NAME	=	libft.a
RM		=	rm -f
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

%.o: %.c	${L_HEAD}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			ar rc ${NAME} ${OBJS}
			ranlib ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS} ${B_OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

bonus:		${OBJS} ${B_OBJS}
			ar rc ${NAME} ${OBJS} ${B_OBJS}
			ranlib ${NAME}
