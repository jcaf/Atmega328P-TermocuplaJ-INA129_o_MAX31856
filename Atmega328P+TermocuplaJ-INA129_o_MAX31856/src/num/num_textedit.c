#include "../system.h"
#include "num_textedit.h"
#include <string.h>
#include "../str/str.h"
struct _num_textedit
{
    //NUM_TEXEDIT_TD value_asint;
    char value_ascharbuff[NUM_TEXTEDIT_CHARBUFF_MAXSIZE];
    int8_t idx_ascursor;

    struct _num_textedit_valuelimits
    {
        NUM_TEXEDIT_TD max;
        NUM_TEXEDIT_TD min;

    } valuelimits;

    struct _num_textedit_disp
    {
        int8_t x;
        int8_t y;
    } disp;

    int8_t NUM_TEXTEDIT_NUM_DIGITS;
};

struct _num_textedit num_textedit;

void num_textedit_set_num_digits(int8_t num_digits)
{
    num_textedit.NUM_TEXTEDIT_NUM_DIGITS = num_digits;
}

void num_textedit_disp_set_x(int8_t x)
{
    num_textedit.disp.x = x;
}
void num_textedit_disp_set_y(int8_t y)
{
    num_textedit.disp.y = y;
}
int8_t num_textedit_disp_get_x(void)
{
    return num_textedit.disp.x;
}
int8_t num_textedit_disp_get_y(void)
{
    return num_textedit.disp.y;
}

void num_textedit_valuelimits_set_max(NUM_TEXEDIT_TD max)
{
    num_textedit.valuelimits.max = max;
}
void num_textedit_valuelimits_set_min(NUM_TEXEDIT_TD min)
{
    num_textedit.valuelimits.min = min;
}
NUM_TEXEDIT_TD num_textedit_valuelimits_get_max( void )
{
    return num_textedit.valuelimits.max;
}
NUM_TEXEDIT_TD num_textedit_valuelimits_get_min(void)
{
    return num_textedit.valuelimits.min;
}
/*
void num_textedit_verify_and_trunc_to_max_val(void)
{
    int8_t idx_ascursor=0;
    //
    NUM_TEXEDIT_TD int_value;
    NUM_TEXEDIT_TD valuelimits_max;

    int_value = num_textedit_get_value_as_int();
    valuelimits_max = num_textedit_valuelimits_get_max();
    if (int_value > valuelimits_max)
    {
        idx_ascursor = num_textedit_set_value_as_char(valuelimits_max);
    }
    else //ok... todo bien
    {
        idx_ascursor = num_textedit_right_justified();
        //cod_ret = 1;
    }
    num_textedit_hwspecific_print_disp(idx_ascursor);
}
*/
//static
//void num_textedit_set_idx_ascursor(int8_t idx_ascursor)
//{
//    num_textedit.idx_ascursor = idx_ascursor;
//}

/*
return idx_ascursor
*/
char*  num_textedit_get_value_as_char(void)
{
    return num_textedit.value_ascharbuff;
}
NUM_TEXEDIT_TD num_textedit_get_value_as_int(void)
{
//    int8_t i = NUM_TEXTEDIT_NUM_DIGITS;
//    do
//    {
//        if (num_textedit.value_ascharbuff)
//        --i;
//    }while (i>0)
//
    return (NUM_TEXEDIT_TD)atoi(num_textedit.value_ascharbuff);
    //return (NUM_TEXEDIT_TD)strtol(num_textedit.value_ascharbuff, (char**)NULL, 10);
}
/*
This funct. is Right-justified
*/
int8_t num_textedit_set_value_as_char(NUM_TEXEDIT_TD value)
{
    uint8_t len;
    char buff[15];
    int8_t idx_ascursor;

    if (value > num_textedit.valuelimits.max)
        value = num_textedit.valuelimits.max;
    else if (value < num_textedit.valuelimits.min)
        value = num_textedit.valuelimits.min;

    itoa(value, buff, 10);

    len = strlen(buff);
    if (len >= num_textedit.NUM_TEXTEDIT_NUM_DIGITS)
    {
        len = num_textedit.NUM_TEXTEDIT_NUM_DIGITS;
        buff[len] = '\0';
    }
    strcpy(num_textedit.value_ascharbuff, buff);
    idx_ascursor = num_textedit_right_justified();//Right-justified
//    num_textedit.idx_ascursor = len;

    return idx_ascursor;
}

int8_t num_textedit_handler(int8_t action, char char_dig)
{
    int8_t i;

    switch (action)
    {
        case NUM_TEXTEDIT_ACTION_BACKSPACE:

            if (--num_textedit.idx_ascursor < 0)
            {
                num_textedit.idx_ascursor = 0;
            }

            num_textedit.value_ascharbuff[num_textedit.idx_ascursor] = ' ';

            break;
        case NUM_TEXTEDIT_ACTION_WRITE:

            if (num_textedit.idx_ascursor  < num_textedit.NUM_TEXTEDIT_NUM_DIGITS)
            {
                for (i=num_textedit.NUM_TEXTEDIT_NUM_DIGITS-1; i > num_textedit.idx_ascursor; i--)
                {
                    num_textedit.value_ascharbuff[i] = num_textedit.value_ascharbuff[i-1];
                }
                num_textedit.value_ascharbuff[num_textedit.idx_ascursor] = char_dig;
                num_textedit.idx_ascursor++;
            }

            break;
    }

    //check limits
    if (num_textedit.idx_ascursor < 0)
    {
        num_textedit.idx_ascursor = 0;
    }
    else if (num_textedit.idx_ascursor > (num_textedit.NUM_TEXTEDIT_NUM_DIGITS) )
    {
        num_textedit.idx_ascursor = num_textedit.NUM_TEXTEDIT_NUM_DIGITS;
    }
    return num_textedit.idx_ascursor;
}

int8_t num_textedit_right_justified(void)
{
    str_right_justified(num_textedit.value_ascharbuff, num_textedit.NUM_TEXTEDIT_NUM_DIGITS);
    num_textedit.idx_ascursor = num_textedit.NUM_TEXTEDIT_NUM_DIGITS;
    return num_textedit.idx_ascursor;
}
//str manipulation...
