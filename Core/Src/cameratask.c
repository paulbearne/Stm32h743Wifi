/*
 * cameratask.c
 *
 *  Created on: Jan 29, 2025
 *      Author: paul
 */

#include "main.h"
#include "cameratask.h"
#include "bspcamera.h"
#include "i2c.h"
#include "dcmi.h"
#include "stdio.h"

#define FrameWidth 160
#define FrameHeight 120

uint16_t pic[FrameWidth][FrameHeight];
uint32_t DCMI_FrameIsReady;
uint32_t Camera_FPS = 0;
extern bspCameraHandleTypeDef hcamera;

void startCameraTask(void const *argument) {
	camera_t camdata;
	bspCameraInit_Device(&hi2c1, FRAMESIZE_QQVGA);
	HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t) &pic,
	FrameWidth * FrameHeight * 2 / 4);
	for (;;) {
		if (DCMI_FrameIsReady) {
			DCMI_FrameIsReady = 0;
			if (hcamera.manuf_id == 0x7fa2
					&& ((hcamera.device_id - 0x2641) <= 2)) {
				camdata.type = 1;  // ov2640
			} else if (hcamera.manuf_id == 0x7fa2
					&& hcamera.device_id == 0x7673) {
				camdata.type = 3; // OV7670
			} else if (hcamera.manuf_id == 0x7fa2
					&& ((hcamera.device_id - 0x7721) <= 2)) {
				camdata.type = 4;
			} else if (hcamera.device_id == 0x5640) {
				camdata.type = 2;

			} else {
				camdata.type = 0;
			}

			camdata.fps = Camera_FPS;
			camdata.id = hcamera.manuf_id;
		}
		osDelay(100);
		xQueueSendToBack(cameraQueueHandle, &camdata, (TickType_t ) 10);
	}
}

void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi) {
	static uint32_t count = 0, tick = 0;

	if (xTaskGetTickCount() - tick >= 1000) {
		tick = xTaskGetTickCount();
		Camera_FPS = count;
		count = 0;
	}
	count++;

	DCMI_FrameIsReady = 1;
}

