/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetan <jetan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:40:30 by jetan             #+#    #+#             */
/*   Updated: 2024/12/14 18:59:33 by jetan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	printf("%d\n", philo->num_of_philo);
	while (i < philo->num_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].eating = 0;
		philo[i].meals_eaten = 0;
		philo[i].last_meal = get_current_time();
		philo[i].start_time = get_current_time();
		philo[i].done_or_dead = &data->dead_flag;
		philo[i].write_lock = &data->write_lock;
		philo[i].dead_lock = &data->dead_lock;
		philo[i].meal_lock = &data->meal_lock;
		i++;
	}
}

void	init_fork(t_data *data, t_philo *philo)
{
	int	i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * philo->num_of_philo);
	while (i < philo->num_of_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < philo->num_of_philo)
	{
		philo->l_fork = &forks[i];
		philo->r_fork = &forks[(i + 1) % philo->num_of_philo];
		i++;
	}
	data->forks = forks;
}

void	init_data(t_data *data, t_philo *philo)
{
	data->dead_flag = 0;
	data->philos = philo;
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
}

void	init_arg(t_philo *philo, int ac, char **av)
{
	if (ac == 6)
		philo->num_of_times_to_eat = ft_atoi(av[5]);
	else
	{
		philo->num_of_philo = ft_atoi(av[1]);
		philo->time_to_die = ft_atoi(av[2]);
		philo->time_to_eat = ft_atoi(av[3]);
		philo->time_to_sleep = ft_atoi(av[4]);
	}
}
