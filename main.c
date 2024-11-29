/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetan <jetan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:00:42 by jetan             #+#    #+#             */
/*   Updated: 2024/11/21 17:43:27 by jetan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	init_data(t_data *data, t_philo *philo)
{
	data->dead_flag = 0;
	data->philos = philo;
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * philo->num_of_philo);
}

void	init_fork(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < philo->num_of_philo)
	{
		philo->l_fork = &data->forks[i];
		philo->r_fork = &data->forks[(i + 1) % philo->num_of_philo];
		i++;
	}
}
// void	init_philo(t_philo *philo)
// {
// 	int	i;
//
// 	i = 0;
// 	while (i < philo->num_of_philo)
// 	{
// 		philo->philos[i].id = i + 1;
// 		i++;
// 	}
// 	printf("%d\n", philos[i].id);
// }

int main(int ac, char **av)
{
	t_philo	philo;
	t_data data;

	if (ac != 5 && ac != 6)
	{
		printf("Wrong number of argument\n");
		return (1);
	}
	if (validate_arg(ac, av) == 0)
		return (1);
	init_arg(&philo, ac, av);
	init_data(&data, &philo);
	init_fork(&data, &philo);
	// init_philo(&philo);
}
