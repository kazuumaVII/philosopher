/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 17:20:57 by frfrance          #+#    #+#             */
/*   Updated: 2021/03/09 13:23:57 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void				clean_str(char **str)
{
	if (str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

unsigned int		get_time(struct timeval start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	now.tv_sec = now.tv_sec - start.tv_sec;
	return ((((unsigned int)now.tv_sec * 1000000 + now.tv_usec)
			- start.tv_usec) / 1000);
}

int					main(int ac, char **av)
{
	t_all			*all;
	t_philo			*philo;
	t_strt			*strt;

	if (ac < 3 || ac > 6)
		return (print_error("Put between 4 or 5 arguments\n"));
	if (check_nb(av))
		return (print_error("Wrong arguments\n"));
	if (!(philo = (t_philo *)malloc(sizeof(t_philo))))
		return (-1);
	if (prsg_arg(philo, ac, av))
		return (print_error("Wrong arguments\n"));
	if (philo->die_time < 20 || philo->eat_time < 20 || philo->sleep_time < 20)
		return (print_error("Enter a value greater than or equal to 20ms\n"));
	if (!(strt = (t_strt *)malloc(sizeof(t_strt) * (philo->nb_philo + 1))))
		return (-1);
	if (!(all = (t_all *)malloc(sizeof(t_all) * (philo->nb_philo + 1))))
		return (-1);
	init_center(philo, strt, all);
	return (0);
}
