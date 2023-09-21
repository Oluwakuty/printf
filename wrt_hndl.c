#include "main.h"

/* WRITE HANDLE */
/**
 * handle_write_char - Prints a string
 * @d: char types.
 * @buffer: Buffer array to handle print
 * @banner:  Calculates active banner.
 * @span: get span.
 * @precise: Precise specifier
 * @mass: Mass specifier
 * Return: Number of chars printed.
 */

int handle_write_char(char d, char buffer[],
		int banner, int span, int precise, int mass)
{
	/* char is stored at left and paddind at buffer's right */
	int p = 0;
	char padded = ' ';

	UNUSED(precise);
	UNUSED(mass);

	if (banner & F_ZERO)
		padded = '0';
	buffer[p++] = d;
	buffer[p] = '\0';
	if (span > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (p = 0; p < span - 1; p++)
			buffer[BUFF_SIZE - p - 2] = padded;
		if (banner & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - p - 1], span - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - p - 1], span - 1) +
					write(1, &buffer[0], 1));
	}
	return (write(1, &buffer[0], 1));
}

/* WRITE NUMBER */
/**
 * write_number - Output a string
 * @is_negative: Lista of arguments
 * @indic: char types.
 * @buffer: Buffer array to handle print
 * @banner:  Calculates active banner
 * @span: get span.
 * @precise: Precise specifier
 * @mass: Mass specifier
 * Return: Number of chars printed.
 */

int write_number(int is_negative, int indic, char buffer[],
		int banner, int span, int precise, int mass)
{
	int lent = BUFF_SIZE - indic - 1;
	char padded = ' ', more_ch = 0;

	UNUSED(mass);

	if ((banner & F_ZERO) && !(banner & F_MINUS))
		padded = '0';
	if (is_negative)
		more_ch = '-';
	else if (banner & F_PLUS)
		more_ch = '+';
	else if (banner & F_SPACE)
		more_ch = ' ';
	return (write_num(indic, buffer, banner, span, precise,
				lent, padded, more_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @indic: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @banner: Banner
 * @span: Span
 * @prec: Precise specifier
 * @lent: Number lent
 * @padded: Pading char
 * @more_d: More char
 * Return: Number of printed chars.
 */

int write_num(int indic, char buffer[],
		int banner, int span, int prec,
		int lent, char padded, char more_d)
{
	int p, padded_start = 1;

	if (prec == 0 && indic == BUFF_SIZE - 2 && buffer[indic] == '0' && span == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && indic == BUFF_SIZE - 2 && buffer[indic] == '0')
		buffer[indic] = padded = ' '; /* span is displayed with padding ' ' */
	if (prec > 0 && prec < lent)
		padded = ' ';
	while (prec > lent)
		buffer[--indic] = '0', lent++;
	if (more_d != 0)
		lent++;
	if (span > lent)
	{
		for (p = 1; p < span - lent + 1; p++)
			buffer[p] = padded;
		buffer[p] = '\0';
		if (banner & F_MINUS && padded == ' ')/* Asign extra char to left of buffer */
		{
			if (more_d)
				buffer[--indic] = more_d;
			return (write(1, &buffer[indic], lent) + write(1, &buffer[1], p - 1));
		}
		else if (!(banner & F_MINUS) && padded == ' ')/* extra char to left of buff */
		{
			if (more_d)
				buffer[--indic] = more_d;
			return (write(1, &buffer[1], p - 1) + write(1, &buffer[indic], lent));
		}
		else if (!(banner & F_MINUS) && padded == '0')/* extra char to left of padd */
		{
			if (more_d)
				buffer[--padded_start] = more_d;
			return (write(1, &buffer[padded_start], p - padded_start) +
					write(1, &buffer[indic], lent - (1 - padded_start)));
		}
	}
	if (more_d)
		buffer[--indic] = more_d;
	return (write(1, &buffer[indic], lent));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @indic: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @banner: Banner specifiers
 * @span: Span specifier
 * @precise: Precise specifier
 * @mass: Mass specifier
 * Return: Number of written chars.
 */

int write_unsgnd(int is_negative, int indic,
		char buffer[],
		int banner, int span, int precise, int mass)
{
	/* The number is stored at the bufer's right and starts at position i */
	int lent = BUFF_SIZE - indic - 1, p = 0;
	char padded = ' ';

	UNUSED(is_negative);
	UNUSED(mass);

	if (precise == 0 && indic == BUFF_SIZE - 2 && buffer[indic] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */
	if (precise > 0 && precise < lent)
		padded = ' ';

	while (precise > lent)
	{
		buffer[--indic] = '0';
		lent++;
	}

	if ((banner & F_ZERO) && !(banner & F_MINUS))
		padded = '0';

	if (span > lent)
	{
		for (p = 0; p < span - lent; p++)
			buffer[p] = padded;
		buffer[p] = '\0';
		if (banner & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[indic], lent) + write(1, &buffer[0], p));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], p) + write(1, &buffer[indic], lent));
		}
	}
	return (write(1, &buffer[indic], lent));
}

/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @indic: Index at which the number starts in the buffer
 * @lent: Lent of number
 * @span: Span specifier
 * @banner: Banner specifier
 * @padded: Char representing the padding
 * @more_d: Char representing extra char
 * @padded_start: Index at which padding should start
 * Return: Number of written chars.
 */

int write_pointer(char buffer[], int indic, int lent,
		int span, int banner, char padded, char more_d, int padded_start)
{
	int p;

	if (span > lent)
	{
		for (p = 3; p < span - lent + 3; p++)
			buffer[p] = padded;
		buffer[p] = '\0';
		if (banner & F_MINUS && padded == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--indic] = 'x';
			buffer[--indic] = '0';
			if (more_d)
				buffer[--indic] = more_d;
			return (write(1, &buffer[indic], lent) + write(1, &buffer[3], p - 3));
		}
		else if (!(banner & F_MINUS) && padded == ' ')/* extra char to left of buffer */
		{
			buffer[--indic] = 'x';
			buffer[--indic] = '0';
			if (more_d)
				buffer[--indic] = more_d;
			return (write(1, &buffer[3], p - 3) + write(1, &buffer[indic], lent));
		}
		else if (!(banner & F_MINUS) && padded == '0')/* extra char to left of padd */
		{
			if (more_d)
				buffer[--padded_start] = more_d;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padded_start], p - padded_start) +
					write(1, &buffer[indic], lent - (1 - padded_start) - 2));
		}
	}
	buffer[--indic] = 'x';
	buffer[--indic] = '0';
	if (more_d)
		buffer[--indic] = more_d;
	return (write(1, &buffer[indic], BUFF_SIZE - indic - 1));
}
