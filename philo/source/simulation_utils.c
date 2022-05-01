/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 09:36:36 by gmyriah           #+#    #+#             */
/*   Updated: 2022/05/01 09:36:37 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_to_ms(struct timeval now)
{
	long long		ms;

	ms = now.tv_sec * 1000;
	ms += now.tv_usec / 1000;
	return (ms);
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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned long int	result;
	int					negative;
	size_t				i;

	result = 0;
	negative = 1;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
		if (result > 2147483647 && negative == 1)
			return (0);
		else if (result > 2147483648 && negative == -1)
			return (0);
	}
	return ((int)(result * negative));
}
