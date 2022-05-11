/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 09:36:19 by gmyriah           #+#    #+#             */
/*   Updated: 2022/05/11 16:58:22 by gmyriah          ###   ########.fr       */
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

int					handle_input(int argc, char **argv, t_data *data);
int					init_data(int **args, t_data *data);
void				init_all_philos(int **args, t_data *data);
void				*actions(void *phil);
int					show_error_message(char *str);
int					print_status(t_phil *phil, char *str);
int					set_current_time(long long *time_ms);
long long			set_time_stamp(t_phil *phil, long long	*time_from_start);
void				*check_death(void *data);


#endif