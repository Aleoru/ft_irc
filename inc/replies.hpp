/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:22:05 by aoropeza          #+#    #+#             */
/*   Updated: 2024/05/11 13:02:46 by akent-go         ###   ########.fr       */
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
# define RPL_QUIT(source, message)  ":" + source + " QUIT :" + message + "\r\n"
# define RPL_PRIVMSG(source, target, message) ":" + source + " PRIVMSG " + target + " :" + message + "\r\n"

// ERROR REPLIES
# define ERR_NOSUCHNICK(user) ": 401 " + user + " :No existe el nick/canal\r\n"
# define ERR_NOSUCHCHANNEL(channel) ": 403 " + channel + " : Channel not Found" + "\r\n"
# define ERR_TOOMANYCHANNELS(user, channel, reason) ": 405 " + user + " " + channel + " :" + reason + "\r\n"
# define ERR_NOTONCHANNEL(channel) ": 442 " + channel + " :No estás en ese canal\r\n"
# define ERR_USERONCHANNEL(user, channel) ": 443 " + user + " " + channel + " " + " :ya está en el canal\r\n"
# define ERR_NEEDMOREPARAMS(user, command, reason) ": 461 " + user + " " + command + " :" + reason + "\r\n"
# define ERR_CHANNELISFULL(user, channel, reason) ": 471 " + user + " " + channel + " :" + reason + "\r\n"
# define ERR_INVITEONLYCHAN(user, channel, reason) ": 473 " + user + " " + channel + " :" + reason + "\r\n"
# define ERR_BADCHANNELKEY(user, channel, reason) ": 475 " + user + " " + channel + " :" + reason + "\r\n"
# define ERR_BADCHANMASK(user, channel, reason) ": 476 " + user + " " + channel + " :" + reason + "\r\n"
# define ERR_CHANOPRIVSNEEDED(user, channel) ": 482 " + user + " " + channel + " :No es operador de canal\r\n"

#endif
