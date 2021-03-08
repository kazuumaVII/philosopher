/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsg.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 18:20:35 by frfrance          #+#    #+#             */
/*   Updated: 2021/03/08 19:05:38 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int				check_nb(char **av)
{
	int			i;

	i = 1;
	while (av[i])
	{
		if (is_not_num(av[i]))
			return (1);
		i++;
	}
	return (0);
}

int				prsg_arg(t_philo *philo, int ac, char **av)
{
	if (!av[2] || !av[3] || !av[4])
		return (1);
	philo->nb_philo = ft_atoi(av[1]);
	philo->die_time = ft_atoi(av[2]);
	philo->eat_time = ft_atoi(av[3]);
	philo->sleep_time = ft_atoi(av[4]);
	if (philo->nb_philo <= 0)
		return (1);
	if (ac == 6)
	{
		philo->max_eat_die = ft_atoi(av[5]);
		if (philo->max_eat_die <= 0)
			return (1);
	}
	else
		philo->max_eat_die = -1;
	return (0);
}
