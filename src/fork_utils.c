/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:08:59 by linhnguy          #+#    #+#             */
/*   Updated: 2024/07/07 00:07:32 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_forks(t_philo *data)
{
	pthread_mutex_lock(data->left_fork);
	if (!check_mutex(data->dead, data))
		return ;
	print_actions(data, "has taken left fork");
	if (check_mutex(data->dead, data) && data->philo != 1)
	{
		pthread_mutex_lock(data->right_fork);
		if (!check_mutex(data->dead, data))
			return ;
		print_actions(data, "has taken right fork");
		print_actions(data, "is eating");
		data->last_ate = current_time(data);
	}
}

void	put_down_forks(t_philo *data)
{
	pthread_mutex_unlock(data->left_fork);
	if (data->philo != 1)
		pthread_mutex_unlock(data->right_fork);
}

void	my_usleep(t_philo *data, int time)
{
	int	start;

	start = current_time(data);
	if (!check_mutex(data->dead, data))
		return ;
	while (current_time(data) - start < time)
	{
		if (!check_mutex(data->dead, data))
			return ;
		else if (current_time(data) - data->last_ate > data->die_time
			&& check_mutex(data->dead, data))
		{
			raise_dead_flag(data);
			print_actions(data, "died");
			return ;
		}
		usleep(500);
	}
	if (data->philo == 1)
		print_actions(data, "died");
}

void	assign_forks(t_philo *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data[0].philo)
	{
		data[i].left_fork = &forks[i];
		if (data->philo == 1)
			data->right_fork = NULL;
		else if (i == data->philo - 1)
			data[i].right_fork = &forks[0];
		else
			data[i].right_fork = &forks[i + 1];
		i++;
	}
}
