#include "philo.h"

void	ft_init_mutex(t_data *simulation)
{
	int				philo_counter;
	pthread_mutex_t	*mutex;

	philo_counter = simulation->nbr_philo;
	mutex = malloc(sizeof(pthread_mutex_t) * philo_counter);
	while (philo_counter--)
		pthread_mutex_init(&mutex[philo_counter], NULL);
	pthread_mutex_init(&simulation->lock_print, NULL);
	simulation->forks = mutex;
}

int	init_simulation(int argc, char **argv, t_data *simulation)
{
	simulation->nbr_philo = ft_atoi(argv[1]);
	simulation->time_to_die = ft_atoi(argv[2]);
	simulation->time_to_eat = ft_atoi(argv[3]);
	simulation->time_to_sleep = ft_atoi(argv[4]);
	simulation->dead = 0;
	if (argc == 5)
	{
		if (simulation->nbr_philo < 1)
			return (0);
		simulation->nbr_of_meals = -1;
	}
	if (argc == 6)
	{
		simulation->nbr_of_meals = ft_atoi(argv[5]);
		if (simulation->nbr_of_meals < 1)
			return (0);
	}
	return (1);
}

int	is_only_digits(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	is_args_valid(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Error!\nSimulation need 4 or 5 arguments");
		return (1);
	}
	i = 1;
	while (argv[i])
	{
		if (!is_only_digits(argv[i]) || ft_atoi(argv[i]) <= 0)
		{
			printf("Arguments aren't valid\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	simulation;

	if (!is_args_valid(argc, argv))
		return (1);
	if (!init_simulation(argc, argv, &simulation))
		return (1);
	ft_init_mutex(&simulation);
	return (0);
}
