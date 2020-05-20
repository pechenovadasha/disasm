/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_check_instr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxane <croxane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 16:22:04 by croxane           #+#    #+#             */
/*   Updated: 2020/05/19 12:11:41 by croxane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dis_asm.h"

char		*dec(int x)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = ft_strnew(8);
	while (i < 8)
	{
		new_str[i] = ((x >> (7 - i)) & 1) + '0';
		i++;
	}
	return (new_str);
}

void		make_instr_two(t_instr *instr, int fd, t_struct *data)
{
	char	buff[1];
	char	*str;

	if (instr->type->number == 1 || instr->type->number == 9
		|| instr->type->number == 12 || instr->type->number == 15)
		ft_arg_one_dir(fd, instr);
	else
	{
		read(fd, buff, 1);
		str = dec((int)buff[0]);
		ft_args_type(str, instr);
		free(str);
		ft_check_args(instr, fd);
	}
	write(data->fd_creat_file, instr->string, ft_strlen(instr->string));
	write(data->fd_creat_file, "\n", 1);
}

void		make_instr(t_struct *data, int fd, char buf)
{
	int		i;
	t_instr	instr;

	i = -1;
	ft_init(&instr);
	while (++i < 17)
	{
		if (type_tab[i].number == buf)
		{
			instr.type = &type_tab[i];
			i = 17;
			instr.string = ft_strdup(instr.type->name);
			instr.string = ft_strjoin_sp(&instr.string,
					ft_strdup(" "), ft_strlen(instr.string));
		}
	}
	make_instr_two(&instr, fd, data);
	free_string(&instr);
}

void		ft_reading(int fd, t_struct *data)
{
	char	buf[COMMENT_LENGTH];

	if (read(fd, buf, PROG_NAME_LENGTH) < 0)
		exit(0);
	data->name = ft_strdup(buf);
	data->name = ft_quotes(data->name);
	if (read(fd, buf, 8) < 0)
		exit(0);
	if (read(fd, buf, COMMENT_LENGTH) < 0)
		exit(0);
	data->comment = ft_strdup(buf);
	data->comment = ft_quotes(data->comment);
	if (read(fd, buf, 4) < 0)
		exit(0);
	ft_creat_file(data);
}

void		ft_opening(char *str, t_struct *data)
{
	int		fd;
	char	buf[4];

	if ((fd = open(str, O_RDONLY)) <= 0)
	{
		write(1, "ERROR of opening\n", 17);
		exit(0);
	}
	read(fd, buf, 4);
	if (buf[0] != 0 && buf[1] != -22 && buf[2] != -125 && buf[3] != -13)
	{
		write(1, "Wrong magic name\n", 17);
		exit(0);
	}
	ft_reading(fd, data);
	while (read(fd, buf, 1) > 0)
		make_instr(data, fd, buf[0]);
}
