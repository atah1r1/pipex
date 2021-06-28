/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahiri <atahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 13:08:26 by atahiri           #+#    #+#             */
/*   Updated: 2021/06/28 14:51:52 by atahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	new = (char *)malloc(lens1 + lens2 + 1);
	if (!new)
		return (NULL);
	while (i < lens1)
	{
		new[i] = *((unsigned char *)s1 + i);
		i++;
	}
	while (j < lens2)
		new[i++] = *((unsigned char *)s2 + j++);
	new[i] = '\0';
	return (new);
}
