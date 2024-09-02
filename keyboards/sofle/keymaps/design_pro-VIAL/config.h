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
#define DYNAMIC_KEYMAP_LAYER_COUNT 10

#define VIAL_TAP_DANCE_ENTRIES 50
#define DYNAMIC_KEYMAP_MACRO_COUNT 50
#define VIAL_COMBO_ENTRIES 50

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

/* ws2812 RGB LED */
#define WS2812_DI_PIN D3
