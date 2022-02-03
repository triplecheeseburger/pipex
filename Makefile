# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 19:37:01 by hakim             #+#    #+#              #
#    Updated: 2022/01/28 00:50:50 by hakim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror 

NAME = mandatory/pipex
SRCS =	mandatory/pipex.c \
		mandatory/utils.c \
		mandatory/str_utils.c \
		mandatory/ft_split.c 
OBJS = $(SRCS:%.c=%.o)
BONUS_NAME = bonus/pipex
BONUS_SRCS = bonus/pipex_bonus.c \
			 bonus/utils_bonus.c \
			 bonus/str_utils_bonus.c \
			 bonus/ft_split_bonus.c \
			 bonus/get_next_line_bonus.c \
			 bonus/get_next_line_utils_bonus.c
BONUS_OBJS = $(BONUS_SRCS:%.c=%.o)
HDR = ./includes
INCLUDES = -I$(HDR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: fclean all clean re bonus
