/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:25:15 by frfrance          #+#    #+#             */
/*   Updated: 2021/03/10 14:59:06 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int							is_eating(t_all *all)
{
	print_philo(all, "is eating\n");
	all->strt->lte = get_time(all->philo->time);
	usleep(all->philo->eat_time * 1000);
	sem_post(all->philo->frk);
	sem_post(all->philo->frk);
	return (1);
}

int							taken_a_fork(t_all *all)
{
	sem_wait(all->philo->frk);
	sem_wait(all->philo->frk);
	print_philo(all, "has taken a fork\n");
	print_philo(all, "has taken a fork\n");
	return (1);
}

void						*if_dead(void *arg)
{
	t_all					*all;
	unsigned int			now;

	all = (t_all *)arg;
	usleep(all->philo->die_time * 1000);
	now = get_time(all->philo->time);
	if (now - all->strt->lte >= (unsigned int)all->philo->die_time)
	{
		print_die(all, "is died\n");
		all->philo->death = true;
		exit(1);
	}
	return (NULL);
}

int							routine(void *arg)
{
	t_all					*all;
	int						i;
	pthread_t				check;

	all = (t_all *)arg;
	i = 0;
	while (all->philo->death == false && all->philo->all_meal == false)
	{
		pthread_detach(check);
		pthread_create(&check, NULL, &if_dead, all);
		taken_a_fork(all);
		is_eating(all);
		print_philo(all, "is sleeping\n");
		usleep(all->philo->sleep_time * 1000);
		print_philo(all, "is thinking\n");
		i++;
		if (all->philo->max_eat_die > 0 && i >= all->philo->max_eat_die)
			all->philo->all_meal = true;
	}
	if (all->philo->death == true)
		exit(1);
	if (all->philo->all_meal == true)
		exit(2);
	return (all->philo->death);
}
