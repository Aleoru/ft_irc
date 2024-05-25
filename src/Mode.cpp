/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:07:41 by aoropeza          #+#    #+#             */
/*   Updated: 2024/05/20 16:51:18 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

void	Server::Mode(std::vector<std::string> cmd, int fd)
{
	User *user = searchUser(fd);
	Channel *channel;

	if (cmd.size() < 3)
	{
		sendMessage(user->getFd(), ERR_NEEDMOREPARAMS(user->getNick(), cmd[0], "You must specified the channel modes"));
		return ;
	}
	if (!userExists(channel->getOperators(), user->getNick()))
	{
		sendMessage(user->getFd(), ERR_CHANOPRIVSNEEDED(user->getNick(), channel->getName()));
		return ;
	}
}