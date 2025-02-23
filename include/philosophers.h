/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:31:16 by nrey              #+#    #+#             */
/*   Updated: 2025/02/23 09:07:31 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_philo
{
	int				id;
	struct s_philo	*next;
	struct s_philo	*prev;
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
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_table;

int		init_table(int argc, char **argv, t_table *table);

t_philo	*init_philo(t_table *table);

void	free_philo(t_philo *head, int nphilo, pthread_mutex_t *forks);