/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetan <jetan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:00:42 by jetan             #+#    #+#             */
/*   Updated: 2024/12/09 21:03:20 by jetan            ###   ########.fr       */
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
		// philo[i].last_meal = get_time;
		// philo[i].start_time = get_time;
		philo[i].done_or_dead = 0;
		philo[i].write_lock = &data->write_lock;
		philo[i].dead_lock = &data->dead_lock;
		philo[i].meal_lock = &data->meal_lock;
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

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_status(t_philo *philo, int id, char *str)
{
	int	time;
	
	time = get_time();
	pthread_mutex_lock(philo->write_lock);
	printf("%d %s\n", id, str);
	pthread_mutex_unlock(philo->write_lock);
}


void	*philo_routine(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;
	printf("%d\n", philo->id);
	while (1)
	{
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
