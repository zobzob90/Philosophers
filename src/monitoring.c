/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:26:02 by eric              #+#    #+#             */
/*   Updated: 2025/04/25 12:15:17 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * philo_is_dead - Vérifie si un philosophe est mort.
 * @philo: Structure représentant un philosophe.
 * @time_to_die: Temps maximum qu'un philosophe peut passer sans manger.
 *
 * Cette fonction vérifie si le temps écoulé depuis le dernier repas
 * d'un philosophe dépasse le temps maximum autorisé (`time_to_die`).
 * Elle utilise un mutex (`meal_lock`) pour protéger l'accès à la variable
 * `last_meal`, garantissant ainsi que cette vérification est thread-safe.
 *
 * Retourne 1 si le philosophe est mort, 0 sinon.
 */
static int	philo_is_dead(t_philo *philo, long time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

/**
 * check_if_decomposing - 
 * Vérifie si un philosophe est mort dans la simulation.
 * @philo: Tableau de structures représentant les philosophes.
 *
 * Cette fonction parcourt tous les philosophes pour 
 * vérifier si l'un d'entre eux
 * est mort en appelant `philo_is_dead`. 
 * Si un philosophe est mort, elle affiche
 * un message indiquant sa mort et 
 * retourne 1 pour signaler que la simulation doit se terminer.
 *
 * Retourne 1 si un philosophe est mort, 0 sinon.
 */
static int	check_if_decomposing(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo[0].philo_nbr)
	{
		if (philo_is_dead(&philo[i], philo[i].time_to_die))
		{
			print_msg("died", &philo[i], philo[i].philo_id);
			return (1);
		}
	}
	return (0);
}

/**
 * check_is_full - Vérifie si tous les philosophes 
 * ont terminé leurs repas.
 * @philo: Tableau de structures représentant les philosophes.
 *
 * Cette fonction parcourt tous les philosophes 
 * pour vérifier si chacun d'entre eux
 * a atteint le nombre limite de repas (`meal_count`). 
 * Si tous les philosophes ont
 * terminé leurs repas, 
 * elle met à jour le drapeau global `is_dead` pour signaler
 * la fin de la simulation.
 *
 * Retourne 1 si tous les philosophes ont terminé leurs repas, 0 sinon.
 */
int	check_is_full(t_philo *philo)
{
	int	i;
	int	finished_turned;

	i = -1;
	finished_turned = 0;
	if (philo[0].meal_count == -1)
		return (0);
	while (++i < philo[0].philo_nbr)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].count_eat >= philo[i].meal_count)
			finished_turned++;
		pthread_mutex_unlock(philo[i].meal_lock);
	}
	if (finished_turned == philo[0].philo_nbr)
	{
		pthread_mutex_lock(philo[0].meal_lock);
		pthread_mutex_lock(philo[0].dead_lock);
		*philo->is_dead = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		pthread_mutex_unlock(philo[0].meal_lock);
		return (1);
	}
	return (0);
}

/**
 * monitor - Thread de monitoring pour la simulation.
 * @av: Tableau de structures représentant les philosophes.
 *
 * Cette fonction est exécutée dans un thread séparé et surveille l'état global
 * de la simulation. Elle effectue les vérifications suivantes :
 * 1. Si un philosophe est mort (`check_if_decomposing`).
 * 2. Si tous les philosophes ont terminé leurs repas (`check_is_full`).
 *
 * Si l'une de ces conditions est remplie, elle affiche un message approprié
 * et termine la simulation.
 *
 * Retourne NULL lorsque la simulation est terminée.
 */
void	*monitor(void *av)
{
	t_philo	*philo;

	philo = (t_philo *)av;
	while (1)
	{
		if (check_if_decomposing(philo) == 1)
			break ;
		if (check_is_full(philo) == 1)
		{
			printf("\033[5m🎉 Les philosophes ont terminé ! 🎉\033[0m\n");
			break ;
		}
	}
	return (NULL);
}
