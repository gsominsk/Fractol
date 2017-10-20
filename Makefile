# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsominsk <gsominsk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/10 11:31:38 by gsominsk          #+#    #+#              #
#    Updated: 2017/03/30 12:09:18 by gsominsk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

FLAGS = -Wall -Wextra -Werror -g -O3

FLAGS_MLX = -lmlx -framework OpenGl -framework AppKit

FLAGS_X11 = -lmlx -lXext -lX11 -lm

LIB = lib/libft.a

SRCS = src_fractol/fractol.c src_fractol/fractol_1.c

BINS = $(SRCS:.c=.o)

all: $(NAME)

makelib:
	make -C lib/

libclean:
	make -C lib/ clean

libfclean:
	make -C lib/ fclean

$(NAME): $(BINS)
	make -C lib/
	gcc -o $(NAME) $(BINS) $(FLAGS) $(FLAGS_MLX) $(LIB)

%.o: %.c
	gcc $(FLAGS) -c -o $@ $<

clean: libclean
	/bin/rm -f $(BINS)

fclean: libfclean clean
	/bin/rm -f $(NAME)

re: fclean all
