/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 17:36:38 by plagache          #+#    #+#             */
/*   Updated: 2020/04/13 16:58:02 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strclr(char *s)
{
	int c;

	c = 0;
	if (!(s == 0))
	{
		while (s[c])
		{
			s[c] = '\0';
			c++;
		}
	}
}