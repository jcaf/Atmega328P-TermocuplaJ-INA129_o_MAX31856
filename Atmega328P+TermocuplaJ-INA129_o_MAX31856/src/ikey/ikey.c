#include "../system.h"
#include "ikey.h"

//scan hardware
#define KB_KEY_PINLEVEL_PRESSED 0
#define KB_KEY_PINLEVEL_RELEASED 1


#define KB_KEY_SCAN_COUNT_DEBOUNCE 4

//set software
#define KB_KEY_STATE_PRESSED 1
#define KB_KEY_STATE_RELEASED 0


#define KBAPP_READY2READ	1
#define KBAPP_ALREADYREAD	0


#define ms 0.001
#define _SYS_TIMMER_X_KEYBOARD_		(5*ms)

#define _FIRE_AT_TIME_THRESHOLD_ ((1000*ms)/(_SYS_TIMMER_X_KEYBOARD_))
#define KB_BEFORE_THR	(0)
#define KB_AFTER_THR	(1)

void ikey_scan(void)
{
    int8_t k = KB_NUM_KEYS-1;

    do
    {
        if (key[k].sm0 == 0)
        {
            if (key[k].keyRead() == KB_KEY_PINLEVEL_PRESSED)
            {
                key[k].sm0++;
            }
        }
        else if (key[k].sm0 == 1)
        {
            if (++key[k].counter0 == KB_KEY_SCAN_COUNT_DEBOUNCE)
            {
                key[k].counter0 = 0x00;

                if (key[k].keyRead() != KB_KEY_PINLEVEL_PRESSED)
                {
                    key[k].sm0--;
                }
                else
                {
                    key[k].bf.state = KB_KEY_STATE_PRESSED;
                    key[k].sm0++;
                }
            }
        }
        else if (key[k].sm0 == 2)
        {
            if (key[k].keyRead() == KB_KEY_PINLEVEL_RELEASED)
                key[k].sm0++;
        }
        else if (key[k].sm0 == 3)
        {
            if (++key[k].counter0 == KB_KEY_SCAN_COUNT_DEBOUNCE)
            {
                key[k].counter0 = 0x00;

                if (key[k].keyRead() != KB_KEY_PINLEVEL_RELEASED)
                {
                    key[k].sm0--;
                }
                else
                {
                    key[k].bf.state = KB_KEY_STATE_RELEASED;
                    key[k].sm0 = 0x00;
                }
            }
        }
    }while (--k >= 0);
}

///////////////////////////////////////////////////////////////////////////
#define NO_GROUP_X 0
//#define AGRUPED 1
#define GROUP_LOCKED		1
#define GROUP_UNLOCKED	0

uint8_t group_x[KB_NUM_KEYS];

static uint8_t key_is_accessible(uint8_t k)
{
    if (key[k].num_group_x != NO_GROUP_X)	//esta agrupado ?
    {
        //aqui fue puesto al presionar la tecla
        if (group_x[key[k].num_group_x] == GROUP_LOCKED)
        {
            //a todos sus companeros se les prohibe el ingreso, solo quien fue el primero en ganar el acceso al grupo entra
            if ( !key[k].bf.OwnerOfGroup)	//Si no es quien gano la propiedad...
            {
                return 0;
            }
        }
    }
    return 1;
}

///////////////////////////////////////////////////////////////////////////
#define _STAGE_START_PARSING_			(0)
#define _STAGE_ISKEY_RELEASED_			(1)
#define _STAGE_ISKEY_READFROMAPP_		(2)
#define _STAGE_FIREATIMEEXPIRED_		(3)
#define _STAGE_PRESSEDANDKEYRELEASE_	(4)

//Reptt deben ser contiguos!
#define _STAGE_REPTT_					(5)
#define _STAGE_REPTT_1_					(6)
#define _STAGE_REPTT_2_					(7)
//
#define _STAGE_END_PARSING_				(8)

