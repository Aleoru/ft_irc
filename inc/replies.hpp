/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:22:05 by aoropeza          #+#    #+#             */
/*   Updated: 2024/04/25 18:49:43 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
# define REPLIES_HPP

// user = nickname
# define RPL_WELCOME(source, user) ": 001 " + user + " :Welcome to the Internet Relay Network " + source + "\r\n"
# define RPL_NOTOPIC(user, channel) ": 331 " + user + " " + channel + " :No topic is set\r\n"
# define RPL_NOTOPIC(user, channel) ": 331 " + user + " " + channel + " :No topic is set\r\n"
# define RPL_TOPIC(user, channel, topic) ": 332 " + user + " " + channel + " :" + topic + "\r\n"
# define RPL_NAMREPLY(user, channel, list) ": 353 " + user + " = " + channel + " :" + list + "\r\n"
# define RPL_ENDOFNAMES(user, channel) ": 366 " + user + " " + channel + " :End of /NAMES list"
# define RPL_INFO(info) ": 371 :" + info + "\r\n"

// source = nickname!username@host
# define RPL_JOIN(source, channel)	":" + source + " JOIN :" + channel + "\r\n"

#endif