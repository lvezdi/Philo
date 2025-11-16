/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 13:51:38 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/11/16 13:51:38 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philo_state(t_philo *philo)
{
	int	died;

	died = 0;
	pthread_mutex_lock(&philo->meal_mutex);
	if (get_time() - philo->last_meal > philo->data->time_to_die)
	{
		print_message(philo, "died\n");
		died = 1;
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	if (died)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		philo->data->stop = 1;
		pthread_mutex_unlock(&philo->data->stop_mutex);
	}
	return (died);
}

static int	check_meals(t_data *data, int i, int *all_done)
{
	pthread_mutex_lock(&data->philos[i].meal_mutex);
	if (data->philos[i].times_eaten < data->num_to_eat)
		*all_done = 0;
	pthread_mutex_unlock(&data->philos[i].meal_mutex);
	return (0);
}

static int	stop_if_done(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
	return (1);
}

static int	check_all_philos(t_data *data)
{
	int	i;
	int	all_done;

	all_done = 1;
	i = 0;
	while (i < data->num_philos)
	{
		if (check_philo_state(&data->philos[i]))
			return (1);
		if (data->num_to_eat != -1)
			check_meals(data, i, &all_done);
		i++;
	}
	if (data->num_to_eat != -1 && all_done)
		return (stop_if_done(data));
	return (0);
}

/*static int	check_all_philos(t_data *data)
{
	int	i;
	int	all_done;

	all_done = 1;
	i = 0;
	while (i < data->num_philos)
	{
		if (check_philo_state(&data->philos[i]))
			return (1);
		if (data->num_to_eat != -1)
		{
			pthread_mutex_lock(&data->philos[i].meal_mutex);
			if (data->philos[i].times_eaten < data->num_to_eat)
				all_done = 0;
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
		}
		i++;
	}
	if (data->num_to_eat != -1 && all_done)
	{
		pthread_mutex_lock(&data->stop_mutex);
		data->stop = 1;
		pthread_mutex_unlock(&data->stop_mutex);
		return (1);
	}
	return (0);
}*/

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->stop_mutex);
		if (data->stop)
		{
			pthread_mutex_unlock(&data->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->stop_mutex);
		if (check_all_philos(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
