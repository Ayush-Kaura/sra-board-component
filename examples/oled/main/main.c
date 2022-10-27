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

#define LV_TICK_PERIOD_MS 1
// static void lv_tick_task(void *arg);

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

	// lv_theme_t * th = lv_theme_default_init(disp,  lv_color_black(), lv_color_white(), false, &lv_font_montserrat_14); 

	// lv_disp_set_theme(disp, th); 

	/* Create and start a periodic timer interrupt to call lv_tick_inc */
    // const esp_timer_create_args_t periodic_timer_args = {
    //     .callback = &lv_tick_task,
    //     .name = "periodic_gui"
    // };
    // esp_timer_handle_t periodic_timer;
    // ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    // ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));
    // lv_obj_t *scr = lv_disp_get_scr_act(NULL);
    // display_sra_logo(scr);
    // lv_obj_clean(scr);
    // lv_task_handler();
    // display_walle_logo(scr);
    // lv_task_handler();
    display_servo_values(10, 10, 10, 10);
    lv_task_handler();

	while (1) {
        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        
        vTaskDelay(pdMS_TO_TICKS(100));
        // lv_task_handler();
	}
	free(buf1);
	ESP_LOGI(TAG, "Successfully displayed Hello World on the OLED Screen");
}

// static void lv_tick_task(void *arg) {
//     (void) arg;

//     lv_tick_inc(LV_TICK_PERIOD_MS);
// }