#include "philo.h"

void	*init_philo_process(void *philosopher)
{
	t_philo		*philo;

	philo = (t_philo *)philosopher;
	philo->time_of_last_meal = get_current_time();
	philo->start_time = get_current_time();
	while (!philo->arg->dead)
	{
		if (philo->arg->dead || philo->stop || ft_cnt_of_meals(philo))
			return (NULL);
		taking_forks(philo);
		if (philo->arg->dead || philo->stop || ft_cnt_of_meals(philo))
			return (NULL);
		eating(philo);
		if (philo->arg->dead || philo->stop || ft_cnt_of_meals(philo))
			return (NULL);
		sleeping(philo);
		if (philo->arg->dead || philo->stop || ft_cnt_of_meals(philo))
			return (NULL);
		thinking(philo);
		if (philo->arg->dead || philo->stop || ft_cnt_of_meals(philo))
			return (NULL);
	}
	return (NULL);
}

void	init_threads(t_data *simulation)
{
	int			i;
	pthread_t	*threads;
	pthread_t	s_tid;

	i = simulation->nbr_philo;
	threads = malloc(sizeof(pthread_t) * i);
	while (i--)
		pthread_create(&threads[i], \
            NULL, init_philo_process, (void *) &simulation->philosofers[i]);
	pthread_create(&s_tid, NULL, ft_galina_monitor, (void *)simulation->philosofers);
	pthread_join(s_tid, NULL);
	simulation->tids = threads;
}

long	get_current_time(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;
	return (res);
}

void init_philosophers(t_data *simulation)
{
	t_philo	*philosophers;
	int 	i;

	philosophers = malloc(sizeof(t_philo) * simulation->nbr_philo);
	i = 0;
	while (i < simulation->nbr_philo)
	{
		philosophers[i].philo_id = i;
		philosophers[i].nbr_philo = simulation->nbr_philo;
		philosophers[i].total_nbr_of_meals = 0;
		philosophers[i].total_nbr_of_meals_1 = simulation->nbr_of_meals;
		philosophers[i].time_to_eat = simulation->time_to_eat;
		philosophers[i].time_to_sleep = simulation->time_to_sleep;
		philosophers[i].time_to_die = simulation->time_to_die;
		philosophers[i].time_of_last_meal = get_current_time();
		philosophers[i].limit_of_life = simulation->time_to_die;
		philosophers[i].stop = 0;
		philosophers[i].l_f = \
			&simulation->forks[philosophers[i].philo_id];
		philosophers[i].r_f = \
			&simulation->forks[(philosophers[i].philo_id + 1) % simulation->nbr_philo];
		philosophers[i].arg = simulation;
		i++;
	}
}

void	init_mutex(t_data *simulation)
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
	init_mutex(&simulation);
	init_philosophers(&simulation);
	init_threads(&simulation);
	return (0);
}
