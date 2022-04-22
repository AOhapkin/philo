#include "philo.h"

int	init_simulation(int argc, char **argv, t_data *simulation)
{
	simulation->nbr_philo =

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
		if (!is_only_digits(argv[i]) || !ft_atol(argv[i]))
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
		return (0);
	if (!init_simulation(argc, argv, &simulation))
	return (0);
}
