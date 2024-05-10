/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:57:55 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/05/10 02:37:06 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include "sockets.h"
# include "replies.hpp"

/* Revisar punto 4.1 del IRC Protocol */

class User
{
private:
	int			_fd;					    // client file descriptor
	std::string	_ipAdd;					    // client ip address
	std::string	_nickname;					// client nickname
	std::string	_username;					// client username
	bool		_checkPass;
	bool		_checkNick;
	bool		_checkUser;
	bool		_hasAccess;					// client password is correct
	int			_nbChannels;				// number of channels of the user

public:
	User();
	User(const User &src);
	User(int fd, std::string ipAdd);
	~User();

	User & operator=(User const &src);

	/*	SETTERS & GETTERS	*/
	int				getFd() const;						// getter for fd
	std::string		getIpAdd() const;					// getter for ipAdd
	std::string		getNick() const;
	std::string		getUsername() const;
	bool			getHasAccess() const;
	bool			getCheckPass() const;
	bool			getCheckNick() const;
	bool			getCheckUser() const;
	int				getNbChannels() const;

	void			setFd(int fd);						// setter for fd
	void			setIpAdd(std::string ipadd); 		// setter for ipadd
	void			setNickname(std::string nick);
	void			setUsername(std::string user);
	void			setHasAccess(bool access);
	void			setCheckPass(bool pass);
	void			setCheckNick(bool nick);
	void			setCheckUser(bool user);
	void			setNbChannels(int num);				// add num to _nbChannels

};

#endif
