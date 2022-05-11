/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 09:36:38 by gmyriah           #+#    #+#             */
/*   Updated: 2022/05/11 17:00:57 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_current_time(long long *time_ms)
{
	struct timeval		current_time;

	if (gettimeofday(&current_time, NULL) != 0)
		return (show_error_message("gettimeofday fail\n"));
	*time_ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (0);
}

int	show_error_message(char *message)
{
	char	*ptr;
	int		i;

	ptr = message;
	i = 0;
	while (*ptr++)
		i++;
	write(2, message, i);
	return (FAIL);
}

static int	init_threads(t_data *data, pthread_t **philos, pthread_t *monitor)
{
	int	i;

	*philos = malloc(sizeof(pthread_t) * data->total_phil);
	if (!(*philos))
		return (show_error_message("malloc error\n"));
	pthread_mutex_init(&(data->mutex_print), NULL);
	pthread_mutex_init(&(data->mutex_time), NULL);
	pthread_mutex_init(&(data->mutex_end), NULL);
	pthread_mutex_init(&(data->mutex_all_have_eaten), NULL);
	data->mutex_forks = malloc(sizeof(pthread_mutex_t) * data->total_phil);
	if (!(data->mutex_forks))
		return (show_error_message("malloc error\n"));
	i = 0;
	while (i < data->total_phil)
		pthread_mutex_init(&(data->mutex_forks[i++]), NULL);
	i = 0;
	while (i < data->total_phil)
	{
		if (pthread_create(*(philos) + i, NULL, &actions, &(data->phil[i])) != 0)
			return (show_error_message("pthread_create fail\n"));
		i++;
	}
	if (pthread_create(monitor, NULL, &check_death, data) != 0)
		return (show_error_message("pthread_create fail\n"));
	return (0);
}

static int	join_threads(t_data *data, pthread_t **philos, pthread_t *monitor)
{
	int	i;

	if (pthread_join(*monitor, NULL) != 0)
		return (show_error_message("pthread_join fail\n"));
	i = 0;
	while (i < data->total_phil)
	{
		if (pthread_join((*philos)[i], (void **) &(data->phil[i])) != 0)
			return (show_error_message("pthread_join fail\n"));
		i++;
	}
	pthread_mutex_destroy(&(data->mutex_print));
	pthread_mutex_destroy(&(data->mutex_time));
	pthread_mutex_destroy(&(data->mutex_end));
	pthread_mutex_destroy(&(data->mutex_all_have_eaten));
	i = 0;
	while (i < data->total_phil)
		pthread_mutex_destroy(&(data->mutex_forks[i++]));
	free(*philos);
	free(data->phil);
	free(data->mutex_forks);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	*philos;
	pthread_t	monitor;

	if (handle_input(argc, argv, &data))
		return (FAIL);
	if (init_threads(&data, &philos, &monitor))
		return (FAIL);
	if (join_threads(&data, &philos, &monitor))
		return (FAIL);
	return (SUCCESS);
}