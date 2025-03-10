#include "philo.h"

int ft_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

size_t ft_valid_input(char **av)
{
    int i;
    int j;

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

time_t get_time_in_ms(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void ft_msg(char *str, int flag)
{
    if (flag == 0)
    {
        printf("%s\n", str);
        exit(1);
    }
}

void ft_start(char **av)
{
    t_data data;

    data.nb_philos = ft_atoi(av[1]);
    data.time_to_die = ft_atoi(av[2]);
    data.time_to_eat = ft_atoi(av[3]);
    data.time_to_sleep = ft_atoi(av[4]);
    data.start_time = get_time_in_ms();
    data.simulation_end = false;
    if (av[5])
        data.must_eat_count = ft_atoi(av[5]);
    else
        data.must_eat_count = -1;  
    ft_philo(&data);
}

bool ft_init_mutex(t_data *data)
{
    size_t i;

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

bool ft_init_philos(t_philo **philos, t_data *data)
{
    size_t i;

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
        i++;
    }
    return (true);
}

void *monitor(void *arg)
{
    t_philo **philos;
    size_t   i;
    int      all_ate;
    
    philos = (t_philo **)arg;
    while (!philos[0]->data->simulation_end)
    {
        i = ((all_ate = 1),0);
        while (i < philos[0]->data->nb_philos)
        {
            if (get_time_in_ms() - philos[i]->last_meal_time > philos[i]->data->time_to_die
                && !philos[i]->is_eating)
            {
                pthread_mutex_lock(&philos[i]->data->print_mutex);
                printf("%ld %ld died\n", get_time_in_ms() - philos[i]->data->start_time, philos[i]->id + 1);
                philos[i]->data->simulation_end = true;
                pthread_mutex_unlock(&philos[i]->data->print_mutex);
                return (NULL);
            }
            if (philos[i]->data->must_eat_count != -1 && 
                philos[i]->meals_eaten < philos[i]->data->must_eat_count)
                all_ate = 0;
            i++;
        }
        if (philos[0]->data->must_eat_count != -1 && all_ate)
        {
            pthread_mutex_lock(&philos[0]->data->print_mutex);
            printf("All philosophers have eaten %d times\n", philos[0]->data->must_eat_count);
            philos[0]->data->simulation_end = true;
            pthread_mutex_unlock(&philos[0]->data->print_mutex);
            return (NULL);
        }
        usleep(1000);
    }
    return (NULL);
}

bool ft_init_pthread(t_philo **philos, t_data *data)
{
    pthread_t monitor_thread;
    size_t i;

    if (pthread_create(&monitor_thread, NULL, monitor, (void *)philos) != 0)
        return (false);
    i = 0;
    while (i < data->nb_philos)
    {
        if (pthread_create(&philos[i]->thread, NULL, routine, (void *)philos[i]) != 0)
            return (false);
        usleep(100);
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

void print_state(t_philo *philo, char *state)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    if (!philo->data->simulation_end)
        printf("%ld %ld %s\n", 
            get_time_in_ms() - philo->data->start_time, philo->id + 1, state);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

void take_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        print_state(philo, "has taken a fork 1");
        pthread_mutex_lock(philo->right_fork);
        print_state(philo, "has taken a fork 2");
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        print_state(philo, "has taken a fork 1");
        pthread_mutex_lock(philo->left_fork);
        print_state(philo, "has taken a fork 1");
    }
}

void eat(t_philo *philo)
{
    philo->is_eating = 1;
    print_state(philo, "is eating");
    philo->last_meal_time = get_time_in_ms();
    usleep(philo->data->time_to_eat * 1000);
    philo->meals_eaten++;
    philo->is_eating = 0;
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void sleep_and_think(t_philo *philo)
{
    print_state(philo, "is sleeping");
    usleep(philo->data->time_to_sleep * 1000);
    print_state(philo, "is thinking");
}

void *routine(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    if (philo->data->nb_philos == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_state(philo, "has taken a fork");
        while (!philo->data->simulation_end)
            usleep(1000);
        pthread_mutex_unlock(philo->left_fork);
        return (NULL);
    }
    if (philo->id % 2)
        usleep(1000);
    while (!philo->data->simulation_end)
    {
        take_forks(philo);
        eat(philo);
        sleep_and_think(philo);
    }
    return (NULL);
}

void cleanup(t_philo **philos, t_data *data)
{
    size_t i;

    i = 0;
    while (i < data->nb_philos)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->print_mutex);
    free(data->forks);
    i = 0;
    while (i < data->nb_philos)
    {
        free(philos[i]);
        i++;
    }
    free(philos);
}

void ft_philo(t_data *data)
{
    t_philo **philos;
    
    if (data->nb_philos == 0)
        return;
    if (!ft_init_mutex(data))
        return;
    philos = malloc(sizeof(t_philo *) * data->nb_philos);
    if (!philos)
    {
        ft_msg("Memory allocation failed for philosophers", 0);
        return;
    }
    if (!ft_init_philos(philos, data))
    {
        cleanup(philos, data);
        return;
    }
    if (!ft_init_pthread(philos, data))
    {
        cleanup(philos, data);
        return;
    }
    cleanup(philos, data);
}
