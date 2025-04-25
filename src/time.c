/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:26:08 by eric              #+#    #+#             */
/*   Updated: 2025/04/23 10:21:10 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * get_current_time - Retourne le temps actuel en millisecondes.
 *
 * Cette fonction utilise `gettimeofday` pour obtenir le temps actuel
 * en secondes et microsecondes depuis l'époque Unix (1er janvier 1970).
 * Elle convertit ensuite ce temps en millisecondes pour une utilisation
 * plus pratique dans la simulation.
 *
 * Retourne :
 * - Le temps actuel en millisecondes sous forme de `long`.
 */
long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
 * ft_usleep - Met le thread en pause pendant 
 * une durée spécifiée en millisecondes.
 * @time_in_ms: Durée de la pause en millisecondes.
 *
 * Cette fonction utilise une boucle active combinée à `usleep` pour
 * garantir une pause précise en millisecondes. 
 * Elle vérifie régulièrement si la durée spécifiée 
 * est écoulée en utilisant `get_current_time`.
 *
 * Paramètres :
 * - time_in_ms : Durée de la pause en millisecondes.
 *
 * Retourne :
 * - 0 si la pause s'est terminée avec succès.
 */
int	ft_usleep(long time_in_ms)
{
	long long	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < time_in_ms)
		usleep(100);
	return (0);
}
