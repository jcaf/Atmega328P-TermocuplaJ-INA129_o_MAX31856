/*
hardware specific: can be an LCD, TFT, etc etc
*/
#include "../system.h"
#include "num_textedit_hwspecific.h"
#include "../lcdan/lcdan.h"
#include "../lcdan/lcdan_aux.h"
#include "../num/num_textedit.h"
#include "../ikey/ikey.h"
#include "../ikey/kb.h"

//


//int8_t
void kb_num_textedit_actionhandler(struct _kb_num_textedit_actionhandler *actionhandler)
{

    //int8_t cod_ret = 0;
    int8_t idx_ascursor=0;
    //
//    NUM_TEXEDIT_TD int_value;
//    NUM_TEXEDIT_TD valuelimits_max;
    //char str[NUM_TEXTEDIT_CHARBUFF_MAXSIZE];
    actionhandler->char_dig=0;
    actionhandler->new_action = NUM_TEXTEDIT_ACTION_NONE;

    if (kb_key_is_ready2read(KB_LYOUT_KEY_1))
    {
        //kb_key_was_read(KB_LYOUT_KEY_1);
        actionhandler->char_dig = '1';
        actionhandler->new_action = NUM_TEXTEDIT_ACTION_WRITE;
    }

    if (kb_key_is_ready2read(KB_LYOUT_KEY_2))
    {
        //kb_key_was_read(KB_LYOUT_KEY_2);

        actionhandler->char_dig = '2';
        actionhandler->new_action = NUM_TEXTEDIT_ACTION_WRITE;
    }
    if (kb_key_is_ready2read(KB_LYOUT_KEY_3))
    {
        //kb_key_was_read(KB_LYOUT_KEY_3);
        //
        actionhandler->char_dig = '3';
        actionhandler->new_action = NUM_TEXTEDIT_ACTION_WRITE;
    }
    if (kb_key_is_ready2read(KB_LYOUT_KEY_4))
    {
        //kb_key_was_read(KB_LYOUT_KEY_4);
        //
        actionhandler->char_dig = '4';
        actionhandler->new_action = NUM_TEXTEDIT_ACTION_WRITE;
    }
    if (kb_key_is_ready2read(KB_LYOUT_KEY_5))
    {
        //kb_key_was_read(KB_LYOUT_KEY_5);
        //
        actionhandler->char_dig = '5';
        actionhandler->new_action = NUM_TEXTEDIT_ACTION_WRITE;
    }
    if (kb_key_is_ready2read(KB_LYOUT_KEY_6))
    {
        //kb_key_was_read(KB_LYOUT_KEY_6);
        actionhandler->char_dig = '6';
        actionhandler->new_action = NUM_TEXTEDIT_ACTION_WRITE;
    }

    if (kb_key_is_ready2read(KB_LYOUT_KEY_7))
    {
        //kb_key_was_read(KB_LYOUT_KEY_7);

        actionhandler->char_dig = '7';
        actionhandler->new_action = NUM_TEXTEDIT_ACTION_WRITE;
    }
    if (kb_key_is_ready2read(KB_LYOUT_KEY_8))
    {
        //kb_key_was_read(KB_LYOUT_KEY_8);
        //
        actionhandler->char_dig = '8';
        actionhandler->new_action = NUM_TEXTEDIT_ACTION_WRITE;
    }
    if (kb_key_is_ready2read(KB_LYOUT_KEY_9))
    {
        //kb_key_was_read(KB_LYOUT_KEY_9);
        //
        actionhandler->char_dig = '9';
        actionhandler->new_action = NUM_TEXTEDIT_ACTION_WRITE;
    }
    if (kb_key_is_ready2read(KB_LYOUT_KEY_0))
    {
        //kb_key_was_read(KB_LYOUT_KEY_0);
        //
        actionhandler->char_dig = '0';
        actionhandler->new_action = NUM_TEXTEDIT_ACTION_WRITE;
    }

    if (kb_key_is_ready2read(KB_LYOUT_KEY_ENTER))
    {
        //kb_key_was_read(KB_LYOUT_KEY_ENTER);
        actionhandler->char_dig = 'E' ;

        //num_textedit_set_value_as_char check for limits, fix and apply right justified
        idx_ascursor = num_textedit_set_value_as_char(num_textedit_get_value_as_int());
        num_textedit_hwspecific_print_disp(idx_ascursor);
    }

    if (kb_key_is_ready2read(KB_LYOUT_KEY_CLEAR))
    {
        //kb_key_was_read(KB_LYOUT_KEY_CLEAR);
        //
        actionhandler->new_action = NUM_TEXTEDIT_ACTION_BACKSPACE;
    }
    //added:
//    if (kb_key_is_ready2read(KB_LYOUT_KEY_MENU))//cancela la edicion
//    {
//        //kb_key_was_read(KB_LYOUT_KEY_MENU);
//        //
//        cod_ret = 2;//cancela la ingresado, restaura el valor anterior
//    }
    //-------------------------------------------------------
    if (actionhandler->new_action > NUM_TEXTEDIT_ACTION_NONE)
    {
        idx_ascursor = num_textedit_handler(actionhandler->new_action, actionhandler->char_dig);
        num_textedit_hwspecific_print_disp(idx_ascursor);
    }

    //return cod_ret;
}


void num_textedit_hwspecific_print_disp(int8_t idx_ascursor)
{
    int8_t disp_x = num_textedit_disp_get_x();
    int8_t disp_y = num_textedit_disp_get_y();
    //
    lcdan_write_cmd(LCDAN_DISP_ON_CURSOR_OFF_BLINK_OFF);
    lcdan_set_cursor(disp_x, disp_y);
    lcdan_print_string(num_textedit_get_value_as_char() );
    lcdan_set_cursor(disp_x+idx_ascursor, disp_y);
    lcdan_write_cmd(LCDAN_DISP_ON_CURSOR_ON_BLINK_ON);
}


/*
/////////////////////////// MODO DE USO //////////////////////
#include "system.h"
#include "num/num_textedit.h"
#include "num/num_textedit_hwspecific.h"
#include "lcdan/lcdan.h"
#include "lcdan/lcdan_aux.h"
#include "ikey/ikey.h"
#include "ikey/kb.h"


void rtcc_set_time(void)
{
    int8_t idx_ascursor;

    lcdan_set_cursor_in_row0(0);
    lcdan_print_PSTRstring(PSTR("SET TIME [24 H]:"));
    //
    num_textedit_disp_set_x(0x0);
    num_textedit_disp_set_y(1);
    num_textedit_valuelimits_set_max(23);
    num_textedit_valuelimits_set_min(0);//por ahora num_textedit manejo enteros positivos
    num_textedit_set_num_digits(2);
    //
    idx_ascursor = num_textedit_set_value_as_char(0);
    num_textedit_hwspecific_print_disp(idx_ascursor);
}

int8_t rtcc_settime_num_textedit(void)
{
    int8_t cod_ret = 0;

    struct _kb_num_textedit_actionhandler actionhandler;

    kb_num_textedit_actionhandler(&actionhandler);//recoge la accion especifica

    if (actionhandler.char_dig == 'E')//Enter
    {
        cod_ret = 1;
    }
    if (kb_key_is_ready2read(KB_LYOUT_KEY_MENU))//cancela la edicion
    {
        //kb_key_was_read(KB_LYOUT_KEY_MENU);
        //
        cod_ret = 2;//cancela la ingresado, restaura el valor anterior
    }
    return cod_ret;
}

*/
