/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceralin <aceralin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 23:12:51 by aceralin          #+#    #+#             */
/*   Updated: 2023/02/25 00:20:00 by aceralin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <limits.h>
# include <stdio.h>

typedef struct s_philo
{
    int nb_philo;
    int to_die;
    int to_eat;
    int to_sleep;
    int must_eat;
}   t_philo;

/*-----------Parsing-------------*/

/*-----------Utils--------------*/
long	ft_atoi(char *str);

#endif