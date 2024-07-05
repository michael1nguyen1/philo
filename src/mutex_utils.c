/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:27:59 by linhnguy          #+#    #+#             */
/*   Updated: 2024/07/05 14:47:04 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_mutex(pthread_mutex_t *check, t_philo *data)
{
    int ret;

	// printf("wow: %p\n", data->alive);
    pthread_mutex_lock(check);
        ret = *data->alive;
    pthread_mutex_unlock(check);
    return (ret);
}

int	destroy_mutex_array(pthread_mutex_t *forks, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free (forks);
	return (0);
}

int create_rest_of_mutex(pthread_mutex_t *print, pthread_mutex_t *dead, t_philo **data)
{
	int i;
	
	i = 0;
	if (pthread_mutex_init(print, NULL) != 0)
		return (put_error_fd(2, "mutex init failed\n"));
	if (pthread_mutex_init(dead, NULL) != 0)
	{
		pthread_mutex_destroy(print);
		return (put_error_fd(2, "mutex init failed\n"));
	}
	while (i < (*data)[0].philo)
	{
		(*data)[i].dead = dead;
		(*data)[i].print = print;
		i++;
	}
	return (0);
}
