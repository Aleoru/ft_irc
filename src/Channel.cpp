/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:19:31 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/17 19:48:13 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/Channel.hpp"

Channel::Channel(std::string name, User user): _name(name)
{
	this->_setTopic = false;
	this->_hasTopic = false;
	this->_hasPass = false;
	this->_invite = false;
	this->_limit = NOLIMIT;
	user.setNbChannels(1);
	_users.push_back(user);
	_operators.push_back(user);
}

Channel::Channel(std::string name, std::string pass, User user): _name(name), _pass(pass)
{
	this->_setTopic = false;
	this->_hasTopic = false;
	this->_hasPass = true;
	this->_invite = false;
	this->_limit = NOLIMIT;
	user.setNbChannels(1);
	_users.push_back(user);
	_operators.push_back(user);
}

Channel::Channel(const Channel &src)
{
	*this = src;
}

Channel::~Channel()
{
}

Channel & Channel::operator=(Channel const &src)
{
	if (this != &src)
	{
		this->_name = src._name;
		this->_pass = src._pass;
		this->_topic = src._topic;
		this->_hasTopic = src._hasTopic;
		this->_setTopic = src._setTopic;
		this->_hasPass = src._hasPass;
		this->_invite = src._invite;
		this->_limit = src._limit;
		this->_users = src._users;
		this->_invitedUsers = src._invitedUsers;
		this->_operators = src._operators;
	}
	return (*this);
}

std::string	Channel::getName() const { return (this->_name); }
std::string	Channel::getTopic() const { return (this->_topic); }
std::string	Channel::getPass() const { return (this->_pass); }
std::vector<User>	Channel::getUsers() const { return (this->_users); }
std::vector<User>	Channel::getOperators() const { return (this->_operators); }
bool		Channel::getHasTopic() const { return (this->_hasTopic); }
bool		Channel::getSetTopic() const { return (this->_setTopic); }
bool		Channel::getInvite() const { return (this->_invite); }
int			Channel::getLimit() const { return (this->_limit); }
bool		Channel::getHasPass() const { return (this->_hasPass); }

void		Channel::setTopic(std::string newTopic){ _topic = newTopic; }
void		Channel::setSetTopic(bool setTopic) { this->_setTopic = setTopic; }
void		Channel::setHasTopic(bool hasTopic) { this->_hasTopic = hasTopic; }
void		Channel::setInvite(bool invite) { this->_invite = invite; }

std::vector<int>	Channel::channelListUsers()
{
	std::vector<int> channelUsers;

	return (channelUsers);
}

void    Channel::addUserToList(User user)
{
    _users.push_back(user);
}

void    Channel::addOperatorToList(User user)
{
    _operators.push_back(user);
}

bool	Channel::operatorExists(std::string nick)
{
	for (size_t i = 0; i < _operators.size(); i++)
	{
		if (_operators[i].getNick().compare(nick) == 0)
			return (true);
	}
	return (false);
}

void	Channel::removeUser(std::string nickname)
{
	for (size_t i = 0; i < _users.size(); i++)
	{
		if (!_users[i].getNick().compare(nickname))
		{
			_users.erase(_users.begin() + i);
			break ;
		}
	}
	for (size_t i = 0; i < _operators.size(); i++)
	{
		if (!_operators[i].getNick().compare(nickname))
		{
			_operators.erase(_operators.begin() + i);
			break ;
		}
	}
}

void	Channel::removeUser(int fd)
{
	for (size_t i = 0; i < _users.size(); i++)
	{
		if (_users[i].getFd() == fd)
		{
			_users.erase(_users.begin() + i);
			break ;
		}
	}
	for (size_t i = 0; i < _operators.size(); i++)
	{
		if (_operators[i].getFd() == fd)
		{
			_operators.erase(_operators.begin() + i);
			break ;
		}
	}
}
