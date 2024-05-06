/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:06:50 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/06 19:45:11 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

void	Server::partCmd(std::vector<std::string> cmd, int fd)
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
}
