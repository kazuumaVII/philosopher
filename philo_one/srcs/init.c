/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 19:25:31 by frfrance          #+#    #+#             */
/*   Updated: 2021/03/09 18:35:36 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void				destroy_philo(t_strt *strt, t_philo *philo, t_all *all)
{
	int				i;

	i = -1;
	usleep(1000);
	pthread_mutex_destroy(philo->setting);
	free(philo->setting);
	while (++i < philo->nb_philo)
		free(strt[i].left_f);
	i = -1;
	while (++i < philo->nb_philo)
		free(strt[i].lock);
	free(all->philo);
	free(all->strt);
	free(all);
}

int					death_philo(t_philo *philo)
{
	while (philo->death == false && philo->all_meal == false)
		usleep(1000);
	usleep(1000);
	if (philo->death == false)
		pthread_mutex_lock(philo->setting);
	if (philo->all_meal == true)
		write(1, "\nall the philosophers have eaten\n", 33);
	return (1);
}

int					init_philo(t_philo *philo, t_strt *strt)
{
	int				i;

	i = -1;
	if (!(philo->setting = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t))))
		return (0);
	pthread_mutex_init(philo->setting, NULL);
	philo->all_meal = false;
	while (++i < philo->nb_philo)
	{
		if (!(strt[i].left_f = malloc(sizeof(pthread_mutex_t))))
			return (0);
		pthread_mutex_init(strt[i].left_f, NULL);
		if (!(strt[i].lock = malloc(sizeof(pthread_mutex_t))))
			return (0);
		pthread_mutex_init(strt[i].lock, NULL);
		strt[i].index = i + 1;
		strt[i].lte = 0;
	}
	i = -1;
	while (++i < philo->nb_philo - 1)
		strt[i].right_f = strt[i + 1].left_f;
	strt[i].right_f = strt[0].left_f;
	return (1);
}

int					creat_philo(t_philo *philo, t_strt *strt, t_all *all)
{
	int				i;

	i = -1;
	gettimeofday(&philo->time, NULL);
	philo->death = false;
	while (++i < philo->nb_philo)
	{
		all[i].strt = &strt[i];
		all[i].philo = philo;
		if (pthread_create(&strt[i].thread, NULL, &routine, &all[i]))
			return (0);
		usleep(200);
	}
	return (1);
}

void				init_center(t_philo *philo, t_strt *strt, t_all *all)
{
	init_philo(philo, strt);
	creat_philo(philo, strt, all);
	death_philo(philo);
	destroy_philo(strt, philo, all);
}
