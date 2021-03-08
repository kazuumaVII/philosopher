/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:25:15 by frfrance          #+#    #+#             */
/*   Updated: 2021/03/08 19:19:00 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int					eat(t_all *all)
{
	print_philo(all, "is eating");
	all->strt->lte = get_time(all->philo->time);
	usleep(all->philo->eat_time * 1000);
	pthread_mutex_unlock(all->strt->left_f);
	pthread_mutex_unlock(all->strt->right_f);
	return (1);
}

int					take_fork(t_all *all)
{
	pthread_mutex_lock(all->strt->left_f);
	pthread_mutex_lock(all->strt->right_f);
	print_philo(all, "has taken a fork");
	print_philo(all, "has taken a fork");
	return (1);
}

void				*checker(void *arg)
{
	t_all			*all;
	unsigned int	now;

	all = (t_all *)arg;
	usleep(all->philo->die_time * 1000);
	now = get_time(all->philo->time);
	if (now - all->strt->lte >= (unsigned int)all->philo->die_time)
	{
		all->philo->death = true;
		print_die(all, "is dead");
	}
	return (NULL);
}

void				*routine(void *arg)
{
	t_all			*all;
	pthread_t		check;
	int				i;

	i = 0;
	all = (t_all *)arg;
	pthread_mutex_lock(all->strt->lock);
	while (all->philo->death == false && all->philo->all_meal == false)
	{
		pthread_create(&check, NULL, &checker, all);
		take_fork(all);
		eat(all);
		print_philo(all, "is sleeping");
		usleep(all->philo->sleep_time * 1000);
		print_philo(all, "is thinking");
		pthread_detach(check);
		i++;
		if (all->philo->max_eat_die > 0 && i >= all->philo->max_eat_die)
			all->philo->all_meal = true;
	}
	pthread_detach(check);
	pthread_mutex_unlock(all->strt->lock);
	return (NULL);
}
