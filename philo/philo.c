/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:59:24 by marvin            #+#    #+#             */
/*   Updated: 2025/03/09 11:59:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    if (ac < 5 || ac > 6)
    {
        ft_msg("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]", 0);
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
