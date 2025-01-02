/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:55:17 by aoropeza          #+#    #+#             */
/*   Updated: 2024/05/02 19:55:17 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"


void	Server::kickCmd(std::vector<std::string> cmd, int fd)
{

	if (cmd.size() < 3)
	{
		sendMessage(fd, ERR_NEEDMOREPARAMS(searchUser(fd)->getNick(), cmd[0], "/kick [channel] [user] [<reason>]"));
		return ;
	}

	std::string channel_name = cmd[1];
	std::string kickedUser = cmd[2];
	std::string comment = "No reason given";

	if (!searchChannel(channel_name))
	{
		sendMessage(fd, ERR_NOSUCHCHANNEL(searchUser(fd)->getNick(), channel_name, "No such channel"));
		return ;
	}

	Channel *canal = searchChannel(channel_name);
	std::vector<User> users = canal->getUsers();
	std::vector<User>::iterator it = users.begin();

	if (canal->operatorExists(searchUser(fd)->getNick())) 	// Is operator
	{
		for(; it != users.end(); ++it)
		{
			if (!it->getNick().compare(kickedUser)) 	// user to kick exists on the channel?
			{
				if (cmd.size() > 3)
					comment = cmd[3];
				sendMsgUsersList(canal->getUsers(), RPL_KICK(getUserSource(searchUser(fd)), canal->getName(), kickedUser, comment)); //enviar respuesta
				canal->removeUser(searchUser(kickedUser)->getFd());	// remove user from channel
				return ;
			}
		}
			sendMessage(fd, ERR_NOTONCHANNEL(searchUser(fd)->getNick(), canal->getName(), "User not on channel"));
			return ;
	}
	else
		sendMessage(fd, ERR_CHANOPRIVSNEEDED(searchUser(fd)->getNick(), canal->getName()));
}