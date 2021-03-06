#include <u8g2.h>

static u8g2_t u8g2;

static enum {
	LEFT,
	RIGHT,
	CENTER,
} align_mode = LEFT;

void oled_on() {
	u8g2_SetPowerSave(&u8g2, 0);
}

void oled_off() {
	u8g2_SetPowerSave(&u8g2, 1);
}

void oled_clear() {
	u8g2_ClearBuffer(&u8g2);
}

void oled_update() {
	u8g2_SendBuffer(&u8g2);
}

int oled_font_width() {
	return u8g2_GetMaxCharWidth(&u8g2);
}

int oled_font_ascent() {
	return u8g2_GetAscent(&u8g2);
}

int oled_font_descent() {
	return -u8g2_GetDescent(&u8g2);
}

void oled_font_small() {
	u8g2_SetFont(&u8g2, u8g2_font_helvR08_tr);
}

void oled_font_medium() {
	u8g2_SetFont(&u8g2, u8g2_font_helvR12_tr);
}

void oled_font_large() {
	u8g2_SetFont(&u8g2, u8g2_font_helvR24_tr);
}

void oled_align_left() {
	align_mode = LEFT;
}

void oled_align_right() {
	align_mode = RIGHT;
}

void oled_align_center() {
	align_mode = CENTER;
}

int oled_string_width(const char *s) {
	return u8g2_GetStrWidth(&u8g2, s);
}

void oled_draw_string(int x, int y, const char *s) {
	if (align_mode != LEFT) {
		int w = u8g2_GetStrWidth(&u8g2, s);
		if (align_mode == CENTER) {
			w /= 2;
		}
		x -= w;
	}
	u8g2_DrawStr(&u8g2, x, y, s);
}

void oled_draw_box(int x, int y, int w, int h) {
	u8g2_DrawBox(&u8g2, x, y, w, h);
}

extern uint8_t i2c_callback(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
extern uint8_t gpio_and_delay_callback(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

void oled_init() {
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, i2c_callback, gpio_and_delay_callback);
	u8x8_SetI2CAddress(&u8g2.u8x8, 0x3C << 1);
	u8g2_InitDisplay(&u8g2);

	oled_on();
	oled_clear();
}
