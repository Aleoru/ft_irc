/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:11:57 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/04/11 19:23:34 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "../inc/User.hpp"
# include "../inc/Server.hpp"
# include <vector>
# include <iostream>

# define NOLIMIT 0
# define RPL_NOTOPIC 331
# define RPL_TOPIC 332
# define RPL_NAMREPLY 353
# define RPL_JOIN(source, channel)	": " + source + " JOIN :" + channel

/*	Hay 2 tipos de canales, el que nos interesa es el '&' ya que es conocido
	solo por los clintes del servidor	*/

class User;

class Channel
{
private:
	std::string			_name;
	std::string			_pass;		// k: set/remove channel key
	std::string			_topic;
	bool				_hasTopic;	// t: topic settable by channel operator only flag
	bool				_setTopic;	// t: topic settable by channel operator only flag
	int					_limit;		// l: set/remove user limit - 0 = no limit
	bool				_invite;	// i: set/remove invite-only
	std::vector<User>	_users;
	std::vector<User>	_operators;	// o: give/take channel operator privilege

public:
	Channel(std::string name, User user);
	Channel(std::string name, std::string pass, User user);
    //Channel(const Channel &src);
	~Channel();

	std::string			getName(void) const;
	std::string			getTopic(void) const;
	std::vector<User>	getUsers(void) const;

	std::vector<int>    channelListUsers();
    void                addUserToList(User user);

};

#endif
