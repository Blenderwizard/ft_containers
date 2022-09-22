# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrathelo <student.42nice.fr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 15:25:19 by jrathelo          #+#    #+#              #
#    Updated: 2022/09/22 11:10:19 by jrathelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
_BLACK			= \033[0;30m
_RED 			= \033[0;31m
_GREEN			= \033[0;32m
_BROWN			= \033[0;33m
_BLUE			= \033[0;34m
_PURPLE			= \033[0;35m
_CYAN			= \033[0;36m
_LIGHT_GRAY		= \033[0;37m
_DARK_GRAY		= \033[1;30m
_LIGHT_RED		= \033[1;31m
_LIGHT_GREEN	= \033[1;32m
_YELLOW			= \033[1;33m
_LIGHT_BLUE		= \033[1;34m
_LIGHT_PURPLE	= \033[1;35m
_LIGHT_CYAN		= \033[1;36m
_WHITE			= \033[1;37m
_NC 			= \033[0m

# Inverted, i.e. colored backgrounds
_IGREY			= \x1b[40m
_IRED			= \x1b[41m
_IGREEN			= \x1b[42m
_IYELLOW		= \x1b[43m
_IBLUE			= \x1b[44m
_IPURPLE		= \x1b[45
_ICYAN			= \x1b[46m
_IWHITE			= \x1b[47m

# Color reset
_COLOR_RESET	= \033[0m

# Folders
INCLUDES = -I./includes
SRC_DIR = src
MY_OUTS = objs/ft
STL_OUTS = objs/stl

# Source Files
SRC = main.cpp
SRC_PLUS_PATH = $(addprefix $(SRC_DIR)/, $(SRC))

# Output Files
MY_OUT = $(subst $(SRC_DIR)/, $(MY_OUTS)/, $(patsubst %.cpp, %.opp, $(SRC_PLUS_PATH)))
STL_OUT = $(subst $(SRC_DIR)/, $(STL_OUTS)/, $(patsubst %.cpp, %.opp, $(SRC_PLUS_PATH)))

MY_NAME = my_container
STL_NAME = stl_container

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g #-O3 -fsanitize=address

all : $(MY_NAME) $(STL_NAME)

$(MY_NAME): $(MY_OUT)
	@echo "$(_PURPLE)Linking $(MY_NAME)$(_COLOR_RESET)"
	@$(CC) $(CFLAGS) $(MY_OUT) -o $(MY_NAME) $(INCLUDES)
	@echo "$(_GREEN)DONE$(_COLOR_RESET)"

$(STL_NAME): $(STL_OUT)
	@echo "$(_PURPLE)Linking $(STL_NAME)$(_COLOR_RESET)"
	@$(CC) $(CFLAGS) $(STL_OUT) -o $(STL_NAME) $(INCLUDES)
	@echo "$(_GREEN)DONE$(_COLOR_RESET)"

$(MY_OUT): $(MY_OUTS)/%.opp : $(SRC_DIR)/%.cpp
	@echo "$(_CYAN)Compiling $(basename $(notdir $*.opp)) $(_COLOR_RESET)"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(STL_OUT): $(STL_OUTS)/%.opp : $(SRC_DIR)/%.cpp
	@echo "$(_CYAN)Compiling $(basename $(notdir $*.opp)) $(_COLOR_RESET)"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -D STD -c $< -o $@ $(INCLUDES)

re: fclean
	@make $(MY_NAME)
	@make $(STL_NAME)

fclean: clean
	@echo "$(_RED)Cleaning output files$(_COLOR_RESET)"
	@rm -rf $(MY_NAME)
	@rm -rf $(STL_NAME)

clean:
	@echo "$(_RED)Cleaning object files$(_COLOR_RESET)"
	@rm -rf $(MY_OUTS)
	@rm -rf $(STL_OUTS)
	
.PHONY: clean fclean re all