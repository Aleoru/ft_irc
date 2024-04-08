/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:11:57 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/04/08 19:55:24 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "../inc/User.hpp"
# include <vector>
# include <iostream>

#define NOLIMIT 0

/*	Hay 2 tipos de canales, el que nos interesa es el '&' ya que es conocido
	solo por los clintes del servidor	*/

class User;

class Channel
{
private:
	std::string			_name;
	std::string			_pass;		// k: set/remove channel key
	std::string			_topic;
	bool				_setTopic;	// t: topic settable by channel operator only flag
	int					_limit;		// l: set/remove user limit - 0 = no limit
	bool				_invite;	// i: set/remove invite-only
	std::vector<User>	_users;
	std::vector<User>	_operators;	// o: give/take channel operator privilege

public:
	Channel(std::string name);
	~Channel();

	std::vector<int>    channelListUsers();
};

#endif
