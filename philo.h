#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>

typedef struct s_philo
{
	int	num_of_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int	num_of_times_to_eat;
	int	id;
	int	eating;
	int	meals_eaten;
	size_t	last_meal;
	size_t	start_time;
	int	*dead;
	pthread_t	thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int	dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

void	validate_arg(int ac, char **av);
void	data_init(t_philo *data, int ac, const char *av[]);


int	ft_isdigit(int c);
int	ft_atoi(const char *str);

#endif
