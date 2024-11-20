/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetan <jetan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:12:28 by jetan             #+#    #+#             */
/*   Updated: 2024/11/18 18:56:11 by jetan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	validate_arg(int ac, char **av)
{
	int	i;
	
	if (ac != 5 && ac != 6)
	{
		printf("Wrong number of argument\n");
		return ;
	}
	i = 0;
	while (av[++i])
	{
		if (!ft_isdigit(av[i]))
		{
			printf("Invalid argument\n");
			return ;
		}
		i++;
	}
}
