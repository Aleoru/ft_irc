/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:00:08 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/25 19:39:48 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

# include <iostream>
# include <vector>
# include <iterator>
# include <algorithm>
# include <sstream>
# include <errno.h>
# include <netdb.h>
# include <poll.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h> 
# include <sys/poll.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <signal.h>
# include <ctime>
# include <cmath>

# define NUMPHRASES 11

class   Bot 
{
private:
	std::string	_ipAdd;
	std::string _pass;
	std::string _nickname;
	std::string _user;
	int         _ircSock;
	int			_port;
	std::vector<std::string> _dialogues;
	Bot();

public:
	Bot(std::string ip, int port, std::string pass, std::string nick);
	~Bot();
	
	void    	connectBot();
	void		working();

	int			sendMessage(int fd, const std::string str);

	/*PARSER*/
	void		parser(std::string reply);
	std::string	findNickname(std::string str);
	std::string	joinMessage(std::vector<std::string> str, int pos);
};

#endif