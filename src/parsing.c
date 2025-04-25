/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:12:35 by eric              #+#    #+#             */
/*   Updated: 2025/04/03 10:54:39 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	optional_arg(int ac, char *av[], t_philo *philo)
{
	if (ac == 6)
	{
		philo->meal_count = ft_atol(av[5]);
		if (philo->meal_count <= 0)
		{
			printf("Error: number of meals must be greater than 0\n");
			return (1);
		}
	}
	else
		philo->meal_count = -1;
	return (0);
}

static int	check_args_value(t_philo *philo)
{
	if (philo->philo_nbr > 200 || philo->philo_nbr < 1)
		return (ft_putstr_fd
			("Error: invalid number of philosophers (1-200)\n", 2), 1);
	if (philo->time_to_die <= 59
		|| philo->time_to_eat <= 59 || philo->time_to_sleep <= 59)
		return (ft_putstr_fd
			("Error: all time arguments must be greater than 60 ms\n", 2), 1);
	return (0);
}

int	parse_args(int ac, char *av[], t_philo *philo)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (ft_putstr_fd
			("Error: invalid number of arguments\n", 2), 1);
	i = 1;
	while (i < ac)
	{
		if (!is_positive_num(av[i]))
			return (ft_putstr_fd
				("Error : arguments must be a positive numbers\n", 2), 1);
		i++;
	}
	philo->philo_nbr = ft_atol(av[1]);
	philo->time_to_die = ft_atol(av[2]);
	philo->time_to_eat = ft_atol(av[3]);
	philo->time_to_sleep = ft_atol(av[4]);
	if (optional_arg(ac, av, philo) || check_args_value(philo))
		return (1);
	return (0);
}
