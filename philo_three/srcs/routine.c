/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:25:15 by frfrance          #+#    #+#             */
/*   Updated: 2021/03/08 17:48:41 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned int	get_time(struct timeval start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	now.tv_sec = now.tv_sec - start.tv_sec;
	return ((((unsigned int)now.tv_sec * 1000000 + now.tv_usec)
			- start.tv_usec) / 1000);
}

int			eat(t_all *all)
{
	writer(all, "is eating");

	// va etre egal au time de now
	all->strt->last_time_eat = get_time(all->philo->time);


	usleep(all->philo->eat_time * 1000);
	sem_post(all->philo->frk);
	sem_post(all->philo->frk);

	return (1);
}


int			take_fork(t_all *all)
{

	sem_wait(all->philo->frk);
	sem_wait(all->philo->frk);
	writer(all, "has taken a fork");
	writer(all, "has taken a fork");
	return (1);
}

void		*checker(void *arg)
{
	t_all			*all;
	unsigned int	now;




	all = (t_all *)arg;

	// suspend  l'exécution  du  thread (pour lancer routine avant)
	usleep(all->philo->die_time * 1000);

	// permet davoir le time actuelle
	now = get_time(all->philo->time);


	// quand le time now et de la derniere fois ou il a mange et superieur
	// ou egal au time neccessaire a sa survie donner en argument le philo meurt
	if (now - all->strt->last_time_eat >= (unsigned int)all->philo->die_time)
	{
		output_die(all, "is dead");
		all->philo->die = true;

		exit(1);
	}

	return (NULL);
}

int		routine(void *arg)
{
	t_all		*all;
	int			i;
	pthread_t	check;

	all = (t_all *)arg;

	i = 0;

	// va tourner tant que les philo sont vivants
	while (all->philo->die == false && all->philo->all_meal == false)
	{
		pthread_detach(check);
		pthread_create(&check, NULL, &checker, all);

		// quand le philo va prendre les fourchettes
		take_fork(all);
		// quand il va manger
		eat(all);

		writer(all, "is sleeping");
		usleep(all->philo->sleep_time * 1000);
		writer(all, "is thinking");
		i++;
		// libère automatiquement les ressources allouées à la sortie

		// verif la modif avec round

		// printf("all->philo->max_eat_die %d\n", all->philo->max_eat_die);

		if (all->philo->max_eat_die > 0 && i >= all->philo->max_eat_die)
			all->philo->all_meal = true;
	}
	if (all->philo->die == true)
		exit(1);
	if (all->philo->all_meal == true)
		exit(2);

	return (all->philo->die);
}


