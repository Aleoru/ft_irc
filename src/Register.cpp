/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Register.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:27:17 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/27 16:07:33 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

bool 	Server::validateChars(std::string str)
{
	for(size_t i = 0; i < str.size(); i++)
	{
		if(!std::isalnum(str[i]) && str[i] != '_')
			return (false);
	}
	return (true);
}

void	Server::passCmd(std::vector<std::string> cmd, int fd)
{
	std::string msn;
	std::string nick = searchUser(fd)->getNick();
	if (cmd.size() == 2)
	{
		std::cout << "executing pass command " << fd << std::endl;
		if (!cmd[1].compare(this->_pass))
		{
			User	*user = searchUser(fd);
			user->setCheckPass(true);
			msn = "valid pass";
			std::cout << msn << std::endl;
			sendMessage(fd, RPL_INFO(nick, msn));
		}
		else
		{
			msn = "wrong pass";
			std::cout << msn << std::endl;
			sendMessage(fd, RPL_INFO(nick, msn));
		}
	}
	else
	{
		msn = " no pass";
		sendMessage(fd, ERR_NEEDMOREPARAMS(nick, cmd[0], msn));
	}
}

void	Server::nickCmd(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() == 2)
	{
		if (!validateChars(cmd[1]) || cmd[1].size() > 9)
		{
			sendMessage(fd, ERR_ERRONEUSNICKNAME(searchUser(fd)->getNick()));
			return ;
		}
		if (userExists(getUsers() ,cmd[1]) == false && searchUser(fd)->getHasAccess()) // nick change
		{
			sendMsgUsersList(_users, RPL_NICKCHANGE(getUserSource(searchUser(fd)), cmd[1]));
			searchUser(fd)->setNickname(cmd[1]);
			for (size_t i = 0; i < _channels.size(); i++)
			{
				if (userExists(_channels[i].getUsers() ,cmd[1]))
				{
					sendMsgUsersList(_channels[i].getUsers(), RPL_NICKCHANGE(getUserSource(searchUser(fd)), cmd[1]));
					std::vector<User>::iterator it;
					for (; it != _channels[i].getUsers().end(); it++)
					{
						if (it->getNick() == cmd[1])
						{
							it->setNickname(cmd[1]);
							break ;
						}
					}
					sendUserList(_channels[i], *it);
				}
			}
		}
		else if (userExists(getUsers() ,cmd[1]) == false)                              // nick register
		{
			User	*user = searchUser(fd);
			user->setNickname(cmd[1]);
			user->setCheckNick(true);
			if (user->getCheckNick() && user->getCheckUser() && user->getCheckPass() && user->getHasAccess() == false)
			{
				user->setHasAccess(true);
				sendMessage(fd, RPL_WELCOME(searchUser(fd)->getNick(), getUserSource(searchUser(fd))));
				std::vector<std::string> vec;
				vec.reserve(2); 
				vec.resize(2);
				vec[0] ="JOIN";
				vec[1] ="#General";
				findCommand(vec, fd, false);
			}
		}
		else
		{
			std::cout << "error: nick on use" << std::endl;
			sendMessage(fd, ERR_NICKINUSE(cmd[1]));
		}
	}
	else if (cmd.size() == 1)
	{
		std::cout << "error: no nick" << std::endl;
		sendMessage(fd, ERR_NONICKNAME(searchUser(fd)->getNick()));
	}
	else
	{
		std::cout << "error: nick arguments" << std::endl;
		sendMessage(fd, ERR_NEEDMOREPARAMS(searchUser(fd)->getNick(), cmd[0], "/NICK [nick]"));
	}
}

void	Server::userCmd(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() >= 2)
	{
		User	*user = searchUser(fd);
		user->setUsername(cmd[1]);
		user->setCheckUser(true);
		if (user->getCheckNick() && user->getCheckUser() && user->getCheckPass() && user->getHasAccess() == false)
		{
			user->setHasAccess(true);
			sendMessage(fd, RPL_WELCOME(searchUser(fd)->getNick(), getUserSource(searchUser(fd))));
			std::vector<std::string> vec;
			vec.reserve(2); 
			vec.resize(2);
			vec[0] ="JOIN";
			vec[1] ="#General";
			findCommand(vec, fd, false);
		}
	}
	else
		sendMessage(fd, ERR_NEEDMOREPARAMS(searchUser(fd)->getNick(), cmd[0], "/USER [user]"));

}