/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:07:41 by aoropeza          #+#    #+#             */
/*   Updated: 2024/05/25 21:16:37 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

void	modeQuery(Server *s, std::vector<std::string> cmd, int fd)
{
	Channel 	*channel = s->searchChannel(cmd[1]);
	std::string	modes = "+";

	if (channel->getInvite())
		modes += 'i';
	if (channel->getHasPass())
		modes += 'k';
	if (channel->getLimit())
		modes += 'l';
	if (channel->getSetTopic())
		modes += 't';
	s->sendMessage(fd, RPL_CHANNELMODEIS(s->searchUser(fd)->getNick(), channel->getName(), modes));
}

void	modeChange(Server *s, std::vector<std::string> cmd, int fd)
{
	Channel *channel = s->searchChannel(cmd[1]);
	User	*user = s->searchUser(fd);

	if (cmd.size() < 3)
	{
		s->sendMessage(fd, ERR_NEEDMOREPARAMS(user->getNick(), cmd[0], "You must specified the channel modes"));
		return ;
	}
	if (!channel->operatorExists(user->getNick()))
		s->sendMessage(fd, ERR_CHANOPRIVSNEEDED(user->getNick(), channel->getName()));
	
	std::string flags = cmd[2];
	bool		sign = true;

	for (size_t i = 0; i < flags.size(); i++)
	{
		if (flags[i] == '-')
			sign = false;
		else if (flags[i] == '+')
			sign = false;
		else if (flags[i] == 'i')
			;// codigo sin arg
		else if (flags[i] == 'k')
		{	
			;// codigo con arg si es +
		}
		else if (flags[i] == 'l')
		{
			;// codigo con arg si es +
		}
		else if (flags[i] == 'o')
		{
			;// codigo con arg siempre
		}
		else if (flags[i] == 't')
		{
			;// codigo sin arg
		}
		
	}
	
}

void	Server::Mode(std::vector<std::string> cmd, int fd)
{
	User *user = searchUser(fd);

	if (cmd.size() < 2)
	{
		sendMessage(user->getFd(), ERR_NEEDMOREPARAMS(user->getNick(), cmd[0], "You must specified the channel modes"));
		return ;
	}
	if (!searchChannel(cmd[1]))
	{
		sendMessage(user->getFd(), ERR_NOSUCHCHANNEL(searchUser(fd)->getNick(), cmd[1], "Bad channel name"));
		return ;
	}
	if (cmd.size() == 2)
		modeQuery(this, cmd, fd);
	else
		modeChange(this, cmd, fd);
}
