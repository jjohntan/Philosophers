/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetan <jetan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:00:42 by jetan             #+#    #+#             */
/*   Updated: 2024/12/16 17:41:04 by jetan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all(t_data *data)
{
	int	i;
	
	i = 0;
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->dead_lock);
	while (i < data->philos->num_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

void	create_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		philo[i].thread = pthread_create(&philo[i].thread, NULL, &philo_routine,
								   &philo[i]);
		i++;
	}
	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

void	print_status(t_philo *philo, int id, char *str)
{
	int	time;
	
	time = get_current_time() - philo->start_time;
	pthread_mutex_lock(philo->write_lock);
	printf("%d %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

int	done_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->done_or_dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!done_loop(philo))
	{
		ft_eat(philo);
		ft_sleep(philo);
		print_status(philo, philo->id, "is thinking");
	}
	return NULL;
}

int main(int ac, char **av)
{
	t_philo	*philo;
	t_data data;

	if (ac != 5 && ac != 6)
	{
		printf("Wrong number of argument\n");
		return (1);
	}
	if (validate_arg(ac, av) == 0)
		return (1);
	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	init_arg(philo, ac, av);
	init_data(&data, philo);
	init_fork(&data, philo);
	init_philo(philo, &data);
	create_thread(philo);
	sleep(5);
}
