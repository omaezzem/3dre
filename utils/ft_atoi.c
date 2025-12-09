/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:58:42 by mel-badd          #+#    #+#             */
/*   Updated: 2025/12/06 17:58:46 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					s;
	long				r;
	long				tmp;

	i = 0;
	s = 1;
	r = 0;
	tmp = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			s = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = r;
		r = r * 10 + (str[i++] - '0');
		if (s == 1 && tmp != r / 10)
			return (-1);
		else if (s == -1 && tmp != r / 10)
			return (0);
	}
	return (r * s);
}
