#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define SUCCESS	0
# define FAIL	1

typedef struct s_philo
{
	int				n;
	int				num_of_eat;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	check_mutex;
	pthread_t		thread;
	struct s_info	*info;
	struct timeval	last_time_to_eat;
}					t_philo;

typedef struct s_info
{
	int				num_of_philo;
	int				num_of_eat_finish_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	int				finish;
	pthread_mutex_t	finish_mutex;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	struct timeval	create_at;
}					t_info;

int			init(t_info *info, int argc, char *argv[]);
void		*philo(void *argv);
void		*monitor(void *argv);
void		*monitor_each_must_eat(void *argv);
int			ft_atoi(const char *nptr);
int			show_error_message(char *message);
int			ft_malloc_memset(void *dst, size_t size);
long long	time_to_ms(struct timeval now);
void		print_philo_msg(t_philo *philo, char *str);

#endif