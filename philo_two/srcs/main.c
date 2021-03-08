/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 17:20:57 by frfrance          #+#    #+#             */
/*   Updated: 2021/03/08 16:44:09 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
		philo->max_eat_die = ft_atoi(av[5]);
	else
		philo->max_eat_die = -1;

	// print_arg(philo);
	return (0);
}

int				check_nb(char **av)
{
	int 		i;

	i = 1;
	while (av[i])
	{
		if (is_not_num(av[i]))
			return (1);
		i++;
	}

	return (0);
}

void	philo_delete(t_strt *strt, t_philo *philo, t_all *all)
{
	int		i;

	i = -1;
	usleep(1000);
	while (++i < philo->nb_philo)
		pthread_detach(strt[i].thread);
	free(all->strt);
	free(all->philo);
	free(all);
}

int		check_philo_die(t_philo *philo)
{
	char		*time;

	while (philo->die == false && philo->all_meal == false)
		usleep(1000);
	usleep(1000);


	// if (philo->die == false)
	// 	pthread_mutex_lock(philo->writer);
	if (philo->all_meal == true)
	{
		sem_wait(philo->writer);
		time = ft_uitoa(get_time(philo->time));
		write(1, "all meals are ate\n", 18);
		ft_strdel(&time);
	}
	return (1);
}

int				main(int ac, char **av)
{
	t_philo		*philo;
	t_strt		*strt;
	t_all		*all;

	// Gestion error
	if (ac < 3 || ac > 6)
		return(print_error("Put between 4 or 5 arguments\n"));
	if (check_nb(av))
		return (print_error("Wrong arguments\n"));

	// Malloc des 3 structures
	if (!(philo = (t_philo *)malloc(sizeof(t_philo))))
		return (-1);

	// Structure remplis avec les arguments
	if (prsg_arg(philo, ac, av))
		return (print_error("Wrong arguments\n"));
	if (!(strt = (t_strt *)malloc(sizeof(t_strt) * (philo->nb_philo + 1))))
		return (-1);
	if (!(all = (t_all *)malloc(sizeof(t_all) * (philo->nb_philo + 1))))
		return (-1);

	init_center(philo, strt);

	creat_philo(philo, strt, all);


	check_philo_die(philo);
	philo_delete(strt, philo, all);
	return (0);
}
