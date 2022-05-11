/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 09:36:41 by gmyriah           #+#    #+#             */
/*   Updated: 2022/05/11 17:00:09 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_digits_integer(const char *str)
{
	int	i;
	int	num_digits;

	i = 0;
	num_digits = 0;
	if (str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		if (!((str[i] >= 48) && (str[i] <= 57)))
			return (1);
		num_digits++;
		i++;
	}
	if (num_digits > 10)
		return (1);
	return (0);
}

static int	ft_atoi_phil(const char *str)
{
	int					i;
	int					neg;
	unsigned long long	nb;

	neg = 1;
	i = 0;
	nb = 0;
	if (check_digits_integer(str))
		return (-1);
	while ((str[i] == ' ') || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-')
		neg = -1;
	if ((str[i] == '+') || (str[i] == '-') || str[i] == '0')
		i++;
	while ((str[i] >= '0') && (str[i] <= '9') && (str[i] != '\0'))
		nb = nb * 10 + str[i++] - '0';
	if (((nb > 2147483647) && (neg == 1)) || ((neg == -1) && (nb > 2147483648)))
		return (-1);
	return (neg * (int)nb);
}

void	init_all_philos(int **args, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_phil)
	{
		data->phil[i].phil_id = i + 1;
		data->phil[i].total_phil = (*args)[0];
		data->phil[i].time_to_eat = (*args)[2];
		data->phil[i].time_to_sleep = (*args)[3];
		data->phil[i].num_eat = 0;
		data->phil[i].last_meal_ms = data->start_ms;
		data->phil[i].ptr_data = data;
		if (i == 0)
			data->phil[i].left_fork_id = data->phil[i].total_phil - 1;
		else
			data->phil[i].left_fork_id = i - 1;
		data->phil[i].right_fork_id = i;
		i++;
	}
}

static int	check_atoi(char **argv, int **args)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		(*args)[i - 1] = ft_atoi_phil(argv[i]);
		if ((*args)[i++ - 1] <= 0)
			return (show_error_message("Input error!\n"));
	}
	if (i != 6)
		(*args)[i - 1] = -1;
	return (SUCCESS);
}

int	handle_input(int argc, char **argv, t_data *data)
{
	int	*args;

	args = malloc(sizeof(int) * 5);
	if (!args)
		return (show_error_message("Malloc error\n"));
	if (!((argc == 5) || (argc == 6)))
	{
		free(args);
		return (show_error_message("Wrong arguments number\n"));
	}
	else
		if (check_atoi(argv, &args))
			return (FAIL);
	if (init_data(&args, data))
		return (FAIL);
	free(args);
	return (0);
}
