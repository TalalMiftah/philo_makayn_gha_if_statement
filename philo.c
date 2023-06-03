/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:20:16 by tmiftah           #+#    #+#             */
/*   Updated: 2023/05/17 19:18:19 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initial(t_philo *philo, char **str, int ac)
{
	philo->d1 = 0;
	philo->index = 0;
	philo->ac = ac;
	philo->number_of_philos = ft_atoi(str[1]);
	philo->time_to_die = ft_atoi(str[2]);
	philo->time_to_eat = ft_atoi(str[3]);
	philo->time_to_sleep = ft_atoi(str[4]);
	if (str[5])
		philo->time_op = ft_atoi(str[5]);
	if(pthread_mutex_init(&philo->death, NULL) != 0)
		return (1);
	if(pthread_mutex_init(&philo->eat, NULL) != 0)
		return (1);
	if(pthread_mutex_init(&philo->print, NULL) != 0)
		return (1);
	return (0);
}

int	start(t_philo *philo)
{
	t_est *h;

	h = philo->head;
	philo->start = current_time();
	while (h)
	{
		h->last_meal = current_time();
		if (h->phi->number_of_philos == 1)
		{
			if (pthread_create(&h->philo_id, NULL, routine1, h))
				return (1);
		}
		else if (pthread_create(&h->philo_id, NULL, routine, h))
			return (1);
		h = h->next;
		if (h == philo->head)
			break ;
	}
	while (h)
	{
		if (pthread_join(h->philo_id, NULL))
			return (1);
		h = h->next;
		if (h == philo->head)
			break ;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	philo;
	
	philo.head = NULL;
	if (ac > 6 || ac < 5)
		return (write(2, "Error\n", 6), 1);
	if (ft_parsing(av, &philo))
		return (write(2, "Error\n", 6), 1);
	if (initial(&philo, av, ac) != 0)
		return (write(2, "Error\n", 6), 1);
	if (start(&philo) != 0)
		return (write(2, "Error\n", 6), 1);
	if (philo.d1 == 1)
		printf("%lld\t%d\tis died\n", current_time() - philo.start, philo.index);
	return (0);
}
