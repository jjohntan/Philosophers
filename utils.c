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

void	validate_arg(char **av)
{
	int	i;
	
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