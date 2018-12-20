/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include "my.h"

static void print_map(data_t *data)
{
	data->move.sem_op = 1;
	while (semctl(data->sem, 0, GETVAL) > 0);
	semop(data->sem, &data->move, 1);
	for (int i = 0; i < MAP_LENGTH; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			printf("%3i", data->map[MAP_LENGTH * i + j]);
		}
		printf("\n");
	}
	data->move.sem_op = -1;
	semop(data->sem, &data->move, 1);
}

static int	check_map(data_t *data)
{
	int	i = 0;
	int	tmp;

	while (data->map[i] == 0 && i != (MAP_LENGTH * MAP_WIDTH))
		i++;
	tmp = data->map[i];
	i = 0;
	while (i != (MAP_LENGTH * MAP_WIDTH))
	{
		if (data->map[i] != 0 && data->map[i] != tmp)
			return (0);
		i++;
	}
	return (1);
}

static int host_display(data_t *data, int check)
{
	if (data->host == 1 && check != 1)
		while (semctl(data->sem, 1, GETVAL) != -1)
		{
			printf("connected : %d\n",
				semctl(data->sem, 1, GETVAL));
			print_map(data);
			sleep(1);
		}
	return (SUCESS);
}

static int host_play(data_t *data, char *dead)
{
	printf("connected : %d\n", semctl(data->sem, 1, GETVAL));
	if (move_bot(data, data->team_name) == ERROR)
		*dead = 1;
	print_map(data);
	return (SUCESS);
}

int game_loop(data_t *data)
{
	char dead = 0;
	char check = 0;
	char tmp = 0;

	while (dead == 0 && check == 0)
	{
		if (data->host == 1)
			host_play(data, &dead);
		else
			if (move_bot(data, data->team_name) == ERROR)
				dead = 1;
		if (check_map(data) == 0)
			tmp = 1;
		if (tmp == 1)
			if (check_map(data) == 1)
				check = 1;
		sleep(1);
	}
	host_display(data, check);
	return (SUCESS);
}
