/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:58:15 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/04/24 17:21:07 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

Server::Server(int port, std::string pass) : _port(port), _pass(pass)
{
	std::cout << "Server created" << std::endl;
	std::cout << "port: " << _port << std::endl;
	std::cout << "pass: " << _pass << std::endl;
	_signal = false;
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

int	Server::validPort(const std::string port)
{
	for (size_t i = 0; i < port.length(); i++)
	{
		if (!std::isdigit(port[i]))
			return (0);
	}
	int num = std::stoi(port);
	// Ports 0 to 1023 are reserved for specific services and protocols
	if (num < 1024 || num > 65535)
		return (0);
	return (1);
}

int	Server::validPass(const std::string pass)
{
	if (pass.length() > 8)
		return (0);
	return (1);
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
		std::cout << YEL << "Client [" << fd << "] Data: " << std::endl << WHI << buff;
		// code to process the received data
		//sendMessage(fd, "371 : receive message"); //371 info?
 		parser(buff, fd, true);

	}
}

int Server::sendMessage(int fd, const std::string str)
{
	if (send(fd, str.c_str(), str.length(), 0) == -1)
	{
		std::cout << "error sending message" << std::endl;
		return (1);
	}
	return (0);
}

// create and set a new User
void Server::acceptNewUser()
{
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

	// config newPoll fd
	newPoll.fd = newUserFd;							// add the client socket to the pollfd
	newPoll.events = POLLIN;						// set the event to POLLIN for reading data
	newPoll.revents = 0;							// set the revents to 0
	_fds.push_back(newPoll);						// add the client socket to the pollfd

	// set the client file descriptor and convert the ip address to string and set it
	User	user(newUserFd, inet_ntoa((userAdd.sin_addr)));
	_users.push_back(user);							// add the client to the vector of clients

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
		throw(std::runtime_error("failed to create socket"));
	// set the socket option (SO_REUSEADDR) to reuse the address
	int en = 1;
	if (setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		throw(std::runtime_error("failed to set option (SO_REUSEADDR) on socket"));
	// set the socket option (O_NONBLOCK) for non-blocking socket
	if (fcntl(_serverFd, F_SETFL, O_NONBLOCK) == -1)
		throw(std::runtime_error("failed to set option (O_NONBLOCK) on socket"));
	// bind the socket to the address
	if (bind(_serverFd, (struct sockaddr *)&serverAdd, sizeof(serverAdd)) == -1)
		throw(std::runtime_error("failed to bind socket"));
	// listen for incoming connections and making the socket a passive socket
	if (listen(_serverFd, SOMAXCONN) == -1)
		throw(std::runtime_error("listen() failed"));

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
			throw(std::runtime_error("poll() failed"));
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
		//printUsers();
		printChannels();
	}
	closeFds(); // close the file descriptors when the server stops
}

// debug functions
void	Server::printUsers()
{
	std::cout << "Server fd: " << _fds[0].fd << std::endl;
	for(size_t i = 0; i < _users.size(); i++)
	{
		std::cout << "User [" << i << "] fd: " << _users[i].getFd() << std::endl;
 	}
}

void	Server::printChannels()
{
	std::cout << "Server fd: " << _fds[0].fd << std::endl;
	for(size_t i = 0; i < _channels.size(); i++)
	{
		std::cout << "Channel [" << i << "] name: " << _channels[i].getName() << std::endl;
 	}
}

int Server::getPort() const 
{
	return _port;
}

int Server::getServerFd() const {
	return _serverFd;
}

const std::string& Server::getPass() const {
	return _pass;
}

const std::vector<User>& Server::getUsers() const {
	return _users;
}

const std::vector<struct pollfd>& Server::getFds() const {
	return _fds;
}

const std::vector<Channel>& Server::getChannels() const {
	return _channels;
}

bool Server::getSignal() 
{
	return _signal;
}

void Server::setPort(int port)
{
	_port = port;
}

void Server::setServerFd(int serverFd)
{
	_serverFd = serverFd;
}

void Server::setPass(std::string &pass)
{
	_pass = pass;
}

void Server::setUsers(const std::vector<User>& users) 
{
        _users = users;
}

void Server::setFds(const std::vector<struct pollfd>& fds) 
{
    _fds = fds;
}

void Server::setChannels(const std::vector<Channel>& channels) 
{
    _channels = channels;
}

void Server::setSignal(bool signal) 
{
    _signal = signal;
}