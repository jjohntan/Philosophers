/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetan <jetan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:00:42 by jetan             #+#    #+#             */
/*   Updated: 2024/11/18 18:55:41 by jetan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init(t_program *data, int ac, const char *av[])
{
	if (ac == 6)
	{
		data->num_of_philo(av[1]);
		data->time_to_die(av[2]);
		data->time_to_eat(av[3]);
		data->time_to_sleep(av[4]);
	}
	else
	{
		data->num_of_times_to_eat(av[5]);
	}
}

int main(int ac, const char *av[])
{
	t_program	data;

	if (ac != 5 && ac != 6)
	{
		printf("Wrong number of argument\n");
		return (1);
	}
	validate_arg(av);
	init(&data, ac, av);
}
