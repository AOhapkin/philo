/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitioring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 09:36:22 by gmyriah           #+#    #+#             */
/*   Updated: 2022/05/11 17:02:31 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(int **args, t_data *data)
{
	data->total_phil = (*args)[0];
	data->time_to_die = (*args)[1];
	data->total_eat = (*args)[4];
	data->end = -1;
	data->phil = malloc (sizeof(t_phil) * data->total_phil);
	if (!data->phil)
		return (show_error_message("Malloc error!\n"));
	if (set_current_time(&(data->start_ms)))
		return (1);
	data->all_have_eaten = 0;
	init_all_philos(args, data);
	return (0);
}

long long	set_time_stamp(t_phil *phil, long long	*time_from_start)
{
	long long	now_ms;

	if (set_current_time(&now_ms))
		return (FAIL);
	*time_from_start = now_ms - phil->ptr_data->start_ms;
	return (SUCCESS);
}

static int	check_all_have_eaten(t_data *data)
{
	pthread_mutex_lock(&(data->mutex_all_have_eaten));
	if (data->all_have_eaten == data->total_phil)
	{
		pthread_mutex_unlock(&(data->mutex_all_have_eaten));
		pthread_mutex_lock(&(data->mutex_end));
		data->end = 0;
		pthread_mutex_unlock(&(data->mutex_end));
		return (1);
	}
	else
		pthread_mutex_unlock(&(data->mutex_all_have_eaten));
	return (0);
}

static int	check_time_to_die(t_data *data, int i)
{
	long long	now_ms;
	long long	time_from_start;

	if (set_current_time(&now_ms))
		return (FAIL);
	pthread_mutex_lock(&(data->mutex_time));
	if ((now_ms - data->phil[i].last_meal_ms) > \
		((long long)data->time_to_die))
	{
		pthread_mutex_unlock(&(data->mutex_time));
		pthread_mutex_lock(&(data->mutex_end));
		data->end = 0;
		pthread_mutex_unlock(&(data->mutex_end));
		if (set_time_stamp(&(data->phil[i]), &time_from_start))
			return (FAIL);
		pthread_mutex_lock(&(data->mutex_print));
		printf("%lld %d died\n", time_from_start, data->phil[i].phil_id);
		pthread_mutex_unlock(&(data->mutex_print));
		return (FAIL);
	}
	else
		pthread_mutex_unlock(&(data->mutex_time));
	return (SUCCESS);
}

void	*check_death(void *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < ((t_data *)data)->total_phil)
		{
			if (check_all_have_eaten((t_data *)data))
				return (NULL);
			if (check_time_to_die((t_data *)data, i))
				return (NULL);
			i++;
		}
	}
}
