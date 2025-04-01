/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 01:37:45 by nrey              #+#    #+#             */
/*   Updated: 2025/04/01 21:30:32 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eat_pair(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (is_dead(philo->table))
		return (pthread_mutex_unlock(philo->left_fork), 0);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	if (is_dead(philo->table))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	print_state(philo, "has taken a fork");
	return (1);
}

int	eat_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (is_dead(philo->table))
		return (pthread_mutex_unlock(philo->right_fork), 0);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	if (is_dead(philo->table))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	print_state(philo, "has taken a fork");
	return (1);
}

int	philo_eats(t_philo *philo)
{
	if (is_dead(philo->table))
		return (0);
	if (philo->id % 2 == 0)
	{
		if (!eat_pair(philo))
			return (0);
	}
	else
	{
		if (!eat_odd(philo))
			return (0);
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->lastmeal = get_ms_time(philo->table);
	pthread_mutex_unlock(&philo->meal_mutex);
	if (is_dead(philo->table))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	can_eat(philo);
	return (1);
}

void	active_routine(t_philo *philo)
{
	while (!is_dead(philo->table))
	{
		print_state(philo, "is thinking");
		if (!philo_eats(philo))
			break ;
		if (is_dead(philo->table))
			break ;
		pthread_mutex_lock(&philo->meal_mutex);
		philo->mealcount++;
		pthread_mutex_unlock(&philo->meal_mutex);
		if (philo->table->ntimemusteat != -1
			&& philo->mealcount >= philo->table->ntimemusteat)
			break ;
		if (is_dead(philo->table))
			break ;
		print_state(philo, "is sleeping");
		precise_usleep(philo->table->timetosleep, philo->table);
		if (is_dead(philo->table))
			break ;
		print_state(philo, "is thinking");
		precise_usleep(5, philo->table);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->nphilo == 1)
	{
		print_state(philo, "has taken a fork");
		precise_usleep(philo->table->timetodie + 2, philo->table);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		precise_usleep(philo->table->timetoeat / 10, philo->table);
	active_routine(philo);
	return (NULL);
}
