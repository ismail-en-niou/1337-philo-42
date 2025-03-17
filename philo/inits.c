/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:34:06 by ien-niou          #+#    #+#             */
/*   Updated: 2025/03/17 12:56:32 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_init_pthread(t_philo **philos, t_data *data)
{
	pthread_t	monitor_thread;
	size_t		i;

	if (pthread_create(&monitor_thread, NULL, monitor, (void *)philos) != 0)
		return (false);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&philos[i]->thread, NULL, routine,
				(void *)philos[i]) != 0)
			return (false);
		i++;
	}
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(philos[i]->thread, NULL);
		i++;
	}
	if (pthread_join(monitor_thread, NULL))
	{
		exit(EXIT_FAILURE);
	}
	return (true);
}

void	ft_start(char **av)
{
	t_data	data;

	data.nb_philos = ft_atoi(av[1]);
	data.time_to_die = ft_atoi(av[2]);
	data.time_to_eat = ft_atoi(av[3]);
	data.time_to_sleep = ft_atoi(av[4]);
	data.start_time = get_time_in_ms();
	atomic_init(&data.simulation_end, false);
	if (av[5])
		data.must_eat_count = ft_atoi(av[5]);
	else
		data.must_eat_count = -1;
	ft_philo(&data);
}

bool	ft_init_mutex(t_data *data)
{
	size_t	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return (false);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (false);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (false);
	return (true);
}

bool	ft_init_philos(t_philo **philos, t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (false);
		philos[i]->id = i;
		philos[i]->data = data;
		philos[i]->meals_eaten = 0;
		philos[i]->is_eating = 0;
		philos[i]->last_meal_time = get_time_in_ms();
		philos[i]->left_fork = &data->forks[i];
		philos[i]->right_fork = &data->forks[(i + 1) % data->nb_philos];
		if (pthread_mutex_init(&philos[i]->state_mutex, NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}
