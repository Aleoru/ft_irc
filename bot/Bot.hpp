/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:00:08 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/21 05:15:11 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

# include <iostream>
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

class   Bot 
{
private:
	std::string	_ipAdd;
	std::string _pass;
	std::string _nickname;
	std::string _user;
	int         _ircSock;
	int			_port;
	Bot();

public:
	Bot(std::string ip, int port, std::string pass, std::string nick);
	~Bot();
	
	void    	connectBot();
	void		workingBot();
	int			sendMessage(int fd, const std::string str);
};

#endif