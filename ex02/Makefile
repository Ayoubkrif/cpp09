# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/17 12:32:52 by aykrifa           #+#    #+#              #
#                                                                              #
# **************************************************************************** #

# directories
SRC_DIR   = sources
CLASS_DIR = classes
OBJ_DIR   = build

# Sources files listing
SRC_FILES = \
	main.cpp \
	\

# Classes files listing
CLASS_FILES = \
	PmergeMe/PmergeMe.cpp \
	\

CLASSES = $(addprefix $(CLASS_DIR)/, $(CLASS_FILES))
SOURCES = $(addprefix $(SRC_DIR)/,$(SRC_FILES))

# include directories
INC_DIR = \
	includes \
		$(CLASS_DIR)/PmergeMe \

##################################################################################
#compilation
NAME		= PmergeMe
CC			= c++
CFLAGS 		= -Wall -Wextra -Werror -std=c++98 -MMD -MP -g3
PREPROC		=
INCLUDES	= $(addprefix -I, $(INC_DIR))

# Objets (même structure que SOURCES ou CLASSES mais dans objs/)
OBJS = $(CLASSES:%.cpp=$(OBJ_DIR)/%.o) \
		$(SOURCES:%.cpp=$(OBJ_DIR)/%.o)

DEPS = $(OBJS:.o=.d)

all: $(NAME)
.PHONY: all

# LINK
$(NAME): $(OBJS)
	$(CC) $(OBJS) \
		-o $@

#compilation
$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(INCLUDES) \
		$< -o $@

# COMMENT
-include $(DEPS)

clean:
	rm -rf $(OBJ_DIR)
.PHONY: clean

fclean: clean
	rm -f $(NAME)
.PHONY: fclean

re: fclean
	make all
.PHONY: re

bear:
	bear -- make re
.PHONY: bear

test:
	SHUF=$(echo '11 2 17 0 16 8 6 15 10 3 21 1 18 9 14 19 12 5 4 20 13 7')
	/home/aykrifa/Desktop/repo/cpp09/ex02/PmergeMe $SHUF
	/home/aykrifa/Downloads/cpp09/ex02/PmergeMe $SHUF

shuf:
	SHUF=$(shuf -i 0-9 -n 10)
	/home/aykrifa/Desktop/repo/cpp09/ex02/PmergeMe $SHUF
	/home/aykrifa/Downloads/cpp09/ex02/PmergeMe $SHUF

