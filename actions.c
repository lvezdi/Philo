/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 13:40:28 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/11/16 17:49:50 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken a fork\n");
	pthread_mutex_unlock(philo->left_fork);
	usleep(philo->data->time_to_die * 1000);
	return (0);
}

static int	handle_stop(t_philo *philo, pthread_mutex_t *first,
		pthread_mutex_t *second)
{
	pthread_mutex_unlock(&philo->data->stop_mutex);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
	return (0);
}

static void	assign_forks(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if (philo->id % 2 == 1)
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
	else
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
}

int	handle_eating(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->data->num_philos == 1)
		return (handle_one_philo(philo));
	assign_forks(philo, &first, &second);
	pthread_mutex_lock(first);
	print_message(philo, "has taken a fork\n");
	pthread_mutex_lock(second);
	print_message(philo, "has taken a fork\n");
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (philo->data->stop)
		return (handle_stop(philo, first, second));
	pthread_mutex_unlock(&philo->data->stop_mutex);
	print_message(philo, "is eating\n");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}
