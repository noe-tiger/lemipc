/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#ifndef MY_H_
# define MY_H_

# include <sys/types.h>
# include <sys/shm.h>
# include <sys/sem.h>
# include <sys/msg.h>
# include <sys/ipc.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

# define ERROR 84
# define SUCESS 0
# define MAP_LENGTH 10
# define MAP_WIDTH 10
# define SPACE 2

# define HELP "USAGE\n\t./lemipc PATH TEAM_NUMBER\nDESCRIPTION\n\
\tPATH\tpath you'll give to ftok\n\tTEAM_NUMBER\tteam number of \
the current champion (greater than 0)"

typedef struct	pos_s
{
	int	x;
	int	y;
}		pos_t;

typedef struct	data_s
{
	int *map;
	key_t key;
	int mem;
	int msg;
	int sem;
	int team_name;
	pos_t pos;
	int host;
	struct sembuf move;
	struct sembuf alive;
}		data_t;

int connect(data_t *, char *, int);
int disconnect(data_t *);
int game_loop(data_t *);
int move_bot(data_t *, int);

int north(data_t *);
int south(data_t *);
int east(data_t *);
int west(data_t *);

extern int (*direction[4])(data_t *data);

#endif /* MY_H_ !*/
