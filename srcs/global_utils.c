/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:18:20 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/21 15:18:24 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool		ft_isdigit(int c);
static int	ft_overflow(int sign);

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	char	*s;

	result = 0;
	sign = 1;
	s = (char *)str;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (ft_isdigit(*s))
	{
		if (result != (result * 10 + *s - '0') / 10)
			return (ft_overflow(sign));
		result = (result * 10) + (*s - '0');
		s++;
	}
	return ((int)result * sign);
}

bool	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57))
		return (true);
	return (false);
}

static int	ft_overflow(int sign)
{
	if (sign < 0)
		return ((int)LONG_MIN);
	else
		return ((int)LONG_MAX);
}

bool	is_event(int philo_id)
{
	if (philo_id % 2 == 0)
		return (true);
	return (false);
}
