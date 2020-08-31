# lv_port_sstar
lvgl针对SigmaStar硬件平台的一份移植。

## Quick Start

```sh
git clone https://xxxx.xx/lv_port_sstar
cd lv_port_sstar
git submodule init && git submodule update
make
./demo
```

## 子模块说明

### lvgl
lvgl图形库的主体。项目地址为[https://github.com/lvgl/lvgl.git](https://github.com/lvgl/lvgl.git)

### lv_examples
使用lvgl图形库编写的一些demo，项目地址为[https://github.com/lvgl/lv_examples.git](https://github.com/lvgl/lv_examples.git)

### lv_drivers
lvgl的驱动，这里主要使用了针对Linux fbdev的display驱动和基于events的input device驱动。项目地址为
[https://github.com/lvgl/lv_drivers.git](https://github.com/lvgl/lv_drivers.git)

## 配置文件

### lv_conf.h
lvgl的配置文件，主要配置屏幕分辨率和颜色模型
```h
/*====================
  Graphical settings
 *====================*/

/* Maximal horizontal and vertical resolution to support by the library.*/
#define LV_HOR_RES_MAX          (800)
#define LV_VER_RES_MAX          (480)

/* Color depth:
 * - 1:  1 byte per pixel
 * - 8:  RGB332
 * - 16: RGB565
 * - 32: ARGB8888
 */
#define LV_COLOR_DEPTH     32

/* Swap the 2 bytes of RGB565 color.
 * Useful if the display has a 8 bit interface (e.g. SPI)*/
#define LV_COLOR_16_SWAP   0
```

### lv_ex_conf.h
`lv_examples`子模块的配置文件，主要通过配置一些宏来控制编译哪些`example`.

```h
/*********************
 * DEMO USAGE
 *********************/

/*Show some widget*/
#define LV_USE_DEMO_WIDGETS        1
#if LV_USE_DEMO_WIDGETS
#define LV_DEMO_WIDGETS_SLIDESHOW  1
#endif

/*Printer demo, optimized for 800x480*/
#define LV_USE_DEMO_PRINTER     1

/*Demonstrate the usage of encoder and keyboard*
#define LV_USE_DEMO_KEYPAD_AND_ENCODER     0

/*Benchmark your system*/
#define LV_USE_DEMO_BENCHMARK   0

/*Stress test for LVGL*/
#define LV_USE_DEMO_STRESS      0
```

### lv_drv_conf.h
lv_drivers子模块的配置文件，配置使用哪些driver，无需修改。

## 配置触摸屏分辨率
如果触摸屏的点触分辨率和显示的分辨率不同，会导致点击时无法找到正确的位置，
使用下面的方式可以查看和修改触摸屏的分辨率。

```sh
git clone https://github.com/aaron201912/UuidSSDPlayer.git
```

在`UuidSSDPlayer/tool`下，找到`1024x600.bin`和`800x480.bin`，使用下面的命令修改。

```sh
echo 800x480.bin > /sys/bus/i2c/devices/1-005d/gtcfg
echo 1024x600.bin > /sys/bus/i2c/devices/1-005d/gtcfg
```
