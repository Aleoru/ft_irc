/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:22:05 by aoropeza          #+#    #+#             */
/*   Updated: 2024/05/19 13:55:16 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
# define REPLIES_HPP

// user = nickname
# define RPL_WELCOME(user, source) ": 001 " + user + " :Welcome to the Internet Relay Network " + source + "\r\n"
# define RPL_NOTOPIC(user, channel) ": 331 " + user + " " + channel + " :No topic is set\r\n"
# define RPL_TOPIC(user, channel, topic) ": 332 " + user + " " + channel + " :" + topic + "\r\n"
# define RPL_INVITING(user, channel) ": 341 " + user + " " + channel + "\r\n"
# define RPL_NAMREPLY(user, channel, list) ": 353 " + user + " = " + channel + " :" + list + "\r\n"
# define RPL_ENDOFNAMES(user, channel) ": 366 " + user + " " + channel + " :End of /NAMES list\r\n"
# define RPL_INFO(user,info) ": 371 :" + user + " " + info + "\r\n"

// source = nickname!username@host
# define RPL_NICKCHANGE(source, newname) ":" + source + " NICK " + newname + "\r\n"
# define RPL_JOIN(source, channel) ":" + source + " JOIN :" + channel + "\r\n"
# define RPL_PART(source, channel) ":" + source + " PART :" + channel + "\r\n"
# define RPL_QUIT(source, message) ":" + source + " QUIT :" + message + "\r\n"
# define RPL_INVITE(source, target, channel) ":" + source + " INVITE " + target + " :" + channel + "\r\n"
# define RPL_KICK(source, channel, target, reason) ":" + source + " KICK " + channel + " " + target + " " + reason + "\r\n"
# define RPL_PRIVMSG(source, target, message) ":" + source + " PRIVMSG " + target + " :" + message + "\r\n"

// ERROR REPLIES
# define ERR_NOSUCHNICK(user) ": 401 " + user + " :No such nick\r\n"
# define ERR_NOSUCHCHANNEL(user, channel, reason) ": 403 " + user + " " + channel + " :" + reason + "\r\n"
# define ERR_TOOMANYCHANNELS(user, channel, reason) ": 405 " + user + " " + channel + " :" + reason + "\r\n"
# define ERR_NONICKNAME(nickname) ": 431 " + nickname + " :No nickname given" + "\r\n"
# define ERR_ERRONEUSNICKNAME(nickname) ": 432 " + nickname + " Invalid chars given" + "\r\n" 
# define ERR_NICKINUSE(nickname) ": 433 " + nickname + " :Nickname in use" + "\r\n"
# define ERR_NOTONCHANNEL(user, channel) ": 442 " + user + " " + channel + " :User not on channel\r\n"
# define ERR_USERONCHANNEL(user, channel) ": 443 " + user + " " channel + " " + " :User already on channel\r\n"
# define ERR_NEEDMOREPARAMS(user, command, reason) ": 461 " + user + " " + command + " :" + reason + "\r\n"
# define ERR_PASSWDMISMATCH(user) ": 464 " + user + " :Password incorrect\r\n"
# define ERR_CHANNELISFULL(user, channel, reason) ": 471 " + user + " " + channel + " :" + reason + "\r\n"
# define ERR_INVITEONLYCHAN(user, channel, reason) ": 473 " + user + " " + channel + " :" + reason + "\r\n"
# define ERR_BADCHANNELKEY(user, channel, reason) ": 475 " + user + " " + channel + " :" + reason + "\r\n"
# define ERR_BADCHANMASK(user, channel, reason) ": 476 " + user + " " + channel + " :" + reason + "\r\n"
# define ERR_CHANOPRIVSNEEDED(user, channel) " : 482 " + user + " " + channel + " :You don't have operator priviledges\r\n"

#endif
