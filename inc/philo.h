/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:02:27 by eric              #+#    #+#             */
/*   Updated: 2025/04/17 16:07:31 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				fork_id;
}	t_fork;

typedef struct s_philo
{
	pthread_t			thread;
	int					philo_id;
	int					philo_nbr;
	int					count_eat;
	int					eating;
	int					meal_count;
	long				last_meal;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				start_time;
	int					*is_dead;
	t_fork				*r_fork;
	t_fork				*l_fork;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*meal_lock;
}	t_philo;

typedef struct s_prog
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	t_philo			*philo;
}	t_prog;

/*COLOR*/
const char	*get_color(int philo_id);
/*PARS UTILS*/
int			is_digit(char c);
int			is_space(char c);
bool		is_positive_num(char *str);
long		ft_atol(const char *str);
/*PARSING*/
int			parse_args(int ac, char *av[], t_philo *philo);
/*INIT*/
void		init_data(t_philo *philo, char *av[]);
void		init_philo(t_philo *philo, t_prog *program,
				t_fork *forks, char *av[]);
void		init_prog(t_prog *program, t_philo *philo);
void		init_forks(t_fork *forks, int philo_num);
/*TIME*/
long		get_current_time(void);
int			ft_usleep(long time_in_ms);
/*ROUTINE*/
void		eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		think(t_philo *philo);
int			is_dead(t_philo *philo);
void		*routine(void *av);
/*MONITOR*/
int			check_is_full(t_philo *philo);
void		*monitor(void *av);
/*UTILS*/
void		ft_putstr_fd(char *s, int fd);
size_t		ft_strlen(const char *str);
void		print_msg(const char *str, t_philo *philo, int philo_id);
void		cleanup(char *str, t_prog *prog, t_fork *forks);
int			ft_strcmp(const char *s1, const char *s2);
int			has_reached_meal_limit(t_philo *philo);
/*MAIN*/
int			create_thread(t_prog *prog, t_fork *forks);
#endif