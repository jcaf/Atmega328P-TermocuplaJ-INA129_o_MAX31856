#ifndef NUM_TEXTEDIT_HWSPECIFIC_H_
#define NUM_TEXTEDIT_HWSPECIFIC_H_

    struct _kb_num_textedit_actionhandler
    {
        int8_t new_action;
        int8_t char_dig;
    };

    //int8_t
    void kb_num_textedit_actionhandler(struct _kb_num_textedit_actionhandler *actionhandler);

    void num_textedit_hwspecific_print_disp(int8_t idx_ascursor);
#endif // NUM_TEXTEDIT_HWSPECIFIC_H_

