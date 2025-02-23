/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 07:57:59 by nrey              #+#    #+#             */
/*   Updated: 2025/02/23 09:09:37 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	fill_philo(long nphilo, pthread_mutex_t *forks, t_philo **head,
	t_philo **prev)
{
	long	i;
	t_philo	*new;

	i = 0;
	*head = NULL;
	while (i < nphilo)
	{
		new = malloc(sizeof(t_philo));
		if (!new)
			return (free_philo(*head, i, forks), 1);
		new->id = i + 1;
		new->left_fork = &forks[i];
		new->right_fork = &forks[(i + 1) % nphilo];
		new->next = NULL;
		if (*prev)
		{
			(*prev)->next = new;
			new->prev = *prev;
		}
		else
			*head = new;
		*prev = new;
		i++;
	}
	return (0);
}

t_philo	*init_philo(t_table *table)
{
	long	i;
	t_philo	*head;
	t_philo	*prev;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->nphilo);
	if (!table->forks)
		return (NULL);
	head = NULL;
	prev = NULL;
	i = 0;
	while (i < table->nphilo)
		pthread_mutex_init(&table->forks[i++], NULL);
	if (fill_philo(table->nphilo, table->forks, &head, &prev) == 1)
		return (free(table->forks), NULL);
	prev->next = head;
	head->prev = prev;
	return (head);
}
