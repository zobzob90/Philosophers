/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:26:05 by eric              #+#    #+#             */
/*   Updated: 2025/04/25 12:15:12 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * eat - Permet à un philosophe de manger.
 * @philo: Structure représentant un philosophe.
 *
 * Cette fonction gère l'action de manger pour un philosophe. 
 * Elle effectue les étapes suivantes :
 * 1. Vérifie si le philosophe est mort ou si tous 
 * 		les philosophes ont terminé leurs repas.
 * 2. Verrouille les mutex des fourchettes 
 * 		(droite puis gauche).
 * 3. Met à jour les données du philosophe 
 * 		(dernier repas, compteur de repas).
 * 4. Attend le temps nécessaire pour manger 
 * 		(`time_to_eat`).
 * 5. Déverrouille les mutex des fourchettes.
 *
 * Si le philosophe est seul (cas spécial avec `philo_nbr == 1`), 
 * il ne peut pas prendre deux fourchettes
 * et attend simplement jusqu'à ce qu'il meure.
 */
void	eat(t_philo *philo)
{
	if (is_dead(philo) && check_is_full(philo))
		return ;
	pthread_mutex_lock(&philo->r_fork->mutex);
	print_msg("has taken a fork", philo, philo->philo_id);
	if (philo->philo_nbr == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(&philo->r_fork->mutex);
		return ;
	}
	pthread_mutex_lock(&philo->l_fork->mutex);
	print_msg("has taken a fork", philo, philo->philo_id);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	print_msg("is eating", philo, philo->philo_id);
	philo->last_meal = get_current_time();
	philo->count_eat++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->l_fork->mutex);
	pthread_mutex_unlock(&philo->r_fork->mutex);
}

/**
 * ft_sleep - Permet à un philosophe de dormir.
 * @philo: Structure représentant un philosophe.
 *
 * Cette fonction gère l'action de dormir pour un philosophe. 
 * Elle effectue les étapes suivantes :
 * 1. Vérifie si le philosophe est mort.
 * 2. Affiche un message indiquant que le philosophe dort.
 * 3. Attend le temps nécessaire pour dormir (`time_to_sleep`).
 */
void	ft_sleep(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	print_msg("is sleeping", philo, philo->philo_id);
	ft_usleep(philo->time_to_sleep);
}

/**
 * think - Permet à un philosophe de penser.
 * @philo: Structure représentant un philosophe.
 *
 * Cette fonction gère l'action de penser pour un philosophe. 
 * Elle effectue les étapes suivantes :
 * 1. Vérifie si le philosophe est mort.
 * 2. Affiche un message indiquant que le philosophe pense.
 */
void	think(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	print_msg("is thinking", philo, philo->philo_id);
}

/**
 * is_dead - Vérifie si la simulation est terminée (un philosophe est mort).
 * @philo: Structure représentant un philosophe.
 *
 * Cette fonction vérifie si le drapeau global `is_dead` est activé, 
 * indiquant qu'un philosophe est mort
 * ou que la simulation est terminée. 
 * Elle utilise un mutex (`dead_lock`) pour garantir un accès thread-safe.
 *
 * Retourne 1 si la simulation est terminée, 0 sinon.
 */
int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->is_dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

/**
 * routine - Routine principale exécutée par chaque philosophe.
 * @av: Argument passé au thread (structure représentant un philosophe).
 *
 * Cette fonction gère le cycle de vie d'un philosophe. 
 * Elle effectue les étapes suivantes :
 * 1. Si l'ID du philosophe est pair, 
 * 		il attend 100 ms avant de commencer (pour éviter les conflits).
 * 2. Tant que la simulation n'est pas terminée (`is_dead`), 
 * 		le philosophe effectue les actions suivantes :
 *    - Manger (`eat`).
 *    - Dormir (`ft_sleep`).
 *    - Penser (`think`).
 * 3. Si le philosophe a atteint son quota de repas 
 * (`has_reached_meal_limit`), il quitte la boucle.
 *
 * Retourne un pointeur vers la structure du philosophe.
 */
void	*routine(void *av)
{
	t_philo	*philo;

	philo = (t_philo *) av;
	if (philo->philo_id % 2 == 0)
		ft_usleep(100);
	while (!is_dead(philo))
	{
		eat(philo);
		if ((philo->meal_count != -1
				&& has_reached_meal_limit(philo)) || is_dead(philo))
			break ;
		ft_sleep(philo);
		if (is_dead(philo))
			break ;
		think(philo);
	}
	return (av);
}