void ikey_parsing(void)
{
    uint8_t k;

    for (k=0; k < KB_NUM_KEYS; k++)
    {
        if ( key[k].sm1 == _STAGE_START_PARSING_ )
        {
            if ( key_is_accessible(k) )
            {
                if (key[k].bf.state == KB_KEY_STATE_PRESSED)
                {
                    //........................................................
                    if (key[k].bf.OnKeyPressed)
                    {
                        key[k].bf.ReadyToRead = KBAPP_READY2READ;	//Populate Key to app.

                        if (key[k].bf.Reptt)
                        {
                            key[k].sm1 = _STAGE_REPTT_;
                        }
                        else
                        {
                            key[k].sm1 = _STAGE_ISKEY_RELEASED_;
                        }
                    }
                    else if ( key[k].bf.OnKeyPressedAndKeyRelease)
                    {
                        key[k].sm1 = _STAGE_PRESSEDANDKEYRELEASE_;
                    }

                    else if (key[k].bf.AtTimeExpired)
                    {
                        key[k].sm1 = _STAGE_FIREATIMEEXPIRED_;
                    }

                    //Add++
                    key[k].bf.InProcessing = 1;
                    //++

                    //........................................................

                    if (key[k].num_group_x != NO_GROUP_X)
                    {
                        group_x[ key[k].num_group_x ] = GROUP_LOCKED;
                        key[k].bf.OwnerOfGroup = 1;
                    }
                    //........................................................
                }
            }
        }

        //_________________________________________________________________________________________
        //comprueba entre las pasadas de repeticion/no repeticion si se ha soltado la tecla
        if ( (key[k].sm1 >= _STAGE_REPTT_ ) && (key[k].sm1 <= _STAGE_REPTT_2_))
        {
            if (key[k].bf.state == KB_KEY_STATE_RELEASED)			//ya solto?
            {
                key[k].counter1 = 0;				//stop timmer
                key[k].sm1 = _STAGE_ISKEY_READFROMAPP_;
            }
        }
        //.............................................................................
        if (key[k].sm1 == _STAGE_REPTT_ )
        {
            if ( ++key[k].counter1 >= key[k].repp.to_start)
            {
                key[k].counter1 =0;
                key[k].sm1 = _STAGE_REPTT_1_;
            }
        }
        if (key[k].sm1 == _STAGE_REPTT_1_)	//ping-pong between 1<->2
        {
            if (key[k].bf.ReadyToRead == KBAPP_ALREADYREAD)			//ya leyo?
            {
                key[k].bf.ReadyToRead = KBAPP_READY2READ;				//Repopulate again
                key[k].sm1 = _STAGE_REPTT_2_;
            }
        }
        if (key[k].sm1 == _STAGE_REPTT_2_)	//ping-pong 2<->1
        {
            if ( ++key[k].counter1 >= key[k].repp.after_start)
            {
                key[k].counter1 = 0;
                key[k].sm1 = _STAGE_REPTT_1_;
            }
        }
        //_________________________________________________________________________________________
        if (key[k].sm1 == _STAGE_PRESSEDANDKEYRELEASE_ )
        {
            if (key[k].bf.state == KB_KEY_STATE_RELEASED)	//ya solto?
            {
                key[k].bf.ReadyToRead = KBAPP_READY2READ;							//Populate Key to app.
                key[k].sm1 = _STAGE_ISKEY_READFROMAPP_;		//esperar x leer
            }
        }
        //_________________________________________________________________________________________
        if (key[k].sm1 == _STAGE_FIREATIMEEXPIRED_ )
        {
            key[k].counter1++;

            if (key[k].bf.state == KB_KEY_STATE_RELEASED)	//ya solto?
            {
                if (key[k].counter1 <= (_FIRE_AT_TIME_THRESHOLD_) )	//USANDO UN SOLO CONTADOR,
                {
                    key[k].counter1	= 0;							//PUES SE USA EN TIEMPOS DIFERENTES

                    key[k].bf.ReadyToRead = KBAPP_READY2READ;
                    key[k].bf.AtTimeExpired_BeforeOrAfter = KB_BEFORE_THR;

                    key[k].sm1 = _STAGE_ISKEY_READFROMAPP_;		//Go directly to wait for read key from high-level application
                }
            }

            if (key[k].counter1 > (_FIRE_AT_TIME_THRESHOLD_) )
            {
                key[k].counter1 = 0x0000;

                key[k].bf.ReadyToRead = KBAPP_READY2READ;
                key[k].bf.AtTimeExpired_BeforeOrAfter = KB_AFTER_THR;	//queda senializado

                if (!key[k].bf.Reptt)							//x No Reptt
                {
                    key[k].sm1 = _STAGE_ISKEY_RELEASED_;   //wait for key is release
                }
                else
                {
                    key[k].sm1 = _STAGE_REPTT_2_;
                }
            }
        }
        //_________________________________________________________________________________________
        if (key[k].sm1 == _STAGE_ISKEY_RELEASED_)		//MODO->FireOnKeyPressed + no Repetitibilidad 	//MODO->solo esperar que suelte
        {
            if (key[k].bf.state == KB_KEY_STATE_RELEASED)						//ya solto?
            {
                key[k].sm1 = _STAGE_ISKEY_READFROMAPP_;   //esperar x leer
            }
        }
        //_________________________________________________________________________________________
        if (key[k].sm1 == _STAGE_ISKEY_READFROMAPP_)
        {
            if (key[k].bf.ReadyToRead == KBAPP_ALREADYREAD)	//ya leyo? //added 2019: || (terminate_key) la app. mata el proceso...
            {
                key[k].sm1 = _STAGE_END_PARSING_;
            }
        }
        //_________________________________________________________________________________________
        if (key[k].sm1 == _STAGE_END_PARSING_)
        {
            if (key[k].num_group_x > NO_GROUP_X)	//forma grupo?
            {
                group_x[key[k].num_group_x] = GROUP_UNLOCKED;
                key[k].bf.OwnerOfGroup = 0;
            }

            key[k].sm1 = _STAGE_START_PARSING_;

            //Add++
            key[k].bf.InProcessing = 0;
            //++
        }

    }
}

