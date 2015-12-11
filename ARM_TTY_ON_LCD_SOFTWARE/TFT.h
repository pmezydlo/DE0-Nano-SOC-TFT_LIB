#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include "hwlib.h"
#include "socal/socal.h"
#include "socal/hps.h"
#include "socal/alt_gpio.h"

#define Hsize 480
#define Vsize 272

int strlen(const char *str);
uint8_t RGB565TORGB323(uint16_t COLOR);
uint16_t RGB565(uint8_t R, uint8_t G, uint8_t B);
uint8_t RGB323(uint8_t R, uint8_t G, uint8_t B);
void TFT_text(void *h2p_lw_addr, char* text, uint16_t x, uint16_t y, uint16_t COLOR);
void TFT_char(void *h2p_lw_addr,char sign,uint16_t x, uint16_t y, uint16_t COLOR);
void TFT_fill(void *h2p_lw_addr,uint8_t COLOR);
void TFT_rectangle(void *h2p_lw_addr,uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t COLOR);
void TFT_circle(void *h2p_lw_addr,uint16_t x, uint16_t y, uint16_t rad, uint8_t COLOR);
void TFT_rounddd(void *h2p_lw_addr,uint16_t x, uint16_t y, uint16_t rad, uint8_t COLOR);
void TFT_line(void *h2p_lw_addr,uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t COLOR);
void TFT_setpix(void *h2p_lw_addr,unsigned short X, unsigned short Y, uint8_t COLOR);
int getaddr(unsigned short X, unsigned short Y);
void TFT_bitmap(void *h2p_lw_addr, uint16_t *img, uint16_t x, uint16_t y);


