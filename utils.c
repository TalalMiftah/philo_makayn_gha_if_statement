#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	size_t	result;
	int		sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			sign *= -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		result *= 10;
		result += (*str - '0');
		if ((result > 2147483648 && sign == -1)
			|| (result > 2147483647 && sign == 1))
			return (1);
		str++;
	}
	return (result * sign);
}

int	ft_parsing(char **av, t_philo *philo)
{
	philo->i = 1;
	while (av[philo->i])
	{
		philo->number_of_philos = 0;
		if (ft_atoi(av[philo->i]) < 0)
			return (1);
		if (av[philo->i][0] == '+' && av[philo->i][1])
			philo->number_of_philos++;
		while (av[philo->i][philo->number_of_philos])
			if (ft_isdigit(av[philo->i][philo->number_of_philos++]) == 0)
				return (1);
		if ((philo->i == 1 && ft_atoi(av[philo->i]) > 200)
			|| (philo->i == 1 && ft_atoi(av[philo->i]) < 1))
			return (1);
		if ((philo->i >= 2 && philo->i <= 4) && ft_atoi(av[philo->i]) < 60)
			return (1);
		philo->i++;
	}
	philo->number_of_philos = ft_atoi(av[1]);
	philo->i = 1;
	while (philo->i <= philo->number_of_philos)
		ft_lstadd_back(&philo->head, lst_new(philo->i++, philo));
	return (0);
}
