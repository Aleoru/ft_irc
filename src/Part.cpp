/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:06:50 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/27 03:19:23 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

//Part format sent by the client: PART #channel :Leaving // CMD, CHANNEL, REASON
void Server::partCmd(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() >= 2)
	{
		std::vector<std::string> channels = split(cmd[1], ',');
		for (size_t i = 0; i < channels.size(); i++)
		{
			if (channelExists(channels[i]))
			{
				sendMsgUsersList(_users, RPL_PART(getUserSource(searchUser(fd)),channels[i]));
				if (userExists(searchChannel(channels[i])->getUsers(), searchUser(fd)->getNick()))
				{
					rmUserFromChannel(searchChannel(channels[i])->getName(), searchUser(fd)->getNick());
					searchUser(fd)->setNbChannels(-1);
				}
			}
			else
			{
				sendMessage(fd, ERR_NOSUCHCHANNEL(searchUser(fd)->getNick(), cmd[2], "No such channel"));
			}
		}
	}
	else
	{
		sendMessage(fd, ERR_NEEDMOREPARAMS(searchUser(fd)->getNick(), cmd[0], "/PART [#channel,]"));
	}
}

//QUIT format sent by the client: QUIT :Leaving // CMD, REASON
void Server::quitCmd(std::vector<std::string> cmd, int fd)
{
	std::cout<<"quitCmd"<<std::endl;
	if (cmd.size() == 2)
	{
		std::cout<<cmd[1]<<fd<<std::endl;
		sendMsgUsersList(_users, RPL_QUIT(getUserSource(searchUser(fd)), cmd[1]));
		for (size_t  i = 0; i < _channels.size(); i++)
		{
			if (userExists(_channels[i].getUsers(), searchUser(fd)->getNick()))
			{
				sendMsgUsersList(_users, RPL_PART(getUserSource(searchUser(fd)),_channels[i].getName()));
				rmUserFromChannel(_channels[i].getName(), searchUser(fd)->getNick());
			}
		}
		*this->file << "x" << fd << ":" << "\n";
		clearClients(fd);
	}
	else
	{
		sendMessage(fd, ERR_NEEDMOREPARAMS(searchUser(fd)->getNick(), cmd[0], "/QUIT [:reason]"));
	}
}
