/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 22:35:42 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/19 22:37:01 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

void 	Server::privMsgCmd(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() >= 3)
	{
		std::string			nickname = searchUser(fd)->getNick();
		std::string			subStr;
		std::string			msg;
		size_t				len = 400;

		cmd[2].erase(cmd[2].begin());
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
		sendMessage(fd, ERR_NEEDMOREPARAMS(searchUser(fd)->getNick(), cmd[0], "/PRIVMSG [channel] [message]"));
	}
}