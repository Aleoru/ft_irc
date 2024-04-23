/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:22:05 by aoropeza          #+#    #+#             */
/*   Updated: 2024/04/23 20:29:25 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
# define REPLIES_HPP

// user = nickname
# define RPL_NOTOPIC(user, channel) ": 331 " + user + " " + channel + " :No topic is set\r\n"
# define RPL_TOPIC(user, channel, topic) ": 332 " + user + " " + channel + " :" + topic + "\r\n"
# define RPL_NAMREPLY(user, channel, list) ": 353 " + user + " " + channel + " :" + list + "\r\n"

// source = nickname!username@host
# define RPL_JOIN(source, channel)	":" + source + " JOIN :" + channel + "\r\n"

#endif