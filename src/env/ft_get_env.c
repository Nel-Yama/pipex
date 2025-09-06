/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nel-yama@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:26:17 by nel-yama          #+#    #+#             */
/*   Updated: 2025/08/27 19:26:17 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*ft_get_env(const char *var, char **envp)
{
	int		i;
	size_t	var_len;

	if (!envp || !envp[0])
		return (NULL);
	var_len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(var, envp[i], var_len) && envp[i][var_len] == '=')
			return (envp[i] + var_len + 1);
		i++;
	}
	return (NULL);
}
