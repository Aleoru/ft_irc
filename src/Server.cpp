/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:58:15 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/27 17:47:15 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

Server::Server(int port, std::string pass) : _port(port), _pass(pass)
{
	std::cout << "Server created" << std::endl;
	std::cout << "port: " << _port << std::endl;
	std::cout << "pass: " << _pass << std::endl;
	_signal = false;
	this->file = new std::ofstream("./server.log");
}

Server::~Server()
{
	std::cout << "Server deleted" << std::endl;
	delete (this->file);
}

// clear the clients
void Server::clearClients(int fd)
{
	// remove the client from all channels
	User *user = searchUser(fd);
	if (user)
	{
		for(size_t i = 0; i < _channels.size(); i++)
		{
			//if (userExists(_channels[i].getUsers(), user->getNick()))
				rmUserFromChannel(_channels[i].getName(), user->getNick());
		}
	}
	// remove the client from the pollfd
	for(size_t i = 0; i < _fds.size(); i++)
	{
		if (_fds[i].fd == fd)
		{
			_fds.erase(_fds.begin() + i);
			break ;
		}
 	}
	// remove the client from the vector of clients
 	for(size_t i = 0; i < _users.size(); i++)
	{
		if (_users[i].getFd() == fd)
		{
			_users.erase(_users.begin() + i);
			break ;
		}
 	}
}

void	Server::rmUserFromChannel(std::string channel, std::string nickname)
{
	for (size_t i = 0; i < _channels.size(); i ++)
	{
		if (!_channels[i].getName().compare(channel))
		{
			_channels[i].removeUser(nickname);
			break ;
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

int	ft_stoi(char const *str)
{
	int i;
	int sign;
	int n;

	i = 0;
	sign = 1;
	n = 0;
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32) && str[i])
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n * sign);
}

int	Server::validPort(const std::string port)
{
	for (size_t i = 0; i < port.length(); i++)
	{
		if (!std::isdigit(port[i]))
			return (0);
	}
	int num = ft_stoi(port.c_str());
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
	char buff[1024];
	memset(buff, 0, sizeof(buff));

	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1 , 0); // receive the data
	// check if the client disconnected
	if(bytes <= 0)
	{
		std::cout << RED << "Client [" << fd << "] Disconnected" << WHI << std::endl;
		*this->file << "x" << fd << ":" << "\n";
		clearClients(fd);	// clear the client
		close(fd);			// close the client socket
	}
 	else
	{
		// print the received data
		buff[bytes] = '\0';
		std::cout << YEL << "Client [" << fd << "] Data: " << std::endl << WHI << buff;
		// code to process the received data
		*this->file << ">" << fd << ":" << buff << "\n";
 		parser(buff, fd, false);
	}
}

void Server::sendMessage(int fd, const std::string str)
{
	// add to fd queue msgs
	std::map<int, std::queue<std::string> >::iterator it = _msgs.begin();
	for (; it != _msgs.end(); it++)
	{
		if (it->first == fd)
		{
			it->second.push(str);
			return ;
		}
	}
	// new key
	std::queue<std::string> q;
	q.push(str);
	_msgs.insert(std::pair<int,std::queue<std::string> >(fd,q));
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
	newPoll.events = POLLIN | POLLOUT;				// set the event to POLLIN/POLLOUT for reading data
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

	newPoll.fd = _serverFd;  			// add the server socket to the pollfd
	newPoll.events = POLLIN | POLLOUT;	// set the event to POLLIN | POLLOUT for reading data
	newPoll.revents = 0;				// set the revents to 0
	_fds.push_back(newPoll);    		// add the server socket to the pollfd
}

void Server::serverInit()
{
	// create and config the server socket
	configServerSocket();
	// create general channel
	Channel general("#General", "General channel"); 
	_channels.push_back(general);
	std::cout << GRE << "Server [" << _serverFd << "] Connected" << WHI << std::endl;
	std::cout << "Waiting to accept a connection...\n";
	// run the server until the signal is received
	std::map<int, std::queue<std::string> >::iterator it;
	while (Server::_signal == false)
	{
		// wait for an event
		if((poll(&_fds[0],_fds.size(),-1) == -1) && Server::_signal == false)
			throw(std::runtime_error("poll() failed"));
		// check all file descriptors
		for (size_t i = 0; i < _fds.size(); i++)
		{
			if (_fds[i].revents & (POLLERR | POLLNVAL | POLLHUP))
			{
				// Cerrar la conexion y borrar el usuario como con QUIT
				std::vector<std::string> args;
				args.push_back("QUIT");
				args.push_back("error");
				this->clearClients(_fds[i].fd);
			}
			// check if there is data to read
			if (_fds[i].revents & POLLIN)
			{
    			if (_fds[i].fd == _serverFd)
     				acceptNewUser(); 			// accept new client
    			else
     				receiveNewData(_fds[i].fd);	// receive new data from a registered client
			}
			// check if fds is raady to write
			if (_fds[i].revents & POLLOUT)
			{
				it = _msgs.find(_fds[i].fd);
				if (it != _msgs.end() && it->second.size() > 0)
				{
					std::string strOut = it->second.front();
					*this->file << "<" << _fds[i].fd << ":" << strOut << "\n";
					send(_fds[i].fd, strOut.c_str(), strOut.length(), MSG_NOSIGNAL);
					it->second.pop();
				}
			}
		}
	}
	closeFds(); // close the file descriptors when the server stops
}

// getters
int Server::getPort() const {return _port;}
int Server::getServerFd() const {return _serverFd;}
const std::string& Server::getPass() const {return _pass;}
const std::vector<User>& Server::getUsers() const {return _users;}
const std::vector<struct pollfd>& Server::getFds() const {return _fds;}
const std::vector<Channel>& Server::getChannels() const {return _channels;}
bool Server::getSignal() const {return _signal;}
// setters
void Server::setPort(int port) {_port = port;}
void Server::setServerFd(int serverFd) {_serverFd = serverFd;}
void Server::setPass(std::string &pass) {_pass = pass;}
void Server::setUsers(const std::vector<User>& users) {_users = users;}
void Server::setFds(const std::vector<struct pollfd>& fds) {_fds = fds;}
void Server::setChannels(const std::vector<Channel>& channels) {_channels = channels;}
void Server::setSignal(bool signal) {_signal = signal;}
