/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 19:25:31 by frfrance          #+#    #+#             */
/*   Updated: 2021/03/10 14:58:41 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int						philo_wait(t_philo *philo, t_all *all)
{
	int		i;
	int		status;

	i = -1;
	usleep(1000);
	while (++i < philo->nb_philo)
	{
		waitpid(all[i].strt->pid, &status, WNOHANG);
		status /= 256;
		if (status == 1)
			philo->death = true;
		if (status == 2)
			philo->all_meal = true;
		if (status == 1 || status == 2)
			break ;
		if (i + 1 == philo->nb_philo)
			i = -1;
	}
	if (philo->death == false)
		philo->all_meal = true;
	return (1);
}

void					destroy_philo(t_strt *strt, t_philo *philo, t_all *all)
{
	int		i;

	i = -1;
	usleep(1000);
	while (++i < philo->nb_philo)
		pthread_detach(strt[i].thread);
	free(all->philo);
	free(all->strt);
	free(all);
}

int						death_philo(t_philo *philo)
{
	char				*time;

	time = NULL;
	while (philo->death == false && philo->all_meal == false)
		usleep(1000);
	usleep(1000);
	if (philo->all_meal == true)
	{
		sem_wait(philo->setting);
		write(1, "\nall the philosophers have eaten\n", 33);
		clean_str(&time);
	}
	return (1);
}

int						init_philo(t_philo *philo, t_strt *strt)
{
	int					i;
	sem_t				*frk;
	sem_t				*printer;

	sem_unlink("fork");
	sem_unlink("printer");
	printer = sem_open("printer", O_CREAT | O_EXCL, S_IRWXU, 1);
	frk = sem_open("fork", O_CREAT | O_EXCL, S_IRWXU, philo->nb_philo);
	philo->setting = printer;
	philo->frk = frk;
	i = -1;
	philo->all_meal = false;
	while (++i < philo->nb_philo)
	{
		strt[i].index = i + 1;
		strt[i].lte = 0;
	}
	return (1);
}

int						creat_philo(t_philo *philo, t_strt *strt, t_all *all)
{
	int					i;

	i = -1;
	gettimeofday(&philo->time, NULL);
	philo->death = false;
	while (++i < philo->nb_philo)
	{
		all[i].strt = &strt[i];
		all[i].philo = philo;
		all[i].strt->pid = fork();
		if (all[i].strt->pid == 0)
		{
			routine(&all[i]);
			exit(all[i].philo->death);
		}
		usleep(30);
	}
	philo_wait(philo, all);
	return (1);
}
