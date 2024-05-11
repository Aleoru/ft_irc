/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Register.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:27:17 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/11 03:10:10 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

void	Server::passCmd(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() == 2)
	{
		std::cout << "executing pass command " << fd << std::endl;
		if (!cmd[1].compare(this->_pass))
		{
			User	*user = searchUser(fd);
			user->setCheckPass(true);
			//sendMessage(fd, ": 371  : valid pass \r\n"); //info debug en cliente
		}
		else
		{
			std::cout << "wrong pass";
			//sendMessage(fd, ": 371  : wrong pass \r\n");
		}
	}
	else
	{
		//ERR_NEEDMOREPARAMS
	}
}

// nick max size?
// nick invalid characteres?
void	Server::nickCmd(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() == 2)
	{
		if (userExists(getUsers() ,cmd[1]) == false && searchUser(fd)->getHasAccess()) //cambio de nick
		{
			sendMessage(fd, RPL_NICKCHANGE(searchUser(fd)->getNick(), cmd[1]));
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
				sendMessage(fd, RPL_WELCOME(getUserSource(searchUser(fd)), searchUser(fd)->getNick()));
			}
		}
		else
		{
			std::cout << "error: nick on use" << std::endl;
			// ERR_NICKNAMEINUSE 
			sendMessage(fd, ERR_NICKINUSE(cmd[1]));
		}
	}
	else if (cmd.size() == 1)
	{
		//no nick ERR_NONICKNAME(nickname)
	}
	else
	{
		std::cout << "error: nick arguments" << std::endl;
		//enviar mensaje al cliente
	}
}

void	Server::userCmd(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() == 2)
	{
		User	*user = searchUser(fd);
		user->setUsername(cmd[1]);
		user->setCheckUser(true);
		if (user->getCheckNick() && user->getCheckUser() && user->getCheckPass() && user->getHasAccess() == false)
		{
			user->setHasAccess(true);
			sendMessage(fd, RPL_WELCOME(getUserSource(searchUser(fd)), searchUser(fd)->getNick()));
		}
	}
	else
	{
		//ERR_NEEDMOREPARAMS
	}
}
