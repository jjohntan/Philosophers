/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetan <jetan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:45:36 by jetan             #+#    #+#             */
/*   Updated: 2024/12/21 22:50:19 by jetan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/**
 * @brief Initializing the philo struct
 */
void	init_philo(t_data *data, char **av)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philo[i].num_philo = data->num_philo;
		data->philo[i].philo_id = i + 1;
		data->philo[i].eating = 0;
		data->philo[i].num_meal = 0;
		data->philo[i].time_start_eat = get_time_ms();
		data->philo[i].last_meal = get_time_ms();
		assign_time(&data->philo[i], av);
		data->philo[i].dead_or_done_lock = &data->dead_or_done_lock;
		data->philo[i].do_lock = &data->do_lock;
		data->philo[i].message_lock = &data->message_lock;
		data->philo[i].done_or_die = &data->done_or_die;
		data->philo[i].l_fork = &data->fork[i];
		if (i == 0)
			data->philo[i].r_fork = &data->fork
			[data->philo[i].num_philo - 1];
		else
			data->philo[i].r_fork = &data->fork[i - 1];
		i++;
	}
}

/**
 * @brief Initializing the forks mutexes
 */
void	init_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
}

/**
 *  @brief initializing the data struct
 */
void	init_data(t_data *data, char **av)
{
	data->num_philo = ft_atol(av[1]);
	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	if (data->philo == NULL)
		return ;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (data->fork == NULL)
		return ;
	data->done_or_die = 0;
	pthread_mutex_init(&data->dead_or_done_lock, NULL);
	pthread_mutex_init(&data->do_lock, NULL);
	pthread_mutex_init(&data->message_lock, NULL);
}
