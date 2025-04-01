/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 01:37:45 by nrey              #+#    #+#             */
/*   Updated: 2025/04/01 16:24:23 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int    philo_eats(t_philo *philo)
{
	if (is_dead(philo->table))
		return (0);
    if (philo->id % 2 == 0)
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
    }
    else
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
    print_state(philo, "is eating");
    precise_usleep(philo->table->timetoeat, philo->table);
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);

    return (1);
}

void    *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;

	if (philo->table->nphilo == 1)
	{
		print_state(philo, "has taken a fork");
        precise_usleep(philo->table->timetodie + 2, philo->table);
        return NULL;
	}
    if (philo->id % 2 == 0)
        precise_usleep(philo->table->timetoeat / 10, philo->table);
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
        //precise_usleep(5, philo->table);
    }
    return NULL;
}