#include <stdio.h>



typedef struct s_vbs
{
	int				i;
	int				pos;
	int				ini;
	int				size;
	char			**palabra;
}					t_vbs;

#include <stdlib.h>

// int	num_words(char const *s, char c)
// {
// 	int	num;
// 	int	i;

// 	num = 0;
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != c)
// 		{
// 			num++;
// 			while (s[i] != c && s[i + 1])
// 				i++;
// 		}
// 		else
// 			return (2);
// 		i++;
// 	}
// 	return (num);
// }

// static char	*fill_word(char *palabra, char *s, int ini, int pos)
// {
// 	int	j;

// 	j = 0;
// 	while (ini < pos)
// 	{
// 		palabra[j] = s[ini];
// 		j++;
// 		ini++;
// 	}
// 	palabra[j] = '\0';
// 	return (palabra);
// }

// static int	find_pos(char *palabra, char c, int *size, int *ini)
// {
// 	int	i;

// 	i = *ini + *size;
// 	*size = 0;
// 	if (palabra[i] && palabra[i] == c)
// 		(i)++;
// 	*ini = i;
// 	while (palabra[i] != c && palabra[i])
// 	{
// 		(*size)++;
// 		i++;
// 	}
// 	return (i);
// }

// static void	ft_free(char **s)
// {
// 	int	i;

// 	i = 0;
// 	while (*(s + i))
// 	{
// 		free(*(s + i));
// 		i++;
// 	}
// 	free(s);
// }

// char	**ft_split(char const *s, char c)
// {
// 	t_vbs	a;

// 	a.i = 0;
// 	a.size = 0;
// 	a.ini = 0;
// 	a.palabra = (char **)malloc((num_words(s, c) + 1) * sizeof(char *));
// 	if (!a.palabra)
// 		return (NULL);
// 	while (a.i < num_words(s, c))
// 	{
// 		a.pos = find_pos((char *)s, c, &a.size, &a.ini);
// 		a.palabra[a.i] = (char *)malloc((a.size + 1) * sizeof(char));
// 		if (!a.palabra[a.i])
// 		{
// 			ft_free(a.palabra);
// 			return (NULL);
// 		}
// 		a.palabra[a.i] = fill_word(a.palabra[a.i], (char *)s, a.ini, a.pos);
// 		a.i++;
// 	}
// 	a.palabra[a.i] = NULL;
// 	return (a.palabra);
// }


#include <stdio.h>
#include <stdlib.h>

char	*fill_word(char *palabra, const char *s, int ini, int pos)
{
	int	j;

	j = 0;
	while (ini < pos)
	{
		palabra[j] = s[ini];
		j++;
		ini++;
	}
	palabra[j] = '\0';
	return (palabra);
}

int	find_first_delimiter(const char *s, char c)
{
	int pos = 0;

	while (s[pos] && s[pos] != c)
		pos++;
	return (pos);
}

void	free_memory(char **palabra, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		free(palabra[i]);
		i++;
	}
	free(palabra);
}

char	**allocate_and_fill(const char *s, int pos, int len)
{
	char **palabra;

	palabra = (char **)malloc(3 * sizeof(char *));
	if (!palabra)
		return (NULL);
	palabra[0] = (char *)malloc((pos + 1) * sizeof(char));
	if (!palabra[0])
		return (free_memory(palabra, 0), NULL);
	palabra[1] = (char *)malloc((len - pos) * sizeof(char));
	if (!palabra[1])
		return (free_memory(palabra, 1), NULL);
	fill_word(palabra[0], s, 0, pos);
	fill_word(palabra[1], s, pos + 1, len);
	palabra[2] = NULL;
	return (palabra);
}

char	**ft_split(const char *s, char c)
{
	int pos;
	int len;

	len = 0;
	while (s[len])
		len++;
	pos = find_first_delimiter(s, c);
	if (pos >= len) {
		return NULL;
	}
	return (allocate_and_fill(s, pos, len));
}

int main ()
{
	const char *a = "a===";
	char **split;
	split = ft_split(a, '=');
	if (split != NULL) {
		printf("Primera palabra: '%s'\nSegunda palabra: '%s'\n", split[0], split[1]);
		free_memory(split, 2);
	} else {
		printf("No se encontró el delimitador o hubo un error.\n");
	}
	return (0);
}
