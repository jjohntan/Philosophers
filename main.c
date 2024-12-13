/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetan <jetan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:00:42 by jetan             #+#    #+#             */
/*   Updated: 2024/12/13 18:48:43 by jetan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	
	time = get_time() - philo->start_time;
	pthread_mutex_lock(philo->write_lock);
	printf("%d %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	print_status(philo, philo->id, "has taken a fork");
	print_status(philo, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	philo->last_meal = get_time();
	philo->meals_eaten++;
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->f_fork);
}

void	*philo_routine(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;
	printf("%d\n", philo->id);
	while (1)
	{
		eat(philo);
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
