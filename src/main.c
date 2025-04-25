/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:25:59 by eric              #+#    #+#             */
/*   Updated: 2025/04/25 11:53:40 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	display_init(t_philo *philo)
{
	int	i;

	printf("\n✅ Initialisation & Parsing réussis !\n");
	printf("-----------------------------------------\n");
	printf("👥 Nombre de philosophes : %d\n", philo->philo_nbr);
	printf("💀 Temps pour mourir     : %ld ms\n", philo->time_to_die);
	printf("🍝 Temps pour manger     : %ld ms\n", philo->time_to_eat);
	printf("💤 Temps pour dormir     : %ld ms\n", philo->time_to_sleep);
	if (philo->meal_count != -1)
		printf("🍽 Nombre limite de repas : %d\n", philo->meal_count);
	else
		printf("🍽 Nombre limite de repas : Illimité\n");
	printf("🕒 Timestamp initial     : %ld ms\n", philo->start_time);
	printf("-----------------------------------------\n");
	i = -1;
	while (++i < philo->philo_nbr)
	{
		printf("👤 Philo %d → 🍴 gauche : %d | 🍴 droite : %d\n",
			philo[i].philo_id,
			philo[i].l_fork->fork_id,
			philo[i].r_fork->fork_id);
	}
	printf("-----------------------------------------\n\n");
}

void	print_msg(const char *str, t_philo *philo, int philo_id)
{
	long		time;
	const char	*color;

	color = get_color(philo_id);
	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!ft_strcmp(str, "died"))
	{
		pthread_mutex_lock(philo->dead_lock);
		*philo->is_dead = 1;
		pthread_mutex_unlock(philo->dead_lock);
		printf("%s%ld %d %s\033[0m\n", color, time, philo_id, str);
	}
	if (!is_dead(philo))
	{
		printf("%s%ld %d %s\033[0m\n", color, time, philo_id, str);
	}
	pthread_mutex_unlock(philo->write_lock);
}

/**
 * Crée et gère les threads pour la simulation des philosophes.
 * @prog: Structure contenant les données globales du programme.
 * @forks: Tableau de structures représentant les fourchettes.
 *
 * Cette fonction effectue les étapes suivantes :
 * 1. Crée un thread de monitoring (`obs`) 
 * 		qui surveille l'état global de la simulation.
 *    - Le thread de monitoring exécute la fonction `monitor`, 
 * 		qui vérifie si un philosophe
 *      est mort ou si tous les philosophes 
 * 		ont terminé leurs repas.
 * 2. Crée un thread pour chaque philosophe, 
 * 		qui exécute la fonction `routine`.
 *    - La fonction `routine` gère le cycle de vie du philosophe: 
 * 		manger, dormir, penser.
 * 3. Attend la fin du thread de monitoring (`pthread_join`).
 *    - Cela garantit que la simulation ne se termine pas
 * 		tant que le monitoring n'a pas
 *      détecté la fin de la simulation.
 * 4. Attend la fin de chaque thread philosophe (`pthread_join`).
 *    - Cela garantit que tous les philosophes ont 
 * 		terminé leurs actions avant que le
 *      programme principal ne se termine.
 *
 * En cas d'erreur (échec de création ou de jointure d'un thread),
 * la fonction `cleanup`
 * est appelée pour libérer les ressources 
 * et afficher un message d'erreur.
 *
 * Retourne 0 si tous les threads 
 * ont été créés et joints avec succès.
 */
int	create_thread(t_prog *prog, t_fork *forks)
{
	pthread_t	obs;
	int			i;

	if (pthread_create(&obs, NULL, &monitor, prog->philo) != 0)
		cleanup("Thread Creation error", prog, forks);
	i = -1;
	while (++i < prog->philo[0].philo_nbr)
	{
		if (pthread_create(&prog->philo[i].thread, NULL,
				&routine, &prog->philo[i]) != 0)
			cleanup("Thread creation error", prog, forks);
	}
	i = -1;
	if (pthread_join(obs, NULL) != 0)
		cleanup("Thread Join Error !", prog, forks);
	while (++i < prog->philo[0].philo_nbr)
	{
		if (pthread_join(prog->philo[i].thread, NULL) != 0)
			cleanup("Thread join Error !", prog, forks);
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_philo	philo[200];
	t_prog	prog;
	t_fork	forks[200];

	if (parse_args(ac, av, philo) != 0)
		return (1);
	init_prog(&prog, philo);
	init_forks(forks, ft_atol(av[1]));
	init_philo(philo, &prog, forks, av);
	display_init(philo);
	create_thread(&prog, forks);
	cleanup(NULL, &prog, forks);
	return (0);
}
