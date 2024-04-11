#include "../inc/Server.hpp"

void	Server::createNewChannel(std::string name, User user)
{
	name.erase(name.begin() + name.length() - 2, name.end());
	std::cout << "[" << RED << name << WHI << "]" << std::endl;
	Channel	channel(name, user);
	std::string	rpl;
	rpl.append(": ");
	rpl.append(std::to_string(RPL_NOTOPIC) + " ");
	rpl.append(user.getNick() + " ");
	rpl.append(channel.getName() + " :No topic is set\r\n");
	_channels.push_back(channel);

	std::string msg = ":aoropeza!aoropeza@localhost JOIN :" + channel.getName();
	msg.append("\r\n");

	send(user.getFd(), msg.c_str(), msg.length(), 0);
	send(user.getFd(), rpl.c_str(), rpl.length(), 0);
	sendUserList(channel, user);
	std::cout << GRE << "Channel [" << name << "] succesfully created" << WHI << std::endl;
}

void	Server::joinNewChannel(std::string name, User user)
{
	if (!channelExists(name))
		createNewChannel(name, user);
	else
	{
		Channel channel(searchChannel(name));
		// Add User to channel
		send(user.getFd(), channel.getTopic().c_str(), channel.getTopic().length(), RPL_TOPIC);
		std::cout << CYA << "User [" << user.getFd() << "] joined the channel [" << channel.getName() << "]" << WHI << std::endl;
	}
}

User	Server::searchUser(int fd)
{
	for (size_t i = 0; i < _users.size(); i++)
	{
		if (_users[i].getFd() == fd)
			return (_users[i]);
	}
	throw std::exception();
}

Channel	Server::searchChannel(std::string name)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getName().compare(name) == 0)
			return (_channels[i]);
	}
	throw std::exception();

}

bool	Server::userExists(std::string nick)
{
	for (size_t i = 0; i < _users.size(); i++)
	{
		if (_users[i].getNick().compare(nick) == 0)
			return (true);
	}
	return (false);
}

bool	Server::channelExists(std::string name)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getName().compare(name) == 0)
			return (true);
	}
	return (false);

}

void	Server::sendUserList(Channel channel, User user)
{
	std::string			rpl;
	std::vector<User>	userlist(channel.getUsers());

	rpl.append(": ");
	rpl.append(std::to_string(RPL_NAMREPLY) + " ");
	rpl.append(user.getNick() + " = ");
	rpl.append(channel.getName() + " :");
	for (size_t i = 0; i < userlist.size(); i++)
	{
		rpl.append(userlist[i].getNick() + " ");	// cambiar por _nick
	}
	rpl.append("\r\n");
	std::cout << YEL << rpl << WHI;
	send(user.getFd(), rpl.c_str(), rpl.length(), 0);

}