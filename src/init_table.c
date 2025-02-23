/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:42:43 by nrey              #+#    #+#             */
/*   Updated: 2025/02/23 08:39:34 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long	ft_atol(char *str)
{
	long	result;

	result = 0;
	if (ft_strlen(str) > 10)
		return (2147483647);
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (result > 2147483647)
		return (2147483647);
	return (result);
}

int	only_has_nums(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

int	parse_nums(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (only_has_nums(argv[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	init_table(int argc, char **argv, t_table *table)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (parse_nums(argv) == 1)
		return (1);
	table->nphilo = ft_atol(argv[1]);
	table->timetodie = ft_atol(argv[2]);
	table->timetoeat = ft_atol(argv[3]);
	table->timetosleep = ft_atol(argv[4]);
	if (argc == 6)
		table->ntimemusteat = ft_atol(argv[5]);
	else
		table->ntimemusteat = -1;
	return (0);
}
