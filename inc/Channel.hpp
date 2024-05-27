/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:11:57 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/27 04:56:08 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "User.hpp"
# include "Server.hpp"
# include "replies.hpp"
# include <vector>
# include <iostream>

# define NOLIMIT 0

class User;

class Channel
{
private:
	std::string			_name;
	std::string			_pass;		// k: set/remove channel key
	std::string			_topic;
	bool				_hasTopic;	// check to send the correct RPL_TOPIC or RPL_NOTOPIC
	bool				_setTopic;	// t: topic settable by channel operator only flag
	bool				_hasPass;	// check if channel has pass or not
	bool				_invite;	// i: set/remove invite-only
	size_t				_limit;		// l: set/remove user limit - 0 = no limit
	std::vector<User>	_users;
	std::vector<User>	_invitedUsers;
	std::vector<User>	_operators;	// o: give/take channel operator privilege

	/* Los usuarios se almacenaran todos en users siempre y cuando esten dentro del canal
	da igual que sean operadores o no. Para los comandos que se requiera el permiso de
	operador, de esta manera se podrá consultar solo esa lista. Y para mandar un mensaje
	a todo el mundo se podrá usar directamente la de usuarios. */

public:
	Channel(std::string name, User user);
	Channel(std::string name, std::string topic);
	Channel(std::string name, std::string pass, User user);
    Channel(const Channel &src);
	~Channel();

	Channel & operator=(Channel const &src);

	std::string			getName(void) const;
	std::string			getTopic(void) const;
	std::string			getPass(void) const;
	std::vector<User>	getUsers(void) const;
	std::vector<User>	getOperators(void) const;
	std::vector<User>	getInvitedUsers(void) const;
	bool				getHasTopic(void) const;
	bool				getSetTopic(void) const;
	bool				getHasPass(void) const;
	bool				getInvite(void) const;
	size_t				getLimit(void) const;

	void				setTopic(std::string newTopic);
	void				setPass(std::string newPass);
	void				setSetTopic(bool setTopic);
	void				setHasTopic(bool hasTopic);
	void				setInvite(bool setInvite);
	void				setHasPass(bool hasPass);
	void				setLimit(size_t limit);

	std::vector<int>    channelListUsers();
    void                addUserToList(User user);
    void                addOperatorToList(User user);
	void				addUserToInvited(User user);
	bool				operatorExists(std::string nick);
	void				removeUser(std::string nickname);
	void				removeUser(int fd);
	void				removeOperator(std::string nickname);


};

#endif
