#include "../system.h"
#include "str.h"

/*
str_int[] deberia ser minimo del tamano [num_digs+1]; siempre en el ultimo byte
se almacena el null-termiated '\0'

Justify to right an integer-as-string, begining with the first "num_digs"
*/
void str_right_justified(char *str_int, uint8_t num_digs)
{
    char buff[STR_BUFF_MAXSIZE];
    int8_t len;
    int8_t idx;
    int int_val;
    //
    int_val = atoi(str_int);//TRIM ALL SPACE.. for now I use atoi()
    itoa(int_val, buff, 10);//buff se convierte con '\0' terminated
    len = strlen(buff);
    //
    idx = num_digs-len;

    //strncpy(&str_int[idx], buff , len);
    strcpy(&str_int[idx], buff);
    while (--idx>=0)
        {str_int[idx] = ' ';}
}