///////////////////////////////////////////////////////////////////////////
//ninguna tecla presionada a nivel de hardware
///////////////////////////////////////////////////////////////////////////
//uint8_t AllKeysReleased(void)
//{
//    uint8_t i;
//    for (i=0; i<KB_NUM_KEYS; i++)
//    {
//        if (key[i].bf.state == KB_KEY_STATE_PRESSED)
//        {
//            return 0;
//        }
//    }
//    return 1;
//}
int8_t ikey_all_hw_released(void)//hardware release
{
    uint8_t i;
    for (i=0; i<KB_NUM_KEYS; i++)
    {
        if (key[i].bf.state == KB_KEY_STATE_PRESSED)
        {
            return 0;
        }
    }
    return 1;
}

void ikey_all_clear_flag(void)//clear ReadyToRead
{
    uint8_t i;
    for (i=0; i<KB_NUM_KEYS; i++)
    {
        //if (key[i].bf.ReadyToRead)
            key[i].bf.ReadyToRead = 0;
    }
}

int8_t ikey_all_process_finished(void)
{
    uint8_t i;
    for (i=0; i<KB_NUM_KEYS; i++)
    {
        if (key[i].bf.InProcessing == 1)
        {
            return 0;
        }
    }
    return 1;
}
/*
int8_t kb_change_process_focus(void)
{
    int8_t cod_ret = 0;
    static  int8_t sm0;
    if (sm0 == 0)
    {
        if (ikey_all_hw_released())
        {
            ikey_all_clear_flag();//libera todas sus maquinas de estados
            sm0++;
        }
    }
    else
    {
        if (ikey_all_process_finished())
        {
            sm0 = 0;
            cod_ret = 1;
        }
    }
    return cod_ret;
}
*/

///////////////////////////////////////////////////////////////////////////
//todos los eventos de tecla leidas -> all keys completed their current processes
///////////////////////////////////////////////////////////////////////////
//uint8_t AllKeysCompletedProcessing(void)
//{
//    uint8_t i;
//    for (i=0; i<KB_NUM_KEYS; i++)
//    {
//        if (key[i].bf.InProcessing == 1)
//        {
//            return 0;
//        }
//    }
//    return 1;
//}

