/* philo.h */
#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_data
{
    size_t      nb_philos;
    time_t      time_to_die;
    time_t      time_to_eat;
    time_t      time_to_sleep;
    int         must_eat_count;
    time_t      start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    bool        simulation_end;
} t_data;

typedef struct s_philo
{
    size_t      id;
    pthread_t   thread;
    time_t      last_meal_time;
    int         meals_eaten;
    int         is_eating;
    t_data      *data;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
} t_philo;

/* Utils functions */
int     ft_isdigit(char c);
size_t  ft_valid_input(char **av);
time_t  get_time_in_ms(void);
size_t  ft_atoi(const char *str);
void    ft_msg(char *str, int flag);

/* Main philosopher functions */
void    ft_start(char **av);
void    ft_philo(t_data *data);
bool    ft_init_philos(t_philo **philos, t_data *data);
bool    ft_init_pthread(t_philo **philos, t_data *data);
bool    ft_init_mutex(t_data *data);
void    *routine(void *arg);
void    *monitor(void *arg);
void    take_forks(t_philo *philo);
void    eat(t_philo *philo);
void    sleep_and_think(t_philo *philo);
void    print_state(t_philo *philo, char *state);
void    cleanup(t_philo **philos, t_data *data);

#endif