#include "main.h"

/**
 * get_precise - Calculates the precise for printing
 * @format: Formatted string in which to print the arguments
 * @p: List of arguments to be printed.
 * @my_list: list of arguments.
 * Return: Precise.
 */

int get_precise(const char *format, int *p, va_list my_list)
{
	int curr_p = *p + 1;
	int precise = -1;

	if (format[curr_p] != '.')
		return (precise);
	precise = 0;

	for (curr_p += 1; format[curr_p] != '\0'; curr_p++)
	{
		if (is_digit(format[curr_p]))
		{
			precise *= 10;
			precise += format[curr_p] - '0';
		}
		else if (format[curr_p] == '*')
		{
			curr_p++;
			precise = va_arg(my_list, int);
			break;
		}
		else
			break;
	}
	*p = curr_p - 1;
	return (precise);
}
