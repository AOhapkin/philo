/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 09:36:38 by gmyriah           #+#    #+#             */
/*   Updated: 2022/05/01 09:36:40 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	show_philo_message(t_philo *philo, char *message)
{
	long long		ms;
	struct timeval	now;

	pthread_mutex_lock(&philo->info->finish_mutex);
	gettimeofday(&now, NULL);
	ms = time_to_ms(now) - time_to_ms(philo->info->create_at);
	if (!philo->info->finish)
		printf("%lld\t%d\t %s\n", ms, philo->n + 1, message);
	pthread_mutex_unlock(&philo->info->finish_mutex);
}

static void	join_and_destroy_philos(t_info *info)
{
	int		i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_join(info->philos[i].thread, NULL);
		pthread_mutex_destroy(&info->philos[i++].check_mutex);
	}
	free(info->philos);
	i = 0;
	while (i < info->num_of_philo)
		pthread_mutex_destroy(&info->forks[i++]);
	free(info->forks);
}

static void	create_philos(t_info *info)
{
	int			i;
	pthread_t	thread;

	gettimeofday(&info->create_at, NULL);
	i = 0;
	while (i < info->num_of_philo)
	{
		info->philos[i].last_time_to_eat = info->create_at;
		pthread_create(&info->philos[i].thread, NULL, \
			run_philo_actions, &info->philos[i]);
		pthread_create(&thread, NULL, monitor, &info->philos[i]);
		pthread_detach(thread);
		i++;
	}
	if (info->num_of_must_eat != 0)
	{
		pthread_create(&thread, NULL, monitor_each_must_eat, info);
		pthread_detach(thread);
	}
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 5 && argc != 6)
		return (show_error_message("Error: wrong arguments\n"));
	memset(&info, 0, sizeof(info));
	if (init_simulation(&info, argc, argv))
		return (1);
	create_philos(&info);
	join_and_destroy_philos(&info);
	return (0);
}
