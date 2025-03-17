/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validInput.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:33:48 by ien-niou          #+#    #+#             */
/*   Updated: 2025/03/17 13:30:00 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philosopher_death(t_philo **philos, size_t i)
{
	if (get_time_in_ms()
		- get_last_meal_time(philos[i]) > philos[i]->data->time_to_die
		&& !get_is_eating(philos[i]))
	{
		pthread_mutex_lock(&philos[i]->data->print_mutex);
		if (!get_simulation_end(philos[i]->data))
		{
			printf("\033[0;31m%ld %ld died \033[0m\n", get_time_in_ms()
				- philos[i]->data->start_time, philos[i]->id + 1);
			set_simulation_end(philos[i]->data, true);
		}
		pthread_mutex_unlock(&philos[i]->data->print_mutex);
		return (1);
	}
	return (0);
}

static int	check_all_philosophers_ate(t_philo **philos)
{
	if (philos[0]->data->must_eat_count != -1)
	{
		pthread_mutex_lock(&philos[0]->data->print_mutex);
		if (!get_simulation_end(philos[0]->data))
		{
			printf("All philosophers have eaten %d times\n",
				philos[0]->data->must_eat_count);
			set_simulation_end(philos[0]->data, true);
		}
		pthread_mutex_unlock(&philos[0]->data->print_mutex);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo	**philos;
	size_t	i;
	int		all_ate;

	philos = (t_philo **)arg;
	while (!get_simulation_end(philos[0]->data))
	{
		i = 0;
		all_ate = 1;
		while (i < philos[0]->data->nb_philos)
		{
			if (check_philosopher_death(philos, i))
				return (NULL);
			if (philos[i]->data->must_eat_count != -1
				&& get_meals_eaten(philos[i]) < philos[i]->data->must_eat_count)
				all_ate = 0;
			i++;
		}
		if (all_ate && check_all_philosophers_ate(philos))
			return (NULL);
		ft_sleep(1, philos[0]->data);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		while (!get_simulation_end(philo->data))
			ft_sleep(100, philo->data);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2)
		ft_sleep(10, philo->data);
	while (!get_simulation_end(philo->data))
	{
		take_forks(philo);
		eat(philo);
		if (get_simulation_end(philo->data))
			break ;
		sleep_and_think(philo);
	}
	return (NULL);
}

void	ft_philo(t_data *data)
{
	t_philo	**philos;

	if (data->nb_philos == 0)
		return ;
	if (!ft_init_mutex(data))
		return ;
	philos = malloc(sizeof(t_philo *) * data->nb_philos);
	if (!philos)
	{
		ft_msg("Memory allocation failed for philosophers", 0);
		return ;
	}
	if (!ft_init_philos(philos, data))
	{
		cleanup(philos, data);
		return ;
	}
	if (!ft_init_pthread(philos, data))
	{
		cleanup(philos, data);
		return ;
	}
	cleanup(philos, data);
}
