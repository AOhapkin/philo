/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 09:36:25 by gmyriah           #+#    #+#             */
/*   Updated: 2022/05/11 17:01:39 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_usleep(int ms)
{
	long long		start;
	long long		now;

	if (set_current_time(&start) || set_current_time(&now))
		return (FAIL);
	while ((now - start) < (long long)ms)
	{
		usleep(100);
		if (set_current_time(&now))
			return (FAIL);
	}
	return (SUCCESS);
}

int	print_status(t_phil *phil, char *str)
{
	long long	time_from_start;

	pthread_mutex_lock(&(phil->ptr_data->mutex_end));
	pthread_mutex_lock(&(phil->ptr_data->mutex_all_have_eaten));
	if ((phil->ptr_data->end == -1) && \
		(phil->ptr_data->all_have_eaten != phil->ptr_data->total_phil))
	{
		if (set_time_stamp(phil, &time_from_start))
			return (1);
		pthread_mutex_lock(&(phil->ptr_data->mutex_print));
		printf("%lld %d %s\n", time_from_start, phil->phil_id, str);
		pthread_mutex_unlock(&(phil->ptr_data->mutex_print));
	}
	pthread_mutex_unlock(&(phil->ptr_data->mutex_all_have_eaten));
	pthread_mutex_unlock(&(phil->ptr_data->mutex_end));
	return (0);
}

static int	eating(t_phil *phil, int first_fork, int second_fork)
{
	pthread_mutex_lock(&(phil->ptr_data->mutex_forks[first_fork]));
	if (print_status(phil, "has taken a fork"))
		return (1);
	if (phil->ptr_data->total_phil == 1)
	{
		pthread_mutex_lock(&(phil->ptr_data->mutex_end));
		phil->ptr_data->end = 0;
		pthread_mutex_unlock(&(phil->ptr_data->mutex_end));
		pthread_mutex_unlock(&(phil->ptr_data->mutex_forks[first_fork]));
		return (1);
	}
	pthread_mutex_lock(&(phil->ptr_data->mutex_forks[second_fork]));
	if (print_status(phil, "is eating"))
		return (1);
	pthread_mutex_lock(&(phil->ptr_data->mutex_time));
	if (set_current_time(&(phil->last_meal_ms)))
		return (1);
	pthread_mutex_unlock(&(phil->ptr_data->mutex_time));
	phil->num_eat++;
	if (ft_usleep(phil->time_to_eat))
		return (1);
	pthread_mutex_unlock(&(phil->ptr_data->mutex_forks[second_fork]));
	pthread_mutex_unlock(&(phil->ptr_data->mutex_forks[first_fork]));
	return (0);
}

static int	check_and_eat(t_phil *phil)
{
	if (eating(phil, phil->right_fork_id, phil->left_fork_id))
		return (1);
	if (phil->num_eat == phil->ptr_data->total_eat)
	{
		pthread_mutex_lock(&(phil->ptr_data->mutex_all_have_eaten));
		phil->ptr_data->all_have_eaten++;
		if (phil->ptr_data->all_have_eaten == phil->ptr_data->total_phil)
		{
			pthread_mutex_unlock(&(phil->ptr_data->mutex_all_have_eaten));
			return (1);
		}
		pthread_mutex_unlock(&(phil->ptr_data->mutex_all_have_eaten));
	}
	return (0);
}

void	*actions(void *phil)
{
	t_phil	*phil_tmp;

	phil_tmp = &(*(t_phil *)phil);
	if (phil_tmp->phil_id % 2 == 0)
		usleep(100);
	while (1)
	{		
		pthread_mutex_lock(&(phil_tmp->ptr_data->mutex_end));
		if (phil_tmp->ptr_data->end)
		{
			pthread_mutex_unlock(&(phil_tmp->ptr_data->mutex_end));
			if (check_and_eat(phil_tmp))
				return (NULL);
			if (print_status(phil, "is sleeping"))
				return (NULL);
			if (ft_usleep(phil_tmp->time_to_sleep) || \
                print_status(phil, "is thinking"))
				return (NULL);
		}
		else
		{
			pthread_mutex_unlock(&(phil_tmp->ptr_data->mutex_end));
			return (NULL);
		}
	}
}
