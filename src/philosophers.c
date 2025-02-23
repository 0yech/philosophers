/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:31:40 by nrey              #+#    #+#             */
/*   Updated: 2025/02/23 09:12:04 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table		table;
	t_philo		*philos;

	if (init_table(argc, argv, &table) == 1)
		return (1);
	philos = init_philo(&table);
	printf("Numbers of philo : %ld\n", table.nphilo);
	printf("Time To Die : %ld\n", table.timetodie);
	printf("Time To Eat : %ld\n", table.timetoeat);
	printf("Time To Sleep : %ld\n", table.timetosleep);
	printf("Numbers of times to eat : %ld\n", table.ntimemusteat);
	printf("philo n%d's left fork ptr : %p\n", philos->id, philos->left_fork);
	printf("philo n%d's right fork ptr : %p\n", philos->id, philos->right_fork);
	printf("\n");
	printf("philo n%d's right fork ptr : %p\n", philos->prev->id, philos->prev->right_fork);
	printf("philo n%d's left fork ptr : %p\n", philos->next->id, philos->next->left_fork);
	free_philo(philos, table.nphilo, table.forks);
	return (0);
}
