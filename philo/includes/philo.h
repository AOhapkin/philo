/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 09:36:19 by gmyriah           #+#    #+#             */
/*   Updated: 2022/05/11 16:57:04 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define SUCCESS	0
# define FAIL		1

typedef struct s_phil
{
	int					phil_id;
	int					total_phil;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_eat;
	int					left_fork_id;
	int					right_fork_id;
	long long			last_meal_ms;
	struct s_data		*ptr_data;
}	t_phil;

typedef struct s_data
{
	int					total_phil;
	int					time_to_die;
	int					total_eat;
	int					all_have_eaten;
	int					end;
	long long			start_ms;
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		mutex_time;
	pthread_mutex_t		mutex_end;
	pthread_mutex_t		mutex_all_have_eaten;
	pthread_mutex_t		*mutex_forks;
	t_phil				*phil;
}	t_data;

int			init_simulation(t_info *info, int argc, char *argv[]);
void		*run_philo_actions(void *argv);
void		*monitor(void *argv);
void		*monitor_each_must_eat(void *argv);
int			ft_atoi(const char *nptr);
int			show_error_message(char *message);
int			ft_malloc(void *dst, size_t size);
long long	time_to_ms(struct timeval now);
void		show_philo_message(t_philo *philo, char *str);

#endif