/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceralin <aceralin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 23:13:01 by aceralin          #+#    #+#             */
/*   Updated: 2023/05/04 17:49:56 by aceralin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*ft_thread(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	philo->last_meal_time = get_time(philo->start_time);
	if ((philo->index % 2) == 0)
		usleep(10000);
	while (!philo->dead && philo->times_must_eat)
		routine(philo);
	return (NULL);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	zero_before_number(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (!str)
		return (0);
	if (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			i++;
		while (str[i] == '0')
			i++;
	}
	while (str[i])
	{
		len++;
		i++;
	}
	if (len > 11)
		return (1);
	else
		return (0);
}

int	check_arg(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (0);
	i = 1;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) > 11 && zero_before_number(argv[i]))
			return (0);
		if (ft_atoi(argv[i]) == 0 || ft_atoi(argv[i]) > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	data;

	if (!check_arg(argc, argv))
		return (printf("Error\n"), 1);
	philo = malloc(sizeof (t_philo) * ft_atoi(argv[1]));
	if (!philo)
		return (printf("Error: Malloc philo fail"), 1);
	data.forks = malloc(sizeof (t_forks) * ft_atoi(argv[1]));
	if (!data.forks)
		return (printf("Error: Malloc fork fail"), free(philo), 1);
	if (init_all(philo, argv, &data))
		return (free(philo), free(data.forks), 1);
	init_thread(philo, &data);
	free(philo);
	free(data.forks);
	return (0);
}
