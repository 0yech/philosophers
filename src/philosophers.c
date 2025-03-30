/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:31:40 by nrey              #+#    #+#             */
/*   Updated: 2025/03/30 15:38:08 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_philos(t_philo *philos, t_table table)
{
	t_philo *cpy;
	int i;

	i = 0;
	cpy = philos;
	while (i < table.nphilo)
	{
		printf("id : %d\n", cpy->id);
		printf("lastmeal : %ld\n", cpy->lastmeal);
		printf("left fork : %p\n", cpy->left_fork);
		printf("right fork : %p\n", cpy->right_fork);
		printf("\n");
		cpy = cpy->next;
		i++;
	}
	printf("TABLE INFO\n");
	printf("Numbers of philo : %ld\n", table.nphilo);
	printf("Time to die : %ld\n", table.timetodie);
	printf("Time to eat : %ld\n", table.timetoeat);
	printf("Time to sleep : %ld\n", table.timetosleep);
	printf("Num times to eat : %ld\n", table.ntimemusteat);
}

int	main(int argc, char **argv)
{
	t_table		table;

	if (init_table(argc, argv, &table) == 1)
		return (1);
	table.philos = init_philo(&table);
	if (!table.philos)
		return (1);
	if (pthread_mutex_init(&table.write_mutex, NULL) != 0)
		return (free_philo(table.philos, table.nphilo, table.forks), 1);
	//print_philos(table.philos, table);
	init_lastmeal(&table);
	table.is_dead = 0;
	pthread_mutex_init(&table.dead_mutex, NULL);
	if (create_threads(&table) != 0)
		return (free_philo(table.philos, table.nphilo, table.forks), 1);
	monitor(&table);
	join_threads(&table);
	free_philo(table.philos, table.nphilo, table.forks);
	pthread_mutex_destroy(&table.dead_mutex);
	pthread_mutex_destroy(&table.write_mutex);
	free(table.threads);
	return (0);
}
