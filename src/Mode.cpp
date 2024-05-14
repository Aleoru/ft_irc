#include "../inc/User.hpp"
#include "../inc/Server.hpp"
#include "../inc/Channel.hpp"
#include "../inc/replies.hpp"


/*Para el mode tenemos que hacer varias cositas, realmente es simple, es una función que solo pueden usar los administradores y que
Cambia los estados del canal, es decir, esta mañana se queda hecho, veamos el protocolo:
Dividimos el mode en 2 partes:
-Modos del canal
-Modos del usuario

********MODOS DEL CANAL********
o - give/take channel operator privileges;
	   p - private channel flag;
	   i - invite-only channel flag;
	   t - topic settable by channel operator only flag;
	   m - moderated channel;
	   l - set the user limit to channel;
	   k - set a channel key (password).

   When using the 'o' option, a restriction on a total of three
   per mode command has been imposed.


*/
std::string trim(const std::string& str)
{
	std::string::const_iterator begin = str.begin();
	std::string::const_iterator end = str.end();

	while (begin != end && std::isspace(*begin))
		++begin;
	while (begin != end && std::isspace(*(end - 1)))
		--end;
	return std::string(begin, end);
}

bool	isNum(std::string str)
{
	int i = 0;

	while (i <= str.length())
	{
		if (str[i] <= '0' || str[i] >= '9')
			return false;
		i++;
	}
	return true;
}

int		countUsers(Channel canal)
{
	std::vector<User> users = canal.getUsers();
	return ((int)users.size());
}

bool	checkFlag(std::string flag, int mode) //Esta función comprueba las flags
{
	//usamos un trim para el principio y final del string, que elimine espacios y tabulaciones
	//Después comprobamos los flags y a mamarla
	flag = trim(flag); //es posible que los parametros ya vengan trimeados⚠️
	if (mode == 0) //mode es 1 si estamos haciendo un cambio pa usuarios
	{
		if (flag != "-o" && flag != "+o")
			return false; //lanzar un mensaje de flag erronea
	}
	else if (mode == 1) //mode es 2 si metemos flags menos la +-l
	{
		if (flag != "-i" && flag != "+i" && flag != "+t" && flag != "-t")
			return false;
	}
	else 
	{
		if (flag != "+l" && flag != "-l")
			return false;
	}
	return true;
}

