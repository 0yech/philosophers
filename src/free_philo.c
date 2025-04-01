/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 09:04:58 by nrey              #+#    #+#             */
/*   Updated: 2025/04/01 21:25:38 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philo(t_philo *head, int nphilo, pthread_mutex_t *forks)
{
	t_philo	*tmp;
	t_philo	*next;
	int		i;

	i = 0;
	if (!head)
		return ;
	tmp = head;
	while (i < nphilo)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
		i++;
	}
	free(forks);
}
