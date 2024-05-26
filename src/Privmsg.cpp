/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 22:35:42 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/26 21:51:49 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

void 	Server::privMsgCmd(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() >= 3)
	{
		std::vector<std::string>	receiver = split(cmd[1], ',');
		std::string			nickname = searchUser(fd)->getNick();
		std::string			subStr;
		std::string			msg;
		size_t				len = 400;

	
		if (cmd[2][0] == ':')
			cmd[2].erase(cmd[2].begin());
		for (size_t i = 2; i < cmd.size(); i++)
		{
			msg.append(cmd[i]);
			if (i < cmd.size())
				msg.append(" ");
		}
		std::vector<User>	users;
		//std::cout << YEL << getUserSource(searchUser(fd)) << WHI << std::endl;
		for (size_t k = 0; k < receiver.size(); k++)
		{
			if (receiver[k][0] != '&' && receiver[k][0] != '#')
			{
				if (!userExists(_users, receiver[k]))
				{
					sendMessage(fd, ERR_NOSUCHNICK(searchUser(fd)->getNick(), receiver[k]));
					continue ;
				}
				size_t j = 0;
				while (j < msg.size())
				{
					subStr = msg.substr(j, len);
					sendMessage(searchUser(receiver[k])->getFd(), RPL_PRIVMSG(getUserSource(searchUser(fd)), searchUser(receiver[k])->getNick(), subStr));
					std::cout << YEL << RPL_PRIVMSG(getUserSource(searchUser(fd)), receiver[k], subStr) << WHI << std::endl;
					j += len;
				}
			}
			else
			{
				if (!searchChannel(receiver[k]))
				{
					sendMessage(fd, ERR_NOSUCHCHANNEL(searchUser(fd)->getNick(), receiver[k], "No such channel"));
					continue ;
				}
				else
					users = searchChannel(receiver[k])->getUsers();
				for (size_t i = 0; i < users.size(); i++)
				{
					if (!users[i].getNick().compare(nickname))
						continue ;
					size_t j = 0;
					while (j < msg.size())
					{
						subStr = msg.substr(j, len);
						sendMessage(users[i].getFd(), RPL_PRIVMSG(getUserSource(searchUser(fd)), receiver[k], subStr));
						std::cout << YEL << RPL_PRIVMSG(getUserSource(searchUser(fd)), receiver[k], subStr) << WHI << std::endl;
						j += len;
					}
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