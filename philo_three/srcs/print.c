/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:12:32 by frfrance          #+#    #+#             */
/*   Updated: 2021/03/09 18:43:12 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int					print_error(char *str)
{
	int				i;

	i = 0;
	while (str[i])
		write(2, &str[i++], 1);
	return (1);
}

void				print_philo(t_all *all, char *str)
{
	unsigned int	valu;
	char			tab[50];
	int				ret;

	valu = get_time(all->philo->time);
	ret = convert_to_str(valu, tab, 0);
	tab[ret] = '\t';
	ret += convert_to_str((unsigned long)all->strt->index, tab, ret + 1);
	tab[ret + 1] = '\t';
	ret = insert_status(tab, str, ret + 2);
	sem_wait(all->philo->setting);
	write(1, tab, ret);
	sem_post(all->philo->setting);
}

void				print_die(t_all *all, char *str)
{
	char			tab[50];
	int				ret;

	sem_wait(all->philo->setting);
	ret = convert_to_str(all->strt->lte + all->philo->die_time, tab, 0);
	tab[ret] = '\t';
	ret += convert_to_str((unsigned long)all->strt->index, tab, ret + 1);
	tab[ret + 1] = '\t';
	ret = insert_status(tab, str, ret + 2);
	write(1, tab, ret);
}
