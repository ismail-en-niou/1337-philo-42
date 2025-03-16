/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:42:36 by ien-niou          #+#    #+#             */
/*   Updated: 2025/03/16 08:08:59 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

size_t	ft_valid_input(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_sleep(size_t time, t_data *dt)
{
	size_t	start;
	time_t	end;

	start = get_time_in_ms();
	end = start + time;
	while (get_time_in_ms() < end)
	{
		if (dt->simulation_end)
			return (0);
		usleep(100);
	}
	return (1);
}

void	ft_msg(char *str, int flag)
{
	if (flag == 0)
	{
		printf("%s\n", str);
		exit(1);
	}
}
