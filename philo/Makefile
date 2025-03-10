NAME = philo
CC = cc 
FLAGS = -Wall -Wextra -Werror # -g -fsanitize=thread -pthread 

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
CYAN = \033[0;36m
RESET = \033[0m

HEADERS = philo.h
MAIN = philo.c

SRC = atoi.c validInput.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(MAIN) $(OBJS)
	@$(CC) $(FLAGS) $(MAIN) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Compilation successful!$(RESET)"

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@echo "$(YELLOW)Object files removed.$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)Executable removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re  
