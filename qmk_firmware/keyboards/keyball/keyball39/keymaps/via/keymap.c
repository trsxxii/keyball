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

enum custom_keycodes {
    USER0 = SAFE_RANGE, // ホールドでスクロールモード
    USER1,              // ミュート
    USER2,              // 音量アップ
    USER3,              // 音量ダウン
    USER4,              // 再生/一時停止
    USER5,              // 次のトラック
    USER6,              // 前のトラック
    USER7,              // Mission Control
    USER8               // Ctrl + Shift
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Layer 0 (Base)
  [0] = LAYOUT_universal(
    KC_Q           , KC_W           , KC_E           , KC_R           , KC_T           ,                            KC_Y           , KC_U           , KC_I           , KC_O           , KC_P           ,
    KC_A           , KC_S           , KC_D           , KC_F           , LT(3,KC_G)     ,                            LT(4,KC_H)     , KC_J           , KC_K           , KC_L           , KC_MINUS       ,
    KC_Z           , KC_X           , KC_C           , KC_V           , KC_B           ,                            KC_N           , KC_M           , KC_COMM        , KC_DOT         , KC_SLSH        ,
    USER8          , KC_LGUI        , KC_LALT        , LSFT_T(KC_LNG2), LT(1,KC_SPC)   , LCTL_T(KC_LNG1),  KC_BSPC, LT(2,KC_ENT)   , _______        , _______        , _______        , KC_GRV
  ),

  // Layer 1 (Navigation)
  [1] = LAYOUT_universal(
    KC_ESC         , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        ,                            XXXXXXX        , KC_HOME        , KC_UP          , KC_END         , XXXXXXX        ,
    KC_TAB         , A(KC_1)        , A(KC_2)        , A(KC_3)        , XXXXXXX        ,                            XXXXXXX        , KC_LEFT        , KC_DOWN        , KC_RIGHT       , KC_PAGE_UP     ,
    XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        ,                            XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , KC_PAGE_DOWN   ,
    XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        ,  KC_DEL , KC_LSFT        , XXXXXXX        , XXXXXXX        , XXXXXXX      , TT(5)
  ),

  // Layer 2 (Symbols)
  [2] = LAYOUT_universal(
    KC_QUOT        , KC_DQUO        , KC_EXLM        , XXXXXXX        , KC_ASTR        ,                            XXXXXXX        , KC_UNDS        , KC_PIPE        , XXXXXXX        , KC_PERC        ,
    KC_AT          , KC_SCLN        , KC_DLR         , XXXXXXX        , XXXXXXX        ,                            KC_HASH        , KC_PLUS        , XXXXXXX        , KC_EQL         , XXXXXXX        ,
    XXXXXXX        , XXXXXXX        , KC_COLN        , KC_CIRC        , KC_BSLS        ,                            KC_AMPR        , KC_MINS        , XXXXXXX        , XXXXXXX        , XXXXXXX        ,
    XXXXXXX        , XXXXXXX        , XXXXXXX        , _______        , _______        , _______        , _______ , _______        , _______        , _______        , _______        , TT(6)
  ),

  // Layer 3 (Brackets)
  [3] = LAYOUT_universal(
    KC_CAPS        , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        ,                            XXXXXXX        , XXXXXXX        , KC_LCBR        , KC_RCBR        , XXXXXXX        ,
    XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        ,                            XXXXXXX        , XXXXXXX        , KC_LPRN        , KC_RPRN        , XXXXXXX        ,
    XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        ,                            XXXXXXX        , XXXXXXX        , KC_LBRC        , KC_RBRC        , XXXXXXX        ,
    XXXXXXX        , XXXXXXX        , XXXXXXX        , _______        , _______        , _______        , _______ , _______        , _______        , _______        , _______        , XXXXXXX
  ),

  // Layer 4 (Numpad + Media keys)
  [4] = LAYOUT_universal(
    XXXXXXX        , KC_1           , KC_2           , KC_3           , XXXXXXX        ,                            XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        ,
    XXXXXXX        , KC_4           , KC_5           , KC_6           , KC_DOT         ,                            XXXXXXX        , XXXXXXX        , USER3          , USER1          , USER2          ,
    XXXXXXX        , KC_7           , KC_8           , KC_9           , KC_SLSH        ,                            XXXXXXX        , XXXXXXX        , USER6          , USER4          , USER5          ,
    XXXXXXX        , XXXXXXX        , KC_0           , _______        , _______        , _______        , _______ , _______        , _______        , _______        , _______        , XXXXXXX
  ),

