#include "main.h"

/**
 * get_mass - Calculates the mass to cast the argument
 * @format: Formatted string in which to print the arguments
 * @p: List of arguments to be printed.
 * Return: Precise.
 */

int get_mass(const char *format, int *p)
{
	int curr_p = *p + 1;
	int mass = 0;

	if (format[curr_p] == 'l')
		mass = S_LONG;
	else if (format[curr_p] == 'h')
		mass = S_SHORT;

	if (mass == 0)
		*p = curr_p - 1;
	else
		*p = curr_p;
	return (mass);
}
