 /* Copyright 2024 rikardoricz 
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
#pragma once

// Vial
#define VIAL_KEYBOARD_UID {0x51, 0x7B, 0xD5, 0x6B, 0xBA, 0x59, 0xD2, 0xA1}
#define VIAL_UNLOCK_COMBO_ROWS {4, 0}
#define VIAL_UNLOCK_COMBO_COLS {4, 1}
#define DYNAMIC_KEYMAP_LAYER_COUNT 5

#define MASTER_LEFT
#define SPLIT_USB_DETECT

#define CUSTOM_FONT

#define CUSTOM_LAYER_READ //if you remove this it causes issues - needs better guarding


// #define QUICK_TAP_TERM 0
// #ifdef TAPPING_TERM
//     #undef TAPPING_TERM
//     #define TAPPING_TERM 200
// #endif
#define NO_ACTION_TAPPING

// #define ENCODER_DIRECTION_FLIP

#define RGBLIGHT_SLEEP

#define RGBLIGHT_LAYERS

/* ws2812 RGB LED */
#define WS2812_DI_PIN D3

#ifdef RGBLIGHT_ENABLE
    #undef RGBLIGHT_LED_COUNT

	//#define RGBLIGHT_EFFECT_BREATHING
	#define RGBLIGHT_EFFECT_RAINBOW_MOOD
	//#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
	//#define RGBLIGHT_EFFECT_SNAKE
	//#define RGBLIGHT_EFFECT_KNIGHT
	//#define RGBLIGHT_EFFECT_CHRISTMAS
	//#define RGBLIGHT_EFFECT_STATIC_GRADIENT
	//#define RGBLIGHT_EFFECT_RGB_TEST
	//#define RGBLIGHT_EFFECT_ALTERNATING
	//#define RGBLIGHT_EFFECT_TWINKLE

    #define RGBLIGHT_LED_COUNT 12
	#undef RGBLED_SPLIT
	#define RGBLED_SPLIT { 6, 6 } // haven't figured out how to use this yet

	//#define RGBLIGHT_LED_COUNT 30
    #undef RGBLIGHT_LIMIT_VAL
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif