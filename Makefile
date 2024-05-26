# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/08 11:06:32 by aoropeza          #+#    #+#              #
#    Updated: 2024/05/26 23:30:57 by aoropeza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= irc_server
SRCDIR	= src
OBJDIR	= obj
BOTDIR	= bot
INCDIR	= inc

SRC		:= $(wildcard $(SRCDIR)/*.cpp)
OBJS	:= $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
INC		= -I
INCFILES := $(wildcard $(INC)/*.h*)
#INC		= -I Server.hpp -I User.hpp -I Channel.hpp -I sockets.h

CC		= g++
CPPFLAGS = -g -Wall -Werror -Wextra -std=c++98
RM		= rm -rf

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

bonus:
	$(MAKE) -C $(BOTDIR)
	@./$(BOTDIR)/Botito 127.0.0.1 5555 hola bot

obj/%.o : src/%.cpp $(INCFILES)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(@D)
	@$(CC) $(CPPFLAGS) -o $@ -c $< -I $(INC) && printf "$(WHITE)$(BOLD)\rCompiling: \
	$(CYAN)$(notdir $@)$(GREEN)\r\e[35C[OK]\n$(RESET)"

clean :
	@$(RM) $(OBJDIR) && printf "$(GREEN)$(BOLD)All objects cleaned! :)\n$(RESET)"
	$(MAKE) -C $(BOTDIR) clean

fclean : clean
	@$(RM) $(NAME) && printf "$(YELLOW)$(NAME) $(GREEN)has been clean \n$(RESET)"
	$(MAKE) -C $(BOTDIR) fclean

re : fclean all

.PHONY : all clean fclean re