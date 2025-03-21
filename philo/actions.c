/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:40:43 by ien-niou          #+#    #+#             */
/*   Updated: 2025/03/17 16:19:41 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->simulation_end)
		printf("\033[0;32m%ld\033[0m \033[0;36m%ld\033[0m \033[0;33m%s\033[0m\n",
			get_time_in_ms() - philo->data->start_time, philo->id + 1, state);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	print_state(philo, "is eating");
	pthread_mutex_lock(&philo->state_mutex);
	philo->is_eating = 1;
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->state_mutex);
	ft_sleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_lock(&philo->state_mutex);
	philo->meals_eaten++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->state_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_and_think(t_philo *philo)
{
	print_state(philo, "is sleeping");
	ft_sleep(philo->data->time_to_sleep, philo->data);
	print_state(philo, "is thinking");
}

void	cleanup(t_philo **philos, t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&philos[i]->state_mutex);
		free(philos[i]);
		i++;
	}
	free(data->forks);
	free(philos);
}
