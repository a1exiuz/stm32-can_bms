#include "ssd1306.h"
#include "i2c.h"

const uint8_t font5x7[][5] = {
     // Numbers 0-9
    {0x3E,0x51,0x49,0x45,0x3E}, // 0
    {0x00,0x42,0x7F,0x40,0x00}, // 1
    {0x42,0x61,0x51,0x49,0x46}, // 2
    {0x21,0x41,0x45,0x4B,0x31}, // 3
    {0x18,0x14,0x12,0x7F,0x10}, // 4
    {0x27,0x45,0x45,0x45,0x39}, // 5
    {0x3C,0x4A,0x49,0x49,0x30}, // 6
    {0x01,0x71,0x09,0x05,0x03}, // 7
    {0x36,0x49,0x49,0x49,0x36}, // 8
    {0x06,0x49,0x49,0x29,0x1E}, // 9

    // Letters A-Z
    {0x7E,0x11,0x11,0x11,0x7E}, // A
    {0x7F,0x49,0x49,0x49,0x36}, // B
    {0x3E,0x41,0x41,0x41,0x22}, // C
    {0x7F,0x41,0x41,0x22,0x1C}, // D
    {0x7F,0x49,0x49,0x49,0x41}, // E
    {0x7F,0x09,0x09,0x09,0x01}, // F
    {0x3E,0x41,0x49,0x49,0x7A}, // G
    {0x7F,0x08,0x08,0x08,0x7F}, // H
    {0x00,0x41,0x7F,0x41,0x00}, // I
    {0x20,0x40,0x41,0x3F,0x01}, // J
    {0x7F,0x08,0x14,0x22,0x41}, // K
    {0x7F,0x40,0x40,0x40,0x40}, // L
    {0x7F,0x02,0x0C,0x02,0x7F}, // M
    {0x7F,0x04,0x08,0x10,0x7F}, // N
    {0x3E,0x41,0x41,0x41,0x3E}, // O
    {0x7F,0x09,0x09,0x09,0x06}, // P
    {0x3E,0x41,0x51,0x21,0x5E}, // Q
    {0x7F,0x09,0x19,0x29,0x46}, // R
    {0x46,0x49,0x49,0x49,0x31}, // S
    {0x01,0x01,0x7F,0x01,0x01}, // T
    {0x3F,0x40,0x40,0x40,0x3F}, // U
    {0x1F,0x20,0x40,0x20,0x1F}, // V
    {0x3F,0x40,0x38,0x40,0x3F}, // W
    {0x63,0x14,0x08,0x14,0x63}, // X
    {0x07,0x08,0x70,0x08,0x07}, // Y
    {0x61,0x51,0x49,0x45,0x43}, // Z

    // Special characters
    {0x00,0x36,0x36,0x00,0x00}, // :
    {0x23,0x13,0x08,0x64,0x62}, // %
    {0x06,0x09,0x09,0x06,0x00}  // ° (degree symbol)
};

void SSD1306_send_command(uint8_t cmd) {
    I2C_write_reg(SSD1306_ADDR, SSD1306_CMD_MODE, cmd);
}

void SSD1306_init(void) {
    SSD1306_send_command(SSD1306_DISPLAY_OFF);

    SSD1306_send_command(SSD1306_CLOCK_DIVIDE_RATIO);
    SSD1306_send_command(SSD1306_OSCILLATOR_FREQUENCY);

    SSD1306_send_command(SSD1306_MULTIPLEX_RATIO);
    SSD1306_send_command(SSD1306_64MUX);

    SSD1306_send_command(SSD1306_DISPLAY_OFFSET);
    SSD1306_send_command(SSD1306_NO_OFFSET);

    SSD1306_send_command(SSD1306_START_LINE);

    SSD1306_send_command(SSD1306_CHARGE_PUMP);
    SSD1306_send_command(SSD1306_ENABLE_PUMP);

    SSD1306_send_command(SSD1306_SET_MEM_ADDR_MODE);
    SSD1306_send_command(SSD1306_HORIZONTAL_ADDR);

    SSD1306_send_command(SSD1306_SET_COM_OUTPUT_DIR);

    SSD1306_send_command(SSD1306_SET_COM_PINS_CFG);
    SSD1306_send_command(SSD1306_COM_PINS_VAL);

    SSD1306_send_command(SSD1306_SET_CONTRAST);
    SSD1306_send_command(SSD1306_CONTRAST_VAL);

    SSD1306_send_command(SSD1306_SET_PRE_CHARGE);
    SSD1306_send_command(SSD1306_PRE_CHARGE_VAL);

    SSD1306_send_command(SSD1306_SET_VCOMH_LVL);
    SSD1306_send_command(SSD1306_VCOMH_VAL);

    SSD1306_send_command(SSD1306_ENTIRE_DISPLAY_ON);

    SSD1306_send_command(SSD1306_SET_NORMAL_DISPLAY);

    SSD1306_send_command(SSD1306_DISPLAY_ON);
}

void SSD1306_send_data(uint8_t data) {
    I2C_write_reg(SSD1306_ADDR, SSD1306_DATA_MODE, data);
}

void SSD1306_set_cursor(uint8_t col, uint8_t page) {
    SSD1306_send_command(SSD1306_SET_COLUMN_ADDR);
    SSD1306_send_command(col);
    SSD1306_send_command(127);

    SSD1306_send_command(SSD1306_SET_PAGE_ADDR);
    SSD1306_send_command(page);
    SSD1306_send_command(7);
}

void SSD1306_fill(uint8_t val) {
    SSD1306_set_cursor(0, 0);

    for(uint16_t i = 0; i < 1024; i++) {
        SSD1306_send_data(val);
    }
}

void SSD1306_print_char(char c) {
    uint8_t index = 0;

    if(c == ' ') {
        for(uint8_t i = 0; i < 6; i++) {
            SSD1306_send_data(0x00);
            return;
        }
    } else if((c >= '0') && (c <= '9')) {
        index = (c - '0');
    } else if((c >= 'A') && (c <= 'Z')) {
        index = 10 + (c - 'A');
    } else if(c == ':') {
        index = 36;
    } else if(c == '%') {
        index = 37;
    } else if(c == 'DEGREE_CHAR') {
        index = 38;
    }

    for(uint8_t i = 0; i < 5; i++) {
        SSD1306_send_data(font5x7[index][i]);
    }

    SSD1306_send_data(0x00);
}

void SSD1306_print_str(const char *c) {
    if(!c)
        return;

    while(*c) {
        SSD1306_print_char(*c++);
    }
}
