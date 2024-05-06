/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:22:05 by aoropeza          #+#    #+#             */
/*   Updated: 2024/05/06 19:38:53 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
# define REPLIES_HPP

// user = nickname
# define RPL_WELCOME(source, user) ": 001 " + user + " :Welcome to the Internet Relay Network " + source + "\r\n"
# define RPL_NOTOPIC(user, channel) ": 331 " + user + " " + channel + " :No topic is set\r\n"
# define RPL_TOPIC(user, channel, topic) ": 332 " + user + " " + channel + " :" + topic + "\r\n"
# define RPL_INVITING(user, channel) ": 341 " + user + " " + channel + "\r\n"
# define RPL_NAMREPLY(user, channel, list) ": 353 " + user + " = " + channel + " :" + list + "\r\n"
# define RPL_ENDOFNAMES(user, channel) ": 366 " + user + " " + channel + " :End of /NAMES list\r\n"
# define RPL_INFO(info) ": 371 :" + info + "\r\n"

// source = nickname!username@host
# define RPL_JOIN(source, channel)	":" + source + " JOIN :" + channel + "\r\n"
# define RPL_PART(source, channel)	":" + source + " PART :" + channel + "\r\n"
# define RPL_PRIVMSG(source, target, message) ":" + source + " PRIVMSG " + target + " :" + message + "\r\n"

// ERROR REPLIES
# define ERR_NOSUCHNICK(user) ": 401 " + user + " No existe el nick/canal" + "\r\n"
# define ERR_USERONCHANNEL(user, channel) ": 443 " + user + " " channel + " " + " :ya está en el canal " + "\r\n"
# define ERR_NOTONCHANNEL(channel) ": 442 " + channel + " :No estás en ese canal" + "\r\n"
# define ERR_CHANOPRIVSNEEDED(channel) " : 482" + channel + " :No es operador de canal" + "\r\n"

#endif
