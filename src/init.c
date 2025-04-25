/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:25:56 by eric              #+#    #+#             */
/*   Updated: 2025/04/23 08:53:34 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * init_forks - Initialise les fourchettes et leurs mutex associés.
 * @forks: Tableau de structures représentant les fourchettes.
 * @philo_num: Nombre total de philosophes (et donc de fourchettes).
 *
 * Cette fonction initialise un tableau de fourchettes. 
 * Chaque fourchette est
 * associée à un mutex pour garantir un accès exclusif. 
 * Chaque fourchette reçoit
 * également un identifiant unique (fork_id) 
 * correspondant à son index dans le tableau.
 */
void	init_forks(t_fork *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i].mutex, NULL);
		forks[i].fork_id = i;
		i++;
	}
}

/**
 * init_data - Initialise les paramètres 
 * de simulation pour un philosophe.
 * @philo: Structure représentant un philosophe.
 * @av: Tableau des arguments passés au programme.
 *
 * Cette fonction configure les paramètres spécifiques à un philosophe,
 * tels que le nombre total de philosophes,
 * le temps avant de mourir, le temps pour manger,
 * le temps pour dormir, et le nombre limite de repas 
 * (s'il est spécifié).
 * Si aucun nombre limite de repas n'est fourni, 
 * la valeur par défaut est -1,
 * indiquant qu'il n'y a pas de limite.
 */
void	init_data(t_philo *philo, char *av[])
{
	philo->philo_nbr = ft_atol(av[1]);
	philo->time_to_die = ft_atol(av[2]);
	philo->time_to_eat = ft_atol(av[3]);
	philo->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		philo->meal_count = ft_atol(av[5]);
	else
		philo->meal_count = -1;
}

/**
 * init_philo - Initialise les philosophes avec leurs paramètres et ressources.
 * @philo: Tableau de structures représentant les philosophes.
 * @program: Structure contenant les données globales du programme.
 * @forks: Tableau de structures représentant les fourchettes.
 * @av: Tableau des arguments passés au programme.
 *
 * Cette fonction initialise chaque philosophe avec :
 * - Un identifiant unique (philo_id).
 * - Les paramètres de simulation (temps pour manger, dormir, etc.).
 * - Les références aux mutex globaux pour la synchronisation.
 * - Les fourchettes gauche et droite, assignées de manière circulaire.
 * 
 * Les philosophes partagent des mutex globaux pour protéger les sorties,
 * l'état de mort, et le compteur de repas.
 */
void	init_philo(t_philo *philo, t_prog *program, t_fork *forks, char *av[])
{
	int	i;
	int	nb;

	nb = ft_atol(av[1]);
	i = -1;
	while (++i < nb)
	{
		philo[i].philo_id = i + 1;
		philo[i].eating = 0;
		philo[i].count_eat = 0;
		init_data(&philo[i], av);
		philo[i].start_time = get_current_time();
		philo[i].last_meal = get_current_time();
		philo[i].write_lock = &program->write_lock;
		philo[i].dead_lock = &program->dead_lock;
		philo[i].meal_lock = &program->meal_lock;
		philo[i].is_dead = &program->dead_flag;
		philo[i].l_fork = &forks[i];
		if (i == 0)
			philo[i].r_fork = &forks[nb - 1];
		else
			philo[i].r_fork = &forks[i - 1];
	}
}

/**
 * init_prog - Initialise les données globales du programme.
 * @program: Structure contenant les données globales du programme.
 * @philo: Tableau de structures représentant les philosophes.
 *
 * Cette fonction initialise les données globales
 * nécessaires pour la simulation :
 * - Un drapeau global (`dead_flag`) pour indiquer si un philosophe est mort.
 * - Un tableau de philosophes.
 * - Des mutex globaux pour synchroniser les sorties, 
 * l'état de mort, et le compteur de repas.
 */
void	init_prog(t_prog *program, t_philo *philo)
{
	program->dead_flag = 0;
	program->philo = philo;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}
