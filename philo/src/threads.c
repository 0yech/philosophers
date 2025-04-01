/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 01:57:32 by nrey              #+#    #+#             */
/*   Updated: 2025/04/01 21:19:19 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	join_threads(t_table *table)
{
	long	i;

	i = 0;
	while (i < table->nphilo)
	{
		if (pthread_join(table->threads[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	create_threads(t_table *table)
{
	long	i;
	t_philo	*tmp;

	i = 0;
	table->threads = malloc(sizeof(pthread_t) * table->nphilo);
	if (!table->threads)
		return (1);
	tmp = table->philos;
	while (i < table->nphilo)
	{
		if (pthread_create(&table->threads[i], NULL,
				philo_routine, (void *)tmp) != 0)
			return (1);
		tmp = tmp->next;
		i++;
	}
	return (0);
}
