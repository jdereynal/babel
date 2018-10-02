/*
** EPITECH PROJECT, 2018
** babel
** File description:
** main
*/

#include "TcpServer.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
		return 84;
	boost::asio::io_service io;
	auto port = std::stoi(av[1]);
	if (!port || port < 0)
		return (84);
	auto serv = new TcpServer(io, port);
	io.run();
	return 0;
}
