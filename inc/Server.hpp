/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:58:27 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/26 22:04:42 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <vector>
# include <sstream>
# include <cstring>			// Comprobar
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

	/*	JOIN COMMAND	*/
	void		createNewChannel(std::string name, User *user);
	void		createNewChannel(std::string name, std::string pass, User *user);
	void		joinNewChannel(std::string name, User *user);
	void		joinNewChannel(std::string name, std::string pass, User *user);
	void		joinCmd(std::vector<std::string> cmd, int fd);
	
	/*	PART	*/
	void		partCmd(std::vector<std::string> cmd, int fd);

	/*	QUIT	*/
	void		quitCmd(std::vector<std::string> cmd, int fd);

	/*	PASS, NICK, USER COMMAND	*/
	void		passCmd(std::vector<std::string> cmd, int fd);	//prueba
	void		nickCmd(std::vector<std::string> cmd, int fd);	//prueba
	void		userCmd(std::vector<std::string> cmd, int fd);	//prueba

	/*	PRIVMSG		*/
	void 		privMsgCmd(std::vector<std::string> cmd, int fd);

	/*	INVITE	*/
	void		inviteCmd(std::vector<std::string> cmd, int fd);

	/*	KICK	*/
	void		kickCmd(std::vector<std::string> cmd, int fd);

	/*	TOPIC	*/
	void 		changeTopic(std::vector<std::string> cmd, int fd);

	/*	MODE	*/
	void		modecmd(std::vector<std::string> cmd, int fd);

	/*	DEBUG	*/
	void		printUsers(std::vector<User> userlist, std::string channelName);
	void		printChannels();
	void		infoServer();

	/*	UTILS	*/
	User		*searchUser(int fd);
	User		*searchUser(std::string nick);
	Channel		*searchChannel(std::string name);
	bool		channelExists(std::string name);
	bool		userExists(std::vector<User> userlist, std::string nickname);
	bool		maskMatch(std::string mask, std::string name);					//filter names by mask
	bool		invalidChars(std::string str, std::string chars);
	static bool	is_number(const std::string& s);
	void		rmUserFromChannel(std::string channel, std::string nickname);
	void		promoteUser(std::string nickname, std::string channel); 			//promote user to operator
	void		sendUserList(Channel channel, User user);
	std::string	getUserSource(User *user);
	std::vector<std::string>	split(const std::string str, char delimiter);
	static int	ft_stoi(const char *str);


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
