/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 22:32:03 by mfujishi          #+#    #+#             */
/*   Updated: 2021/04/13 05:39:29 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*dest;
	unsigned const char	*src;

	dest = s1;
	src = s2;
	while (n--)
	{
		if (*dest != *src)
			return (*dest - *src);
		dest++;
		src++;
	}
	return (0);
}
