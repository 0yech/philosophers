/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by nrey              #+#    #+#             */
/*   Updated: 2025/03/28 20:09:48 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long    get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	get_ms_time(t_table *table)
{
	return ((get_current_time() - table->start));
}

void    precise_usleep(long time_ms, t_table *table)
{
	long	start;

	start = get_ms_time(table);
	while (get_ms_time(table) - start < time_ms)
	{
		if (is_dead(table))
			break ;
		usleep(100);
	}
}