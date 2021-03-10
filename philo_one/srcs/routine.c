/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:25:15 by frfrance          #+#    #+#             */
/*   Updated: 2021/03/09 19:03:23 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int					is_eating(t_all *all)
{
	print_philo(all, "is eating\n");
	all->strt->lte = get_time(all->philo->time);
	usleep(all->philo->eat_time * 1000);
	pthread_mutex_unlock(all->strt->left_f);
	pthread_mutex_unlock(all->strt->right_f);
	return (1);
}

int					taken_a_fork(t_all *all)
{
	pthread_mutex_lock(all->strt->left_f);
	print_philo(all, "has taken a fork\n");
	pthread_mutex_lock(all->strt->right_f);
	print_philo(all, "has taken a fork\n");
	return (1);
}

void				*if_dead(void *arg)
{
	t_all			*all;
	unsigned int	now;

	all = (t_all *)arg;
	usleep(all->philo->die_time * 1000);
	now = get_time(all->philo->time);
	if (now - all->strt->lte >= (unsigned int)all->philo->die_time)
	{
		all->philo->death = true;
		print_die(all, "is died\n");
	}
	return (NULL);
}

void				*routine(void *str)
{
	t_all			*all;
	pthread_t		check;
	int				i;

	i = 0;
	all = (t_all *)str;
	pthread_mutex_lock(all->strt->lock);
	while (all->philo->death == false && all->philo->all_meal == false)
	{
		pthread_create(&check, NULL, &if_dead, all);
		taken_a_fork(all);
		is_eating(all);
		print_philo(all, "is sleeping\n");
		usleep(all->philo->sleep_time * 1000);
		print_philo(all, "is thinking\n");
		pthread_detach(check);
		i++;
		if (all->philo->max_eat_die > 0 && i >= all->philo->max_eat_die)
			all->philo->all_meal = true;
	}
	pthread_detach(check);
	pthread_mutex_unlock(all->strt->lock);
	return (NULL);
}
