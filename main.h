#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - Struct op
 * @fmt: The format.
 * @fn: The function associated.
 */
struct fmt
{
        char fmt;
        int (*fn)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct fmt fmt_t - Struct op
 *
 * @fmt: The format.
 * @fm_t: The function associated.
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int handle_print(const char *fmt, int *p,
va_list my_list, char buffer[], int banner, int span, int precise, int mass);

/* FUNCTIONS */
/* Funtions to print chars and strings */
int print_char(va_list kind, char buffer[],
int banner, int span, int precise, int mass);

int print_string(va_list kind, char buffer[],
int banner, int span, int precise, int mass);

int print_percent(va_list kind, char buffer[],
int banner, int span, int precise, int mass);

/* Functions to print numbers */
int print_int(va_list kind, char buffer[],
int banner, int span, int precise, int mass);

int print_binary(va_list kind, char buffer[],
int banner, int span, int precise, int mass);

int print_unsigned(va_list kind, char buffer[],
int banner, int span, int precise, int mass);

int print_octal(va_list kind, char buffer[],
int banner, int span, int precise, int mass);

int print_hexadecimal(va_list kind, char buffer[],
int banner, int span, int precise, int mass);

int print_hexa_upper(va_list kind, char buffer[],
int banner, int span, int precise, int mass);

int print_hexa(va_list kind, char map_to[],
char buffer[], int banner, char banner_ch, int span, int precise, int mass);


/* Function to print non printable characters */
int print_non_printable(va_list kind, char buffer[],
int banner, int span, int precise, int mass);

/* Funcion to print memory address */
int print_pointer(va_list kind, char buffer[],
int banner, int span, int precise, int mass);

/* Funciotns to handle other specifiers */
int get_banner(const char *format, int *p);
int get_span(const char *format, int *p, va_list my_list);
int get_precise(const char *format, int *p, va_list my_list);
int get_mass(const char *format, int *p);

/*Function to print string in reverse*/
int print_reverse(va_list kind, char buffer[],
int banner, int span, int precise, int mass);

/*Function to print a string in rot 13*/
int print_rot13string(va_list kind, char buffer[],
int banner, int span, int precise, int mass);

/* width handler */
int handle_write_char(char d, char buffer[],
int banner, int span, int precise, int mass);

int write_number(int is_positive, int indic, char buffer[],
int banner, int span, int precise, int mass);

int write_num(int indic, char bff[], int banner, int span, int precise,
int lengt, char padded, char more_d);

int write_pointer(char buffer[], int indic, int lent,
int span, int banner, char padded, char more_d, int padded_start);

int write_unsgnd(int is_negative, int indic,
char buffer[],
int banner, int span, int precise, int mass);

/* UTILS */
int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);
long int convert_size_number(long int mum, int mass);
long int convert_size_unsgnd(unsigned long int mum, int mass);

#endif /* MAIN_H */
