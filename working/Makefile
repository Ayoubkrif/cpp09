GREEN  = \033[1;32m
RED    = \033[1;31m
VIOLET = \033[1;35m
ORANGE = \033[38;5;208m
BLEU   = \033[1;34m
JAUNE  = \033[1;33m
ROSE   = \033[1;95m
RESET  = \033[0m
NAME = PmergeMe

SRCS = main.cpp PmergeMe.cpp
OBJS = $(SRCS:.cpp=.o)
CFLAGS = -std=c++98 -Werror -Wall -Wextra 
CC = c++

all : $(NAME)

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) && \
	echo "$(GREEN)🔥Compilation done!🔥$(RESET)" || \
	{ echo "$(RED)Compilation failed!$(RESET)"; exit 1; }

clean :
	@rm -rf $(OBJS)
	@echo "$(JAUNE)​🧼🧼 OBJS cleaned all! 🧼​🧼$(RESET)"

fclean : clean
	@rm -rf $(OBJS) $(NAME)
	@echo "$(VIOLET)​🧼​🧼​🧼🧼 Successfully cleaned all! 🧼​​🧼​​🧼​🧼$(RESET)"

shuf:
	SHUF="$$(shuf -i 0-999 -n 1000)" && \
	./$(NAME)	$$SHUF

re : fclean $(NAME)

.PHONY: all clean fclean re
