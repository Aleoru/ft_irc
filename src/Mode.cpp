/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:07:41 by aoropeza          #+#    #+#             */
/*   Updated: 2024/05/26 17:57:27 by aoropeza         ###   ########.fr       */
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
	if (channel->getLimit() > 0)
		modes += 'l';
	if (channel->getSetTopic())
		modes += 't';
	if (modes.size() == 1)
		modes.erase(0, 1);
	s->sendMessage(fd, RPL_CHANNELMODEIS(s->searchUser(fd)->getNick(), channel->getName(), modes));
}

void	inviteMode(Server *s, Channel *channel, bool sign, int fd)
{
	if (sign)
	{
		channel->setInvite(sign);
		s->sendMsgUsersList(channel->getUsers(), RPL_MODE(s->getUserSource(s->searchUser(fd)), channel->getName(), "+i"));
	}
	else
	{
		channel->setInvite(sign);
		s->sendMsgUsersList(channel->getUsers(), RPL_MODE(s->getUserSource(s->searchUser(fd)), channel->getName(), "-i"));
	}
}

void	keyMode(Server *s, Channel *channel, bool sign, std::string arg, int fd)
{
	if (sign)
	{
		if (channel->getHasPass())
		{
			s->sendMessage(fd, ERR_KEYSET(s->searchUser(fd)->getNick(), channel->getName(), "Set key mode true but not key was provided"));
			return ;
		}
		channel->setHasPass(sign);
		channel->setPass(arg);
		s->sendMsgUsersList(channel->getUsers(), RPL_MODE_ARG(s->getUserSource(s->searchUser(fd)), channel->getName(), "+k", arg));
	}
	else
	{
		channel->setHasPass(sign);
		s->sendMsgUsersList(channel->getUsers(), RPL_MODE(s->getUserSource(s->searchUser(fd)), channel->getName(), "-k"));
	}
}

void	limitMode(Server *s, Channel *channel, bool sign, std::string arg, int fd)
{
	if (sign)
	{
		if (!s->is_number(arg))
		{
			s->sendMessage(fd, ERR_UMODEUNKNOWNFLAG(s->searchUser(fd)->getNick(), "Bad arg for +l mode"));
			return ;
		}
		channel->setLimit(s->ft_stoi(arg.c_str()));
		s->sendMsgUsersList(channel->getUsers(), RPL_MODE_ARG(s->getUserSource(s->searchUser(fd)), channel->getName(), "+l", arg));
	}
	else
	{
		channel->setLimit(NOLIMIT);
		s->sendMsgUsersList(channel->getUsers(), RPL_MODE(s->getUserSource(s->searchUser(fd)), channel->getName(), "-l"));
	}
}

void	operatorMode(Server *s, Channel *channel, bool sign, std::string arg, int fd)
{
	if (sign)
	{
		if (!s->userExists(channel->getUsers(), arg))
		{
			s->sendMessage(fd, ERR_UMODEUNKNOWNFLAG(s->searchUser(fd)->getNick(), "User not exists or is not in channel"));
			return ;
		}
		channel->addOperatorToList(*s->searchUser(arg));
		s->sendUserList(*channel, *s->searchUser(fd));
		s->sendMsgUsersList(channel->getUsers(), RPL_MODE(s->getUserSource(s->searchUser(fd)), arg, "+o"));
	}
	else
	{
		if (s->userExists(channel->getUsers(), arg))
		{
			s->sendMessage(fd, ERR_UMODEUNKNOWNFLAG(s->searchUser(fd)->getNick(), "User not exists or is not in channel"));
			return ;
		}
		channel->removeOperator(arg);
		s->sendUserList(*channel, *s->searchUser(fd));
		s->sendMsgUsersList(channel->getUsers(), RPL_MODE(s->getUserSource(s->searchUser(fd)), arg, "-o"));
		std::cout << YEL << "Mando mensaje" << std::endl;
	}
}

void	topicMode(Server *s, Channel *channel, bool sign, int fd)
{
	if (sign)
	{
		channel->setSetTopic(sign);
		s->sendMsgUsersList(channel->getUsers(), RPL_MODE(s->getUserSource(s->searchUser(fd)), channel->getName(), "+t"));
	}
	else
	{
		channel->setSetTopic(sign);
		s->sendMsgUsersList(channel->getUsers(), RPL_MODE(s->getUserSource(s->searchUser(fd)), channel->getName(), "-t"));
	}
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
	{
		s->sendMessage(fd, ERR_CHANOPRIVSNEEDED(user->getNick(), channel->getName()));
		return ;	
	}
	std::string flags = cmd[2];
	size_t		args = 3;
	bool		sign = true;

	for (size_t i = 0; i < flags.size(); i++)
	{
		std::string argument = "";
		if (flags[i] == '-')
			sign = false;
		else if (flags[i] == '+')
			sign = true;
		else if (flags[i] == 'i')
			inviteMode(s, channel, sign, fd);
		else if (flags[i] == 'k')
		{
			if (sign && cmd.size() <= args)
			{
				s->sendMessage(fd, ERR_NEEDMOREPARAMS(user->getNick(), cmd[0], "You must specified the channel keyword"));
				return ;
			}
			if (sign)
			{
				argument = cmd[args];
				args++;
			}
			keyMode(s, channel, sign, argument, fd);
		}
		else if (flags[i] == 'l')
		{
			if (sign && cmd.size() <= args)
			{
				s->sendMessage(fd, ERR_NEEDMOREPARAMS(user->getNick(), cmd[0], "You must specified the channel limit number"));
				return ;
			}
			if (sign)
			{
				argument = cmd[args];
				args++;
			}
			limitMode(s, channel, sign, argument, fd);
		}
		else if (flags[i] == 'o')
		{
			if (cmd.size() <= args)
			{
				s->sendMessage(fd, ERR_NEEDMOREPARAMS(user->getNick(), cmd[0], "You must specified the user"));
				return ;
			}
			operatorMode(s, channel, sign, cmd[args], fd);
			args++;
		}
		else if (flags[i] == 't')
			topicMode(s, channel, sign, fd);
		else
		{
			s->sendMessage(fd, ERR_UNKNOWNMODE(user->getNick(), flags[i], "Unknown flag"));
			return ;
		}
	}
	
}

void	Server::modecmd(std::vector<std::string> cmd, int fd)
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
	if (!userExists(searchChannel(cmd[1])->getUsers(), searchUser(fd)->getNick()))
	{
		sendMessage(user->getFd(), ERR_NOTONCHANNEL(searchUser(fd)->getNick(), cmd[1], "You're not on the channel"));
		return ;
	}
	if (cmd.size() == 2)
		modeQuery(this, cmd, fd);
	else
		modeChange(this, cmd, fd);
}
