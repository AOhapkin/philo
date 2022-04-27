#include "philo.h"

long long	time_to_ms(struct timeval now)
{
	long long		ms;

	ms = now.tv_sec * 1000;
	ms += now.tv_usec / 1000;
	return (ms);
}

void	print_philo_msg(t_philo *philo, char *str)
{
	long long		ms;
	struct timeval	now;

	pthread_mutex_lock(&philo->info->finish_mutex);
	gettimeofday(&now, NULL);
	ms = time_to_ms(now) - time_to_ms(philo->info->create_at);
	if (!philo->info->finish)
		printf("%lld\t%d\t %s\n", ms, philo->n + 1, str);
	pthread_mutex_unlock(&philo->info->finish_mutex);
}

int	show_error_message(char *message)
{
	char	*s;
	int		i;

	s = message;
	i = 0;
	while (*s++)
		i++;
	write(2, message, i);
	return (FAIL);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	flag;

	result = 0;
	flag = 1;
	if (*nptr == '-')
		flag *= -1;
	while ('0' <= *nptr && *nptr <= '9')
	{
		result *= 10;
		result += *nptr++ - '0';
	}
	return (result * flag);
}

int	ft_malloc(void *dst, size_t size)
{
	*(void **)dst = malloc(size);
	if (*(void **)dst == NULL)
		return (FAIL);
	memset(*(void **)dst, 0, size);
	return (SUCCESS);
}
