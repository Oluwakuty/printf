#include "main.h"

/**
 * get_span - Calculates the span for printing
 * @format: Formatted string in which to print the arguments.
 * @p: List of arguments to be printed.
 * @my_list: list of arguments.
 * Return: span.
 */

int get_span(const char *format, int *p, va_list my_list)
{
	int curr_p;
	int span = 0;

	for (curr_p = *p + 1; format[curr_p] != '\0'; curr_p++)
	{
		if (is_digit(format[curr_p]))
		{
			span *= 10;
			span += format[curr_p] - '0';
		}
		else if (format[curr_p] == '*')
		{
			curr_p++;
			span = va_arg(my_list, int);
			break;
		}
		else
			break;
	}
	*p = curr_p - 1;
	return (span);
}
