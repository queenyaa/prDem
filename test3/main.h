#ifndef MAIN_H
#define MAIN_H
 
#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
 
/* Flag Modifier Macros */
#define PLUS 1
#define SPACE 2
#define HASH 4
#define ZERO 8
#define NEG 16
#define PLUS_FLG (flgs & 1)
#define SPACE_FLG ((flgs >> 1) & 1)
#define HASH_FLG ((flgs >> 2) & 1)
#define ZERO_FLG ((flgs >> 3) & 1)
#define NEG_FLG ((flgs >> 4) & 1)
 
/* Length Modifier Macros */
#define SHORT 1
#define LONG 2
 
/**
 * struct buff_s - A new type defining a buffer struct.
 * @buffer: A pointer to a character array.
 * @start: A pointer to the start of buffer.
 * @len: The length of the string stored in buffer.
 */
typedef struct buff_s
{
char *buff;
char *st;
unsigned int len;
} buff_t;
 
/**
 * struct convert_s - A new type defining a converter struct.
 * @specifier: A character representing a conversion specifier.
 * @func: A pointer to a conversion function corresponding to specifier.
 */
typedef struct convert_s
{
unsigned char specifier;
unsigned int (*bf)(va_list, buff_t *,
unsigned char, int, int, unsigned char);
} convert_t;
 
/**
 * struct flg_s - A new type defining a flags struct.
 * @flag: A character representing a flag.
 * @value: The integer value of the flag.
 */
typedef struct flg_s
{
unsigned char flg;
unsigned char val;
} flg_t;
 
int _printf(const char *format, ...);
 
/* Conversion Specifier Functions */
unsigned int conv_c(va_list args, buff_t *out,
unsigned char flgs, int wth, int prec, unsigned char len);
unsigned int conv_s(va_list args, buff_t *out,
unsigned char flgs, int wth, int prec, unsigned char len);
unsigned int conv_di(va_list args, buff_t *out,
unsigned char flgs, int wth, int prec, unsigned char len);
unsigned int conv_percent(va_list args, buff_t *out,
unsigned char flgs, int wth, int prec, unsigned char len);
unsigned int conv_b(va_list args, buff_t *out,
unsigned char flgs, int wth, int prec, unsigned char len);
unsigned int conv_u(va_list args, buff_t *out,
unsigned char flgs, int wth, int prec, unsigned char len);
unsigned int conv_o(va_list args, buff_t *out,
unsigned char flgs, int wth, int prec, unsigned char len);
unsigned int conv_x(va_list args, buff_t *out,
unsigned char flgs, int wth, int prec, unsigned char len);
unsigned int conv_X(va_list args, buff_t *out,
unsigned char flgs, int wth, int prec, unsigned char len);
unsigned int conv_S(va_list args, buff_t *out,
unsigned char flgs, int wth, int prec, unsigned char len);
unsigned int conv_p(va_list args, buff_t *out,
unsigned char flgs, int wth, int prec, unsigned char len);
unsigned int conv_r(va_list args, buff_t *out,
unsigned char flgs, int wth, int prec, unsigned char len);
unsigned int conv_R(va_list args, buff_t *out,
unsigned char flgs, int wth, int prec, unsigned char len);
 
/* Handlers */
unsigned char h_flgs(const char *flgs, char *ind);
unsigned char h_length(const char *modifier, char *ind);
int h_wth(va_list args, const char *modifier, char *ind);
int h_p(va_list args, const char *modifier, char *ind);
unsigned int (*h_spec(const char *spec))(va_list, buff_t *,
unsigned char, int, int, unsigned char);
int _strlen(char *s);

/* Modifiers */
unsigned int pr_wth(buff_t *out, unsigned int printed,
unsigned char flgs, int wth);
unsigned int pr_str_wth(buff_t *out,
unsigned char flgs, int wth, int prec, int sz);
unsigned int pr_nwth(buff_t *out, unsigned int printed,
unsigned char flgs, int wth);
 
/* Helper Functions */
buff_t *init_buff(void);
void free_buff(buff_t *out);
unsigned int _memcpy(buff_t *out, const char *src, unsigned int n);
unsigned int conv_sbase(buff_t *out, long int num, char *base,
unsigned char flgs, int wth, int prec);
unsigned int conv_ubase(buff_t *out, unsigned long int num, char *base,
unsigned char flgs, int wth, int prec);
 
#endif /* MAIN_H */
