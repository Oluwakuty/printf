#include "main.h"

void print_buffer(char buffer[], int *buffed_indic);

/**
 * _printf - Printf projectfunction
 * @format: format.
 * Return: Always print characterss.
 */

int _printf(const char *format, ...);

int _printf(const char *format, ...)
{
	int p, linted = 0, linted_chars = 0;
	int banner, span, precise, mass, buffed_indic = 0;

	va_list my_list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(my_list, format);

	for (p= 0; format && format[p] != '\0'; p++)
	{
		if (format[p] != '%')
		{
			buffer[buffed_indic++] = format[p];
			if (buffed_indic == BUFF_SIZE)
				print_buffer(buffer, &buffed_indic);

			/* write(1, &format[p], 1);*/
			linted_chars++;
		}
		else
		{
			print_buffer(buffer, &buffed_indic);
			banner = get_banner(format, &p);
			span = get_span(format, &p, my_list);
			precise = get_precise(format, &p, my_list);
			mass = get_mass(format, &p);
			++p;
			linted = handle_print(format, &p, my_list, buffer,
					banner, span, precise, mass);
			if (linted == -1)
				return (-1);
			linted_chars += linted;
		}
	}
	print_buffer(buffer, &buffed_indic);
	va_end(my_list);
	return (linted_chars);
}

/**
 * print_buffer - To print the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buffed_indic: Index at which to add next char, represents the length.
 */

void print_buffer(char buffer[], int *buffed_indic)
{
	if (*buffed_indic > 0)
		write(1, &buffer[0], *buffed_indic);
	*buffed_indic = 0;
}
