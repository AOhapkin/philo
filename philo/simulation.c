#include "philo.h"

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
