/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:59:24 by marvin            #+#    #+#             */
/*   Updated: 2025/03/15 11:46:29 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		ft_msg("Usage: ./philo nb_philos tim2die tim2eat time2slep [max_eat]",
			0);
		return (1);
	}
	if (!ft_valid_input(av))
	{
		ft_msg("Invalid input: all arguments must be positive numbers", 0);
		return (1);
	}
	ft_start(av);
	return (0);
}
