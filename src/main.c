/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include "my.h"

int help(void)
{
	printf("%s\n", HELP);
	return (ERROR);
}

int	main(int ac, char **av)
{
	data_t data;

	if (ac != 3)
		return (help());
	if (connect(&data, av[1], atoi(av[2])) != SUCESS)
		return (ERROR);
	game_loop(&data);
	return (disconnect(&data));
}
