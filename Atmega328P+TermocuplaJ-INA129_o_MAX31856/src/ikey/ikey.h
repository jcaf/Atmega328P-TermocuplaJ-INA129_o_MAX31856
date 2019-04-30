#ifndef IKEY_H_
#define IKEY_H_
    #include "../types.h"

    #define KB_NUM_KEYS 16

    //ikey index
    #define IKEY_POS1 0
    #define IKEY_POS2 1
    #define IKEY_POS3 2
    #define IKEY_POS4 3

    #define IKEY_POS5 4
    #define IKEY_POS6 5
    #define IKEY_POS7 6
    #define IKEY_POS8 7

    #define IKEY_POS9 8
    #define IKEY_POS10 9
    #define IKEY_POS11 10
    #define IKEY_POS12 11

    #define IKEY_POS13 12
    #define IKEY_POS14 13
    #define IKEY_POS15 14
    #define IKEY_POS16 15

    struct _key
    {
        PTRFX_retUINT8_T keyRead;
        PTRFX_retVOID keyDo;
        uint8_t sm0;        //maquina de estados
        uint8_t counter0;//contador
        uint8_t sm1;
        uint16_t counter1;
        uint8_t  num_group_x;
        struct _bf
        {
            unsigned state:1;

            unsigned OnKeyPressed:1;
            unsigned OnKeyPressedAndKeyRelease:1;
            unsigned AtTimeExpired:1;
            unsigned Reptt:1;
            unsigned ReadyToRead:1;		//soft-populate
            unsigned AtTimeExpired_BeforeOrAfter:1;//para usar a nivel de app
            unsigned OwnerOfGroup:1;
            unsigned InProcessing:1;
        } bf;
        struct _repp
        {
            uint16_t to_start;
            uint8_t after_start;
        } repp;
    };


    void key_initialization(void);

    void ikey_scan(void);
    void ikey_parsing(void);


    //fx expuestas x app
    uint8_t kb_key_is_ready2read(uint8_t k);
    void    kb_set_ready2read(uint8_t k);
    void    kb_key_was_read(uint8_t k);
    void    kb_execfunct(uint8_t k);

    //uint8_t AllKeysReleased(void);//a nivel de hardware...
    //uint8_t AllKeysCompletedProcessing(void);
    //int8_t kb_change_process_focus(void);
    void ikey_all_clear_flag(void);//clear ReadyToRead

    extern volatile struct _key key[];


#endif


