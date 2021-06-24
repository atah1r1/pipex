/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahiri <atahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 13:04:00 by atahiri           #+#    #+#             */
/*   Updated: 2021/06/24 13:04:17 by atahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	count;
	size_t	lens;

	count = 0;
	if (!s)
		return (NULL);
	lens = ft_strlen((char *)s);
	if (start > lens)
		len = 0;
	if (!(str = malloc((len + 1 * sizeof(char)))))
		return (NULL);
	while (count < len && s[start] && start < lens)
	{
		str[count] = *(unsigned char *)(s + start);
		start++;
		count++;
	}
	str[count] = '\0';
	return (str);
}