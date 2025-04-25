/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:15:26 by eric              #+#    #+#             */
/*   Updated: 2025/04/03 10:52:09 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

bool	is_positive_num(char *str)
{
	int		i;
	long	num;

	i = 0;
	if (str[i] == '-')
		return (false);
	else if (str[i] == '+')
	{
		i++;
		if (!is_digit(str[i]))
			return (false);
	}
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (false);
		i++;
	}
	num = ft_atol(str);
	if (num > INT_MAX)
		return (false);
	return (true);
}

long	ft_atol(const char *str)
{
	long	i;
	long	nb;
	long	sign;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb * sign);
}
