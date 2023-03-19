/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceralin <aceralin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 23:12:51 by aceralin          #+#    #+#             */
/*   Updated: 2023/03/19 19:32:43 by aceralin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define EAT "is eating"
# define SLEEP "is sleeping"
# define DIE "died"
# define THINK "is thinking"
# define TAKE_FORK "has taken a fork"

typedef struct s_forks
{
	int				free_fork;
	pthread_mutex_t	mutex_fork;
}					t_forks;

typedef struct s_data
{
	int				someone_died;
	int				nb_philo;
	t_forks			*forks;
	pthread_mutex_t	mutex_philo;
}					t_data;

typedef struct s_philo
{
	int			index;
	int			take_forks;
	pthread_t	id;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			times_must_eat;
	int			last_meal_time;
	int			dead;
	long int	start_time;
	t_forks		*right_fork;
	t_forks		*left_fork;
	t_data		*data;
}				t_philo;

/*-----------Parsing-------------*/
int			check_arg(int argc, char **argv);

/*-----------Init-------------*/
int			init_all(t_philo *philo, char **argv, t_data *data);
void		init_thread(t_philo *philo, t_data *data);

/*-----------Utils--------------*/
long		ft_atoi(char *str);
long int	get_time(long int start_time);
void		print_routine(t_philo *philo, char *action);
void		is_sleeping(t_philo *philo);

/*----------Routine--------------*/
void		routine(t_philo *philo);
void		free_forks(t_philo *philo);
void		check_death(t_philo *philo);
void		*ft_thread(void *p);
#endif