/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahiri <atahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:39:46 by atahiri           #+#    #+#             */
/*   Updated: 2021/06/29 13:27:53 by atahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **envp, char *cmd)
{
	g_all.i = -1;
	while (envp[++g_all.i])
	{
		g_all.j = -1;
		if (!ft_strncmp(envp[g_all.i], "PATH=", 5))
		{
			g_all.s_path = ft_substr(envp[g_all.i], 5, ft_strlen(envp[g_all.i]));
			g_all.paths = ft_split(g_all.sub_path, ':');
			free(g_all.sub_path);
			while (g_all.paths[++g_all.j])
			{
				g_all.command = ft_strjoin("/", cmd);
				g_all.f_path = ft_strjoin(g_all.paths[g_all.j], g_all.command);
				free(g_all.command);
				if (open(g_all.full_path, O_RDONLY) != -1)
				{
					free_d_p(g_all.paths);
					return (g_all.full_path);
				}
				free(g_all.full_path);
			}
			free_d_p(g_all.paths);
		}
	}
	return (NULL);
}
