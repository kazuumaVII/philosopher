# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/27 17:23:26 by frfrance          #+#    #+#              #
#    Updated: 2021/03/08 18:27:16 by frfrance         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one
SRCSDIR = srcs
OBJSDIR = .objs
SRCS = main.c\
		utile.c\
		init.c\
		routine.c\
		prsg.c \
		print.c

INCLUDES = -I .
OBJS = $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))
DPDCS = $(OBJS:.o=.d)
LIB = -lpthread
CFLAGS = -Wall -Wextra -Werror -pthread

opti :
	@(make -j all)

all : $(NAME)

-include $(DPDCS)

$(NAME) : $(OBJS)
	@(gcc $(CFLAGS) $(LIB) $(INCLUDES) $(OBJS) -o $(NAME))
	@(echo "$(NAME) created")

fg : $(OBJS)
	@(gcc $(CFLAGS) -g3 -fsanitize=address $(LIB) $(INCLUDES) $(OBJS) -o $(NAME))
	@(echo "$(NAME) created")

$(OBJSDIR)/%.o : $(SRCSDIR)/%.c | $(OBJSDIR)
	@(echo "Compiling -> $^")
	@(gcc $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@)

$(OBJSDIR) :
	@(mkdir -p .objs)

clean :
	@(rm -f $(NAME))

fclean: clean
	@(rm -rf $(OBJSDIR))

re : fclean all
