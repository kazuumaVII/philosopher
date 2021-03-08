/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:12:32 by frfrance          #+#    #+#             */
/*   Updated: 2021/03/08 19:15:01 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int					print_error(char *str)
{
	int i;

	i = 0;
	while (str[i])
		write(2, &str[i++], 1);
	return (1);
}

void				print_philo(t_all *all, char *str)
{
	unsigned int	valu;
	char			*time;
	char			*idx;

	pthread_mutex_lock(all->philo->setting);
	valu = get_time(all->philo->time);
	time = itoa(valu);
	idx = itoa((unsigned long)all->strt->index);
	write(1, time, ft_strlen(time));
	write(1, "\t", 1);
	write(1, idx, ft_strlen(idx));
	write(1, "\t", 1);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	pthread_mutex_unlock(all->philo->setting);
	clean_str(&idx);
	clean_str(&time);
}

void				print_die(t_all *all, char *str)
{
	char			*idx;
	char			*time;

	pthread_mutex_lock(all->philo->setting);
	time = itoa(all->strt->lte + all->philo->die_time);
	idx = itoa((unsigned long)all->strt->index);
	write(1, "\n", 1);
	write(1, time, ft_strlen(time));
	write(1, " ", 1);
	write(1, idx, ft_strlen(idx));
	write(1, " ", 1);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	clean_str(&idx);
	clean_str(&time);
}
