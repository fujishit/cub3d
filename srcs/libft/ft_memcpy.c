/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:39:46 by mfujishi          #+#    #+#             */
/*   Updated: 2020/11/03 16:49:03 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*ret;
	unsigned const char	*retsrc;

	if (dest == src)
		return (dest);
	ret = (unsigned char *)dest;
	retsrc = (unsigned char *)src;
	while (n--)
		*ret++ = *retsrc++;
	return (dest);
}