void	Server::userMode(std::vector<std::string> cmd, int fd) //LISTO Y EL MODE NO DA RESPUESTA EN LOS CASOS QUE SE CAMBIA EL MODO
{
	/*
		El mode del usuario es super fácil, solo tiene una flag válida, -o que lo convierte en operador
		1- Comprobar todos los cmd's para ver que solo pueda haber 3, cmd[0] = MODE, cmd[1] = #canal cmd[2] = user, cmd[3] = flag +-o
		2- Comprobar que el usuario que vamos a hacer admin está en el canal y que no es admin ya
		3- comprobar la flag y hacer admin al usuario o quitar de admin
	*/
	std::string user = cmd[2];
	std::string channel_in = cmd[1];
	std::string flag = cmd[3];
	Channel *canal = searchChannel(channel_in);
	std::vector<User> usuarios = canal->getUsers();
	std::vector<User>::iterator it;


	if (cmd.size() > 4) //Hemos comprobado que la cantidad de argumentos está bien
		sendMessage(fd, ERR_NEEDMOREPARAMS(searchUser(fd)->getNick(), "MODE", "Invalid arguments"));
	else
	{
		if (checkFlag(cmd[3], 0))
		{
			if (userExists(canal->getUsers(), searchUser(user)->getNick())) //prueba 2 hecha
			{
				if (!canal->operatorExists(searchUser(fd)->getNick()) && cmd[3] == "+o")
					canal->addOperatorToList(*searchUser(fd)); //No reply is sent apparently
				else if (canal->operatorExists(searchUser(fd)->getNick()) && cmd[3] == "+o")
					return ; //Silently ignore the command
				else if (!canal->operatorExists(searchUser(fd)->getNick())  && cmd[3] == "-o")
					return ;
				else
					canal->removeOperatorFromList(usuarios, *searchUser(fd));
			}
		}
		else
			sendMessage(fd, ERR_UMODEUNKNOWNFLAG());
	}
}
void	Server::channelMode(std::vector<std::string> cmd, int fd) //EL MODE NO DA RESPUESTA EN LOS CASOS QUE SE CAMBIA EL MODO
{
	/*
		Aquí llega la función grande, primero las comprobaciones:
		1-Ya hemos comprobado antes que el canal existe entonces no hace falta
		2-Flags
			2.1 (i)- Comprobamos el estado y actuamos
			2.2 (t)- Comprobamos el estado y actuamos
			2.3 (l)- Comprobamos el estado y si el siguiente parámetro es válido:
				2.3.1 Activado y pasamos un (-l)- Desactivamos y ponemos el nº de usuarios a 0
				2.3.2 Activado y pasamos un (+l)- Si el número es el mismo que tenemos guardado ignoramos, sino ponemos el nuevo número
				2.3.3 Desactivado y pasamos un (+l)- activamos y guardamos número de usuarios (OJO tenemos que comprobar que el número mínimo sea el número de usuarios actualmente en el canal)
	*/
	std::string user = cmd[2];
	std::string channel_in = cmd[1];
	std::string flag = cmd[3];
	Channel *canal = searchChannel(channel_in);
	std::vector<User> usuarios = canal->getUsers();
	std::vector<User>::iterator it;


	if (cmd.size() > 4 && cmd.size() < 2)
		sendMessage(fd, ERR_NEEDMOREPARAMS(searchUser(fd)->getNick(), "MODE", "Invalid arguments"));
	else if (cmd.size() == 3) //son las flags i/t
	{
		if (checkFlag(cmd[3], 1)) //tienes que mandar las respuestas no te olvides, aquí hemos comprobado ya que si la flag es mala, enviar un error
		{
			if (canal->getHasTopic() == false && cmd[3] == "+t")
				canal->setHasTopic(true); //No reply is sent apparently
			else if (canal->getHasTopic() == true && cmd[3] == "-t")
				canal->setHasTopic(false);
			else if (canal->getInvite() == false && cmd[3] == "+i") //Si es false no hace falta invitación, si es true si
				canal->setInvite(true);
			else if (canal->getInvite() == true && cmd[3] == "-i")
				canal->setInvite(false);
			else
				return ;
		}
		else
			sendMessage(fd, ERR_UMODEUNKNOWNFLAG());
	}
	else
	{
		if (checkFlag(cmd[3], 2) && isNum(cmd[4])) //Ahora toca el coñazo
		{
			int channel_limit = std::stoi(cmd[4].c_str());
			if (channel_limit < 0)
				return ;
			if (canal->getLimit() > 0 && (cmd[3] == "-l" || (cmd[3] == "+l" && channel_limit == 0)))
				canal->setLimit(0); //Quitamos el límite de usuarios y encima aprovechamos el return de debajo
			else if (cmd[3] == "+l" && (channel_limit < countUsers(*canal))) //si intentamos reducir el tamaño del canal a menos de los usuarios que hay
				return ; //ignora este comando porque el argumento del número es inválido
			else if (cmd[3] == "+l" && canal->getLimit() >= 0 && (channel_limit > 0 && channel_limit < 32))
				canal->setLimit(channel_limit); //cambiamos el límite del canal
		}
		else
			sendMessage(fd, ERR_UMODEUNKNOWNFLAG());
	}
	return ;
}

void	Server::pickMode(std::vector<std::string> cmd, int fd) //ACORDARSE DE COMPROBAR QUE FD TIENE QUE SER ADMIN
{
	//primero comprobamos si el argumento cmd[2] es un canal o un usuario si no es ninguno, comprobamos si es un canal y si no lo es tampoco lanzamos un error
	std::string first_string = cmd[2]; //usamos cmd[2] porque X-Chat autocompleta y cmd[1] pasa como parámetro el canal
	std::string channel_name = cmd[1];
	User *user = searchUser(first_string);
	Channel *channel = searchChannel(first_string);
	
	if (!user->getNick().empty()) //Si es un usuario
	{
		return ; //Es un usuario
	}
	else if (!channel->getName().empty()) //Si es un canal
	{
		return ;
	}
	else
		sendMessage(fd, ERR_NOSUCHNICK(first_string));
}