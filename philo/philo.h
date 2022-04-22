#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				nbr_philo;
	time_t			start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				dead;
	int				nbr_of_meals;
	pthread_mutex_t	*forks;
	pthread_t		*tids;
	pthread_mutex_t	lock_print;
	t_philo			*all_philos;
}					t_data;

int	ft_atoi(const char *str);
int		ft_isspace(int c);

#endif