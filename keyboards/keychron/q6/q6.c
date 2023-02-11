/* Copyright 2022 @ Keychron (https://www.keychron.com)
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

#include "q6.h"

const matrix_row_t matrix_mask[] = {
    0b11111111111111111111,
    0b11111111111111111111,
    0b11111111111111111111,
    0b11111111111111111111,
    0b11111111111111111111,
    0b11111111111111101111,
};

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_TEAL);
}

#if defined(CAPS_WORD_ENABLE)
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;
        case KC_LSFT:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}
#endif /* CAPS_WORD_ENABLE*/

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) {
        return false;
    }
    if (index == 0) {
        default_layer_set(1UL << (active ? 2 : 0));
    }
    return true;
}

#endif // DIP_SWITCH_ENABLE

#if defined(RGB_MATRIX_ENABLE) && (defined(CAPS_LOCK_LED_INDEX) || defined(NUM_LOCK_LED_INDEX))

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                    } break;
                }
            }
            if (!rgb_matrix_is_enabled()) {
                rgb_matrix_set_flags(LED_FLAG_ALL);
                rgb_matrix_enable();
            }
            return false;
    }
    return true;
}

#if defined(NUM_LOCK_LED_INDEX)
const uint8_t num_keys[] = NUM_KEYS_GRID;
#endif // NUM_LOCK_LED_INDEX

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }

    if (IS_LAYER_ON(3)) {
        RGB_MATRIX_INDICATOR_SET_COLOR(19 ,255, 0, 0);
    } else if (IS_LAYER_ON(2)) {
        RGB_MATRIX_INDICATOR_SET_COLOR(18 ,255, 0, 0);
    } else if (IS_LAYER_ON(1)) {
        RGB_MATRIX_INDICATOR_SET_COLOR(17 ,255, 0, 0);
    } else if (IS_LAYER_ON(0)) {
        RGB_MATRIX_INDICATOR_SET_COLOR(16 ,255, 0, 0);
    } else
    {
        RGB_MATRIX_INDICATOR_SET_COLOR(16 ,0 , 0, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(17 ,0, 0, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(18 ,0, 0, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(19 ,0, 0, 0);
    }

    // RGB_MATRIX_INDICATOR_SET_COLOR(index, red, green, blue);
#    if defined(CAPS_LOCK_LED_INDEX)
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_LED_INDEX, 255, 255, 255);
    } else {
        if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_LED_INDEX, 0, 0, 0);
        }
    }
#    endif // CAPS_LOCK_LED_INDEX
#    if defined(NUM_LOCK_LED_INDEX)
    if (!host_keyboard_led_state().num_lock) {
        for (uint8_t i = 0; i < NUM_KEYS_GRID_LEN; i++)
            RGB_MATRIX_INDICATOR_SET_COLOR(num_keys[i], 255, 0, 0);
    } else {
        if (!rgb_matrix_get_flags()) {
            for (uint8_t i = 0; i < NUM_KEYS_GRID_LEN; i++)
                RGB_MATRIX_INDICATOR_SET_COLOR(NUM_LOCK_LED_INDEX, 0, 0, 0);
        }
    }
#    endif // NUM_LOCK_LED_INDEX
    return true;
}

#endif // RGB_MATRIX_ENABLE...
