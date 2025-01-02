/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:58:27 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/27 04:43:40 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <vector>
# include <sstream>
# include <cstring>			
# include <algorithm>
# include <iterator>
# include <queue>
# include <map>
# include <fstream>
# include "User.hpp"
# include "Channel.hpp"
# include "sockets.h"
# include "replies.hpp"


# define RED "\e[1;31m"		// red color
# define WHI "\e[0;37m"		// white color
# define GRE "\e[1;32m"		// green color
# define YEL "\e[1;33m"		// yellow color
# define CYA "\033[36;1m"	// cyan color

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
	std::vector<Channel> 			_channels;			// verctor of channels
	static bool						_signal;			// static boolean for signal
	std::map<int, std::queue<std::string> > _msgs;		// queue msgs
	std::ofstream *file;								// Command log output

public:
	Server(int port, std::string pass);
	~Server();

	/*	SERVER CREATION	*/
	void		serverInit();									// server initialization
	void		configServerSocket();							// server socket creation
	void		acceptNewUser();								// accept new user/client
	void		receiveNewData(int fd);							// receive new data from a registered user
	static int	validPort(const std::string port);				// check if it is a valid port
	static int	validPass(const std::string pass);				// check if it is a valid pass
	static void	signalHandler(int signum); 						// signal handler

	/*	CLEAR FDS AND CLIENTS */
	void		closeFds();										// close file descriptors
	void		clearClients(int fd);							// clear clients

	/*	MESSAGES		*/
	void		sendMessage(int fd, const std::string str);		// send message to a user
	void		sendMsgUsersList(std::vector<User> users, std::string str);

	/*	PARSER			*/
	void		parser(std::string str, int fd, bool debug);
	void		findCommand(std::vector<std::string> cmd, int fd, bool debug);

	/*	COMMANDS	*/
	void		createNewChannel(std::string name, User *user);
	void		createNewChannel(std::string name, std::string pass, User *user);
	void		joinNewChannel(std::string name, User *user);
	void		joinNewChannel(std::string name, std::string pass, User *user);
	void		joinCmd(std::vector<std::string> cmd, int fd);
	void		partCmd(std::vector<std::string> cmd, int fd);
	void		quitCmd(std::vector<std::string> cmd, int fd);
	void		passCmd(std::vector<std::string> cmd, int fd);	//prueba
	void		nickCmd(std::vector<std::string> cmd, int fd);	//prueba
	void		userCmd(std::vector<std::string> cmd, int fd);	//prueba
	void 		privMsgCmd(std::vector<std::string> cmd, int fd);
	void		inviteCmd(std::vector<std::string> cmd, int fd);
	void		kickCmd(std::vector<std::string> cmd, int fd);
	void 		changeTopic(std::vector<std::string> cmd, int fd);
	void		modeCmd(std::vector<std::string> cmd, int fd);


	/*	UTILS	*/
	User		*searchUser(int fd);
	User		*searchUser(std::string nick);
	Channel		*searchChannel(std::string name);
	bool		channelExists(std::string name);
	bool		userExists(std::vector<User> userlist, std::string nickname);
	bool		maskMatch(std::string mask, std::string name);					
	bool		invalidChars(std::string str, std::string chars);
	bool		validateChars(std::string str);
	static bool	is_number(const std::string& s);
	void		rmUserFromChannel(std::string channel, std::string nickname);
	void		promoteUser(std::string nickname, std::string channel);
	void		sendUserList(Channel channel, User user);
	std::string	getUserSource(User *user);
	static int	ft_stoi(const char *str);
	std::vector<std::string>	split(const std::string str, char delimiter);

	/*	DEBUG	*/
	void		printUsers(std::vector<User> userlist, std::string channelName);
	void		printChannels();
	void		infoServer();

	//GETTERS && SETTERS
	int	getPort() const;
	int getServerFd() const;
	const std::string& getPass() const;
	const std::vector<User>& getUsers() const;
	const std::vector<struct pollfd>& getFds() const;
	const std::vector<Channel>& getChannels() const;
	bool getSignal() const;

	void setPort(int port);
	void setServerFd(int serverFd);
	void setPass(std::string &pass);
	void setUsers(const std::vector<User>& users);
	void setFds(const std::vector<struct pollfd>& fds);
	void setChannels(const std::vector<Channel>& channels);
	void setSignal(bool signal);
};

inline bool operator<(const User& a, const User& b)
{
	return a.getNick() < b.getNick();
}

#endif
