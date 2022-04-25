#include "philo.h"

void	*init_philo_process(void *philosopher)
{
	t_philo		*temp_p;

	temp_p = (t_philo *)philosopher;
	temp_p->time_of_last_meal = get_current_time();
	temp_p->start_time = get_current_time();
	while (!temp_p->arg->dead)
	{
		if (temp_p->arg->dead || temp_p->stop || is_enough_meals(temp_p))
			return (NULL);
		taking_forks(temp_p);
		if (temp_p->arg->dead || temp_p->stop || is_enough_meals(temp_p))
			return (NULL);
		eating(temp_p);
		if (temp_p->arg->dead || temp_p->stop || is_enough_meals(temp_p))
			return (NULL);
		sleeping(temp_p);
		if (temp_p->arg->dead || temp_p->stop || is_enough_meals(temp_p))
			return (NULL);
		thinking(temp_p);
		if (temp_p->arg->dead || temp_p->stop || is_enough_meals(temp_p))
			return (NULL);
	}
	return (NULL);
}

void	set_death_and_stop(t_philo *philo, int i)
{
	philo->arg->dead = 1;
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d died\n", get_current_time() - philo->start_time,
		   philo[i].philo_id + 1);
	i = -1;
	while (i < philo[i].nbr_philo)
	{
		philo[i].stop = 1;
		i++;
	}
}

int	is_enough_meals(t_philo *philo)
{
	int	flag_stop_eating;
	int	i;

	if (philo->total_nbr_of_meals != -1 \
		&& philo->total_nbr_of_meals_1 > 0)
	{
		flag_stop_eating = 1;
		i = -1;
		while (++i < philo->nbr_philo)
			if (philo[i].total_nbr_of_meals < philo->total_nbr_of_meals_1)
				flag_stop_eating = 0;
		if (flag_stop_eating == 1)
		{
			i = -1;
			while (i < philo[i].nbr_philo)
			{
				philo[i].stop = 1;
				i++;
			}
			return (1);
		}
	}
	return (0);
}

void	*check_philosophers(void *args)
{
	t_philo	*philos;
	long	current_time;
	int		i;

	philos = (t_philo *)args;
	i = 0;
	while (philos[i].stop == 0)
	{
		i = -1;
		while (++i < philos->nbr_philo)
		{
			current_time = get_current_time();
			if (current_time - philos[i].time_of_last_meal > philos[i].limit_of_life)
			{
				set_death_and_stop(philos, i);
				pthread_mutex_unlock(&philos->lock_print);
				return (NULL);
			}
		}
		if (is_enough_meals(philos) || philos->stop)
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
	pthread_create(&s_tid, NULL, check_philosophers,
				   (void *) simulation->philosofers);
	pthread_join(s_tid, NULL);
	simulation->tids = threads;
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
	simulation->philosofers = philosophers;
}

void	init_mutex(t_data *simulation)
{
	int				counter;
	pthread_mutex_t	*mutex;

	counter = simulation->nbr_philo;
	mutex = malloc(sizeof(pthread_mutex_t) * counter);
	while (counter--)
		pthread_mutex_init(&mutex[counter], NULL);
	pthread_mutex_init(&simulation->lock_print, NULL);
	simulation->forks = mutex;
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
