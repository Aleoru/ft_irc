/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:57:55 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/04/12 13:24:17 by aoropeza         ###   ########.fr       */
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

public:
	User();
	User(const User &src);
	~User();

	int				getFd() const;						// getter for fd
	std::string		getIpAdd() const;						// getter for ipAdd
	std::string		getNick() const;
	std::string		getUsername() const;

	void	setFd(int fd);					// setter for fd
	void	setIpAdd(std::string ipadd); 	// setter for ipadd
	void	setHostname(std::string host);	// setter for hostname
};

#endif
