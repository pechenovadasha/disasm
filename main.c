#include "dis_asm.h"
#include "libft/libft.h"

t_type type_tab[17] =
		{
		{"live",  1, {T_DIR},                                               1},
		{"ld",    2, {T_DIR | T_IND,         T_REG},                        2},
		{"st",    2, {T_REG, T_IND | T_REG},                                3},
		{"add",   3, {T_REG, T_REG, T_REG},                                 4},
		{"sub",   3, {T_REG, T_REG, T_REG},                                 5},
		{"and",   3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6},
		{"or",    3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7},
		{"xor",   3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8},
		{"zjmp",  1, {T_DIR},                                               9},
		{"ldi",   3, {T_REG | T_DIR | T_IND, T_DIR | T_REG,         T_REG}, 10},
		{"sti",   3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},         11},
		{"fork",  1, {T_DIR},                                               12},
		{"lld",   2, {T_DIR | T_IND,         T_REG},                        13},
		{"lldi",  3, {T_REG | T_DIR | T_IND, T_DIR | T_REG,         T_REG}, 14},
		{"lfork", 1, {T_DIR},                                               15},
		{"aff",   1, {T_REG},                                               16},
		{0,       0, {0},                                                   0}
		}; //Эту хуйню надо будет сунуть обязательно куда нибудь, чтобы по ней определять тип инструкции


char	*ft_my_strcpy(const char *str1, char *str2)
{
	while (*str1 == 0)
		str1++;
	while ((*str1 != 0) && (*str1 != '\0'))
	{
		*str2 = *str1;
		str1++;
		str2++;
	}
	*str2 = '\0';
	return(str2);
}

//char *dec(int num)
{
//	char *str;
//	int bin = 0;
//	int k = 1;
//
//	while (num)
//	{
//		bin += (num % 2) * k;
//		k *= 10;
//		num /= 2;
//	}
//	str = ft_itoa(bin);
//	return (str);


//}

char	*dec(int x)
{
	int	i;

	i = 0;
	new_str = ft_strnew(8);
	while (i < 8)
	{
		new_str[i] = ((x >> (7 - i)) & 1) + '0';
		i++;
	}
	return new_str;
}


char *zero(char *str)
{
	int i;
	char *src;

	i = 0;
	while(str[i])
		i++;
	if (i != 8)
	{
		src = (char *) malloc(sizeof(char) * 8);
		src[0] = '0';
		i = 0;
		while(str[i])
		{
			src[i + 1] = str[i];
			i++;
		}
		return(src);
	}
	return(str);
}

//char  *ft_size_args(int fd, t_instr *data)
//{
//	char buf[2];
//	char *value;
//	char *tmp;
//	int *a;
//
//	read(fd, buf, 1);
////	tmp = invert(buf, 1);
//	a = (int *)&buf[0];
//	value = ft_itoa(*a);
//	return(value);
//}

void make_instr(t_struct *data, int fd, char buf)
{
	int i;
	char buff[1];
	char *str;
	t_instr instr;

	i = -1;
	ft_init(&instr);
	while (++i < 17)
	{
		if (type_tab[i].number == buf) {
			instr.type = &type_tab[i];
			i = 17;
			instr.string = ft_strdup(instr.type->name);
			instr.string = ft_strjoin_sp(&instr.string, ft_strdup(" "), ft_strlen(instr.string));
		}
	}
	if (instr.type->number == 1 || instr.type->number == 9 || instr.type->number == 12
			|| instr.type->number == 15)
		ft_arg_one_dir(fd, &instr);
	else
		{
			read(fd, buff, 1);
//			ft_size_args(fd, &instr);
			str = dec((int) buff[0]);
			str = zero(str);
			ft_args_type(str, &instr);
			free(str);
			ft_check_args(&instr, fd);
		}
	write(data->fd_creat_file, instr.string, ft_strlen(instr.string));
	write(data->fd_creat_file, "\n", 1);
	free_string(&instr);

}

char	*ft_quotes(char *str)
{
	int i;
	char *new;

	new = (char *)malloc(sizeof(char) * ft_strlen(str) + 2);
	i = 0;
	new[0] = 34;
	while(str[i])
	{
		new[i + 1] = str[i];
		i++;
	}
	new[i + 1] = 34;
	return(new);
}

void ft_opening(char *str, t_struct *data)
{
	int fd;
	char	buf[2048];

	if ((fd = open(str,  O_RDONLY)) <= 0)
	{
		write(1, "ERROR of opening\n", 17);
		exit(0);
	}
	read(fd, buf, 4);
	if (buf[0] != 0 && buf[1] != -22 && buf[2] != -125 && buf[3] != -13)
	{
		write (1, "Wrong magic name\n", 17);
		exit(0);
	}
	read(fd, buf, 128);
	data->name = ft_strdup(buf);
	data->name = ft_quotes(data->name);
	read(fd, buf, 8);
	read(fd, buf, 2048);
	data->comment = ft_strdup(buf);
	data->comment = ft_quotes(data->comment);
	read(fd, buf, 4);
	data->code = NULL;
	ft_creat_file(data);
	while (read(fd , buf, 1) > 0){
		make_instr(data, fd, buf[0]);//будет добавлять в список новую инструкцию, список надо определить выше
	}
//	write_to_file(data);//собираешь строки из полученных данных и просто записываешь по порядку, как пойдешь по списку

}

char	*file_name(char *str)
{
	int i;
	int j;
	char *name;

	i = ft_strlen(str);
	j = i;
	while (str[i] != '/')
		i--;
	i++;
	name = (char *)malloc(sizeof(char) * (j - i - 2));
	j = 0;
	while (str[i] != '.')
	{
		name[j] = str[i];
		j++;
		i++;
	}
	name = ft_strjoin_sp(&name, ft_strdup(".s"), ft_strlen(name));
	return(name);
}

int main(int argc, char **argv) {

	t_struct data;
	if (argc != 2)
	{
		write(1, "Usage: <dis_asm> <player.cor>\n", 30);
		return(0);
	}
	data.file_name = file_name(argv[1]);
	ft_opening(argv[1], &data);
	return 0;
}