  // Layer 5 (Auto Mouse Layer)
  [5] = LAYOUT_universal(
    _______        , _______        , _______        , _______        , _______        ,                            _______        , _______        , _______        , _______        , _______        ,
    _______        , _______        , _______        , _______        , _______        ,                            _______        , KC_BTN1        , USER0          , KC_BTN2        , _______        ,
    _______        , _______        , _______        , _______        , _______        ,                            _______        , KC_BTN4        , USER7          , KC_BTN5        , _______        ,
    _______        , _______        , _______        , _______        , _______        , _______        , _______ , _______        , _______        , _______        , _______        , _______
  ),

  // Layer 6 (Function + Kb codes)
  [6] = LAYOUT_universal(
    XXXXXXX        , KC_F1          , KC_F2          , KC_F3          , XXXXXXX        ,                            XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , KBC_SAVE       ,
    XXXXXXX        , KC_F4          , KC_F5          , KC_F6          , XXXXXXX        ,                            CPI_I100       , SCRL_DVI       , XXXXXXX        , XXXXXXX        , XXXXXXX        ,
    XXXXXXX        , KC_F7          , KC_F8          , KC_F9          , KC_F12         ,                            CPI_D100       , SCRL_DVD       , XXXXXXX        , XXXXXXX        , XXXXXXX        ,
    XXXXXXX        , KC_F10         , KC_F11         , _______        , _______        , _______        , _______ , _______        , _______        , _______        , _______        , XXXXXXX
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    // オートマウスレイヤーに切り替える
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

// オートマウスレイヤーだったらデフォルトレイヤーに切り替える
static inline void kill_auto_mouse_if_needed(void) {
    if (layer_state_is(AUTO_MOUSE_DEFAULT_LAYER)) {
        layer_off(AUTO_MOUSE_DEFAULT_LAYER);
        set_auto_mouse_timeout(get_auto_mouse_keep_time());
        keyball.total_mouse_movement = 0;
    }
}

static uint16_t user0_timer;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // レイヤーキーHOLDかモッドタップ時はオートマウスレイヤーを解除する
    if (IS_QK_LAYER_TAP(keycode) || IS_QK_MOD_TAP(keycode)) {
        kill_auto_mouse_if_needed();
    }

    switch (keycode) {
        // Modifier系のキーをHOLDした時点でオートマウスレイヤーを解除する
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
        
        // ホールド時はスクロールモード、タップ時はCNTL+左クリック
        case USER0:
            if (record->event.pressed) {
                user0_timer = timer_read();
                keyball_set_scroll_mode(true);
            } else {
                if (timer_elapsed(user0_timer) < TAPPING_TERM) {
                    register_code(KC_LCTL);
                    wait_ms(10);
                    register_code(KC_MS_BTN1);
                    unregister_code(KC_MS_BTN1);
                    wait_ms(10);
                    unregister_code(KC_LCTL);
                }
                keyball_set_scroll_mode(false);
            }
            return false;

        // ミュート
        case USER1:
            if (record->event.pressed) {
                register_code(KC_AUDIO_MUTE);
            } else {
                unregister_code(KC_AUDIO_MUTE); 
            }
            return false;

        // 音量アップ
        case USER2:
            tap_code(KC_AUDIO_VOL_UP);
            return false;

        // 音量ダウン
        case USER3:
            tap_code(KC_AUDIO_VOL_DOWN);
            return false;

        // 再生/一時停止
        case USER4:
            if (record->event.pressed) {
                register_code(KC_MEDIA_PLAY_PAUSE);
            } else {
                unregister_code(KC_MEDIA_PLAY_PAUSE);
            }
            return false;

        // 次のトラック
        case USER5:
            tap_code(KC_MEDIA_NEXT_TRACK);
            return false;

        // 前のトラック
        case USER6:
            tap_code(KC_MEDIA_PREV_TRACK);
            return false;

        // MacのMission Control(WinはPowerToysのKeyboard Managerでタスクビューに変更する)
        case USER7:
            if (record->event.pressed) {
                register_code(KC_RCTL);
                wait_ms(10);
                register_code(KC_UP);
                unregister_code(KC_UP);
            } else {
                unregister_code(KC_RCTL);
            }
            return false;

        // Ctrl + Shift
        case USER8:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_LSFT);
            }
            return false;

    }
    return true;
}

bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        // マウスレイヤーで使うキーはすべてマウスボタンとすることでマウスレイヤーを抜けないようにする
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