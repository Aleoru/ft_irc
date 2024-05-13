/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:11:57 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/13 18:04:41 by akent-go         ###   ########.fr       */
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


/*	Hay 2 tipos de canales, el que nos interesa es el '&' ya que es conocido
	solo por los clintes del servidor	*/

class User;

class Channel
{
private:
	std::string			_name;
	std::string			_pass;		// k: set/remove channel key
	std::string			_topic;
	bool				_hasTopic;	// check to send the correct RPL_TOPIC or RPL_NOTOPIC
	bool				_setTopic;	// t: topic settable by channel operator only flag
	int					_limit;		// l: set/remove user limit - 0 = no limit
	bool				_invite;	// i: set/remove invite-only
	std::vector<User>	_users;
	std::vector<User>	_invitedUsers;
	std::vector<User>	_operators;	// o: give/take channel operator privilege

	/* Los usuarios se almacenaran todos en users siempre y cuando esten dentro del canal
	da igual que sean operadores o no. Para los comandos que se requiera el permiso de 
	operador, de esta manera se podrá consultar solo esa lista. Y para mandar un mensaje
	a todo el mundo se podrá usar directamente la de usuarios. */

public:
	Channel(std::string name, User user);
	Channel(std::string name, std::string pass, User user);
    Channel(const Channel &src);
	~Channel();

	Channel & operator=(Channel const &src);

	std::string			getName(void) const;
	std::string			getTopic(void) const;
	std::vector<User>	getUsers(void) const;
	std::vector<User>	getOperators(void) const;
	bool				getHasTopic(void) const;
	bool				getSetTopic(void) const;

	void				setTopic(std::string newTopic);
	void				setSetTopic(bool setTopic);
	void				setHasTopic(bool hasTopic);

	std::vector<int>    channelListUsers();
    void                addUserToList(User user);
    void                addOperatorToList(User user);
	void    			removeOperatorFromList(User user);
	bool				operatorExists(std::string nick);
	void				removeUser(std::string nickname);
	void				removeUser(int fd);
	bool				getInvite(); //esta función devuelve true si necesitas permisos y false si no necesitas permisos de admin

};

#endif
