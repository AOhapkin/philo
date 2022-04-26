#include "philo.h"

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
