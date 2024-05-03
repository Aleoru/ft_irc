/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Register.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:27:17 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/03 18:31:00 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

// provisional commands
void	Server::nickCmd(std::vector<std::string> cmd, int fd)
{
	std::cout << "executing nick command " << fd << std::endl;
	if (cmd.size() == 2)
	{
		if (userExists(getUsers() ,cmd[1]) == false)
		{
			User	*user = searchUser(fd);
			user->setNickname(cmd[1]);

		}
		else
			std::cout << "error: nick on use" << std::endl;
	}
	else
	{
		std::cout << "error: nick arguments" << std::endl;
	}
}

void	Server::passCmd(std::vector<std::string> cmd, int fd)
{
	std::cout << "executing pass command " << fd << std::endl;
	if (!cmd[1].compare(this->_pass))
	{
		User	*user = searchUser(fd);
		user->setHasAccess(true);
		sendMessage(fd, ": 371  : valid pass \r\n"); //info
	}
	else
	{
		sendMessage(fd, ": 371  : wrong pass \r\n");
		clearClients(fd);
	}
}

void	Server::userCmd(std::vector<std::string> cmd, int fd)
{
	std::cout << "executing user command " << fd << std::endl;
	User	*user = searchUser(fd);
	user->setUsername(cmd[1]);
}
