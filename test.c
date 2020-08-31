/*
 * test.c
 */

#include <stdio.h>
#include <unistd.h>
#include "lv_obj.h"
#include "sstar_port.h"
#include "lv_label.h"
#include "lv_disp.h"
#include "lv_style.h"
#include "lv_examples.h"

int main(void)
{
    sstar_Graphics_Init();

//   lv_obj_t * label = lv_label_create(lv_scr_act(), NULL);
//   lv_label_set_text(label, "Hello world!");
//   lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_demo_widgets();
    //lv_demo_printer();
    while(1) {
        lv_tick_inc(5);
        lv_task_handler();
        usleep(5000);
    }

    sstar_Graphics_Deinit();
    return 0;
}
