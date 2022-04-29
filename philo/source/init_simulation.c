#include "philo.h"

int	ft_malloc(void *dst, size_t size)
{
	*(void **)dst = malloc(size);
	if (*(void **)dst == NULL)
		return (FAIL);
	memset(*(void **)dst, 0, size);
	return (SUCCESS);
}

static void	parse_arguments(t_info *info, int argc, char *argv[])
{
	info->num_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->num_of_must_eat = ft_atoi(argv[5]);
}

static int	validate_info(t_info *info, int argc)
{
	if (argc == 6 && info->num_of_must_eat <= 0)
		return (show_error_message("Error: wrong number of meals\n"));
	if (info->num_of_philo < 0)
		return (show_error_message("Error: wrong number of philosofers\n"));
	if (info->time_to_die < 0)
		return (show_error_message("Error: wrong time to die\n"));
	if (info->time_to_eat < 0)
		return (show_error_message("Error: wrong time to eat\n"));
	if (info->time_to_sleep < 0)
		return (show_error_message("Error: wrong time to sleep\n"));
	return (SUCCESS);
}

static int	init_mutexes(t_info *info)
{
	int		i;

	pthread_mutex_init(&info->finish_mutex, NULL);
	if (ft_malloc(&info->philos, sizeof(t_philo) * info->num_of_philo) || \
		ft_malloc(&info->forks, sizeof(pthread_mutex_t) * info->num_of_philo))
		return (show_error_message("Error: malloc error\n"));
	i = 0;
	while (i < info->num_of_philo)
	{
		info->philos[i].n = i;
		pthread_mutex_init(&info->forks[i], NULL);
		pthread_mutex_init(&info->philos[i].check_mutex, NULL);
		if (i == 0)
			info->philos[i].left = &info->forks[info->num_of_philo - 1];
		else
			info->philos[i].left = &info->forks[i - 1];
		info->philos[i].right = &info->forks[i];
		info->philos[i].info = info;
		i++;
	}
	return (SUCCESS);
}

int	init_simulation(t_info *info, int argc, char **argv)
{
	parse_arguments(info, argc, argv);
	if (validate_info(info, argc))
		return (FAIL);
	if (init_mutexes(info))
		return (FAIL);
	return (SUCCESS);
}
