/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceralin <aceralin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 23:12:51 by aceralin          #+#    #+#             */
/*   Updated: 2023/03/14 18:11:04 by aceralin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>


typedef struct s_forks
{
	int 			free_fork;
	pthread_mutex_t	mutex_fork;
}					t_forks;

typedef struct s_data
{
	int				someone_died;
	int 			nb_philo;
	t_forks			*forks;
	pthread_mutex_t	mutex_philo;
}    	 			t_data;

typedef struct s_philo
{
	int	index;
	pthread_t id;
	//int nb_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int times_must_eat;
	t_forks *right_fork;
	t_forks *left_fork;
	t_data *data;
	
	//nombre de fourchette
}   t_philo;

/*-----------Parsing-------------*/
int	check_arg(int argc, char **argv);

/*-----------Init-------------*/
void	init_all(t_philo *philo, char **argv, t_data *data);

/*-----------Utils--------------*/
long	ft_atoi(char *str);

#endif