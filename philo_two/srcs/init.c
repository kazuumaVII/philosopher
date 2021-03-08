/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 19:25:31 by frfrance          #+#    #+#             */
/*   Updated: 2021/03/08 17:05:33 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


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

	//obtient l'heure de l'horloge du système
	// Le 1 er argument pointe vers la structure timeval
	//le 2eme argument pointe structure du fuseau horaire
	// défini sur NULL car le fuseau horaire struct est obsolète
	gettimeofday(&philo->time, NULL);
	philo->die = false;


	while (++i < philo->nb_philo)
	{

		all[i].strt = &strt[i];
		all[i].philo = philo;
		//NULL pointe sur la structure philo
		// structure init avec "pthread_mutex_init"
		//exec routine en lui passant all comme arguments

		if (pthread_create(&strt[i].thread, NULL, &routine, &all[i]))
			return (0);

		usleep(500);
	}

	return (1);

}

