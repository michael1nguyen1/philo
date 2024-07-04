/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:46:25 by linhnguy          #+#    #+#             */
/*   Updated: 2024/07/04 22:53:36 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *data)
{
	print_actions(data, "is thinking");
}

void	go_to_sleep(t_philo *data)
{
	print_actions(data, "is sleeping");
	my_usleep(data, data->sleep_time);
}

void	eat(t_philo *data)
{
	if (current_time(data) - data->last_ate > data->die_time && 
		check_mutex(data->dead, data))
	{
		*data->alive = 0;
		print_actions(data, "died");
		return ;
	}
	else if (check_mutex(data->dead, data))
	{
		pick_up_forks(data);
		data->last_ate = current_time(data);
		my_usleep(data, data->eat_time);
		data->meals_ate++;
		put_down_forks(data);
	}
	return ;
}
void	*lonely_philo(t_philo *data)
{
	pick_up_forks(data);
	my_usleep(data, data->die_time);
	put_down_forks(data);
	return (NULL);
}