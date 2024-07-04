/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:08:59 by linhnguy          #+#    #+#             */
/*   Updated: 2024/07/04 21:35:17 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_forks(t_philo *data)
{
	pthread_mutex_lock(data->left_fork);
	print_actions(data, "has taken left fork");
	if (data->philo != 1)
	{
		pthread_mutex_lock(data->right_fork);
		print_actions(data, "has taken right fork");
		print_actions(data, "is eating");
		data->last_ate = current_time(data);
	}
	return;
}

void	put_down_forks(t_philo *data)
{
	pthread_mutex_unlock(data->left_fork);
	if (data->philo != 1)
		pthread_mutex_unlock(data->right_fork);
	return ;
}

void	my_usleep(t_philo *data, int time)
{
	int i;

	i = 0;
	while (i < time)
	{
		if (current_time(data) - data->last_ate > data->die_time)
		{
			check_mutex(data->dead, data);
			*data->alive = 0;
			print_actions(data, "died1");
			return ;
		}
		check_mutex(data->dead, data);
		usleep(1000);
		i++;
	}
}