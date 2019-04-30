#ifndef NUM_TEXTEDIT_H_
#define NUM_TEXTEDIT_H_

typedef int16_t NUM_TEXEDIT_TD;
//#define NUM_TEXTEDIT_NUM_DIGITS 4 //[1024]
#define NUM_TEXTEDIT_CHARBUFF_MAXSIZE (4+1)//max. numero de digitos en todos las opc. + '\0'

void num_textedit_disp_set_x(int8_t x);
void num_textedit_disp_set_y(int8_t y);
int8_t num_textedit_disp_get_x(void);
int8_t num_textedit_disp_get_y(void);
void num_textedit_valuelimits_set_max(NUM_TEXEDIT_TD max);
void num_textedit_valuelimits_set_min(NUM_TEXEDIT_TD min);
int8_t num_textedit_set_value_as_char(NUM_TEXEDIT_TD value);
char*  num_textedit_get_value_as_char(void);
int8_t num_textedit_handler(int8_t action, char char_dig);
NUM_TEXEDIT_TD num_textedit_get_value_as_int(void);
NUM_TEXEDIT_TD num_textedit_valuelimits_get_max(void);
NUM_TEXEDIT_TD num_textedit_valuelimits_get_min(void);
int8_t num_textedit_right_justified(void);
void num_textedit_set_num_digits(int8_t num_digits);
//void num_textedit_set_idx_ascursor(int8_t idx_ascursor);//may be static to its source file
//
enum _num_textedit_action
{
    NUM_TEXTEDIT_ACTION_NONE = 0,
    NUM_TEXTEDIT_ACTION_BACKSPACE,
    NUM_TEXTEDIT_ACTION_WRITE,
};

#endif // NUM_TEXTEDIT_H_
