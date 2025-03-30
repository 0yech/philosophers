/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by nrey              #+#    #+#             */
/*   Updated: 2025/03/28 20:15:46 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int     philos_full(t_table *table)
{
    long    i;
    t_philo *tmp;

    if (table->ntimemusteat == -1)
        return (0);
    i = 0;
    tmp = table->philos;
    while (i < table->nphilo)
    {
        pthread_mutex_lock(&tmp->meal_mutex);
        if (tmp->mealcount < table->ntimemusteat)
        {
            pthread_mutex_unlock(&tmp->meal_mutex);
            return (0);
        }
        pthread_mutex_unlock(&tmp->meal_mutex);
        tmp = tmp->next;
        i++;
    }
    return (1);
}

int     is_dead(t_table *table)
{
    int state;

    pthread_mutex_lock(&table->dead_mutex);
    state = table->is_dead;
    pthread_mutex_unlock(&table->dead_mutex);
    return (state);
}

void	monitor(t_table *table)
{
    long    i;
    t_philo *tmp;

    while (1)
    {
        if (philos_full(table))
            return ;
        i = 0;
        tmp = table->philos;
        while (i < table->nphilo)
        {
            pthread_mutex_lock(&tmp->meal_mutex);
            if (get_ms_time(table) - tmp->lastmeal > table->timetodie)
            {
                print_state(tmp, "died");
                pthread_mutex_unlock(&tmp->meal_mutex);
                pthread_mutex_lock(&table->dead_mutex);
                table->is_dead = 1;
                pthread_mutex_unlock(&table->dead_mutex);
                return ;
            }
            pthread_mutex_unlock(&tmp->meal_mutex);
            tmp = tmp->next;
            i++;
        }
        usleep(1000);
    }
}