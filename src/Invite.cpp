/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:55:14 by aoropeza          #+#    #+#             */
/*   Updated: 2024/05/19 14:05:55 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

// /Invite john #politics
void	Server::inviteCmd(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() == 3)
	{
		Channel	*channel = searchChannel(cmd[2]);
		if (channel)
		{
			if (userExists(channel->getOperators(), searchUser(fd)->getNick()))
			{
				if (userExists(_users, cmd[1]))
				{
					channel->addUserToInvited(*searchUser(cmd[1]));
					sendMessage(fd, RPL_INVITE(getUserSource(searchUser(fd)), cmd[1], cmd[2]));
					std::cout<<YEL<<searchUser(fd)->getNick()<<" has invited "<<cmd[1]<<" to "<<cmd[2]<<WHI<<std::endl;
				}
				else
				{
					//error: target not exits
					std::cout<<YEL<<cmd[1]<<" not exits"<<WHI<<std::endl;
				}
			}
			else
			{
				//error: is not an operator
				std::cout<<YEL<<searchUser(fd)->getNick()<<" is not an operator"<<WHI<<std::endl;
			}
		}
		else
		{
			//error: no channel
			std::cout<<YEL<<cmd[2]<<" is not a channel"<<WHI<<std::endl;
		}
	}
	else
	{
		sendMessage(fd, ERR_NEEDMOREPARAMS(searchUser(fd)->getNick(), cmd[0], "/INVITE [user] [#channel]"));
		std::cout<<YEL<<"Incorret arguments"<<WHI<<std::endl;
	}
}
