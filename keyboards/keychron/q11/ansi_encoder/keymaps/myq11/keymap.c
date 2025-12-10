/* Copyright 2023 @ Keychron (https://www.keychron.com)
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
// #include "keymap_extras/keymap_japanese.h"

enum layers{
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_BASE_JP,
    WIN_FN,
    NUM_SYM,  // 記号レイヤー追加
};

enum custom_keycodes {
    M_JIGL = SAFE_RANGE,  // Mouse Jiggler トグルキー
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

// Space長押しでNUM_SYMレイヤーへ
#define SPC_SYM LT(NUM_SYM, KC_SPC)
// #define ENT_CTL RCTL_T(KC_ENT)
// #define ENT_GUI RGUI_T(KC_ENT)

// Mouse Jiggler グローバル変数
bool is_mouse_jiggle_active = false;
bool mouse_jiggle_direction = false; // 左右の方向を交互に切り替え
uint16_t mouse_jiggle_frequency = 15000; // 15秒ごとにマウス移動
uint16_t mouse_jiggle_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_91_ansi(
        KC_MUTE,  KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_NO,    KC_NO,    KC_MUTE,
        _______,  KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_DEL,             DF(MAC_BASE),
        _______,  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            DF(WIN_BASE),
        _______,  KC_BSPC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             DF(WIN_BASE_JP),
        _______,  KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,
        _______,  KC_LGUI,  KC_LALT,  KC_LCTL,  MO(MAC_FN),         SPC_SYM,                       KC_ENT,            KC_CAPS,  MO(MAC_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_91_ansi(
        M_JIGL,  _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   _______,  _______,  RM_TOGG,
        _______,  _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_DEL,            _______,
        _______,  _______,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_PGUP,  LGUI(KC_LEFT), KC_UP, LGUI(KC_RGHT), _______,  _______,  _______,  _______,  _______,
        _______,  _______,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,  _______,              _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,   _______,  KC_NO,    _______,  _______,  _______,  _______,              _______,  _______,
        _______,  _______,  _______,  _______,  _______,            _______,                       _______,            _______,  _______,    _______,  _______,  _______,  _______),

    [WIN_BASE] = LAYOUT_91_ansi(
        KC_MUTE,  KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_NO,    KC_NO,    KC_MUTE,
        _______,  KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_DEL,             DF(MAC_BASE),
        _______,  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            DF(WIN_BASE),
        _______,  KC_BSPC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             DF(WIN_BASE_JP),
        _______,  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,
        _______,  KC_LCTL,  KC_LGUI,  KC_LALT,  MO(WIN_FN),         SPC_SYM,                       KC_ENT,            KC_F13,   MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_BASE_JP] = LAYOUT_91_ansi(
        KC_MUTE,  KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_NO,    KC_NO,    KC_MUTE,
        _______,  KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_DEL,             DF(MAC_BASE),
        _______,  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            DF(WIN_BASE),
        _______,  KC_BSPC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             DF(WIN_BASE_JP),
        _______,  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,
        _______,  KC_LCTL,  KC_LGUI,  KC_LALT,  MO(WIN_FN),         SPC_SYM,                       KC_ENT,            KC_GRV,   MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_91_ansi(
        M_JIGL,  _______,  KC_BRID,  KC_BRIU,  LGUI(KC_TAB), LGUI(KC_E), RM_VALD,   RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,  _______,  RM_TOGG,
        _______,  KC_GRV,   KC_F1,    KC_F2,    KC_F3,        KC_F4,      KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,     _______,            _______,
        _______,  KC_CAPS,  _______,   KC_NO,    KC_NO,        KC_NO,      KC_NO,     KC_PGUP,  KC_HOME,  KC_UP,    KC_END,   _______,  _______,    _______,  _______,            _______,
        _______,  _______,  KC_NO,    KC_NO,    KC_NO,        KC_NO,      KC_NO,     KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,  _______,              _______,            _______,
        _______,  _______,  _______,  _______,  _______,      _______,    _______,   _______,  _______,  _______,  _______,  _______,              _______,  _______,
        _______,  _______,  _______,  _______,  _______,                _______,                       _______,            _______,  _______,    _______,  _______,  _______,  _______),

    [NUM_SYM] = LAYOUT_91_ansi(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   _______,            _______,
        _______,  _______,  KC_TILD,  _______,  _______,  _______,  KC_CIRC,   _______,  KC_PLUS,  KC_LBRC,  KC_RBRC,  _______,  _______,    _______,  _______,            _______,
        _______,  _______,  KC_EXLM,  KC_AT,    KC_HASH,  KC_PERC,  KC_DLR,    KC_AMPR,  KC_EQL,   KC_LPRN,  KC_RPRN,  KC_UNDS,  _______,              KC_PIPE,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   KC_ASTR,  KC_MINS,  KC_LCBR,  KC_RCBR,  _______,              _______,  _______,
        _______,  _______,  _______,  _______,  _______,            _______,                       _______,            _______,  _______,    _______,  _______,  _______,  _______),

};

// Layer-conditional key overrides for WIN_BASE_JP layer only
// These fix symbol output when Windows is set to Japanese keyboard but physical keyboard is US ANSI
// negative_mod_mask: MOD_MASK_CAG = only trigger when Ctrl, Alt, GUI are NOT pressed (Shift is OK)

// Shift+2 -> @ (JIS layout: @ is on [ key)
const key_override_t ko_jp_at = ko_make_with_layers_negmods_and_options(
    MOD_MASK_SHIFT, KC_2, KC_LBRC,
    (1 << WIN_BASE_JP), MOD_MASK_CAG, ko_option_no_reregister_trigger);

// Shift+6 -> ^ (JIS layout: ^ is on = key without shift)
const key_override_t ko_jp_caret = ko_make_with_layers_negmods_and_options(
    MOD_MASK_SHIFT, KC_6, KC_EQL,
    (1 << WIN_BASE_JP), MOD_MASK_CAG, ko_option_no_reregister_trigger);

// Shift+7 -> & (JIS layout: & is Shift+6)
const key_override_t ko_jp_amp = ko_make_with_layers_negmods_and_options(
    MOD_MASK_SHIFT, KC_7, LSFT(KC_6),
    (1 << WIN_BASE_JP), MOD_MASK_CAG, ko_option_no_reregister_trigger);

// Shift+8 -> * (JIS layout: * is Shift+:, which is Shift+')
const key_override_t ko_jp_astr = ko_make_with_layers_negmods_and_options(
    MOD_MASK_SHIFT, KC_8, LSFT(KC_QUOT),
    (1 << WIN_BASE_JP), MOD_MASK_CAG, ko_option_no_reregister_trigger);

// Shift+9 -> ( (JIS layout: ( is Shift+8)
const key_override_t ko_jp_lprn = ko_make_with_layers_negmods_and_options(
    MOD_MASK_SHIFT, KC_9, LSFT(KC_8),
    (1 << WIN_BASE_JP), MOD_MASK_CAG, ko_option_no_reregister_trigger);

// Shift+0 -> ) (JIS layout: ) is Shift+9)
const key_override_t ko_jp_rprn = ko_make_with_layers_negmods_and_options(
    MOD_MASK_SHIFT, KC_0, LSFT(KC_9),
    (1 << WIN_BASE_JP), MOD_MASK_CAG, ko_option_no_reregister_trigger);

// Shift+- -> _ (JIS layout: _ is Shift+backslash which is INT1)
const key_override_t ko_jp_unds = ko_make_with_layers_negmods_and_options(
    MOD_MASK_SHIFT, KC_MINS, LSFT(KC_INT1),
    (1 << WIN_BASE_JP), MOD_MASK_CAG, ko_option_no_reregister_trigger);

// Shift+= -> + (JIS layout: + is Shift+;)
const key_override_t ko_jp_plus = ko_make_with_layers_negmods_and_options(
    MOD_MASK_SHIFT, KC_EQL, LSFT(KC_SCLN),
    (1 << WIN_BASE_JP), MOD_MASK_CAG, ko_option_no_reregister_trigger);

// Shift+' -> " (JIS layout: " is Shift+2)
const key_override_t ko_jp_dquo = ko_make_with_layers_negmods_and_options(
    MOD_MASK_SHIFT, KC_QUOT, LSFT(KC_2),
    (1 << WIN_BASE_JP), MOD_MASK_CAG, ko_option_no_reregister_trigger);

// ' (no shift) -> ' (JIS layout: ' position outputs 7, ' is at Shift+7)
const key_override_t ko_jp_quot = ko_make_with_layers_negmods_and_options(
    0, KC_QUOT, LSFT(KC_7),
    (1 << WIN_BASE_JP), MOD_MASK_CSAG, ko_option_no_reregister_trigger);

// = (no shift) -> = (JIS layout: = position has ^ without shift, = is at Shift+-)
const key_override_t ko_jp_equal = ko_make_with_layers_negmods_and_options(
    0, KC_EQL, LSFT(KC_MINS),
    (1 << WIN_BASE_JP), MOD_MASK_CSAG, ko_option_no_reregister_trigger);

// [ (no shift) -> [ (JIS layout: [ position has @, [ is at ] position)
const key_override_t ko_jp_lbrc = ko_make_with_layers_negmods_and_options(
    0, KC_LBRC, KC_RBRC,
    (1 << WIN_BASE_JP), MOD_MASK_CSAG, ko_option_no_reregister_trigger);

// ] (no shift) -> ] (JIS layout: ] position has [, ] is at \ position)
const key_override_t ko_jp_rbrc = ko_make_with_layers_negmods_and_options(
    0, KC_RBRC, KC_BSLS,
    (1 << WIN_BASE_JP), MOD_MASK_CSAG, ko_option_no_reregister_trigger);

// Shift+[ -> { (JIS layout: Shift+[ outputs `, { is at Shift+])
const key_override_t ko_jp_lcbr = ko_make_with_layers_negmods_and_options(
    MOD_MASK_SHIFT, KC_LBRC, LSFT(KC_RBRC),
    (1 << WIN_BASE_JP), MOD_MASK_CAG, ko_option_no_reregister_trigger);

// Shift+] -> } (JIS layout: Shift+] outputs {, } is at Shift+\)
const key_override_t ko_jp_rcbr = ko_make_with_layers_negmods_and_options(
    MOD_MASK_SHIFT, KC_RBRC, LSFT(KC_BSLS),
    (1 << WIN_BASE_JP), MOD_MASK_CAG, ko_option_no_reregister_trigger);

// \ (no shift) -> \ (JIS layout: \ position has ], \ is at INT3/Yen key with shift)
const key_override_t ko_jp_bsls = ko_make_with_layers_negmods_and_options(
    0, KC_BSLS, LSFT(KC_INT3),
    (1 << WIN_BASE_JP), MOD_MASK_CSAG, ko_option_no_reregister_trigger);

// Shift+\ -> | (JIS layout: Shift+\ outputs }, | is at Shift+INT1)
const key_override_t ko_jp_pipe = ko_make_with_layers_negmods_and_options(
    MOD_MASK_SHIFT, KC_BSLS, LSFT(KC_INT1),
    (1 << WIN_BASE_JP), MOD_MASK_CAG, ko_option_no_reregister_trigger);

// Shift+; -> : (JIS layout: : )
const key_override_t ko_jp_colon = ko_make_with_layers_negmods_and_options(
    MOD_MASK_SHIFT, KC_SCLN, KC_QUOT,
    (1 << WIN_BASE_JP), MOD_MASK_CAG, ko_option_no_reregister_trigger);

const key_override_t *key_overrides[] = {
    &ko_jp_at,
    &ko_jp_caret,
    &ko_jp_amp,
    &ko_jp_astr,
    &ko_jp_lprn,
    &ko_jp_rprn,
    &ko_jp_unds,
    &ko_jp_plus,
    &ko_jp_dquo,
    &ko_jp_quot,
    &ko_jp_equal,
    &ko_jp_lbrc,
    &ko_jp_rbrc,
    &ko_jp_lcbr,
    &ko_jp_rcbr,
    &ko_jp_bsls,
    &ko_jp_pipe,
    &ko_jp_colon,
    NULL
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_FN]   = { ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_BASE_JP] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_FN]   = { ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [NUM_SYM]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
#endif // ENCODER_MAP_ENABLE

// // Speculative Hold コールバック
// // Space/NUM_SYMレイヤーとEnter/Ctrlに対してSpeculative Holdを有効化
// bool get_speculative_hold(uint16_t keycode, keyrecord_t* record) {
//     switch (keycode) {
//         case SPC_SYM:  // Space/NUM_SYM layer-tap
//         case ENT_CTL:  // Enter/Ctrl
//             return true;
//     }
//     return false;  // その他のmod-tapキーには適用しない
// }

// Tapping Term の個別設定（オプション）
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SPC_SYM:
        // case ENT_CTL:
            return 180;  // Space/Enterは少し短めに（デフォルト200ms）
        default:
            return TAPPING_TERM;
    }
}

// Mouse Jiggler: キー処理
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M_JIGL:
            if (record->event.pressed) {
                is_mouse_jiggle_active = !is_mouse_jiggle_active;
            }
            return false;
    }
    return true;
}

// Mouse Jiggler: タイマー処理
void matrix_scan_user(void) {
    if (is_keyboard_master()) {
        // Split keyboardのマスター側のみでタイマーを初期化
        if (mouse_jiggle_timer == 0) {
            mouse_jiggle_timer = timer_read();
        }
    }

    if (is_mouse_jiggle_active) {
        if (timer_elapsed(mouse_jiggle_timer) > mouse_jiggle_frequency) {
            mouse_jiggle_timer = timer_read();
            if (mouse_jiggle_direction) {
                tap_code(MS_LEFT);
            } else {
                tap_code(MS_RGHT);
            }
            mouse_jiggle_direction = !mouse_jiggle_direction;
        }
    }
}
