# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/08 11:06:32 by aoropeza          #+#    #+#              #
#    Updated: 2024/04/08 11:20:29 by aoropeza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= irc_server
SRCDIR	= src
OBJDIR	= obj
INCDIR	= inc

SRC		:= $(wildcard $(SRCDIR)/*.cpp)
OBJS	:= $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
INC		= -I
INCFILES := $(wildcard $(INC)/*.h*)
#INC		= -I Server.hpp -I User.hpp -I Channel.hpp -I sockets.h

CC		= c++
CPPFLAGS = -Wall -Werror -Wextra -std=c++98
RM		= rm -rf

UNAME	= $(shell uname -s)

ifeq ($(UNAME), Linux)
CPPFLAGS = -Wall -Wextra
$(warning Linux detected! Disabling -Werror and -std=c++98...)
endif

BOLD	= \033[1m
RED		= \033[31;1m
GREEN	= \033[32;1m
YELLOW	= \033[33;1m
CYAN	= \033[36;1m
WHITE	= \033[37;1m
RESET	= \033[0m

all : $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME) && printf "$(GREEN)$(BOLD)Your $(NAME) is ready!\n$(RESET)"

obj/%.o : src/%.cpp $(INCFILES)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(@D)
	@$(CC) $(CPPFLAGS) -o $@ -c $< -I $(INC) && printf "$(WHITE)$(BOLD)\rCompiling: \
	$(CYAN)$(notdir $@)$(GREEN)\r\e[35C[OK]\n$(RESET)"

clean :
	@$(RM) $(OBJDIR) && printf "$(GREEN)$(BOLD)All objects cleaned! :)\n$(RESET)"

fclean : clean
	@$(RM) $(NAME) && printf "$(YELLOW)$(NAME) $(GREEN)has been clean \n$(RESET)"

re : fclean all

.PHONY : all clean fclean re