/*
///////////////////////////////////////////////////////////////////////////
uint8_t KB_if_allreleased_clearReadyToRead(void)//no reentrant - interrupt thread
{
    uint8_t i;
    //if ( objsharedfeatkeys.bfSHARED.AllKeysReleased )
    if ( AllKeysReleased() )
    {
        for (i=0; i<KB_NUM_KEYS; i++)		//All-Clear states
        {
            //si hace falta limpiar flag
            if (key[i].bf.ReadyToRead == KBAPP_READY2READ)//consistenciado
            {
                key[i].bf.ReadyToRead = KBAPP_ALREADYREAD;
                key[i].bf.AtTimeExpired_BeforeOrAfter = 0;
            }

        }
        return 1;
    }
    else
    {
        return 0;
    }
}


uint8_t kb_free_and_complete_ps(void)
{
    if (synch_kb.kb_free_and_complete_ps_sm0 == 0)
    {
        if ( KB_if_allreleased_clearReadyToRead() )
        {
            synch_kb.kb_free_and_complete_ps_sm0++;
        }
    }

    if (synch_kb.kb_free_and_complete_ps_sm0 == 1)
    {
        //if ( objsharedfeatkeys.bfSHARED.AllKeysReleased )//double check //only for security
        if ( AllKeysReleased() )//double check //only for security
        {
            if (AllKeysCompletedProcessing() )//if (objsharedfeatkeys.bfSHARED.AllKeysCompleteProcesses )
            {
                synch_kb.kb_free_and_complete_ps_sm0 = 0x00;

                return 1;	//evoluciona statemachine de la funcion que llama
            }
        }
        else
        {
            synch_kb.kb_free_and_complete_ps_sm0 = 0x0;
        }
    }
    return 0;
}


void KB_synch_kb_free_and_complete_ps(void)
{
    if (synch_kb_exposed_to_app.synch_kb_free_and_complete_ps.synch_freecomplete_sm0 == 1)
    {
        if ( kb_free_and_complete_ps() )
        {
            synch_kb_exposed_to_app.synch_kb_free_and_complete_ps.synch_freecomplete_sm0++;
        }
    }
}

void KB_synch_change_layout_keyboard(void)
{
    uint8_t i;

    if (synch_kb_exposed_to_app.key_change_layout.change_sm0 == 1)
    {
        if (key_change_layout.sm0 == 0)
        {
            if ( kb_free_and_complete_ps() )
            {
                key_change_layout.sm0++;
            }
        }

        if (key_change_layout.sm0 == 1)
        {
            key_change_layout.sm0 = 0x00;
            //===================================

            if (synch_kb_exposed_to_app.key_change_layout.stack_mode == (_STACK_MODE)POP)	//(_STACK_MODE)PUSH
            {
                KB_change_layout_keyboard__pop_stack();
            }
            else
            {
                if (synch_kb_exposed_to_app.key_change_layout.stack_mode == (_STACK_MODE)PUSH)	//(_STACK_MODE)PUSH
                {
                    KB_change_layout_keyboard__push_stack();
                }

                for (i=0; i< KB_NUM_KEYS; i++)
                {
                    key[i].key_properties.u._8b_key_properties = synch_kb_exposed_to_app.key_change_layout.p_key_properties[i].u._8b_key_properties;
                    key[i].num_group_x = synch_kb_exposed_to_app.key_change_layout.p_key_properties[i].group_autoexcluding;
                }
            }

            //===================================
            synch_kb_exposed_to_app.key_change_layout.change_sm0++;//populate to application
        }
    }
}
*/

uint8_t kb_key_is_ready2read(uint8_t k)
{
    return key[k].bf.ReadyToRead;
}

void kb_set_ready2read(uint8_t k)
{
    key[k].bf.ReadyToRead = 1;
}
void kb_key_was_read(uint8_t k)
{
    key[k].bf.ReadyToRead = 0;
}

void kb_execfunct(uint8_t k)
{
    key[k].keyDo();
}



