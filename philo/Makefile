# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/15 11:41:59 by ien-niou          #+#    #+#              #
#    Updated: 2025/03/15 11:41:59 by ien-niou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc 
FLAGS = -Wall -Wextra -Werror

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
CYAN = \033[0;36m
RESET = \033[0m

HEADERS = philo.h
MAIN = philo.c

SRC = atoi.c validInput.c inits.c actions.c utils.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(MAIN) $(OBJS)
	@$(CC) $(FLAGS) $(MAIN) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Compilation successful!$(RESET)"

%.o: %.c $(HEADERS)
	@echo "\033[0;36m"
	$(CC) $(FLAGS) -c $< -o $@
	clear 

clean:
	@rm -rf $(OBJS)
	@echo "$(YELLOW)Object files removed.$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)Executable removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re  
