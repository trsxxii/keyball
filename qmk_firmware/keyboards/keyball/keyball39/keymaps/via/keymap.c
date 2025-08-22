/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"
#include "os_detection.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_MINS  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,
    KC_LCTL  , KC_LGUI  , KC_LALT  ,LSFT_T(KC_LNG2),LT(1,KC_SPC),LT(3,KC_LNG1),KC_BSPC,LT(2,KC_ENT),LSFT_T(KC_LNG2),KC_RALT,KC_RGUI, KC_RSFT
  ),

  [1] = LAYOUT_universal(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_RBRC  ,                            KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,
    KC_F5    , KC_EXLM  , S(KC_6)  ,S(KC_INT3), S(KC_8)  ,                           S(KC_INT1), KC_BTN1  , KC_PGUP  , KC_BTN2  , KC_SCLN  ,
    S(KC_EQL),S(KC_LBRC),S(KC_7)   , S(KC_2)  ,S(KC_RBRC),                            KC_LBRC  , KC_DLR   , KC_PGDN  , KC_BTN3  , KC_F11   ,
    KC_INT1  , KC_EQL   , S(KC_3)  , _______  , _______  , _______  ,      TO(2)    , TO(0)    , _______  , KC_RALT  , KC_RGUI  , KC_F12
  ),

  [2] = LAYOUT_universal(
    KC_TAB   , KC_7     , KC_8     , KC_9     , KC_MINS  ,                            KC_NUHS  , _______  , KC_BTN3  , _______  , KC_BSPC  ,
   S(KC_QUOT), KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                            S(KC_9)  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_QUOT  ,
    KC_SLSH  , KC_1     , KC_2     , KC_3     ,S(KC_MINS),                           S(KC_NUHS), KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  ,
    KC_ESC   , KC_0     , KC_DOT   , KC_DEL   , KC_ENT   , KC_BSPC  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  ,                            _______  , _______  , SSNP_HOR , SSNP_VRT , SSNP_FRE ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , SCRL_DVI ,                            _______  , _______  , _______  , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , SCRL_DVD ,                            CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE ,
    QK_BOOT  , KBC_RST  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , KBC_RST  , QK_BOOT
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    keyball_handle_auto_mouse_layer_change(state);
#endif
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

static inline void kill_auto_mouse_if_needed(void) {
    if (layer_state_is(AUTO_MOUSE_DEFAULT_LAYER)) {
        layer_off(AUTO_MOUSE_DEFAULT_LAYER);
        set_auto_mouse_timeout(get_auto_mouse_keep_time());
        keyball.total_mouse_movement = 0;
    }
}

enum custom_keycodes {
    USER0 = SAFE_RANGE, // ホールドでスクロールモード
    USER1,              // ミュート
    USER2,              // 音量アップ
    USER3,              // 音量ダウン
    USER4,              // 再生/一時停止
    USER5,              // 次のトラック
    USER6,              // 前のトラック
    USER7               // Mac用 Mission Control
};

static uint16_t user0_timer;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (IS_QK_LAYER_TAP(keycode) || IS_QK_MOD_TAP(keycode)) {
        kill_auto_mouse_if_needed();
    }

    switch (keycode) {
        case KC_LCTL:
        case KC_RCTL:
        case KC_LSFT:
        case KC_RSFT:
        case KC_LALT:
        case KC_RALT:
        case KC_LGUI:
        case KC_RGUI:
            if (record->event.pressed) {
                kill_auto_mouse_if_needed();
            }
            return true;
        
        case USER0:
            if (record->event.pressed) {
                user0_timer = timer_read();
                keyball_set_scroll_mode(true);
            } else {
                if (timer_elapsed(user0_timer) < TAPPING_TERM) {
                    register_code(KC_LCTL);
                    wait_ms(10);
                    register_code(KC_MS_BTN1);
                    wait_ms(30);
                    unregister_code(KC_MS_BTN1);
                    wait_ms(10);
                    unregister_code(KC_LCTL);
                }
                keyball_set_scroll_mode(false);
            }
            return false;

        case USER1:
            if (record->event.pressed) {
                register_code(KC_AUDIO_MUTE);
            } else {
                unregister_code(KC_AUDIO_MUTE); 
            }
            return false;

        case USER2:
            tap_code(KC_AUDIO_VOL_UP);
            return false;

        case USER3:
            tap_code(KC_AUDIO_VOL_DOWN);
            return false;

        case USER4:
            if (record->event.pressed) {
                register_code(KC_MEDIA_PLAY_PAUSE);
            } else {
                unregister_code(KC_MEDIA_PLAY_PAUSE);
            }
            return false;

        case USER5:
            tap_code(KC_MEDIA_NEXT_TRACK);
            return false;

        case USER6:
            tap_code(KC_MEDIA_PREV_TRACK);
            return false;

        case USER7:
            switch (detected_host_os()) {
                case OS_MACOS:
                    tap_code16(C(KC_UP));
                    break;
                case OS_WINDOWS:
                    if (record->event.pressed) {
                        register_code(KC_LGUI);
                        wait_ms(10);
                        register_code(KC_TAB);
                        wait_ms(30);
                        unregister_code(KC_TAB);
                    } else {
                        unregister_code(KC_LGUI);
                    }
                    break;
                default:
                    tap_code16(C(KC_UP));
                    break;
            }
            return false;

    }
    return true;
}

bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case SCRL_MO:
        case KC_MS_BTN1:
        case KC_MS_BTN2:
        case KC_MS_BTN3:
        case KC_MS_BTN4:
        case KC_MS_BTN5:
        case USER0:
        case USER7:
            return true;
    }
    return is_mouse_record_user(keycode, record);
}