/* Copyright 2022 ShandonCodes
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _1,
    _2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_default(
        KC_ESCAPE, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_GRV, KC_BSPACE,
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_ENTER,
        KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSHIFT,
        KC_LCTRL, KC_LGUI, KC_LALT, KC_SPACE, KC_DEL, KC_SPACE, MO(_1), MO(_2), KC_RCTRL
    ),
    [_1] = LAYOUT_default(
        XXXXXXX, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, XXXXXXX, KC_DEL,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_QUOT,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_2] = LAYOUT_default(
        KC_UP, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX,
        KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};

#ifdef OLED_ENABLE
#define FRAMES 5
#define ANIMATION_SIZE 512
#define TAP_SPEED 30

uint8_t  current_frame = 0;
uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;
uint32_t ANIM_FRAME_DURATION = 1000;

static void render_animation(void) {
    static const char PROGMEM animation_frames[FRAMES][ANIMATION_SIZE] = {
        // 'Base', 32x128px
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
        0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x40, 0xc0, 
        0x40, 0x40, 0x40, 0xc0, 0x40, 0x40, 0x40, 0xc0, 0xc0, 0x40, 0x40, 0xc1, 0xc3, 0x43, 0x43, 0xc3, 
        0x00, 0x00, 0x00, 0x00, 0xfe, 0x66, 0x66, 0xe6, 0xfc, 0x20, 0x20, 0xff, 0xe6, 0x66, 0x66, 0xff, 
        0xe6, 0x26, 0x26, 0x67, 0xe6, 0x26, 0x26, 0xe7, 0xff, 0x66, 0x66, 0xff, 0x7f, 0x26, 0x26, 0x3f, 
        0xe0, 0x20, 0x20, 0x20, 0xff, 0x22, 0x22, 0xff, 0xff, 0x22, 0x22, 0xff, 0xe3, 0x22, 0x22, 0xe3, 
        0x3f, 0x22, 0x22, 0xe2, 0x3f, 0x22, 0x22, 0x3f, 0xff, 0x22, 0x22, 0xff, 0x22, 0x00, 0x00, 0x00, 
        0xff, 0x33, 0x33, 0x33, 0xff, 0x1f, 0x13, 0x13, 0xff, 0xff, 0x33, 0x33, 0xff, 0x33, 0x13, 0x13, 
        0x1f, 0x02, 0x02, 0x03, 0x00, 0x00, 0x00, 0x33, 0xff, 0x33, 0x33, 0xff, 0x02, 0x00, 0x00, 0x00, 
        0xff, 0x11, 0x11, 0x91, 0xff, 0xf0, 0x10, 0x10, 0xff, 0xff, 0x11, 0x11, 0xff, 0x9b, 0x11, 0x11, 
        0xff, 0x91, 0x11, 0x91, 0xff, 0x11, 0x11, 0x1f, 0x1f, 0x11, 0x11, 0x1f, 0x01, 0x00, 0x00, 0x00, 
        0xff, 0x99, 0x99, 0x99, 0xff, 0x99, 0x99, 0xf9, 0xf9, 0x99, 0x99, 0xf9, 0xf9, 0x99, 0x99, 0xf9, 
        0x9f, 0x99, 0x99, 0xf9, 0x1f, 0x19, 0x19, 0x1f, 0xff, 0x99, 0x99, 0xff, 0xff, 0x99, 0x99, 0xff, 
        0xf8, 0x88, 0x88, 0x88, 0xff, 0x89, 0x89, 0xff, 0xff, 0x89, 0x89, 0xff, 0xff, 0x89, 0x89, 0xff, 
        0x88, 0x88, 0x88, 0xf8, 0x88, 0x88, 0x88, 0xf8, 0x80, 0x80, 0x80, 0xff, 0xc9, 0x89, 0x89, 0xff, 
        0xff, 0xcc, 0xcc, 0xcc, 0xff, 0x40, 0x40, 0xcc, 0xff, 0xcc, 0xcc, 0xff, 0xff, 0xcc, 0xcc, 0xff, 
        0xcc, 0x48, 0xc8, 0xff, 0xc8, 0xc8, 0xc8, 0xfc, 0xff, 0xcc, 0xcc, 0xff, 0xff, 0xcc, 0xcc, 0xff, 
        0x7f, 0x7c, 0x7c, 0x7c, 0x7f, 0x7c, 0x7c, 0x7f, 0x7f, 0x7c, 0x7c, 0x7f, 0x7f, 0x7c, 0x7c, 0x7f, 
        0x7c, 0x7c, 0x7c, 0x7f, 0x7c, 0x7c, 0x7c, 0x7f, 0x7f, 0x7c, 0x7c, 0x7f, 0x7f, 0x7c, 0x7c, 0x7f}, 

        // 'Frame_1', 32x128px
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x4c, 0x4c, 0xfc, 0xfc, 0x4c, 
        0x4c, 0xfc, 0xc0, 0x40, 0x40, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x04, 
        0x04, 0x07, 0x07, 0x04, 0x04, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
        0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x40, 0xc0, 
        0x40, 0x40, 0x40, 0xc0, 0x40, 0x40, 0x40, 0xc0, 0xc0, 0x40, 0x40, 0xc1, 0xc3, 0x43, 0x43, 0xc3, 
        0x00, 0x00, 0x00, 0x00, 0xfe, 0x66, 0x66, 0xe6, 0xfc, 0x20, 0x20, 0xff, 0xe6, 0x66, 0x66, 0xff, 
        0xe6, 0x26, 0x26, 0x67, 0xe6, 0x26, 0x26, 0xe7, 0xff, 0x66, 0x66, 0xff, 0x7f, 0x26, 0x26, 0x3f, 
        0xe0, 0x20, 0x20, 0x20, 0xff, 0x22, 0x22, 0xff, 0xff, 0x22, 0x22, 0xff, 0xe3, 0x22, 0x22, 0xe3, 
        0x3f, 0x22, 0x22, 0xe2, 0x3f, 0x22, 0x22, 0x3f, 0xff, 0x22, 0x22, 0xff, 0x22, 0x00, 0x00, 0x00, 
        0xff, 0x33, 0x33, 0x33, 0xff, 0x1f, 0x13, 0x13, 0xff, 0xff, 0x33, 0x33, 0xff, 0x33, 0x13, 0x13, 
        0x1f, 0x02, 0x02, 0x03, 0x00, 0x00, 0x00, 0x33, 0xff, 0x33, 0x33, 0xff, 0x02, 0x00, 0x00, 0x00, 
        0xff, 0x11, 0x11, 0x91, 0xff, 0xf0, 0x10, 0x10, 0xff, 0xff, 0x11, 0x11, 0xff, 0x9b, 0x11, 0x11, 
        0xff, 0x91, 0x11, 0x91, 0xff, 0x11, 0x11, 0x1f, 0x1f, 0x11, 0x11, 0x1f, 0x01, 0x00, 0x00, 0x00, 
        0xff, 0x99, 0x99, 0x99, 0xff, 0x99, 0x99, 0xf9, 0xf9, 0x99, 0x99, 0xf9, 0xf9, 0x99, 0x99, 0xf9, 
        0x9f, 0x99, 0x99, 0xf9, 0x1f, 0x19, 0x19, 0x1f, 0xff, 0x99, 0x99, 0xff, 0xff, 0x99, 0x99, 0xff, 
        0xf8, 0x88, 0x88, 0x88, 0xff, 0x89, 0x89, 0xff, 0xff, 0x89, 0x89, 0xff, 0xff, 0x89, 0x89, 0xff, 
        0x88, 0x88, 0x88, 0xf8, 0x88, 0x88, 0x88, 0xf8, 0x80, 0x80, 0x80, 0xff, 0xc9, 0x89, 0x89, 0xff, 
        0xff, 0xcc, 0xcc, 0xcc, 0xff, 0x40, 0x40, 0xcc, 0xff, 0xcc, 0xcc, 0xff, 0xff, 0xcc, 0xcc, 0xff, 
        0xcc, 0x48, 0xc8, 0xff, 0xc8, 0xc8, 0xc8, 0xfc, 0xff, 0xcc, 0xcc, 0xff, 0xff, 0xcc, 0xcc, 0xff, 
        0x7f, 0x7c, 0x7c, 0x7c, 0x7f, 0x7c, 0x7c, 0x7f, 0x7f, 0x7c, 0x7c, 0x7f, 0x7f, 0x7c, 0x7c, 0x7f, 
        0x7c, 0x7c, 0x7c, 0x7f, 0x7c, 0x7c, 0x7c, 0x7f, 0x7f, 0x7c, 0x7c, 0x7f, 0x7f, 0x7c, 0x7c, 0x7f}, 

        // 'Frame_2', 32x128px
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0xc0, 0xc0, 0x40, 
        0x40, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x04, 0x04, 0x3f, 0x7f, 0x44, 
        0x44, 0x7f, 0x7c, 0x44, 0x44, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
        0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x40, 0xc0, 
        0x40, 0x40, 0x40, 0xc0, 0x40, 0x40, 0x40, 0xc0, 0xc0, 0x40, 0x40, 0xc1, 0xc3, 0x43, 0x43, 0xc3, 
        0x00, 0x00, 0x00, 0x00, 0xfe, 0x66, 0x66, 0xe6, 0xfc, 0x20, 0x20, 0xff, 0xe6, 0x66, 0x66, 0xff, 
        0xe6, 0x26, 0x26, 0x67, 0xe6, 0x26, 0x26, 0xe7, 0xff, 0x66, 0x66, 0xff, 0x7f, 0x26, 0x26, 0x3f, 
        0xe0, 0x20, 0x20, 0x20, 0xff, 0x22, 0x22, 0xff, 0xff, 0x22, 0x22, 0xff, 0xe3, 0x22, 0x22, 0xe3, 
        0x3f, 0x22, 0x22, 0xe2, 0x3f, 0x22, 0x22, 0x3f, 0xff, 0x22, 0x22, 0xff, 0x22, 0x00, 0x00, 0x00, 
        0xff, 0x33, 0x33, 0x33, 0xff, 0x1f, 0x13, 0x13, 0xff, 0xff, 0x33, 0x33, 0xff, 0x33, 0x13, 0x13, 
        0x1f, 0x02, 0x02, 0x03, 0x00, 0x00, 0x00, 0x33, 0xff, 0x33, 0x33, 0xff, 0x02, 0x00, 0x00, 0x00, 
        0xff, 0x11, 0x11, 0x91, 0xff, 0xf0, 0x10, 0x10, 0xff, 0xff, 0x11, 0x11, 0xff, 0x9b, 0x11, 0x11, 
        0xff, 0x91, 0x11, 0x91, 0xff, 0x11, 0x11, 0x1f, 0x1f, 0x11, 0x11, 0x1f, 0x01, 0x00, 0x00, 0x00, 
        0xff, 0x99, 0x99, 0x99, 0xff, 0x99, 0x99, 0xf9, 0xf9, 0x99, 0x99, 0xf9, 0xf9, 0x99, 0x99, 0xf9, 
        0x9f, 0x99, 0x99, 0xf9, 0x1f, 0x19, 0x19, 0x1f, 0xff, 0x99, 0x99, 0xff, 0xff, 0x99, 0x99, 0xff, 
        0xf8, 0x88, 0x88, 0x88, 0xff, 0x89, 0x89, 0xff, 0xff, 0x89, 0x89, 0xff, 0xff, 0x89, 0x89, 0xff, 
        0x88, 0x88, 0x88, 0xf8, 0x88, 0x88, 0x88, 0xf8, 0x80, 0x80, 0x80, 0xff, 0xc9, 0x89, 0x89, 0xff, 
        0xff, 0xcc, 0xcc, 0xcc, 0xff, 0x40, 0x40, 0xcc, 0xff, 0xcc, 0xcc, 0xff, 0xff, 0xcc, 0xcc, 0xff, 
        0xcc, 0x48, 0xc8, 0xff, 0xc8, 0xc8, 0xc8, 0xfc, 0xff, 0xcc, 0xcc, 0xff, 0xff, 0xcc, 0xcc, 0xff, 
        0x7f, 0x7c, 0x7c, 0x7c, 0x7f, 0x7c, 0x7c, 0x7f, 0x7f, 0x7c, 0x7c, 0x7f, 0x7f, 0x7c, 0x7c, 0x7f, 
        0x7c, 0x7c, 0x7c, 0x7f, 0x7c, 0x7c, 0x7c, 0x7f, 0x7f, 0x7c, 0x7c, 0x7f, 0x7f, 0x7c, 0x7c, 0x7f}, 

        // 'Frame_3', 32x128px
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x44, 0x44, 0xfc, 0xfc, 0x44, 
        0x44, 0xfc, 0xc0, 0x40, 0x40, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
        0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x43, 0x47, 0xc4, 
        0x44, 0x47, 0x47, 0xc4, 0x44, 0x47, 0x40, 0xc0, 0xc0, 0x40, 0x40, 0xc1, 0xc3, 0x43, 0x43, 0xc3, 
        0x00, 0x00, 0x00, 0x00, 0xfe, 0x66, 0x66, 0xe6, 0xfc, 0x20, 0x20, 0xff, 0xe6, 0x66, 0x66, 0xff, 
        0xe6, 0x26, 0x26, 0x67, 0xe6, 0x26, 0x26, 0xe7, 0xff, 0x66, 0x66, 0xff, 0x7f, 0x26, 0x26, 0x3f, 
        0xe0, 0x20, 0x20, 0x20, 0xff, 0x22, 0x22, 0xff, 0xff, 0x22, 0x22, 0xff, 0xe3, 0x22, 0x22, 0xe3, 
        0x3f, 0x22, 0x22, 0xe2, 0x3f, 0x22, 0x22, 0x3f, 0xff, 0x22, 0x22, 0xff, 0x22, 0x00, 0x00, 0x00, 
        0xff, 0x33, 0x33, 0x33, 0xff, 0x1f, 0x13, 0x13, 0xff, 0xff, 0x33, 0x33, 0xff, 0x33, 0x13, 0x13, 
        0x1f, 0x02, 0x02, 0x03, 0x00, 0x00, 0x00, 0x33, 0xff, 0x33, 0x33, 0xff, 0x02, 0x00, 0x00, 0x00, 
        0xff, 0x11, 0x11, 0x91, 0xff, 0xf0, 0x10, 0x10, 0xff, 0xff, 0x11, 0x11, 0xff, 0x9b, 0x11, 0x11, 
        0xff, 0x91, 0x11, 0x91, 0xff, 0x11, 0x11, 0x1f, 0x1f, 0x11, 0x11, 0x1f, 0x01, 0x00, 0x00, 0x00, 
        0xff, 0x99, 0x99, 0x99, 0xff, 0x99, 0x99, 0xf9, 0xf9, 0x99, 0x99, 0xf9, 0xf9, 0x99, 0x99, 0xf9, 
        0x9f, 0x99, 0x99, 0xf9, 0x1f, 0x19, 0x19, 0x1f, 0xff, 0x99, 0x99, 0xff, 0xff, 0x99, 0x99, 0xff, 
        0xf8, 0x88, 0x88, 0x88, 0xff, 0x89, 0x89, 0xff, 0xff, 0x89, 0x89, 0xff, 0xff, 0x89, 0x89, 0xff, 
        0x88, 0x88, 0x88, 0xf8, 0x88, 0x88, 0x88, 0xf8, 0x80, 0x80, 0x80, 0xff, 0xc9, 0x89, 0x89, 0xff, 
        0xff, 0xcc, 0xcc, 0xcc, 0xff, 0x40, 0x40, 0xcc, 0xff, 0xcc, 0xcc, 0xff, 0xff, 0xcc, 0xcc, 0xff, 
        0xcc, 0x48, 0xc8, 0xff, 0xc8, 0xc8, 0xc8, 0xfc, 0xff, 0xcc, 0xcc, 0xff, 0xff, 0xcc, 0xcc, 0xff, 
        0x7f, 0x7c, 0x7c, 0x7c, 0x7f, 0x7c, 0x7c, 0x7f, 0x7f, 0x7c, 0x7c, 0x7f, 0x7f, 0x7c, 0x7c, 0x7f, 
        0x7c, 0x7c, 0x7c, 0x7f, 0x7c, 0x7c, 0x7c, 0x7f, 0x7f, 0x7c, 0x7c, 0x7f, 0x7f, 0x7c, 0x7c, 0x7f}, 

        // 'Frame_4', 32x128px
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0xc0, 0xc0, 0x40, 
        0x40, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
        0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc4, 0x44, 0x7f, 0x7f, 0xe6, 
        0x66, 0x7f, 0x7e, 0xe4, 0x64, 0x7c, 0x40, 0xc0, 0xc0, 0x40, 0x40, 0xc1, 0xc3, 0x43, 0x43, 0xc3, 
        0x00, 0x00, 0x00, 0x00, 0xfe, 0x66, 0x66, 0xe6, 0xfc, 0x20, 0x20, 0xff, 0xe6, 0x66, 0x66, 0xff, 
        0xe6, 0x26, 0x26, 0x67, 0xe6, 0x26, 0x26, 0xe7, 0xff, 0x66, 0x66, 0xff, 0x7f, 0x26, 0x26, 0x3f, 
        0xe0, 0x20, 0x20, 0x20, 0xff, 0x22, 0x22, 0xff, 0xff, 0x22, 0x22, 0xff, 0xe3, 0x22, 0x22, 0xe3, 
        0x3f, 0x22, 0x22, 0xe2, 0x3f, 0x22, 0x22, 0x3f, 0xff, 0x22, 0x22, 0xff, 0x22, 0x00, 0x00, 0x00, 
        0xff, 0x33, 0x33, 0x33, 0xff, 0x1f, 0x13, 0x13, 0xff, 0xff, 0x33, 0x33, 0xff, 0x33, 0x13, 0x13, 
        0x1f, 0x02, 0x02, 0x03, 0x00, 0x00, 0x00, 0x33, 0xff, 0x33, 0x33, 0xff, 0x02, 0x00, 0x00, 0x00, 
        0xff, 0x11, 0x11, 0x91, 0xff, 0xf0, 0x10, 0x10, 0xff, 0xff, 0x11, 0x11, 0xff, 0x9b, 0x11, 0x11, 
        0xff, 0x91, 0x11, 0x91, 0xff, 0x11, 0x11, 0x1f, 0x1f, 0x11, 0x11, 0x1f, 0x01, 0x00, 0x00, 0x00, 
        0xff, 0x99, 0x99, 0x99, 0xff, 0x99, 0x99, 0xf9, 0xf9, 0x99, 0x99, 0xf9, 0xf9, 0x99, 0x99, 0xf9, 
        0x9f, 0x99, 0x99, 0xf9, 0x1f, 0x19, 0x19, 0x1f, 0xff, 0x99, 0x99, 0xff, 0xff, 0x99, 0x99, 0xff, 
        0xf8, 0x88, 0x88, 0x88, 0xff, 0x89, 0x89, 0xff, 0xff, 0x89, 0x89, 0xff, 0xff, 0x89, 0x89, 0xff, 
        0x88, 0x88, 0x88, 0xf8, 0x88, 0x88, 0x88, 0xf8, 0x80, 0x80, 0x80, 0xff, 0xc9, 0x89, 0x89, 0xff, 
        0xff, 0xcc, 0xcc, 0xcc, 0xff, 0x40, 0x40, 0xcc, 0xff, 0xcc, 0xcc, 0xff, 0xff, 0xcc, 0xcc, 0xff, 
        0xcc, 0x48, 0xc8, 0xff, 0xc8, 0xc8, 0xc8, 0xfc, 0xff, 0xcc, 0xcc, 0xff, 0xff, 0xcc, 0xcc, 0xff, 
        0x7f, 0x7c, 0x7c, 0x7c, 0x7f, 0x7c, 0x7c, 0x7f, 0x7f, 0x7c, 0x7c, 0x7f, 0x7f, 0x7c, 0x7c, 0x7f, 
        0x7c, 0x7c, 0x7c, 0x7f, 0x7c, 0x7c, 0x7c, 0x7f, 0x7f, 0x7c, 0x7c, 0x7f, 0x7f, 0x7c, 0x7c, 0x7f}
    };
    
    void animate_phase(void) {
        current_frame = (current_frame + 1) % FRAMES;
        oled_write_raw_P(animation_frames[current_frame], ANIMATION_SIZE);
    }

    if (get_current_wpm() != 000) {
        oled_on();  // not essential but turns on animation OLED with any alpha keypress
        if (get_current_wpm() > TAP_SPEED){
            ANIM_FRAME_DURATION = 100;
        } else {
            ANIM_FRAME_DURATION = 1000;
        }
        if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            anim_timer = timer_read32();
            animate_phase();
        }
        anim_sleep = timer_read32();
    } else {
        if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
            oled_off();
        } else {
            if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                anim_timer = timer_read32();
                animate_phase();
            }
        }
    }
}

static void render_status(void) {
    // Host Keyboard Layer Status
    oled_write_ln_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case _1:
            oled_write_ln_P(PSTR("1"), false);
            break;
        case _2:
            oled_write_ln_P(PSTR("2"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        return OLED_ROTATION_270; 
}

bool oled_task_user(void) {
    render_animation();
    render_status();

    oled_write_ln_P(PSTR("WPM:"), false);
    oled_write_ln(get_u8_str(get_current_wpm(), '0'), false);

    return false;
}
#endif
