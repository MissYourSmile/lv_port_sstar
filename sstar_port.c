/*
 * sstar_port.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <linux/input.h>
#include "../lvgl.h"
#include "sstarFb.h"
#include "sstar_port.h"
#include "evdev.h"
#include "fbdev.h"
#include "lv_conf.h"

#define ERR_EXIT(str) \
    do {\
        perror(str);\
        exit(EXIT_FAILURE);\
    } while(0)

// fbdev
//static int fd = 0;
//static struct fb_fix_screeninfo finfo;
//static struct fb_var_screeninfo vinfo;
//static uint8_t *framebuffer;

// lvgl
static lv_color_t *buf_1;
static lv_color_t *buf_2;
static lv_disp_buf_t disp_buf;

//static void sstar_Flush_Callback(struct _disp_drv_t * disp_drv,
//        const lv_area_t * area, lv_color_t * color_p)
//{
//    uint8_t *curr_buf = NULL;
//    uint32_t x, y;
//    uint32_t byte_pre_pixel = vinfo.bits_per_pixel / 8;
//    uint32_t stride = finfo.line_length / sizeof(uint8_t);
//    if (disp_drv->buffer->buf1 == disp_drv->buffer->buf_act)
//    {
//        curr_buf = framebuffer;
//        vinfo.yoffset = 0;
//    }
//    else
//    {
//        curr_buf = framebuffer + vinfo.yres * finfo.line_length;
//        vinfo.yoffset = vinfo.yres;
//    }
//    curr_buf += area->y1 * stride;
//    curr_buf += area->x1 * vinfo.bits_per_pixel / 8;
//    for (y = area->y1; y <= area->y2; ++y)
//    {
//        memcpy(curr_buf, color_p, (area->x2 - area->x1 + 1) * 4);
//        color_p += area->x2 - area->x1 + 1;
//        curr_buf += stride;
//    }
//    if (-1 == ioctl(fd, FBIOPAN_DISPLAY, &vinfo))
//        ERR_EXIT("FBIOPAN_DISPLAY.");
//    lv_disp_flush_ready(disp_drv);
//}
//
//static void fb_Init()
//{
//    const char *fb_dev_name = "/dev/fb0";
//
//    // Open fb_dev
//    fd = open(fb_dev_name, O_RDWR);
//    if (-1 == fd)
//        ERR_EXIT("open fbdev");
//
//    // Get finfo and vinfo
//    if (-1 == ioctl(fd, FBIOGET_FSCREENINFO, &finfo))
//        ERR_EXIT("FBIOGET_FSCREENINFO.");
//
//    if (-1 == ioctl(fd, FBIOGET_VSCREENINFO, &vinfo))
//        ERR_EXIT("FBIOGET_VSCREENINFO.");
//
//    // Mmap framebuffer
//    framebuffer =
//        mmap(0, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
//    if (NULL == framebuffer)
//        ERR_EXIT("mmap failed.");
//}
//
//static void fb_Deinit()
//{
//    munmap(framebuffer, finfo.smem_len);
//    close(fd);
//}

static void disp_Drv_Init()
{
    unsigned int pixel_cnt = 0;
    lv_disp_drv_t disp_drv;
    lv_indev_drv_t input_drv;

    // Lvgl init display buffer
    pixel_cnt = LV_HOR_RES_MAX * LV_VER_RES_MAX;
    buf_1 = (lv_color_t *)malloc(pixel_cnt * sizeof(lv_color_t));
    buf_2 = (lv_color_t *)malloc(pixel_cnt * sizeof(lv_color_t));

    lv_disp_buf_init(&disp_buf, buf_1, buf_2, pixel_cnt);

    // Lvgl init display driver
    lv_disp_drv_init(&disp_drv);
    disp_drv.buffer = &disp_buf;
    disp_drv.flush_cb = fbdev_flush;

    lv_disp_drv_register(&disp_drv);

    // Lvgl init input driver
    lv_indev_drv_init(&input_drv);
    input_drv.type = LV_INDEV_TYPE_POINTER;
    input_drv.read_cb = evdev_read;

    lv_indev_drv_register(&input_drv);
}

static void disp_Drv_Deinit(void)
{
    free(buf_1);
    free(buf_2);
}

void sstar_Graphics_Init(void)
{
    lv_init();
    //fb_Init();
    disp_Drv_Init();
    evdev_init();
    fbdev_init();
}

void sstar_Graphics_Deinit(void)
{
    disp_Drv_Deinit();
    fbdev_exit();
    //fb_Deinit();
}

