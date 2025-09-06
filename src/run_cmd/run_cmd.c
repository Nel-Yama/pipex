/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nel-yama@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:03:45 by nel-yama          #+#    #+#             */
/*   Updated: 2025/08/27 19:03:45 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	*create_cmd_path(char *path_dir, char *cmd)
{
	char	*exec_path;
	char	*tmp;

	if (!path_dir || !cmd)
		return (NULL);
	tmp = ft_strjoin(path_dir, "/");
	if (!tmp)
		return (NULL);
	exec_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (exec_path);
}

static char	*check_cmd(char *cmd, char *path_var)
{
	char	**path_dirs;
	char	*executable_path;
	int		dir_index;

	path_dirs = ft_split(path_var, ':');
	if (!path_dirs)
		return (NULL);
	dir_index = 0;
	while (path_dirs[dir_index])
	{
		executable_path = create_cmd_path(path_dirs[dir_index], cmd);
		if (!executable_path)
			return (free_split(path_dirs), NULL);
		if (access(executable_path, X_OK) == 0)
			return (free_split(path_dirs), executable_path);
		free(executable_path);
		dir_index++;
	}
	return (free_split(path_dirs), NULL);
}

static int	pre_exec(char **cmd, char **envp)
{
	char	*path_var;
	char	*executable_path;

	if (access(*cmd, X_OK) == 0)
		return (1);
	path_var = ft_get_env("PATH", envp);
	if (!path_var)
		return (0);
	executable_path = check_cmd(*cmd, path_var);
	if (!executable_path)
		return (0);
	free(*cmd);
	*cmd = ft_strdup(executable_path);
	if (!cmd[0])
		return (0);
	return (1);
}

int	run_cmd(t_arg *arg, char *cmd, char **envp)
{
	char	**split_cmd;

	split_cmd = ft_split_smart(cmd, " \t");
	if (!pre_exec(&split_cmd[0], envp))
	{
		print_custom_error(2, "pipex: Command not found: ", split_cmd[0]);
		free_split(split_cmd);
		arg->exit_code = 127;
		return (0);
	}
	if (execve(split_cmd[0], split_cmd, envp) == -1)
	{
		if (errno == EACCES || errno == EISDIR)
			arg->exit_code = 126;
		else
			arg->exit_code = 1;
	}
	free_split(split_cmd);
	return (errno);
}
