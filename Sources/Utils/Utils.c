/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceralin <aceralin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 23:12:55 by aceralin          #+#    #+#             */
/*   Updated: 2023/02/25 00:14:20 by aceralin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/philosopher.h"

long	ft_atoi(char *str)
{
	long int	i;
	long int	nb;

	i = 0;
	nb = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{	
		nb = nb * 10 + (str[i] - '0');
		i++;
	}	
	return (nb);
}
