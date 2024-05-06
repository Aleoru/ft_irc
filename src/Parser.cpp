/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:31:58 by aoropeza          #+#    #+#             */
/*   Updated: 2024/05/06 19:43:36 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

static std::vector<std::string> splitcmd(const std::string str)
{
	std::vector<std::string> split;
	std::istringstream tokenStream(str);
	std::string token;
	size_t pos;

	while(std::getline(tokenStream, token))
	{
		pos = token.find_first_of("\r\n");
		if(pos != std::string::npos)
			token = token.substr(0, pos);
		split.push_back(token);
	}

	return (split);
}

std::vector<std::string> Server::split(const std::string str, char delimiter)
{
	std::vector<std::string> split;
	std::string token;
	std::istringstream tokenStream(str);
	while (std::getline(tokenStream, token, delimiter))
	{
		split.push_back(token);
	}
	return (split);
}

void Server::findCommand(std::vector<std::string> cmd, int fd, bool debug)
{
	bool access = searchUser(fd)->getHasAccess();
	if (!cmd[0].compare("PASS") && searchUser(fd)->getCheckPass() == false)
	{
		passCmd(cmd, fd);
		if (debug)
			std::cout << YEL << "Testing PASS client[" << fd << "]: " << searchUser(fd)->getCheckPass() << WHI << std::endl;
	}
	else if (!cmd[0].compare("NICK") && searchUser(fd)->getCheckPass())
	{
		nickCmd(cmd, fd);
		if (debug)
			std::cout << YEL << "Testing NICK client[" << fd << "]: " << searchUser(fd)->getNick() << WHI << std::endl;
	}
	else if (!cmd[0].compare("USER") && searchUser(fd)->getCheckPass())
	{
		userCmd(cmd, fd);
		if (debug)
			std::cout << YEL << "Testing USER client[" << fd << "]: "<< searchUser(fd)->getUsername() << WHI << std::endl;
		//sendMessage(fd, RPL_WELCOME(getUserSource(searchUser(fd)), searchUser(fd)->getNick()));

	}
	else if (!cmd[0].compare("JOIN") && access)
	{
		joinNewChannel(cmd[1], searchUser(fd));
		printUsers(searchChannel(cmd[1])->getUsers());
	}
	else if (!cmd[0].compare("PRIVMSG") && access)
	{
		privMsgCmd(cmd, fd);
	}
	else if (!cmd[0].compare("PART") && access)
	{
		partCmd(cmd, fd);
	}
	//else if (!cmd[0].compare("COMMAND") && access) //need access to execute commands
	std::cout << "-------" << std::endl;
}

// Parser (de mierda xD) provisional
void Server::parser(std::string str, int fd, bool debug)
{
	if (debug)
	{
		std::cout << "str recived: <<" << str << ">>" << std::endl;
		std::cout << "-------------------" << std::endl;
	}
	std::vector<std::string> vec = splitcmd(str);
	if (vec[0].empty())
		return ;
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (debug)
			std::cout << "Substring [" << i << "] -> " << vec[i] << std::endl;
		std::vector<std::string> cmd = split(vec[i], ' ');
		for (size_t j = 0; j < cmd.size(); j++)
		{
			if (debug)
			{
				if (j == 0)
					std::cout << "Comand -> " << cmd[j] << std::endl;
				else
					std::cout << "argument [" << j << "] -> " << cmd[j] << std::endl;
			}
		}
		findCommand(cmd, fd, debug);
	}
}

void		Server::sendMsgUsersList(std::vector<User> users, std::string str)
{
	for (size_t i = 0; i < users.size(); i++)
	{
		sendMessage(users[i].getFd(), str);
	}
}

void 	Server::privMsgCmd(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() >= 3)
	{
		std::string			nickname = searchUser(fd)->getNick();
		std::string			subStr;
		std::string			msg;
		size_t				len = 400;
		for (size_t i = 2; i < cmd.size(); i++)
		{
			msg.append(cmd[i]);
			if (i < cmd.size())
				msg.append(" ");
		}
		//std::vector<User>	users = searchUsersChannel(cmd[1]);
		std::vector<User>	users = searchChannel(cmd[1])->getUsers();
		std::cout << YEL << getUserSource(searchUser(fd)) << WHI << std::endl;
		for (size_t i = 0; i < users.size(); i++)
		{
			if (users[i].getNick().compare(nickname))
			{
				size_t j = 0;
				while (j < msg.size())
				{
					subStr = msg.substr(j, len);;
					sendMessage(users[i].getFd(), RPL_PRIVMSG(getUserSource(searchUser(fd)), cmd[1], subStr));
					std::cout << YEL << RPL_PRIVMSG(getUserSource(searchUser(fd)), cmd[1], subStr) << WHI << std::endl;
					j += len;
				}
			}
		}
	}
	else
	{
		//error number of arguments
	}
}
