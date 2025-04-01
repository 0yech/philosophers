/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:31:16 by nrey              #+#    #+#             */
/*   Updated: 2025/04/01 21:27:07 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	struct s_philo	*next;
	struct s_philo	*prev;
	struct s_table	*table;
	long			lastmeal;
	int				mealcount;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_table
{
	long			nphilo;
	long			timetodie;
	long			timetoeat;
	long			timetosleep;
	long			ntimemusteat;
	long			start;
	int				is_dead;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_t		*threads;
}	t_table;

int		init_table(int argc, char **argv, t_table *table);

t_philo	*init_philo(t_table *table);
void	init_lastmeal(t_table *table);

void	free_philo(t_philo *head, int nphilo, pthread_mutex_t *forks);

long	get_ms_time(t_table *table);
long	get_current_time(void);
void	can_eat(t_philo *philo);

void	print_state(t_philo *philo, char *state);
void	precise_usleep(long time_ms, t_table *table);

void	*philo_routine(void *arg);
int		join_threads(t_table *table);
int		create_threads(t_table *table);

int		is_dead(t_table *table);
void	monitor(t_table *table);

#endif