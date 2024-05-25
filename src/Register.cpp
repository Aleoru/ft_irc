/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Register.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:27:17 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/24 04:37:16 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

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

// nick max size?
// nick invalid characteres?
// reply??? 
void	Server::nickCmd(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() == 2)
	{
		std::string invalids = "@#,:"; //ERR_ERRONEUSNICKNAME
		if (invalidChars(cmd[1], invalids))
		{
			sendMessage(fd, ERR_NICKINUSE(cmd[1]));
			return ;
		}
		if (userExists(getUsers() ,cmd[1]) == false && searchUser(fd)->getHasAccess()) //cambio de nick
		{
			sendMsgUsersList(_users, RPL_NICKCHANGE(getUserSource(searchUser(fd)), cmd[1]));
			//sendMessage(fd, RPL_NICKCHANGE(getUserSource(searchUser(fd)), cmd[1]));
			searchUser(fd)->setNickname(cmd[1]);
		}
		else if (userExists(getUsers() ,cmd[1]) == false)                              //registro de nick
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
