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

bool	findUserList(std::string nick, std::vector<User> users) //PONER EN UTILS
{
	std::vector<User>::iterator it = std::find(users.begin(), users.end(), nick);
	if (it != users.end())
		return true;
	return false;
}

void	invite(Server serv, std::string inv_user, Channel canal, bool needOp) //last var is temporary atm
{
	if (!serv.channelExists(canal.getName())) //Esta comprobación es innecesaria según el protocolo pero es posible que de lugar a un error de segmentación o se crea un canal nuevo?
		return ;
	std::vector<User> users = serv.getUsers(); //Vector for Users in the server
	std::vector<User>::iterator it = users.begin(); //Iterator for users in the server
	std::vector<User> users_ch = canal.getUsers(); //Vector for Users in the channel
	std::vector<User> ops = canal.getOperators(); //FALTA HACER ESTE GETTER
	for(it; it != users.end(); it++)
	{
		if (needOp == true)
		{
			if (it->getNick() == inv_user && !findUserList(it->getNick(), users_ch) && !findUserList(it->getNick(), ops))  //si existe el nick en el servidor y no está unido al canal
			{
				canal.addUserToList(*it);
				serv.sendMessage(1, RPL_INVITING(it->getNick(), canal.getName()));
				return ;
			}
		}
		else if (needOp == false)
		{
			if (it->getNick() == inv_user && !findUserList(it->getNick(), users_ch))  //si existe el nick en el servidor y no está unido al canal
				canal.addUserToList(*it);
		}
	}
	serv.sendMessage(1, ERR_NOSUCHNICK(it->getNick())); //Si no hemos podido añadir el usuario al canal, la última opción es que no exista el usuario y por ende, no se haya podido invitar
	return ;
}