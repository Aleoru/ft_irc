/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:57:55 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/04/08 19:51:51 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include "../inc/sockets.h"

/* Revisar punto 4.1 del IRC Protocol */

class User
{
private:
	int			_fd;					    // client file descriptor
	std::string _ipAdd;					    // client ip address
	std::string _nick;						// client nickname

public:
	User();
	User(const User &src);
	~User();

	int				getFd() const;						// getter for fd
	std::string		getIpAdd() const;						// getter for ipAdd
	std::string		getNick() const;

	void	setFd(int fd);					// setter for fd
	void	setIpAdd(std::string ipadd); 	// setter for ipadd
};

#endif
