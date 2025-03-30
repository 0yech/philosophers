/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:26:43 by nrey              #+#    #+#             */
/*   Updated: 2025/03/30 03:43:19 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    print_state(t_philo *philo, char *state)
{
    pthread_mutex_lock(&philo->table->write_mutex);
    printf("%ld %d %s\n", get_ms_time(philo->table), philo->id, state);
    pthread_mutex_unlock(&philo->table->write_mutex);
}