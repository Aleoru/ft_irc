/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:58:15 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/04/04 00:48:52 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port, std::string pass) : _port(port), _pass(pass)
{
	std::cout << "Server created" << std::endl;
	std::cout << "port: " << _port << std::endl;
	std::cout << "pass: " << _pass << std::endl;
}

Server::~Server()
{
	std::cout << "Server deleted" << std::endl;
}

// clear the clients
void Server::clearClients(int fd)
{
	// remove the client from the pollfd
	for(size_t i = 0; i < _fds.size(); i++)
	{ 
		if (_fds[i].fd == fd)
		{
			_fds.erase(_fds.begin() + i); 
			break;
		}
 	}
	// remove the client from the vector of clients
 	for(size_t i = 0; i < _users.size(); i++)
	{ 
		if (_users[i].getFd() == fd)
		{
			_users.erase(_users.begin() + i); 
			break;
		}
 	}
}

// initialize the static boolean
bool Server::_signal = false; 


void Server::signalHandler(int signum)
{
	(void)signum;
	std::cout << std::endl << "Signal Received!" << std::endl;
	// set the static boolean to true to stop the server
	Server::_signal = true; 
}

void Server::closeFds()
{
	// close all the clients
	for(size_t i = 0; i < _users.size(); i++)
	{ 
		std::cout << RED << "Client [" << _users[i].getFd() << "] Disconnected" << WHI << std::endl;
		close(_users[i].getFd());
	}
	// close the server socket
	if (_serverFd != -1)
	{
		std::cout << RED << "Server [" << _serverFd << "] Disconnected" << WHI << std::endl;
		close(_serverFd);
	}
}

void Server::receiveNewData(int fd)
{
	char buff[1024]; 				// buffer for the received data
	memset(buff, 0, sizeof(buff));	// clear the buffer

	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1 , 0); // receive the data
	// check if the client disconnected
	if(bytes <= 0)
	{ 
		std::cout << RED << "Client [" << fd << "] Disconnected" << WHI << std::endl;
		clearClients(fd);	// clear the client
		close(fd);			// close the client socket
	}
 	else
	{
		// print the received data
		buff[bytes] = '\0';
		std::cout << YEL << "Client [" << fd << "] Data: " << WHI << buff;
		// code to process the received data
	}
}

void Server::acceptNewUser()
{
	// create a new client
	User				user; 
	struct sockaddr_in	userAdd;
	struct pollfd		newPoll;
	socklen_t 			len = sizeof(userAdd);
	// accept the new client
	int newUserFd = accept(_serverFd, (sockaddr *)&(userAdd), &len); 
	if (newUserFd == -1)
  	{
		std::cout << "accept() failed" << std::endl; 
		return;
	}
	// set the socket option (O_NONBLOCK) for non-blocking socket
	if (fcntl(newUserFd, F_SETFL, O_NONBLOCK) == -1) 
	{
		std::cout << "fcntl() failed" << std::endl; 
		return;
	}

	newPoll.fd = newUserFd;							// add the client socket to the pollfd
	newPoll.events = POLLIN;						// set the event to POLLIN for reading data
	newPoll.revents = 0;							// set the revents to 0

	user.setFd(newUserFd);							// set the client file descriptor
	user.setIpAdd(inet_ntoa((userAdd.sin_addr)));	// convert the ip address to string and set it
	_users.push_back(user);							// add the client to the vector of clients
	_fds.push_back(newPoll);						// add the client socket to the pollfd

	std::cout << GRE << "User [" << newUserFd << "] Connected" << WHI << std::endl;
}

void Server::configServerSocket()
{
	struct sockaddr_in	serverAdd;
	struct pollfd		newPoll;
	serverAdd.sin_family = AF_INET;				// set the address family to ipv4
	serverAdd.sin_addr.s_addr = INADDR_ANY;		// set the address to any local machine address
	serverAdd.sin_port = htons(this->_port);	// convert the port to network byte order (big endian)

	// create the server socket
	_serverFd = socket(AF_INET, SOCK_STREAM, 0); 
	// check if the socket is created
	if (_serverFd == -1) 
		throw(std::runtime_error("faild to create socket"));
	// set the socket option (SO_REUSEADDR) to reuse the address
	int en = 1;
	if (setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1) 
		throw(std::runtime_error("faild to set option (SO_REUSEADDR) on socket"));
	// set the socket option (O_NONBLOCK) for non-blocking socket
	if (fcntl(_serverFd, F_SETFL, O_NONBLOCK) == -1)
		throw(std::runtime_error("faild to set option (O_NONBLOCK) on socket"));
	// bind the socket to the address
	if (bind(_serverFd, (struct sockaddr *)&serverAdd, sizeof(serverAdd)) == -1) 
		throw(std::runtime_error("faild to bind socket"));
	// listen for incoming connections and making the socket a passive socket
	if (listen(_serverFd, SOMAXCONN) == -1) 
		throw(std::runtime_error("listen() faild"));

	newPoll.fd = _serverFd;  	// add the server socket to the pollfd
	newPoll.events = POLLIN;	// set the event to POLLIN for reading data
	newPoll.revents = 0;		// set the revents to 0
	_fds.push_back(newPoll);    // add the server socket to the pollfd
}

void Server::serverInit()
{
	// create and config the server socket
	configServerSocket();
	std::cout << GRE << "Server [" << _serverFd << "] Connected" << WHI << std::endl;
	std::cout << "Waiting to accept a connection...\n";
	// run the server until the signal is received
	while (Server::_signal == false)
	{ 
		// wait for an event
		if((poll(&_fds[0],_fds.size(),-1) == -1) && Server::_signal == false) 
			throw(std::runtime_error("poll() faild"));
		// check all file descriptors
		for (size_t i = 0; i < _fds.size(); i++)
		{
			// check if there is data to read
			if (_fds[i].revents & POLLIN)
			{ 
    			if (_fds[i].fd == _serverFd)
     				acceptNewUser(); 			// accept new client
    			else
     				receiveNewData(_fds[i].fd);	// receive new data from a registered client
			}
		}
	}
	closeFds(); // close the file descriptors when the server stops
}