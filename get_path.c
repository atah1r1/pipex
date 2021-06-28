/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahiri <atahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:39:46 by atahiri           #+#    #+#             */
/*   Updated: 2021/06/28 21:58:02 by atahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **envp, char *cmd)
{
	char	**paths;
	char	*command;
	char	*full_path;
	char	*sub_path;
	int		i;
	int		j;

	i = -1;
	while (envp[++i])
	{
		j = -1;
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			sub_path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			paths = ft_split(sub_path, ':');
			free(sub_path);
			while (paths[++j])
			{
				command = ft_strjoin("/", cmd);
				full_path = ft_strjoin(paths[j], command);
				free(command);
				if (open(full_path, O_RDONLY) != -1)
				{
					free_d_p(paths);
					return (full_path);
				}
				free(full_path);
			}
			free_d_p(paths);
		}
	}
	return (NULL);
}
