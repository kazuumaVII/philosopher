/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:12:32 by frfrance          #+#    #+#             */
/*   Updated: 2021/03/08 16:55:35 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_arg(t_philo *philo)
{
	printf("nb_philo = %d\n", philo->nb_philo);
	printf("die_time = %d\n", philo->die_time);
	printf("eat_time = %d\n", philo->eat_time);
	printf("sleep_time = %d\n", philo->sleep_time);
	printf("max_eat_die = %d\n", philo->max_eat_die);
}

int				print_error(char *str)
{
	int i;

	i = 0;
	while (str[i])
		write(2, &str[i++], 1);
	return (1);
}

void			output_die(t_all *all, const char *str)
{
	struct timeval	now;
	char			*time;
	char			*idx;


	gettimeofday(&now, NULL);
	time = ft_uitoa(all->strt->last_time_eat + all->philo->die_time);
	idx = ft_uitoa((unsigned long)all->strt->index);
	sem_wait(all->philo->writer);
	// write(1, ".......", 7 - ft_strlen(time));
	write(1, time, ft_strlen(time));
	write(1, " ", 1);
	write(1, idx, ft_strlen(idx));
	write(1, " ", 1);
	write(1, str, ft_strlen((char *)str));
	write(1, "\n", 1);
	ft_strdel(&idx);
	ft_strdel(&time);
}

void			writer(t_all *all, const char *str)
{
	// struct timeval	now;
	char			*time;
	char			*idx;
	unsigned int	value;


	// gettimeofday(&now, NULL);

	value = get_time(all->philo->time);

	// time actuele pendant les exec
	time = ft_uitoa(value);



	idx = ft_uitoa((unsigned long)all->strt->index);
	sem_wait(all->philo->writer);

	// write(1, ".......", 7 - ft_strlen(time));
	write(1, time, ft_strlen(time));
	write(1, " ", 1);
	write(1, idx, ft_strlen(idx));
	write(1, " ", 1);

	// argument de take_fork
	write(1, str, ft_strlen((char *)str));

	write(1, "\n", 1);

	sem_post(all->philo->writer);
	//free des chaine (remplacer)
	ft_strdel(&idx);
	ft_strdel(&time);
}
