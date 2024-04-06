/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:58:27 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/04/06 12:32:32 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <vector>
# include "User.hpp"
# include "Channel.hpp"
# include "sockets.h"

# define RED "\e[1;31m"		// red color
# define WHI "\e[0;37m"		// white color
# define GRE "\e[1;32m"		// green color
# define YEL "\e[1;33m"		// yellow color

class User;
class Channel;

class Server										
{
private:
	int 							_port;				// server port
	int								_serverFd;			// server socket file descriptor
	std::string						_pass;				// server password
	std::vector<User>				_users;				// vector of user/clients
	std::vector<struct pollfd>		_fds;				// vector of pollfd
	std::vector<Channel> 			_channels;			// vercotr fo channels
	static bool						_signal;			// static boolean for signal
	
public:
	Server(int port, std::string pass);						
	~Server();

	void serverInit();									// server initialization
	void configServerSocket();							// server socket creation
	void acceptNewUser();								// accept new user/client
	void receiveNewData(int fd);						// receive new data from a registered user
	int	 sendMessage(int fd, const std::string str);	// send message to a user

 
	void closeFds();									// close file descriptors
	void clearClients(int fd);							// clear clients

	static void signalHandler(int signum); 				// signal handler
	static int	validPort(const std::string port);		// check if it is a valid port
	static int	validPass(const std::string pass);		// check if it is a valid pass
	
	//debug
	void printUsers();
};

#endif
