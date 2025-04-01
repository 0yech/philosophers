/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 07:57:59 by nrey              #+#    #+#             */
/*   Updated: 2025/04/01 21:25:29 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_lastmeal(t_table *table)
{
	long	i;
	t_philo	*tmp;
	long	start;

	start = get_ms_time(table);
	i = 0;
	tmp = table->philos;
	while (i < table->nphilo)
	{
		tmp->mealcount = 0;
		pthread_mutex_lock(&tmp->meal_mutex);
		tmp->lastmeal = start;
		pthread_mutex_unlock(&tmp->meal_mutex);
		tmp = tmp->next;
		i++;
	}
}

int	init_meal_mutex(t_philo *head, long nphilo)
{
	long	i;
	t_philo	*tmp;

	i = 0;
	tmp = head;
	while (i < nphilo)
	{
		if (pthread_mutex_init(&tmp->meal_mutex, NULL) != 0)
			return (1);
		tmp->lastmeal = get_ms_time(head->table);
		tmp = tmp->next;
		i++;
	}
	return (0);
}

void	assign_table(t_philo *head, t_table *table)
{
	t_philo	*cpy;
	int		i;

	i = 0;
	cpy = head;
	while (i < table->nphilo)
	{
		cpy->table = table;
		i++;
		cpy = cpy->next;
	}
}

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
	assign_table(head, table);
	if (init_meal_mutex(head, table->nphilo) != 0)
		return (free_philo(head, table->nphilo, table->forks), NULL);
	return (head);
}
