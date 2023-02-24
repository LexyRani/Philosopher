/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceralin <aceralin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 23:13:01 by aceralin          #+#    #+#             */
/*   Updated: 2023/02/25 00:29:52 by aceralin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/philosopher.h"

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
		/*if (ft_atoi(argv[i]) <= '0' && ft_atoi(argv[i]) >= '9')
			return (0);*/
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo *philo;

	if (!check_arg(argc, argv))
		printf("FAUX");
	//philo = malloc(sizeof t_philo * ft_atoi(argv[1]));
}
