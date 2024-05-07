/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:19:31 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/02 18:43:09 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/Channel.hpp"

Channel::Channel(std::string name, User user): _name(name)
{
	this->_setTopic = false;
	this->_hasTopic = false;
	this->_limit = NOLIMIT;
	this->_invite = false;
	_users.push_back(user);
	_operators.push_back(user);
	std::cout << GRE << "Channel: "<< name <<" created" << WHI << std::endl;

}

Channel::Channel(std::string name, std::string pass, User user): _name(name), _pass(pass)
{
	this->_setTopic = false;
	this->_limit = NOLIMIT;
	this->_invite = false;
	_users.push_back(user);
	_operators.push_back(user);
	std::cout << GRE << "Channel: "<< name <<" created with password" << WHI << std::endl;

}

/* Channel::Channel(const Channel &src) : _name(src.getName()), 
{

} */

Channel::~Channel()
{
	std::cout << RED << "Channel destroyed" << WHI << std::endl;
}


std::string	Channel::getName() const { return (this->_name); }
std::string	Channel::getTopic() const { return (this->_topic); }
std::vector<User>	Channel::getUsers() const { return (this->_users); }
std::vector<User>	Channel::getOperators() const { return (this->_operators); }
bool		Channel::getHasTopic() const { return (this->_hasTopic); }

void	Channel::setTopic(std::string newTopic){ _topic = newTopic; }

std::vector<int>	Channel::channelListUsers()
{
	std::vector<int> channelUsers;

	return (channelUsers);
}

void    Channel::addUserToList(User user)
{
    _users.push_back(user);
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
}
