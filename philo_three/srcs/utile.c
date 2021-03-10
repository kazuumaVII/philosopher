/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 17:51:22 by frfrance          #+#    #+#             */
/*   Updated: 2021/03/09 18:43:16 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int					is_not_num(char *str)
{
	int				i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int					ft_strlen(char *str)
{
	int				i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int					ft_atoi(char *str)
{
	int		i;
	int		neg;
	int		total;

	total = 0;
	neg = 1;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		total = (total * 10) + (str[i] - 48);
		i++;
	}
	return (total * neg);
}

int					convert_to_str(long unsigned int n, char *buff, int start)
{
	int				i;
	int				ret;

	i = start;
	while (n || (!i && !n))
	{
		buff[i++] = n % 10 + 48;
		n = n / 10;
	}
	buff[i] = '\0';
	ret = i - start;
	i--;
	while (start < i)
	{
		buff[start] ^= buff[i];
		buff[i] ^= buff[start];
		buff[start] ^= buff[i];
		start++;
		i--;
	}
	return (ret);
}

int					insert_status(char *buff, char *status, int i)
{
	buff = buff + i;
	while (status)
	{
		(*((unsigned int *)buff)) = (*((unsigned int *)status));
		if (status[0] && status[1] && status[2] && status[3])
			status += sizeof(unsigned int);
		else
		{
			while (*status)
			{
				*buff = *status;
				buff++;
				status++;
				i++;
			}
			break ;
		}
		buff += sizeof(unsigned int);
		i += sizeof(unsigned int);
	}
	*buff = '\0';
	return (i);
}
