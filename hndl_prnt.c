#include "main.h"

/**
 * handle_print - Output an argument based on its type
 * @fmt: Formatted string in which to print the arguments.
 * @my_list: List of arguments to be printed.
 * @indic: indic.
 * @buffer: Buffer array to handle print.
 * @banner: Calculates active flags
 * @span: get span.
 * @precise: Precise specification
 * @mass: Mass specifier
 * Return: 1 or 2;
 */

int handle_print(const char *fmt, int *indic, va_list my_list, char buffer[],
		int banner, int span, int precise, int mass)
{
	int p, unknow_len = 0, linted_chars = -1;

	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (p = 0; fmt_types[p].fmt != '\0'; p++)
		if (fmt[*indic] == fmt_types[p].fmt)
			return (fmt_types[p].fn(my_list, buffer, banner, span, precise, mass));
	if (fmt_types[p].fmt == '\0')
	{
		if (fmt[*indic] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*indic - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (span)
		{
			--(*indic);
			while (fmt[*indic] != ' ' && fmt[*indic] != '%')
				--(*indic);
			if (fmt[*indic] == ' ')
				--(*indic);
			return (1);
		}
		unknow_len += write(1, &fmt[*indic], 1);
		return (unknow_len);
	}
	return (linted_chars);
}
