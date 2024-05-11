/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:55:14 by aoropeza          #+#    #+#             */
/*   Updated: 2024/05/11 12:57:02 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/User.hpp"
#include "../inc/Server.hpp"
#include "../inc/Channel.hpp"
#include "../inc/replies.hpp"

/*Una vez incluidas las librerias ahora vamos a ponernos con el Invite
Tiene como estructura: invite <nick> #<canal>
PASOS:
1-Verificar si el usuario que invita tiene permisos, lo vamos a poner como variable nula por ahora
2-Verificar si existe el usuario invitado comprobando su nick
3-Si existe el usuario y hay permisos y existe el canal, añadirlo a la lista de invitados
3.5- Si ya existe en la lista de invitados, ignorar el comando, osea no hace nada
*/

void	Server::invite(std::vector<std::string> cmd, int fd) //last var is temporary atm
{
	std::string InvitedNick = cmd[1];
	std::string channelName = cmd[2];
	
	Channel *canal = searchChannel(channelName);
	std::vector<User> users = canal->getUsers(); //Vector for Users in the server
	std::vector<User>::iterator it = users.begin(); //Iterator for users in the server
	if (!searchChannel(channelName))//Si no existe el canal, enviar NOSUCHCHANNEL
	{
		sendMessage(fd, ERR_NOSUCHCHANNEL(canal->getName()));
		return ;
	}
	else
	{
		if (searchUser(InvitedNick) != NULL)
		{
			if (canal->getInvite() == true)
			{
				if (userExists(users, InvitedNick) == true) //Si el usuario ya está en el canal
				{
					sendMessage(fd, ERR_USERONCHANNEL(InvitedNick, canal->getName()));
				}
				else if (userExists(this->getUsers(), InvitedNick) && canal->operatorExists(searchUser(fd)->getNick()))  //si existe el nick en el servidor, y no está dentro del canal ya
				{ //y si fd es administrador
					canal->addUserToList(*searchUser(InvitedNick)); //añadimos usuario a la lista de usuarios del canal
					sendMessage(1, RPL_INVITING(searchUser(InvitedNick)->getNick(), canal->getName()));
					return ;
				}
				else //Si el usuario no es administrador
					sendMessage(1, ERR_CHANOPRIVSNEEDED(searchUser(fd)->getNick(), canal->getName()));
			}
			else
			{
				if (userExists(users, InvitedNick) == true) //Si el usuario ya está en el canal
					sendMessage(fd, ERR_USERONCHANNEL(InvitedNick, canal->getName()));
				else  //si existe el nick en el servidor, y no está dentro del canal ya
				{
					canal->addUserToList(*searchUser(InvitedNick));
					sendMessage(1, RPL_INVITING(searchUser(InvitedNick)->getNick(), canal->getName()));
					return ;
				}
			}
		}
		sendMessage(1, ERR_NOSUCHNICK(it->getNick())); //Si no hemos podido añadir el usuario al canal, la última opción es que no exista el usuario y por ende, no se haya podido invitar
	}
}