/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 17:20:21 by frfrance          #+#    #+#             */
/*   Updated: 2021/03/08 16:26:53 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <string.h>

#include <stdio.h>

#include <stdbool.h>
#include <semaphore.h>


typedef	struct			s_strt
{
	pthread_t			thread;

	pid_t				pid;

	int					index;
	int					lte;
	int					last_time_eat;

}						t_strt;

typedef	struct			s_philo
{
	sem_t				*writer;
	sem_t				*frk;

	int					nb_philo;
	int					die_time;
	int					eat_time;
	int					sleep_time;
	int					max_eat_die;

	bool				all_meal;
	bool				die;

	struct timeval		time;

}						t_philo;

typedef struct		s_all
{
	t_philo		*philo;
	t_strt		*strt;
}					t_all;



/*
**					-- init philosophers --
*/
int			init_center(t_philo *philo, t_strt *strt);
int			creat_philo(t_philo *philo, t_strt *strt, t_all *all);

/*
**					-- routine --
*/
void			*routine(void *arg);
unsigned int	get_time(struct timeval start);

/*
**					-- print --
*/
void		output_die(t_all *all, const char *str);
int			print_error(char *str);
void		writer(t_all *all, const char *str);

/*
**					-- fonction tiers --
*/
int			is_not_num(char *str);
int			ft_atoi(char *str);
void		ft_strdel(char **s);
char				*ft_uitoa(unsigned int n);
int					ft_strlen(char *str);




/*
**					-- fonction a supp --
*/


/*
**					-- fonction a supp --
*/

void	print_arg(t_philo *philo);

#endif

