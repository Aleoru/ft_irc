/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:06:50 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/06 18:54:58 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

/* void	Server::partCmd(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() == 2)
	{
		std::vector<std::string> channels = split(cmd[1], ',');
		for (size_t i = 0; i < channels.size(); i++)
		{
			if (userExists(searchChannel(channels[i])->getUsers(), searchUser(fd)->getNick()))
			{
				rmUserFromChannel(searchChannel(channels[i])->getName(), searchUser(fd)->getNick());
				searchUser(fd)->setNbChannels(-1);
			}
		}
	}
	else
	{
		//error: number of arguments
	}
} */

//Substring [0] -> PART #canal22222 :Leaving
//Comand -> PART
//argument [1] -> #canal22222
//argument [2] -> :Leaving

void Server::partCmd(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() == 3)
	{
		std::vector<std::string> channels = split(cmd[1], ',');
		for (size_t i = 0; i < channels.size(); i++)
		{
			sendMsgUsersList(_users, RPL_PART(getUserSource(searchUser(fd)),channels[i]));
			if (userExists(searchChannel(channels[i])->getUsers(), searchUser(fd)->getNick()))
			{
				rmUserFromChannel(searchChannel(channels[i])->getName(), searchUser(fd)->getNick());
				searchUser(fd)->setNbChannels(-1);
			}
		}
	}
	else
	{
		//error: number of arguments
	}
}
