/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxane <croxane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 16:22:04 by croxane           #+#    #+#             */
/*   Updated: 2020/05/19 12:11:41 by croxane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dis_asm.h"

void	ft_creat_file(t_struct *data)
{
	data->fd_creat_file = open(data->file_name,
			O_WRONLY | O_TRUNC | O_CREAT, S_IREAD | S_IWRITE);
	if (data->fd_creat_file < 0)
	{
		write(1, "File not created\n", 17);
		exit(0);
	}
	write(data->fd_creat_file, NAME_CMD_STRING, 5);
	write(data->fd_creat_file, " ", 1);
	write(data->fd_creat_file, data->name, ft_strlen(data->name));
	write(data->fd_creat_file, "\n", 1);
	write(data->fd_creat_file, COMMENT_CMD_STRING, 8);
	write(data->fd_creat_file, " ", 1);
	write(data->fd_creat_file, data->comment, ft_strlen(data->comment));
	write(data->fd_creat_file, "\n\n", 2);
	free(data->name);
	data->name = 0;
	free(data->comment);
	data->comment = 0;
	free(data->file_name);
	data->file_name = 0;
}

char	*ft_strjoin_sp(char **str, char *buf, size_t len)
{
	char			*newstr;

	if (!(newstr = ft_strnew(len + ft_strlen(buf) + 1)))
		return (NULL);
	ft_strcpy(newstr, *str);
	ft_strcat(newstr, buf);
	ft_strdel(str);
	*str = ft_strdup(newstr);
	ft_strdel(&newstr);
	free(buf);
	return (*str);
}
