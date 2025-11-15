/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:45:38 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/09/15 19:45:38 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    init(t_data *data, char **argv)
{
    data->num_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->num_to_eat = -1;
    
    if (argv[5])
        data->num_to_eat = ft_atoi(argv[5]);
    data->stop = 0;
    pthread_mutex_init(&data->stop_mutex, NULL);
    pthread_mutex_init(&data->print_mutex, NULL);
    data->start_time = get_time();
}

int    fork_initialisation(t_data *data) // inicializacion tenedores
{
    int i;

    i = 0;
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    if (data->forks == NULL)
        return (1);
    while (i < data->num_philos)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
            return (1);
        i++;
    }
    return (0);
}

int     philos_initialisation(t_data *data)//inicialización de philos
{
    int i;

    i = 0;
    data->philos = malloc(sizeof(t_philo) * data->num_philos);
    if (data->philos == NULL)
        return (1);
    while (i < data->num_philos)
    {
        data->philos[i].id = i + 1;
        data->philos[i].data = data;
        data->philos[i].left_f = i;
        data->philos[i].right_f = (i + 1) % data->num_philos;
        data->philos[i].left_fork = &data->forks[data->philos[i].left_f];
        data->philos[i].right_fork =  &data->forks[data->philos[i].right_f];
        data->philos[i].last_meal  = data->start_time;
        data->philos[i].times_eaten = 0;
        data->philos[i].data       = data;
        i++;
    }
    return (0);
}

static int handle_eating(t_philo *philo)  // helper for eating cycle
{
    pthread_mutex_lock(philo->left_fork);
    print_message(philo, "has taken a fork\n");
    if (philo->data->num_philos == 1)
    {
        // Only one fork available; release it and simulate death timing
        pthread_mutex_unlock(philo->left_fork);
        return (0);
    }
    pthread_mutex_lock(philo->right_fork);
    print_message(philo, "has taken a fork\n");
    pthread_mutex_lock(&philo->data->stop_mutex);
    if (philo->data->stop)
    {
        pthread_mutex_unlock(&philo->data->stop_mutex);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        return (0);
    }
    philo->last_meal = get_time();
    philo->times_eaten++;
    print_message(philo, "is eating\n");
    pthread_mutex_unlock(&philo->data->stop_mutex);
    usleep(philo->data->time_to_eat * 1000);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    return (1);
}

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        usleep(1000);  // small stagger for even-numbered philosophers
    while (!philo->data->stop)
    {
        if (!handle_eating(philo))
            break ;
        print_message(philo, "is sleeping\n");
        if (philo->data->stop)
            break ;
        usleep(philo->data->time_to_sleep * 1000);
        print_message(philo, "is thinking\n");
    }
    // If a philosopher was the only one, let monitor print death after time_to_die
    if (philo->data->num_philos == 1)
        usleep((philo->data->time_to_die + 1) * 1000);
    return (NULL);
}

void clean_up(t_data *data)
{
    int i;

    i = 0;

    if (data->philos)
        free(data->philos);
    if (data->forks)
    {
        while (i < data->num_philos)
        {
            pthread_mutex_destroy(&data->forks[i]);
            i++;
        }
        free(data->forks);
    }
    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->stop_mutex);
}
void    print_message(t_philo *philo, char *msg)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("Philo %d %s", philo->id, msg);
    pthread_mutex_unlock(&philo->data->print_mutex);
    long timestamp;

    timestamp = get_time() - philo->data->start_time;
    pthread_mutex_lock(&philo->data->print_mutex);
    if (!philo->data->stop)
        printf("%ld %d %s", timestamp, philo->id, msg);
    pthread_mutex_unlock(&philo->data->print_mutex);
}


int error(void)
{
    printf("Error: something went wrong\n");
    return (1);
}

int start_threads(t_data *data)
{
    int i;
    i = 0;
    while (i < data->num_philos)
    {
        if (pthread_create(&data->philos[i].thread,
                NULL, philo_routine, &data->philos[i]) != 0)
            return (1);
        i++;
    }
    return (0);
}

//SE PUEDE UTILIZAR funciones variádicas?????????
//-----> luego cada vez que hagas un printf te recomiendo que hagas una función donde uses mutex para evitar data races

//si solo hay uno tiene que morir unn if antes del bucle while en la rutina
//nummero de veces comida (actualizar valor)