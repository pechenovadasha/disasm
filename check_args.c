#include "dis_asm.h"

void	ft_args_type(char *str, t_instr *data)
{
	int i;
	int j;

	i = 0;
	j = -1;
	while(i < data->type->count_args * 2)
	{
		if (str[i] == '1' && str[i + 1] == '0')
			data->args[++j] = 1;//1 - dir
		else if (str[i] == '0' && str[i + 1] == '1')
			data->args[++j] = 2;//2-reg
		else if (str[i] == '1' && str[i + 1] == '1')
			data->args[++j] = 3;//3-ind
		i+=2;
	}
}

char	*invert(char *str, int i)
{
	char *new;
	int j;

	j = 0;
	new = ft_strnew(i);
	i--;
	while(i > -1)
	{
		int a = str[i];
		new[j] = str[i];
		j++;
		i--;
	}
	return(new);
}

void	ft_arg_dir(int fd, t_instr *data, int counter)
{
	char buf[T_DIR - counter + 1];
	char *value1;
	int *a;
	short *b;
	char *tmp;


	read(fd, buf, (T_DIR - counter));
	buf[T_DIR - counter] = 0;
	ft_strjoin_sp(&data->string, ft_strdup("%"), ft_strlen(data->string));
	tmp = invert(buf, T_DIR - counter);
	if (counter == 2) {

		b = (short *) tmp;
		value1 = ft_itoa((short) *b);
	}
	else
	{
		a = (int *) tmp;
		value1 = ft_itoa(*a);
	}
	ft_strjoin_sp(&data->string, value1, ft_strlen(data->string));
}



void	ft_arg_reg(int fd, t_instr *data)
{
	char buf[T_REG];
	char *value;

	read(fd, &buf, T_REG);
	value = ft_itoa(buf[0]);
	ft_strjoin_sp(&data->string, ft_strdup("r"), ft_strlen(data->string));
	ft_strjoin_sp(&data->string,  value, ft_strlen(data->string));
}

void	ft_arg_ind(int fd, t_instr *data)
{
	char buf[T_IND + 1];
	char *value1;
	int *a;
	char *tmp;

	read(fd, buf, T_IND);
	buf[T_IND] = 0;
	tmp = invert(buf, T_IND);
	a = (int *) tmp;
	value1 = ft_itoa((short)*a);
	ft_strjoin_sp(&data->string, value1, ft_strlen(data->string));
}

void	ft_arg_one_dir(int fd, t_instr *data)
{
	int counter;

	counter = 0;
	if (data->type->number == 9 || data->type->number == 10 || data->type->number == 11
		|| data->type->number == 13 || data->type->number == 14 || data->type->number == 15)
		counter = 2;
	ft_arg_dir(fd, data, counter);
}

void	ft_check_args(t_instr *data, int fd)
{
	int i;
	int counter;

	i = 0;
	counter = 0;
	while (i < data->type->count_args)
	{
		if(data->args[i] == 1 || data->args[i] == 0)
		{
			if (data->type->number == 9 || data->type->number == 10 || data->type->number == 11
			|| data->type->number == 13 || data->type->number == 14 || data->type->number == 15)
				counter = 2;
			ft_arg_dir(fd, data, counter);
		}
		else if(data->args[i] == 2)
			ft_arg_reg(fd, data);
		else if(data->args[i] == 3)
			ft_arg_ind(fd, data);
		if (i < data->type->count_args - 1)
			ft_strjoin_sp(&data->string, ft_strdup(","), ft_strlen(data->string));
		i++;
	}
}