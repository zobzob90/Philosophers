/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:36:23 by ertrigna          #+#    #+#             */
/*   Updated: 2025/04/16 08:52:42 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

const char	*get_color(int philo_id)
{
	const char	*color[] = {
		"\033[31m",
		"\033[32m",
		"\033[33m",
		"\033[34m",
		"\033[35m",
		"\033[36m",
		"\033[37m",
	};
	int			colour_count;

	colour_count = sizeof(color) / sizeof(color[0]);
	return (color[philo_id % colour_count]);
}
