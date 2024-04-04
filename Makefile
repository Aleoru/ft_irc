NAME	= irc_server
SRC		= main.cpp Server.cpp User.cpp utils.c
OBJS	= $(SRC:.cpp=.o)
INC		= -I Server.hpp -I User.hpp -I sockets.h
CC		= c++
CFLAGS	= -Wall -Werror -Wextra -std=c++98
RM		= rm -rf
UNAME	= $(shell uname -s)

ifeq ($(UNAME), Linux)
CFLAGS	= -Wall -Wextra
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
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) && printf "$(GREEN)$(BOLD)Your $(NAME) is ready!\n$(RESET)"

%.o : %.cpp
	@$(CC) $(CFLAGS) -o $@ -c $< && printf "$(WHITE)\rCompiling: $(CYAN)$(notdir $@)$(GREEN)\r\e[35C[OK]\n$(RESET)"

clean :
	@$(RM) $(OBJS) && printf "$(YELLOW)All objects have been clean \n$(RESET)"

fclean : clean
	@$(RM) $(NAME) && printf "$(YELLOW)$(NAME) $(GREEN)has been clean \n$(RESET)"

re : fclean all

.PHONY : all clean fclean re