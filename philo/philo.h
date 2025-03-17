/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:46:36 by ien-niou          #+#    #+#             */
/*   Updated: 2025/03/17 12:57:14 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* philo.h */
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdatomic.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	size_t			nb_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat_count;
	time_t			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;
	atomic_bool		simulation_end;
}					t_data;

typedef struct s_philo
{
	size_t			id;
	pthread_t		thread;
	time_t			last_meal_time;
	int				meals_eaten;
	int				is_eating;
	t_data			*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	state_mutex;
}					t_philo;

/* Utils functions */
int					ft_isdigit(char c);
size_t				ft_valid_input(char **av);
time_t				get_time_in_ms(void);
size_t				ft_atoi(const char *str);
void				ft_msg(char *str, int flag);
int					ft_sleep(size_t time, t_data *dt);

/* Main philosopher functions */
void				ft_start(char **av);
void				ft_philo(t_data *data);
bool				ft_init_philos(t_philo **philos, t_data *data);
bool				ft_init_pthread(t_philo **philos, t_data *data);
bool				ft_init_mutex(t_data *data);
void				*routine(void *arg);
void				*monitor(void *arg);
void				take_forks(t_philo *philo);
void				eat(t_philo *philo);
void				sleep_and_think(t_philo *philo);
void				print_state(t_philo *philo, char *state);
void				cleanup(t_philo **philos, t_data *data);

/*getters and setters */
int					get_is_eating(t_philo *philo);
int					get_meals_eaten(t_philo *philo);
void				increment_meals_eaten(t_philo *philo);
bool				get_simulation_end(t_data *data);
void				set_simulation_end(t_data *data, bool value);
void				set_last_meal_time(t_philo *philo, time_t time);
void				set_is_eating(t_philo *philo, int value);
time_t				get_last_meal_time(t_philo *philo);

#endif