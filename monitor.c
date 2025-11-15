#include "philo.h"

static int check_philo_state(t_philo *philo)
{
    long now;

    pthread_mutex_lock(&philo->data->stop_mutex);
    now = get_time();
    if ((now - philo->last_meal) > philo->data->time_to_die)
    {
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("%ld %d died\n", now - philo->data->start_time, philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);
        philo->data->stop = 1;
        pthread_mutex_unlock(&philo->data->stop_mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->data->stop_mutex);
    return (0);
}

void *monitor_routine(void *arg)
{
    t_data *data;
    int    i;
    int    all_done;

    data = (t_data *)arg;
    while (!data->stop)
    {
        all_done = 1;
        i = 0;
        while (i < data->num_philos)
        {
            if (check_philo_state(&data->philos[i]))
                return (NULL);
            if (data->num_to_eat != -1 &&
                data->philos[i].times_eaten < data->num_to_eat)
            {
                all_done = 0;
            }
            i++;
        }
        if (data->num_to_eat != -1 && all_done)
        {
            pthread_mutex_lock(&data->stop_mutex);
            data->stop = 1;
            pthread_mutex_unlock(&data->stop_mutex);
            return (NULL);
        }
        usleep(1000);  // sleep 1ms between checks
    }
    return (NULL);
}

long    get_time(void)
{
	struct timeval  tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
