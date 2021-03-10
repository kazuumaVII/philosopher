/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 17:20:21 by frfrance          #+#    #+#             */
/*   Updated: 2021/03/10 15:29:10 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <semaphore.h>

typedef	struct			s_philo
{
	int					nb_philo;
	int					die_time;
	int					eat_time;
	int					sleep_time;
	int					max_eat_die;
	bool				all_meal;
	bool				death;
	struct timeval		time;
	sem_t				*frk;
	sem_t				*setting;
}						t_philo;

typedef	struct			s_strt
{
	int					index;
	int					lte;
	pthread_t			thread;
}						t_strt;

typedef struct			s_all
{
	t_philo				*philo;
	t_strt				*strt;
}						t_all;

/*
**							-- init philosophers --
*/
void					init_center(t_philo *philo, t_strt *strt, t_all *all);

/*
**							-- routine --
*/
void					*routine(void *str);
unsigned int			get_time(struct timeval start);

/*
**							-- parsing --
*/
int						prsg_arg(t_philo *philo, int ac, char **av);
int						check_nb(char **av);

/*
**							-- print --
*/
void					print_philo(t_all *all, char *str);
void					print_die(t_all *all, char *str);
int						print_error(char *str);

/*
**							-- fonction tiers --
*/
int						is_not_num(char *str);
int						ft_atoi(char *str);
void					clean_str(char **str);
int						ft_strlen(char *str);
int						insert_status(char *buff, char *status, int i);
int						convert_to_str(long unsigned int n, char *buff,
										int start);


#endif
