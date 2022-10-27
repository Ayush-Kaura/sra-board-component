/*
 * MIT License
 *
 * Copyright (c)  2021 Society of Robotics and Automation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "oled.h"
#include "sra_board.h"

static const char *TAG = "oled_example";

void app_main()
{

    // init_oled();

	lv_init();
	
	/* Initialize I2C bus used by the drivers */
	lvgl_i2c_driver_init(I2C_NUM_0, OLED_SDA, OLED_SCL, OLED_IIC_FREQ_HZ);
	ssd1306_init();

	lv_color_t* buf1 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);

    lv_disp_draw_buf_t disp_buf;

    uint32_t size_in_px = DISP_BUF_SIZE; 
	size_in_px *= 8;
    
    /* Initialize the working buffer depending on the selected display */
    lv_disp_draw_buf_init(&disp_buf, buf1, NULL, size_in_px);

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
	disp_drv.hor_res = 128;                 
	disp_drv.ver_res = 64;
    disp_drv.flush_cb = ssd1306_flush;
    disp_drv.rounder_cb = ssd1306_rounder;
    disp_drv.set_px_cb = ssd1306_set_px_cb;
    disp_drv.draw_buf = &disp_buf;

    lv_disp_t * disp = lv_disp_drv_register(&disp_drv);

	ESP_LOGI(TAG, "Successfully displayed Hello World on the OLED Screen");
}

