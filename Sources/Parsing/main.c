/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceralin <aceralin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 23:13:01 by aceralin          #+#    #+#             */
/*   Updated: 2023/03/14 20:01:28 by aceralin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void   *ft_thread(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	// pthread_mutex_lock(&philo->data->mutex_philo);
	// printf("Je suis %d\n", philo->index);
	// pthread_mutex_unlock(&philo->data->mutex_philo);
	if (philo->index % 2)
		usleep(10000); //10.000 microsecondes = 10 millisecondes
	routine(philo);
	return (NULL);
}

int	check_arg(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (0);
	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) == 0 || ft_atoi(argv[i]) > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo *philo;
	t_data	data;
	int		i;

	i = 0;
	if (!check_arg(argc, argv))
		return (printf("Error\n"), 1);
	philo = malloc(sizeof (t_philo) * ft_atoi(argv[1]));
	if(!philo)
		return(printf("Error: Malloc philo fail"), 1);
	data.forks = malloc(sizeof (t_forks) * ft_atoi(argv[1]));
	if(!data.forks)
		return(printf("Error: Malloc fork fail"), free(philo), 1);
	init_all(philo, argv, &data);
	printf("%d, %d, %d, %d, %d \n", data.nb_philo, philo->time_to_die, philo->time_to_eat, philo->time_to_sleep, philo->times_must_eat);
	// initialiser les threads
	while (i < data.nb_philo)
	{
		if (pthread_create(&philo[i].id, NULL, &ft_thread, &philo[i]) != 0)
		{
			printf("Error thread\n");
			break ;
		}
		i++;
	}
	
	while (i)
	{
		i--;
		pthread_join(philo[i].id, NULL);
	}
	return (0);
}
//valgrind --tool=helgrind permet de voir les data race