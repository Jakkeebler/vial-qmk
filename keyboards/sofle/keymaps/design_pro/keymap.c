/* Copyright 2024 Jeron Kuxhausen
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
  // SOFLE RGB
#include <stdio.h>

// For Debugging
#include "print.h"

#include QMK_KEYBOARD_H

// Layer Declaration
enum sofle_layers {
    _QWERTY,
    _ILSTR,
    _LFTHND,
    _FUNCPAD,
};

// Custom Keycodes Declaration
enum custom_keycodes {
    KC_LAYER = SAFE_RANGE,
    KC_ARTBRD,
    KC_FUNC,
};

// Custom Keycode Functions
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LAYER:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                register_code(KC_LBRC);
            } else {
                unregister_code(KC_LBRC);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
            }
            return false;
        case KC_ARTBRD:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_0);
            } else {
                unregister_code(KC_0);
                unregister_code(KC_LCTL);
            }
            return false;
        case KC_FUNC:
            if (record->event.pressed) {
                layer_on(_FUNCPAD);
            } else {
                layer_off(_FUNCPAD);
            }
            return false;
    }
    return true;
}

// Tap Dance Declaration
enum {
    DANCE_ESC,
    DANCE_ENT,
    DANCE_MINS,
    DANCE_EQL,
    DANCE_LBRC,
    DANCE_RBRC,
    DANCE_F1,
    DANCE_F2,
    DANCE_F3,
    DANCE_F4,
    DANCE_F5,
    DANCE_F6,
    DANCE_F7,
    DANCE_F8,
    DANCE_F9,
    DANCE_F10,
    DANCE_F11,
    DANCE_F12,
    DANCE_0,
    DANCE_1,
    DANCE_2,
    DANCE_3,
    DANCE_5,
    DANCE_7,
    DANCE_8,
    DANCE_A,
    DANCE_B,
    DANCE_C,
    DANCE_D,
    DANCE_E,
    DANCE_F,
    DANCE_G,
    DANCE_H,
    DANCE_I,
    DANCE_J,
    DANCE_K,
    DANCE_L,
    DANCE_N,
    DANCE_O,
    DANCE_P,
    DANCE_Q,
    DANCE_R,
    DANCE_S,
    DANCE_T,
    DANCE_V,
    DANCE_W,
    DANCE_X,
    DANCE_Y,
    DANCE_Z,
    TAP_DANCE_COUNT
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD,
    TD_MORE_TAPS
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

static td_state_t dance_state[TAP_DANCE_COUNT];

td_state_t dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    } else if (state->count == 3) {
        if (state->pressed) return TD_TRIPLE_HOLD;
        else return TD_TRIPLE_TAP;
    }
    return TD_MORE_TAPS;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dance Functions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Dance Escape
void on_dance_ESC(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_ESC_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_ESC] = dance_step(state);
    switch (dance_state[DANCE_ESC]) {
        case TD_SINGLE_TAP: register_code16(KC_ESC); break;
        case TD_SINGLE_HOLD:
            layer_on(_LFTHND);
            break;
        case TD_DOUBLE_TAP:
            layer_off(_ILSTR);
            layer_on(_QWERTY);
            break;
        default: break;
    }
}

void dance_ESC_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_ESC]) {
        case TD_SINGLE_TAP: unregister_code16(KC_ESC); break;
        case TD_SINGLE_HOLD:
            layer_off(_LFTHND);
            break;
        default: break;
    }
    dance_state[DANCE_ESC] = 0;
}

// Dance Enter
void on_dance_ENT(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_ENT_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_ENT] = dance_step(state);
    switch (dance_state[DANCE_ENT]) {
        case TD_SINGLE_TAP: register_code16(KC_ENT); break;
        case TD_SINGLE_HOLD:
            layer_on(_FUNCPAD);
            break;
        default: break;
    }
}

void dance_ENT_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_ENT]) {
        case TD_SINGLE_TAP: unregister_code16(KC_ENT); break;
        case TD_SINGLE_HOLD:
            layer_off(_FUNCPAD);
            break;
        default: break;
    }
    dance_state[DANCE_ENT] = 0;
}

// Dance Minus
void on_dance_MINS(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_MINS_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_MINS] = dance_step(state);
    switch (dance_state[DANCE_MINS]) {
        case TD_SINGLE_TAP: register_code16(KC_MINS); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_MINS);
            break;
        default: break;
    }
}

void dance_MINS_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_MINS]) {
        case TD_SINGLE_TAP: unregister_code16(KC_MINS); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_MINS);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_MINS] = 0;
}


// Dance Equals
void on_dance_EQL(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_EQL_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_EQL] = dance_step(state);
    switch (dance_state[DANCE_EQL]) {
        case TD_SINGLE_TAP: register_code16(KC_EQL); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_EQL);
            break;
        default: break;
    }
}

void dance_EQL_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_EQL]) {
        case TD_SINGLE_TAP: unregister_code16(KC_EQL); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_EQL);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_EQL] = 0;
}

// Dance Left Bracket
void on_dance_LBRC(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_LBRC_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_LBRC] = dance_step(state);
    switch (dance_state[DANCE_LBRC]) {
        case TD_SINGLE_TAP: register_code16(KC_LBRC); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_LBRC);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_LBRC);
            break;
        default: break;
    }
}

void dance_LBRC_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_LBRC]) {
        case TD_SINGLE_TAP: unregister_code16(KC_LBRC); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_LBRC);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_LBRC);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_LBRC] = 0;
}

// Dance Right Bracket
void on_dance_RBRC(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_RBRC_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_RBRC] = dance_step(state);
    switch (dance_state[DANCE_RBRC]) {
        case TD_SINGLE_TAP: register_code16(KC_RBRC); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_RBRC);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_RBRC);
            break;
        default: break;
    }
}

void dance_RBRC_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_RBRC]) {
        case TD_SINGLE_TAP: unregister_code16(KC_RBRC); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_LCTL);
            unregister_code(KC_RBRC);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_LCTL);
            unregister_code(KC_LSFT);
            unregister_code(KC_RBRC);
            break;
        default: break;
    }
    dance_state[DANCE_RBRC] = 0;
}

// Dance F1
void on_dance_F1(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_F1_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_F1] = dance_step(state);
    switch (dance_state[DANCE_F1]) {
        case TD_SINGLE_TAP: register_code16(KC_F1); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_F1);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LSFT);
            register_code(KC_F1);
            break;
        case TD_TRIPLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_F1);
            break;
        default: break;
    }
}

void dance_F1_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_F1]) {
        case TD_SINGLE_TAP: unregister_code16(KC_F1); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_F1);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_F1);
            unregister_code(KC_LSFT);
            break;
        case TD_TRIPLE_TAP:
            unregister_code(KC_F1);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_F1] = 0;
}

// Dance F2
void on_dance_F2(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_F2_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_F2] = dance_step(state);
    switch (dance_state[DANCE_F2]) {
        case TD_SINGLE_TAP: register_code16(KC_F2); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_F2);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LSFT);
            register_code(KC_F2);
            break;
        case TD_TRIPLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_F2);
            break;
        default: break;
    }
}

void dance_F2_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_F2]) {
        case TD_SINGLE_TAP: unregister_code16(KC_F2); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_F2);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_F2);
            unregister_code(KC_LSFT);
            break;
        case TD_TRIPLE_TAP:
            unregister_code(KC_F2);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_F2] = 0;
}

// Dance F3
void on_dance_F3(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_F3_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_F3] = dance_step(state);
    switch (dance_state[DANCE_F3]) {
        case TD_SINGLE_TAP: register_code16(KC_F3); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_F3);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LSFT);
            register_code(KC_F3);
            break;
        case TD_TRIPLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_F3);
            break;
        default: break;
    }
}

void dance_F3_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_F3]) {
        case TD_SINGLE_TAP: unregister_code16(KC_F3); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_F3);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_F3);
            unregister_code(KC_LSFT);
            break;
        case TD_TRIPLE_TAP:
            unregister_code(KC_F3);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_F3] = 0;
}

// Dance F4
void on_dance_F4(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_F4_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_F4] = dance_step(state);
    switch (dance_state[DANCE_F4]) {
        case TD_SINGLE_TAP: register_code16(KC_F4); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_F4);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LSFT);
            register_code(KC_F4);
            break;
        case TD_TRIPLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_F4);
            break;
        default: break;
    }
}

void dance_F4_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_F4]) {
        case TD_SINGLE_TAP: unregister_code16(KC_F4); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_F4);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_F4);
            unregister_code(KC_LSFT);
            break;
        case TD_TRIPLE_TAP:
            unregister_code(KC_F4);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_F4] = 0;
}

// Dance F5
void on_dance_F5(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_F5_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_F5] = dance_step(state);
    switch (dance_state[DANCE_F5]) {
        case TD_SINGLE_TAP: register_code16(KC_F5); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_F5);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LSFT);
            register_code(KC_F5);
            break;
        case TD_TRIPLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_F5);
            break;
        default: break;
    }
}

void dance_F5_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_F5]) {
        case TD_SINGLE_TAP: unregister_code16(KC_F5); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_F5);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_F5);
            unregister_code(KC_LSFT);
            break;
        case TD_TRIPLE_TAP:
            unregister_code(KC_F5);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_F5] = 0;
}

// Dance F6
void on_dance_F6(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_F6_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_F6] = dance_step(state);
    switch (dance_state[DANCE_F6]) {
        case TD_SINGLE_TAP: register_code16(KC_F6); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_F6);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LSFT);
            register_code(KC_F6);
            break;
        case TD_TRIPLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_F6);
            break;
        default: break;
    }
}

void dance_F6_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_F6]) {
        case TD_SINGLE_TAP: unregister_code16(KC_F6); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_F6);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_F6);
            unregister_code(KC_LSFT);
            break;
        case TD_TRIPLE_TAP:
            unregister_code(KC_F6);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_F6] = 0;
}

// Dance F7
void on_dance_F7(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_F7_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_F7] = dance_step(state);
    switch (dance_state[DANCE_F7]) {
        case TD_SINGLE_TAP: register_code16(KC_F7); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_F7);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LSFT);
            register_code(KC_F7);
            break;
        case TD_TRIPLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_F7);
            break;
        default: break;
    }
}

void dance_F7_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_F7]) {
        case TD_SINGLE_TAP: unregister_code16(KC_F7); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_F7);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_F7);
            unregister_code(KC_LSFT);
            break;
        case TD_TRIPLE_TAP:
            unregister_code(KC_F7);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_F7] = 0;
}

// Dance F8
void on_dance_F8(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_F8_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_F8] = dance_step(state);
    switch (dance_state[DANCE_F8]) {
        case TD_SINGLE_TAP: register_code16(KC_F8); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_F8);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LSFT);
            register_code(KC_F8);
            break;
        case TD_TRIPLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_F8);
            break;
        default: break;
    }
}

void dance_F8_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_F8]) {
        case TD_SINGLE_TAP: unregister_code16(KC_F8); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_F8);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_F8);
            unregister_code(KC_LSFT);
            break;
        case TD_TRIPLE_TAP:
            unregister_code(KC_F8);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_F8] = 0;
}

// Dance F9
void on_dance_F9(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_F9_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_F9] = dance_step(state);
    switch (dance_state[DANCE_F9]) {
        case TD_SINGLE_TAP: register_code16(KC_F9); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_F9);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LSFT);
            register_code(KC_F9);
            break;
        case TD_TRIPLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_F9);
            break;
        default: break;
    }
}

void dance_F9_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_F9]) {
        case TD_SINGLE_TAP: unregister_code16(KC_F9); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_F9);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_F9);
            unregister_code(KC_LSFT);
            break;
        case TD_TRIPLE_TAP:
            unregister_code(KC_F9);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_F9] = 0;
}

// Dance F10
void on_dance_F10(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_F10_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_F10] = dance_step(state);
    switch (dance_state[DANCE_F10]) {
        case TD_SINGLE_TAP: register_code16(KC_F10); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_F10);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LSFT);
            register_code(KC_F10);
            break;
        case TD_TRIPLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_F10);
            break;
        default: break;
    }
}

void dance_F10_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_F10]) {
        case TD_SINGLE_TAP: unregister_code16(KC_F10); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_F10);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_F10);
            unregister_code(KC_LSFT);
            break;
        case TD_TRIPLE_TAP:
            unregister_code(KC_F10);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_F10] = 0;
}

// Dance F11
void on_dance_F11(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_F11_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_F11] = dance_step(state);
    switch (dance_state[DANCE_F11]) {
        case TD_SINGLE_TAP: register_code16(KC_F11); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_F11);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LSFT);
            register_code(KC_F11);
            break;
        case TD_TRIPLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_F11);
            break;
        default: break;
    }
}

void dance_F11_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_F11]) {
        case TD_SINGLE_TAP: unregister_code16(KC_F11); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_F11);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_F11);
            unregister_code(KC_LSFT);
            break;
        case TD_TRIPLE_TAP:
            unregister_code(KC_F11);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_F11] = 0;
}

// Dance F12
void on_dance_F12(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_F12_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_F12] = dance_step(state);
    switch (dance_state[DANCE_F12]) {
        case TD_SINGLE_TAP: register_code16(KC_F12); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_F12);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LSFT);
            register_code(KC_F12);
            break;
        case TD_TRIPLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_F12);
            break;
        default: break;
    }
}

void dance_F12_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_F12]) {
        case TD_SINGLE_TAP: unregister_code16(KC_F12); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_F12);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_F12);
            unregister_code(KC_LSFT);
            break;
        case TD_TRIPLE_TAP:
            unregister_code(KC_F12);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_F12] = 0;
}

// Dance 0
void on_dance_0(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_0_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_0] = dance_step(state);
    switch (dance_state[DANCE_0]) {
        case TD_SINGLE_TAP: register_code16(KC_0); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_0);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_0);
            break;
        default: break;
    }
}

void dance_0_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_0]) {
        case TD_SINGLE_TAP: unregister_code16(KC_0); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_0);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
            unregister_code(KC_0);
            break;
        default: break;
    }
    dance_state[DANCE_0] = 0;
}

// Dance 1
void on_dance_1(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_1_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_1] = dance_step(state);
    switch (dance_state[DANCE_1]) {
        case TD_SINGLE_TAP: register_code16(KC_1); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_1);
        default: break;
    }
}

void dance_1_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_1]) {
        case TD_SINGLE_TAP: unregister_code16(KC_1); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_1);
            unregister_code(KC_LCTL);
        default: break;
    }
    dance_state[DANCE_1] = 0;
}

// Dance 2
void on_dance_2(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_2_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_2] = dance_step(state);
    switch (dance_state[DANCE_2]) {
        case TD_SINGLE_TAP: register_code16(KC_2); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_2);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_2);
            break;
        default: break;
    }
}

void dance_2_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_2]) {
        case TD_SINGLE_TAP: unregister_code16(KC_2); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_2);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
            unregister_code(KC_2);
            break;
        default: break;
    }
    dance_state[DANCE_2] = 0;
}

// Dance 3
void on_dance_3(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_3_finished(tap_dance_state_t *state, void *user_data) {

    dance_state[DANCE_3] = dance_step(state);
    switch (dance_state[DANCE_3]) {
        case TD_SINGLE_TAP: register_code16(KC_3); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_3);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_3);
            break;
        default: break;
    }
}

void dance_3_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_3]) {
        case TD_SINGLE_TAP: unregister_code16(KC_3); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_3);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_3);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_3] = 0;
}

// Dance 5
void on_dance_5(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_5_finished(tap_dance_state_t *state, void *user_data) {

    dance_state[DANCE_5] = dance_step(state);
    switch (dance_state[DANCE_5]) {
        case TD_SINGLE_TAP: register_code16(KC_5); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_5);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_5);
            break;
        default: break;
    }
}

void dance_5_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_5]) {
        case TD_SINGLE_TAP: unregister_code16(KC_5); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_5);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_5);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_5] = 0;
}

// Dance 7
void on_dance_7(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_7_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_7] = dance_step(state);
    switch (dance_state[DANCE_7]) {
        case TD_SINGLE_TAP: register_code16(KC_7); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_7);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_7);
            break;
        default: break;
    }
}

void dance_7_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_7]) {
        case TD_SINGLE_TAP: unregister_code16(KC_7); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_7);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_7);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_7] = 0;
}

// Dance 8
void on_dance_8(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_8_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_8] = dance_step(state);
    switch (dance_state[DANCE_8]) {
        case TD_SINGLE_TAP: register_code16(KC_8); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_8);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_8);
            break;
        default: break;
    }
}

void dance_8_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_8]) {
        case TD_SINGLE_TAP: unregister_code16(KC_8); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_8);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_8);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_8] = 0;
}

// Dance A
void on_dance_A(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_A_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_A] = dance_step(state);
    switch (dance_state[DANCE_A]) {
        case TD_SINGLE_TAP: register_code16(KC_A); break;
        case TD_SINGLE_HOLD: register_code16(KC_LGUI); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_A);
            break;
        default: break;
    }
}

void dance_A_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_A]) {
        case TD_SINGLE_TAP: unregister_code16(KC_A); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_LGUI); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_A);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_A] = 0;
}

// Dance B
void on_dance_B(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_B_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_B] = dance_step(state);
    switch (dance_state[DANCE_B]) {
        case TD_SINGLE_TAP: register_code16(KC_B); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_B);
            break;
        default: break;
    }
}

void dance_B_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_B]) {
        case TD_SINGLE_TAP: unregister_code16(KC_B); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_B);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_B] = 0;
}

// Dance C
void on_dance_C(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_C_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_C] = dance_step(state);
    switch (dance_state[DANCE_C]) {
        case TD_SINGLE_TAP: register_code16(KC_C); break;
        case TD_SINGLE_HOLD:
            register_code(KC_LSFT);
            register_code(KC_C);
            break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_C);
            break;
        default: break;
    }
}

void dance_C_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_C]) {
        case TD_SINGLE_TAP: unregister_code16(KC_C); break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_C);
            unregister_code(KC_LSFT);
            break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_C);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_C] = 0;
}

// Dance D
void on_dance_D(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_D_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_D] = dance_step(state);
    switch (dance_state[DANCE_D]) {
        case TD_SINGLE_TAP: register_code16(KC_D); break;
        case TD_SINGLE_HOLD: register_code16(KC_LALT); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_D);
            break;
        default: break;
    }
}

void dance_D_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_D]) {
        case TD_SINGLE_TAP: unregister_code16(KC_D); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_LALT); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_D);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_D] = 0;
}

// Dance E
void on_dance_E(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_E_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_E] = dance_step(state);
    switch (dance_state[DANCE_E]) {
        case TD_SINGLE_TAP: register_code16(KC_E); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_E);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_E);
            break;
        default: break;
    }
}

void dance_E_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_E]) {
        case TD_SINGLE_TAP: unregister_code16(KC_E); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_E);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_E);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_E] = 0;
}

// Dance F
void on_dance_F(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_F_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_F] = dance_step(state);
    switch (dance_state[DANCE_F]) {
        case TD_SINGLE_TAP: register_code16(KC_F); break;
        case TD_SINGLE_HOLD: register_code16(KC_LCTL); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_F);
            break;
        default: break;
    }
}

void dance_F_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_F]) {
        case TD_SINGLE_TAP: unregister_code16(KC_F); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_LCTL); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_F);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_F] = 0;
}

// Dance G
void on_dance_G(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_G_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_G] = dance_step(state);
    switch (dance_state[DANCE_G]) {
        case TD_SINGLE_TAP: register_code16(KC_G); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_G);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_G);
            break;
        default: break;
    }
}

void dance_G_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_G]) {
        case TD_SINGLE_TAP: unregister_code16(KC_G); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_G);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_G);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_G] = 0;
}

// Dance H
void on_dance_H(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_H_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_H] = dance_step(state);
    switch (dance_state[DANCE_H]) {
        case TD_SINGLE_TAP: register_code16(KC_H); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_H);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_H);
            break;
        default: break;
    }
}

void dance_H_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_H]) {
        case TD_SINGLE_TAP: unregister_code16(KC_H); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_H);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_H);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_H] = 0;
}

// Dance I
void on_dance_I(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_I_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_I] = dance_step(state);
    switch (dance_state[DANCE_I]) {
        case TD_SINGLE_TAP: register_code16(KC_I); break;
        case TD_SINGLE_HOLD:
            layer_on(_ILSTR);
            break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_I);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_I);
            break;
        case TD_TRIPLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_I);
            break;
        default: break;
    }
}

void dance_I_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_I]) {
        case TD_SINGLE_TAP: unregister_code16(KC_I); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_I);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_I);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
            break;
        case TD_TRIPLE_TAP:
            unregister_code(KC_I);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_I] = 0;
}

// Dance J
void on_dance_J(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_J_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_J] = dance_step(state);
    switch (dance_state[DANCE_J]) {
        case TD_SINGLE_TAP: register_code16(KC_J); break;
        case TD_SINGLE_HOLD: register_code16(KC_RCTL); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_J);
            break;
        default: break;
    }
}

void dance_J_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_J]) {
        case TD_SINGLE_TAP: unregister_code16(KC_J); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_RCTL); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_J);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_J] = 0;
}

// Dance K
void on_dance_K(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_K_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_K] = dance_step(state);
    switch (dance_state[DANCE_K]) {
        case TD_SINGLE_TAP: register_code16(KC_K); break;
        case TD_SINGLE_HOLD: register_code16(KC_RALT); break;
        default: break;
    }
}

void dance_K_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_K]) {
        case TD_SINGLE_TAP: unregister_code16(KC_K); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_RALT); break;
        default: break;
    }
    dance_state[DANCE_K] = 0;
}

// Dance L
void on_dance_L(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_L_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_L] = dance_step(state);
    switch (dance_state[DANCE_L]) {
        case TD_SINGLE_TAP: register_code16(KC_L); break;
        case TD_SINGLE_HOLD: register_code16(KC_RGUI); break;
        default: break;
    }
}

void dance_L_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_L]) {
        case TD_SINGLE_TAP: unregister_code16(KC_L); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_RGUI); break;
        default: break;
    }
    dance_state[DANCE_L] = 0;
}

// Dance N
void on_dance_N(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_N_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_N] = dance_step(state);
    switch (dance_state[DANCE_N]) {
        case TD_SINGLE_TAP: register_code16(KC_N); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_N);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_N);
            break;
        default: break;
    }
}

void dance_N_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_N]) {
        case TD_SINGLE_TAP: unregister_code16(KC_N); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_N);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_N);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_N] = 0;
}

// Dance O
void on_dance_O(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_O_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_O] = dance_step(state);
    switch (dance_state[DANCE_O]) {
        case TD_SINGLE_TAP: register_code16(KC_O); break;
        case TD_SINGLE_HOLD:
            register_code(KC_LSFT);
            register_code(KC_O);
            break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_O);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_O);
            break;
        default: break;
    }
}

void dance_O_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_O]) {
        case TD_SINGLE_TAP: unregister_code16(KC_O); break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_O);
            unregister_code(KC_LSFT);
            break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_O);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_O);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_O] = 0;
}

// Dance P
void on_dance_P(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_P_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_P] = dance_step(state);
    switch (dance_state[DANCE_P]) {
        case TD_SINGLE_TAP: register_code16(KC_P); break;
        case TD_SINGLE_HOLD:
            register_code(KC_LSFT);
            register_code(KC_P);
            break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_P);
            break;
        default: break;
    }
}

void dance_P_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_P]) {
        case TD_SINGLE_TAP: unregister_code16(KC_P); break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_P);
            unregister_code(KC_LSFT);
            break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_P);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_P] = 0;
}

// Dance Q
void on_dance_Q(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_Q_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_Q] = dance_step(state);
    switch (dance_state[DANCE_Q]) {
        case TD_SINGLE_TAP: register_code16(KC_Q); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_Q);
            break;
        default: break;
    }
}

void dance_Q_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_Q]) {
        case TD_SINGLE_TAP: unregister_code16(KC_Q); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_Q);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_Q] = 0;
}

// Dance R
void on_dance_R(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_R_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_R] = dance_step(state);
    switch (dance_state[DANCE_R]) {
        case TD_SINGLE_TAP: register_code16(KC_R); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_R);
        default: break;
    }
}

void dance_R_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_R]) {
        case TD_SINGLE_TAP: unregister_code16(KC_R); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_R);
            unregister_code(KC_LCTL);
        default: break;
    }
    dance_state[DANCE_R] = 0;
}

// Dance S
void on_dance_S(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_S_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_S] = dance_step(state);
    switch (dance_state[DANCE_S]) {
        case TD_SINGLE_TAP: register_code16(KC_S); break;
        case TD_SINGLE_HOLD: register_code16(KC_LSFT); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_S);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_S);
            break;
        case TD_TRIPLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_S);
            break;
        default: break;
    }
}

void dance_S_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_S]) {
        case TD_SINGLE_TAP: unregister_code16(KC_S); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_LSFT); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_S);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_S);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        case TD_TRIPLE_TAP:
            unregister_code(KC_S);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_S] = 0;
}

// Dance T
void on_dance_T(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_T_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_T] = dance_step(state);
    switch (dance_state[DANCE_T]) {
        case TD_SINGLE_TAP: register_code16(KC_T); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_T);
        default: break;
    }
}

void dance_T_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_T]) {
        case TD_SINGLE_TAP: unregister_code16(KC_T); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_T);
            unregister_code(KC_LCTL);
        default: break;
    }
    dance_state[DANCE_T] = 0;
}

// Dance V
void on_dance_V(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_V_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_V] = dance_step(state);
    switch (dance_state[DANCE_V]) {
        case TD_SINGLE_TAP: register_code16(KC_V); break;
        case TD_SINGLE_HOLD:
            register_code(KC_LSFT);
            register_code(KC_V);
            break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_V);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_V);
            break;
        case TD_TRIPLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_V);
            break;
        default: break;
    }
}

void dance_V_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_V]) {
        case TD_SINGLE_TAP: unregister_code16(KC_V); break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_V);
            unregister_code(KC_LSFT);
            break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_V);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_V);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        case TD_TRIPLE_TAP:
            unregister_code(KC_V);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_V] = 0;
}

// Dance W
void on_dance_W(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_W_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_W] = dance_step(state);
    switch (dance_state[DANCE_W]) {
        case TD_SINGLE_TAP: register_code16(KC_W); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_W);
            break;
        default: break;
    }
}

void dance_W_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_W]) {
        case TD_SINGLE_TAP: unregister_code16(KC_W); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_W);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_W] = 0;
}

// Dance X
void on_dance_X(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_X_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_X] = dance_step(state);
    switch (dance_state[DANCE_X]) {
        case TD_SINGLE_TAP: register_code16(KC_X); break;
        case TD_SINGLE_HOLD:
            register_code(KC_LSFT);
            register_code(KC_X);
            break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_X);
            break;
        default: break;
    }
}

void dance_X_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_X]) {
        case TD_SINGLE_TAP: unregister_code16(KC_X); break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_X);
            unregister_code(KC_LSFT);
            break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_X);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_X] = 0;
}

// Dance Y
void on_dance_Y(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_Y_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_Y] = dance_step(state);
    switch (dance_state[DANCE_Y]) {
        case TD_SINGLE_TAP: register_code16(KC_Y); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_Y);
        case TD_TRIPLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_Y);
            break;
        default: break;
    }
}

void dance_Y_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_Y]) {
        case TD_SINGLE_TAP: unregister_code16(KC_Y); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_Y);
            unregister_code(KC_LCTL);
        case TD_TRIPLE_TAP:
            unregister_code(KC_Y);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_Y] = 0;
}

// Dance Z
void on_dance_Z(tap_dance_state_t *state, void *user_data) {
    // Used for Immediate Actions
}

void dance_Z_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DANCE_Z] = dance_step(state);
    switch (dance_state[DANCE_Z]) {
        case TD_SINGLE_TAP: register_code16(KC_Z); break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_Z);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_Z);
            break;
        default: break;
    }
}

void dance_Z_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DANCE_Z]) {
        case TD_SINGLE_TAP: unregister_code16(KC_Z); break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_Z);
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_Z);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            break;
        default: break;
    }
    dance_state[DANCE_Z] = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Keymaps
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Qwerty Layer
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [_QWERTY] = LAYOUT(
    KC_ESC,     KC_1,           KC_2,          KC_3,            KC_4,           KC_5,                                               KC_6,           KC_7,       KC_8,           KC_9,       KC_0,       KC_MINS,
    KC_TAB,     KC_Q,           TD(DANCE_W),   KC_E,            KC_R,           TD(DANCE_T),                                        KC_Y,           KC_U,       TD(DANCE_I),    KC_O,       KC_P,       KC_BSPC,
    KC_F15,     TD(DANCE_A),    TD(DANCE_S),   TD(DANCE_D),     TD(DANCE_F),    KC_G,                                               KC_H,           KC_J,       KC_K,           KC_L,       KC_SCLN,    KC_QUOT,
    KC_LSFT,    TD(DANCE_Z),    TD(DANCE_X),   TD(DANCE_C),     TD(DANCE_V),    KC_B,          KC_END,           KC_HOME,           TD(DANCE_N),    KC_M,       KC_COMM,        KC_DOT,     KC_SLSH,    KC_LSFT,
                                KC_LCTL,       OSL(_FUNCPAD),   KC_BSPC,        KC_SPC,        TD(DANCE_ENT),    TD(DANCE_ENT),     KC_SPC,         KC_BSPC,    OSL(_FUNCPAD),  KC_NO
),
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Illustrator Layer
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [_ILSTR] = LAYOUT(
    TD(DANCE_ESC),  TD(DANCE_1),    TD(DANCE_2),    TD(DANCE_3),    KC_4,           TD(DANCE_5),                                    KC_6,           TD(DANCE_7),    TD(DANCE_8),    KC_9,           TD(DANCE_0),    KC_MINS,
    KC_TAB,         KC_Q,           TD(DANCE_W),    TD(DANCE_E),    KC_R,           TD(DANCE_T),                                    TD(DANCE_Y),    KC_U,           TD(DANCE_I),    TD(DANCE_O),    TD(DANCE_P),    KC_BSPC,
    KC_F15,         TD(DANCE_A),    TD(DANCE_S),    TD(DANCE_D),    TD(DANCE_F),    TD(DANCE_G),                                    TD(DANCE_H),    TD(DANCE_J),    TD(DANCE_K),    TD(DANCE_L),    KC_SCLN,        KC_QUOT,
    KC_LSFT,        TD(DANCE_Z),    TD(DANCE_X),    TD(DANCE_C),    TD(DANCE_V),    TD(DANCE_B),    KC_ARTBRD,      KC_LAYER,       TD(DANCE_N),    KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,        KC_LSFT,
                                    KC_LCTL,        OSL(_FUNCPAD),  KC_BSPC,        KC_SPC,         TD(DANCE_ENT),  TD(DANCE_ENT),  KC_SPC,         KC_BSPC,        OSL(_FUNCPAD),  KC_NO
),
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Left Hand Layer
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [_LFTHND] = LAYOUT(
  TD(DANCE_ESC),   KC_6,            TD(DANCE_7),    TD(DANCE_8),    KC_9,           TD(DANCE_0),                                    KC_6,          TD(DANCE_7),  TD(DANCE_8),       KC_9,           TD(DANCE_0),    KC_MINS,
  KC_TAB,          TD(DANCE_Y),     KC_U,           TD(DANCE_I),    TD(DANCE_O),    TD(DANCE_P),                                    TD(DANCE_Y),   KC_U,         TD(DANCE_I),       TD(DANCE_O),    TD(DANCE_P),    KC_BSPC,
  KC_F15,          TD(DANCE_H),     TD(DANCE_J),    TD(DANCE_K),    TD(DANCE_L),    KC_SCLN,                                        TD(DANCE_H),   TD(DANCE_J),  TD(DANCE_K),       TD(DANCE_L),    KC_SCLN,        KC_QUOT,
  KC_LSFT,         TD(DANCE_N),     KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,        KC_LAYER,       KC_LAYER,       TD(DANCE_N),   KC_M,         KC_COMM,           KC_DOT,         KC_SLSH,        KC_LSFT,
                                    KC_LCTL,        OSL(_FUNCPAD),  KC_BSPC,        KC_SPC,         TD(DANCE_ENT),  TD(DANCE_ENT),  KC_SPC,        KC_BSPC,      OSL(_FUNCPAD),     KC_NO
),
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Layer
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
[_FUNCPAD] = LAYOUT(
    KC_ESC,     TD(DANCE_F1),   TD(DANCE_F2),   TD(DANCE_F3),   TD(DANCE_F4),   TD(DANCE_F5),                           KC_EQL,     KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,
    KC_TAB,     TD(DANCE_F6),   TD(DANCE_F7),   TD(DANCE_F8),   TD(DANCE_F9),   TD(DANCE_F10),                          KC_SLSH,    KC_7,   KC_8,   KC_9,    KC_NO,   KC_BSPC,
    KC_NO,      TD(DANCE_F11),  KC_NO,          KC_UP,          KC_NO,          TD(DANCE_F12),                          KC_MINS,    KC_4,   KC_5,   KC_6,    KC_NO,   KC_DEL,
    KC_LSFT,    KC_NO,          KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_NO,          KC_NO,      KC_NO,      KC_PLUS,    KC_1,   KC_2,   KC_3,    KC_NO,   KC_RSFT,
                                QK_BOOT,        _______,        _______,        KC_SPC,         KC_ENT,     KC_ENT,     KC_SPC,     KC_0,   KC_0,   KC_DOT
),

};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OLED Functions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Cool Images
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

static void render_qwerty(void) {
    static const char PROGMEM qwerty_logo[] = {
        // 'QWERTY', 128x32px
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x80, 0xc0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0, 0xe0, 0xc0, 0x00, 0x00, 0x60, 0xe0,
        0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0,
        0xe0, 0xe0, 0xe0, 0x60, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
        0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0,
        0x80, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
        0x00, 0x00, 0x60, 0xe0, 0xe0, 0xe0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe,
        0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x1f,
        0xff, 0xff, 0xff, 0xfe, 0x00, 0xe0, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xf0, 0x00, 0xfc, 0xff,
        0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1,
        0xe1, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xc1, 0xe1, 0xff, 0xff, 0xff, 0x7f,
        0x3f, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 0x01,
        0x00, 0x00, 0x00, 0x03, 0x0f, 0x7f, 0xff, 0xff, 0xfc, 0xf8, 0xff, 0xff, 0x7f, 0x1f, 0x03, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f,
        0xff, 0xff, 0xff, 0xff, 0xe0, 0x80, 0x80, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00,
        0x03, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff,
        0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1,
        0xc1, 0xc0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x03, 0x03, 0xff, 0xff, 0xff, 0xff,
        0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x03, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0f, 0x1f, 0x1f, 0x0c, 0x08, 0x00, 0x00,
        0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03,
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
        0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03,
        0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    oled_write_raw_P(qwerty_logo, sizeof(qwerty_logo));
}

static void render_illstr(void) {
    static const char PROGMEM ilstr_logo[] = {
        // 'ILLUSTRATOR', 128x32px
        0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0,
        0xe0, 0xc0, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0,
        0xe0, 0xc0, 0xc0, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0,
        0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
        0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0x80, 0x00,
        0x00, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
        0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xf1, 0xe1,
        0xcf, 0x8f, 0x0f, 0x0f, 0x00, 0x01, 0x03, 0x03, 0xff, 0xff, 0xff, 0xff, 0x03, 0x03, 0x03, 0x01,
        0x00, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xc1, 0xe3, 0xff, 0xff, 0x7f, 0x1e, 0x00, 0x00, 0x00, 0xc0,
        0xff, 0xff, 0xff, 0x07, 0xff, 0xff, 0xfe, 0x80, 0x00, 0x03, 0x03, 0x03, 0xff, 0xff, 0xff, 0xff,
        0x03, 0x03, 0x03, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0x03, 0xff, 0xff, 0xff, 0xfe,
        0x00, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xc1, 0xc3, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xc0, 0xc0,
        0xc0, 0xc0, 0x00, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0xff, 0xff,
        0xff, 0xff, 0x80, 0x80, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xf0, 0xf0, 0xf1, 0xc3, 0x83, 0x87,
        0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
        0x00, 0xff, 0xff, 0xff, 0xff, 0x03, 0x03, 0x0f, 0xff, 0xff, 0xfe, 0xfc, 0x00, 0x00, 0xf0, 0xff,
        0xff, 0xff, 0x7d, 0x78, 0x7f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
        0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x80, 0x80, 0xc0, 0xff, 0xff, 0xff, 0x7f,
        0x00, 0xff, 0xff, 0xff, 0xff, 0x07, 0x03, 0x07, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
        0x07, 0x07, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x01, 0x03,
        0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x07, 0x07,
        0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x07, 0x07,
        0x07, 0x03, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x01, 0x00,
        0x00, 0x03, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00
    };

    oled_write_raw_P(ilstr_logo, sizeof(ilstr_logo));
}

static void render_funct(void) {
    static const char PROGMEM func_logo[] = {
        // 'FUNCTION', 128x32px
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
        0xe0, 0xe0, 0xe0, 0xc0, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0,
        0xe0, 0xe0, 0xe0, 0x00, 0x00, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0,
        0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
        0xc0, 0x80, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
        0xe0, 0xc0, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0,
        0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
        0x80, 0x00, 0x00, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xe3, 0xe3,
        0xe3, 0xe3, 0xe3, 0x01, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff,
        0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xc0, 0xff, 0xff,
        0xff, 0xff, 0xff, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 0x03, 0x1f, 0x1f,
        0x1f, 0x1f, 0x1e, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x03,
        0x03, 0x01, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
        0x01, 0x01, 0x01, 0x07, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xfc, 0xe0, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x03, 0x03,
        0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x80, 0x80, 0xff, 0xff,
        0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x0f, 0x7f, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x80, 0x80, 0x80, 0xc0, 0xfc, 0xfc,
        0xfc, 0xfc, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
        0x80, 0x80, 0x80, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00,
        0x07, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
        0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07,
        0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
        0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x03, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07,
        0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x02,
        0x00, 0x00, 0x01, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    oled_write_raw_P(func_logo, sizeof(func_logo));
}

static void render_lfthand(void) {
    static const char PROGMEM lfthand_logo[] = {
        // 'SWTICH', 128x32px
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0x80,
        0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x00,
        0x00, 0x00, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00,
        0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00,
        0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0xe0,
        0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xf1, 0xe1, 0xc1, 0xcf, 0x8f, 0x8f, 0x0f,
        0x04, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0xfc, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xfe,
        0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
        0x01, 0x03, 0x03, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0xff,
        0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 0x03, 0x1f, 0x1f, 0x1f, 0x1f, 0x1e, 0x00, 0x00, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xc0, 0xe0, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf1, 0xc3, 0x83, 0x87, 0x8f, 0xff, 0xff, 0xff, 0xfe,
        0x38, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0x3f, 0x00, 0x1f, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
        0xff, 0xff, 0xff, 0xff, 0x80, 0x80, 0x80, 0xc0, 0xfc, 0xfc, 0xfc, 0xfc, 0x7c, 0x00, 0x00, 0xff,
        0xff, 0xff, 0xff, 0xff, 0x03, 0x03, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x01,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07,
        0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x07,
        0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    oled_write_raw_P(lfthand_logo, sizeof(lfthand_logo));
}

static void print_status_logo(void) {
    oled_clear();

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            render_qwerty();
            break;
        case _ILSTR:
            render_illstr();
            break;
        case _LFTHND:
            render_lfthand();
            break;
        case _FUNCPAD:
            render_funct();
            break;
        default:
            render_logo();
            break;
    }
}

// oled_rotation_t oled_init_user(oled_rotation_t rotation) {
//     if (is_keyboard_master()) {
//         return OLED_ROTATION_270;
//     }
//     return rotation;
// }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_logo();
        // print_status_narrow();
    } else {
        render_logo();
        // print_status_logo();
        // print_status_narrow();
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Encoder Functions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool encoder_update_user(uint8_t index, bool clockwise)
{
  // Print the current layer for debugging
  printf("Current layer: %d\n", get_highest_layer(layer_state));

  if (index == 0)
  {
    switch (get_highest_layer(layer_state)) {
    case _QWERTY:
    case _FUNCPAD:
      if (clockwise) {
        register_code(KC_WH_D);
        unregister_code(KC_WH_D);
      } else {
        register_code(KC_WH_U);
        unregister_code(KC_WH_U);
      }
      break;
    case _ILSTR:
      if (clockwise) {
        register_code(KC_LCTL);
        register_code(KC_EQL);
        unregister_code(KC_EQL);
        unregister_code(KC_LCTL);
      } else {
        register_code(KC_LCTL);
        register_code(KC_MINS);
        unregister_code(KC_MINS);
        unregister_code(KC_LCTL);
      }
      break;
    case _LFTHND:
      if (clockwise) {
        register_code(KC_LCTL);
        register_code(KC_RBRC);
        unregister_code(KC_RBRC);
        unregister_code(KC_LCTL);
      } else {
        register_code(KC_LCTL);
        register_code(KC_LBRC);
        unregister_code(KC_LBRC);
        unregister_code(KC_LCTL);
      }
      break;
    default:
      if (clockwise) {
        register_code(KC_D);
        unregister_code(KC_D);
      } else {
        register_code(KC_U);
        unregister_code(KC_U);
      }
      break;
    }
  }
  else if (index == 1)
  {
    switch (get_highest_layer(layer_state)) {
    case _QWERTY:
    case _FUNCPAD:
      if (clockwise) {
        register_code(KC_WH_D);
        unregister_code(KC_WH_D);
      } else {
        register_code(KC_WH_U);
        unregister_code(KC_WH_U);
      }
      break;
    case _ILSTR:
      if (clockwise) {
        register_code(KC_LCTL);
        register_code(KC_RBRC);
        unregister_code(KC_RBRC);
        unregister_code(KC_LCTL);
      } else {
        register_code(KC_LCTL);
        register_code(KC_LBRC);
        unregister_code(KC_LBRC);
        unregister_code(KC_LCTL);
      }
      break;
    case _LFTHND:
      if (clockwise) {
        register_code(KC_LCTL);
        register_code(KC_RBRC);
        unregister_code(KC_RBRC);
        unregister_code(KC_LCTL);
      } else {
        register_code(KC_LCTL);
        register_code(KC_LBRC);
        unregister_code(KC_LBRC);
        unregister_code(KC_LCTL);
      }
      break;
    default:
      if (clockwise) {
        register_code(KC_WH_D);
        unregister_code(KC_WH_D);
      } else {
        register_code(KC_WH_U);
        unregister_code(KC_WH_U);
      }
      break;
    }
  }

  return false;
}

tap_dance_action_t tap_dance_actions[] = {
        [DANCE_ESC] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_ESC, dance_ESC_finished, dance_ESC_reset),
        [DANCE_ENT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_ENT, dance_ENT_finished, dance_ENT_reset),
        [DANCE_MINS] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_MINS, dance_MINS_finished, dance_MINS_reset),
        [DANCE_EQL] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_EQL, dance_EQL_finished, dance_EQL_reset),
        [DANCE_LBRC] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_LBRC, dance_LBRC_finished, dance_LBRC_reset),
        [DANCE_RBRC] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_RBRC, dance_RBRC_finished, dance_RBRC_reset),
        [DANCE_F1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_F1, dance_F1_finished, dance_F1_reset),
        [DANCE_F2] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_F2, dance_F2_finished, dance_F2_reset),
        [DANCE_F3] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_F3, dance_F3_finished, dance_F3_reset),
        [DANCE_F4] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_F4, dance_F4_finished, dance_F4_reset),
        [DANCE_F5] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_F5, dance_F5_finished, dance_F5_reset),
        [DANCE_F6] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_F6, dance_F6_finished, dance_F6_reset),
        [DANCE_F7] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_F7, dance_F7_finished, dance_F7_reset),
        [DANCE_F8] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_F8, dance_F8_finished, dance_F8_reset),
        [DANCE_F9] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_F9, dance_F9_finished, dance_F9_reset),
        [DANCE_F10] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_F10, dance_F10_finished, dance_F10_reset),
        [DANCE_F11] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_F11, dance_F11_finished, dance_F11_reset),
        [DANCE_F12] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_F12, dance_F12_finished, dance_F12_reset),
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
        [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
        [DANCE_3] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_3, dance_3_finished, dance_3_reset),
        [DANCE_5] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_5, dance_5_finished, dance_5_reset),
        [DANCE_7] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_7, dance_7_finished, dance_7_reset),
        [DANCE_8] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_8, dance_8_finished, dance_8_reset),
        [DANCE_A] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_A, dance_A_finished, dance_A_reset),
        [DANCE_B] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_B, dance_B_finished, dance_B_reset),
        [DANCE_C] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_C, dance_C_finished, dance_C_reset),
        [DANCE_D] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_D, dance_D_finished, dance_D_reset),
        [DANCE_E] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_E, dance_E_finished, dance_E_reset),
        [DANCE_F] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_F, dance_F_finished, dance_F_reset),
        [DANCE_G] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_G, dance_G_finished, dance_G_reset),
        [DANCE_H] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_H, dance_H_finished, dance_H_reset),
        [DANCE_I] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_I, dance_I_finished, dance_I_reset),
        [DANCE_J] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_J, dance_J_finished, dance_J_reset),
        [DANCE_K] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_K, dance_K_finished, dance_K_reset),
        [DANCE_L] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_L, dance_L_finished, dance_L_reset),
        [DANCE_N] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_N, dance_N_finished, dance_N_reset),
        [DANCE_O] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_O, dance_O_finished, dance_O_reset),
        [DANCE_P] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_P, dance_P_finished, dance_P_reset),
        [DANCE_Q] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_Q, dance_Q_finished, dance_Q_reset),
        [DANCE_R] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_R, dance_R_finished, dance_R_reset),
        [DANCE_S] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_S, dance_S_finished, dance_S_reset),
        [DANCE_T] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_T, dance_T_finished, dance_T_reset),
        [DANCE_V] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_V, dance_V_finished, dance_V_reset),
        [DANCE_W] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_W, dance_W_finished, dance_W_reset),
        [DANCE_X] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_X, dance_X_finished, dance_X_reset),
        [DANCE_Y] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_Y, dance_Y_finished, dance_Y_reset),
        [DANCE_Z] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_Z, dance_Z_finished, dance_Z_reset),
};
