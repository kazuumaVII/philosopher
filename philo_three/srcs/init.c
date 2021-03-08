/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 19:25:31 by frfrance          #+#    #+#             */
/*   Updated: 2021/03/08 17:46:01 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int		philo_wait(t_philo *philo, t_all *all)
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
			philo->die = true;
		if (status == 2)
			philo->all_meal = true;
		if (status == 1 || status == 2)
			break ;
		if (i + 1 == philo->nb_philo)
			i = -1;
	}
	if (philo->die == false)
		philo->all_meal = true;
	return (1);
}

int			init_center(t_philo *philo, t_strt *strt)
{
	int					i;
	sem_t				*frk;
	sem_t				*display;

	// supp les semaphore
	sem_unlink("printer");
	sem_unlink("fork");
	display = sem_open("printer", O_CREAT | O_EXCL, S_IRWXU, 1);
	frk = sem_open("fork", O_CREAT | O_EXCL, S_IRWXU, philo->nb_philo);
	// 			O_CREAT
	// Crée le sémaphore nommé s'il n'existe pas déjà
	//			O_EXCL
	// Provoque l' échec si le sémaphore nommé existe déjà
	//			S_IRWXU
	//l'utilisateur (propriétaire du fichier) a l'autorisation de lecture, d'écriture et d'exécution
	// 			last arg = value semaphore

	philo->writer = display;
	philo->frk = frk;
	i = -1;
	philo->all_meal = false;
	while (++i < philo->nb_philo)
	{
		strt[i].index = i + 1;
		strt[i].last_time_eat = 0;
	}
	return (1);
}


int			creat_philo(t_philo *philo, t_strt *strt, t_all *all)
{
	int		i;

	i = -1;
	gettimeofday(&philo->time, NULL);
	philo->die = false;
	while (++i < philo->nb_philo)
	{
		all[i].strt = &strt[i];
		all[i].philo = philo;
		all[i].strt->pid = fork();
		if (all[i].strt->pid == 0)
		{
			routine(&all[i]);
			exit(all[i].philo->die);
		}
		usleep(30);
	}
	philo_wait(philo, all);



	return (1);

}

