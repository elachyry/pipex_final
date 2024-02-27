# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 14:39:33 by melachyr          #+#    #+#              #
#    Updated: 2024/02/27 01:36:53 by melachyr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
SRCS = mandatory/libft/ft_split.c mandatory/libft/ft_split_2.c mandatory/libft/ft_strlen.c mandatory/libft/ft_strdup.c mandatory/libft/ft_substr.c\
	   mandatory/libft/ft_strjoin.c mandatory/libft/ft_strncmp.c mandatory/libft/ft_strchr.c mandatory/libft/ft_strrchr.c mandatory/libft/ft_putstr_fd.c\
	   mandatory/exceptions/exceptions.c mandatory/in_cmd/get_in_cmd_location.c mandatory/in_cmd/get_in_cmd.c mandatory/out_cmd/get_out_cmd_location.c\
	   mandatory/out_cmd/get_out_cmd.c mandatory/in_cmd/in_cmd_process.c mandatory/out_cmd/out_cmd_process.c\
	   mandatory/pipex.c mandatory/init_vars.c
SRCSB = bonus/libft/ft_split.c bonus/libft/ft_isalpha.c bonus/libft/ft_split_2.c bonus/libft/ft_strlen.c bonus/libft/ft_strdup.c bonus/libft/ft_substr.c bonus/libft/ft_strcmp.c\
	   bonus/libft/ft_strjoin.c bonus/libft/ft_strncmp.c bonus/libft/ft_strchr.c bonus/libft/ft_strrchr.c bonus/libft/ft_putstr_fd.c\
	   bonus/exceptions/exceptions.c bonus/utils/get_cmd_location.c bonus/utils/get_cmd.c bonus/utils/processes.c bonus/utils/pipes.c bonus/utils/cmds.c\
	   bonus/get_next_line/get_next_line.c bonus/get_next_line/get_next_line_utils.c\
	   bonus/pipex.c bonus/init_vars.c

OBJS = $(SRCS:.c=.o)
OBJSB = $(SRCSB:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
all: $(NAME)

$(NAME): $(OBJS) #-fsanitize=address -g3
	$(CC) $(CFLAGS) $(OBJS) -o $@

bonus: $(OBJSB) #-fsanitize=address -g3
	$(CC)  $(CFLAGS) $(OBJSB) -o $(NAME)

clean:
	rm -f $(OBJS) $(OBJSB)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re