#ifndef OV2640_H
#define OV2640_H

#include "main.h"
#include "bspcamera.h"


int ov2640_init(framesize_t framesize);
int ov2640_reset();
int ov2640_set_special_effect(uint8_t sde);
int ov2640_set_exposure(int exposure);
int ov2640_set_framesize(framesize_t framesize);
int ov2640_set_exposure(int exposure);
int ov2640_set_pixformat(pixformat_t pixformat);
int ov2640_check_framesize(uint8_t framesize);
int ov2640_set_contrast(int level);
int ov2640_set_brightness(int level);
int ov2640_set_saturation(int level);
int ov2640_set_quality(int qs);
int ov2640_set_colorbar(int enable);
int ov2640_set_hmirror(int enable);
int ov2640_set_vflip(int enable);
int ov2640_set_light_mode(uint8_t mode);
int ov2640_set_night_mode(int enable);

#endif
