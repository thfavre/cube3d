#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "libft.h"
#include "color.h"
#include "parsing.h"

bool	validate_line(char* line, char* expected_name);
bool	parse_rgb(char* rgb_string, int* colors);
void	free_split(char **split);

bool	parse_color(char* line, int* color, char* expected_name)
{
	char**	splited_line;
	int		colors[3];

	if (!validate_line(line, expected_name))
		return false;
	splited_line = ft_split(line, ' ');
	free(line);
	if (!parse_rgb(splited_line[1], colors))
		return false;
	*color = rgb(colors[0], colors[1], colors[2]);
	free_split(splited_line);
	return true;
}


bool	validate_line(char* line, char* expected_name)
{
	char**	splited_line;

	if (line == NULL)
		return false;
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	splited_line = ft_split(line, ' '); // free this when needed
	if (splited_line == NULL)
		return false;
	if (ft_strcmp(splited_line[0], expected_name) != 0) {
		printf("Error, expected '%s' but got '%s'\n", expected_name, splited_line[0]);
		return false;
	}
	if (splited_line[1] == NULL || splited_line[2] != NULL) {
		printf("Error, expected a color in this format: '%s R,G,B'\n", expected_name);
		return false;
	}
	free_split(splited_line);
	return true;
}

bool	parse_rgb(char* rgb_string, int* colors)
{
	char**	str_rgb;
	int		color;
	int		i;

	str_rgb = ft_split(rgb_string, ','); // free this when needed
	if (str_rgb == NULL || str_rgb[0] == NULL || str_rgb[1] == NULL || str_rgb[2] == NULL || str_rgb[3] != NULL)
	{
		printf("Error, expected a color in the format 'R,G,B'\n");
		return false;
	}
	i = -1;
	while (++i < 3)
	{
		if (!ft_is_str_digit(str_rgb[i]))
		{
			printf("Error, invalid color '%s', must be numeric\n", str_rgb[i]);
			return false;
		}
		color = ft_atoi(str_rgb[i]);
		if (color < 0 || color > 255)
		{
			printf("Error, invalid color '%s', must be between 0 and 255\n", str_rgb[i]);
			return false;
		}
		colors[i] = color;
	}
	free_split(str_rgb);
	return true;
}