/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahiri <atahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:39:46 by atahiri           #+#    #+#             */
/*   Updated: 2021/07/05 15:31:49 by atahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**collect_paths(char **envp)
{
	char	*sub_path;
	char	**paths;
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			sub_path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			paths = ft_split(sub_path, ':');
			free(sub_path);
		}
	}
	return (paths);
}

char	*get_path(char **envp, char *cmd)
{
	char	**paths;
	char	*command;
	char	*full_path;
	int		j;

	j = -1;
	if (ft_strchr(cmd, '/'))
		return (cmd);
	paths = collect_paths(envp);
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
	return (NULL);
}
