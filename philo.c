/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:26:19 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/09/02 17:26:19 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_data  data;
    int     i;
    pthread_t   monitor;

    if (argc != 5 && argc != 6)
        return (error());

    if (!verification(argv))
        return (error());

    init(&data, argv);

    if (fork_initialisation(&data))
        return (error());

    if (philos_initialisation(&data))
        return (error());

    if (start_threads(&data))
        return (error());
    i = 0;
    pthread_create(&monitor, NULL, monitor_routine, &data);
    while (i < data.num_philos)
    {
        pthread_join(data.philos[i].thread, NULL);
        i++;
    }
    pthread_join(monitor, NULL);
    clean_up(&data);
    return (0);
}
