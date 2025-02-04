/*

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
along with this program.  If not, see http://www.gnu.org/licenses/.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

#define NAV 2
#define SYM 3
#define NUM 4
#define CONF 5

enum keycodes {
    OS_SHFT = SAFE_RANGE,
    MY_ARRO
};

// Left-hand home row mods
#define GUI_1 LGUI_T(KC_1)
#define ALT_2 LALT_T(KC_2)
#define CTL_4 LCTL_T(KC_4)
#define SFT_3 LSFT_T(KC_3)

//osm
#define OS_LGUI OSM(MOD_LGUI)
#define OS_LALT OSM(MOD_LALT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_RGUI OSM(MOD_RGUI)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_RSFT OSM(MOD_RSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // alpha
 [0] = LAYOUT_universal(
    S(KC_9)  ,  KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y     , KC_U     , KC_I     , KC_O     , KC_P   , S(KC_0)  ,
    QK_GESC   , KC_A     , KC_S     , KC_D     , KC_F    ,  KC_G    ,                                         KC_H     , KC_J     , KC_K     , KC_L    ,  KC_SCLN, KC_QUOT,
    KC_LBRC   , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH, KC_RBRC   ,
                    KC_LGUI,KC_LALT,                     KC_LCTL,   KC_SPC,  LT(SYM,KC_TAB),           LT(NAV,KC_BSPC),    LSFT_T(KC_DEL) , _______,      _______,LT(CONF, KC_PSCR)
  ),

  // mouse
  [1] = LAYOUT_universal(
    _______  ,  _______ , _______  , _______  , _______  , _______  ,                                         _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  ,  _______ , _______  , KC_BTN3  , KC_BTN1  , KC_BTN2  ,                                         _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  ,  _______ , _______  , _______  , _______  , _______  ,                                         _______  , KC_BTN1  , KC_BTN3  , KC_BTN2  , _______  , _______  ,
                  _______  , _______ ,          _______  , _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),

  [NAV] = LAYOUT_universal(
    _______ ,  KC_F1   , KC_F2    , KC_F3    , KC_F4     , KC_F5    ,                                         KC_F6    , KC_F7       , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    _______ ,  OS_LGUI , OS_LALT  , OS_LSFT  , OS_LCTL   , KC_ENT   ,                                         KC_LEFT  , KC_DOWN     , KC_UP    , KC_RGHT  , KC_HOME  , KC_F12  ,
    _______ ,  _______ , _______  , _______  , _______   , KC_MPRV  ,                                         KC_MNXT  , KC_MPLY     , KC_VOLD  , KC_VOLU  , KC_END  , _______  ,
                  _______  , _______ ,          _______  , _______ , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),

    //asdf)')()([][][=>->-=-=-=-=-=-=-=--=-=|||||``''''``
  [SYM] = LAYOUT_universal(
    _______ ,  S(KC_1) , S(KC_2)  , S(KC_3)  , S(KC_4)  , S(KC_5)  ,                                           S(KC_6)   , S(KC_7)   , S(KC_8)    , S(KC_9)  , S(KC_0)   , S(KC_BSLS)  ,
    _______  , OS_LGUI , OS_LALT  , OS_LSFT  , OS_LCTL  , MY_ARRO  ,                                           _______,  S(KC_LBRC), S(KC_RBRC) , _______  , _______  ,  KC_GRV ,
    _______ , _______  ,  S(KC_1)  ,  KC_MINS , KC_EQL  , S(KC_EQL),                                           _______ , KC_LBRC   , KC_RBRC    , KC_DOT  , KC_SLSH  , KC_BSLS  ,
                  _______  , _______ ,        _______  , _______ , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),

  [NUM] = LAYOUT_universal(
    _______ ,  KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                         KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , _______,
    _______  , OS_LGUI , OS_LALT  , OS_LSFT  , OS_LCTL   , _______  ,                                         _______  , OS_RCTL  , OS_RSFT  , OS_LALT  , OS_RGUI  , _______  ,
    _______ ,  KC_F1   , KC_F2    , KC_F3    , KC_F4     , KC_F5    ,                                         KC_F6    , KC_F7       , KC_F8    , KC_F9 , KC_F10   , KC_F11   ,
                  _______  , _______ ,        _______  , _______ , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),

  //function
  // [4] = LAYOUT_universal(
  //   SSNP_FRE ,  KC_F1   , KC_F2    , KC_F3   , KC_F4    , KC_F5    ,                                         KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
  //   SSNP_VRT ,  KC_F1   , KC_F2    , KC_F3   , KC_F4    , KC_F5    ,                                         KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
  //   SSNP_HOR ,  _______ , _______  , _______ , _______  , _______  ,                                         _______  , _______  , _______  , _______  , _______  , _______  ,
  //                 _______  , _______ ,        _______  , _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  // ),

  //config
  [CONF] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                        RGB_M_P  , RGB_M_G  , RGB_M_SW  , RGB_M_K , RGB_M_R , RGB_M_SN  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , SCRL_DVI ,                                        RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , SCRL_DVD ,                                        CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , _______  , KBC_SAVE ,
                  QK_BOOT  , KBC_RST  , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , KBC_RST  , QK_BOOT
  ),

  //
  // [2] = LAYOUT_universal(
  //   _______  ,S(KC_QUOT), KC_7     , KC_8    , KC_9     , S(KC_8)  ,                                         S(KC_9)  , S(KC_1)  , S(KC_6)  , KC_LBRC  , S(KC_4)  , _______  ,
  //   _______  ,S(KC_SCLN), KC_4     , KC_5    , KC_6     , KC_RBRC  ,                                         KC_NUHS  , KC_MINS  , S(KC_EQL), S(KC_3)  , KC_QUOT  , S(KC_2)  ,
  //   _______  ,S(KC_MINS), KC_1     , KC_2    , KC_3     ,S(KC_RBRC),                                        S(KC_NUHS),S(KC_INT1), KC_EQL   ,S(KC_LBRC),S(KC_SLSH),S(KC_INT3),
  //                 KC_0     , KC_DOT  , _______  ,         _______  , _______  ,                   KC_DEL   , _______  , _______       , _______  , _______
  // ),

};
// clang-format on
//
//KC_BTN1
const uint16_t PROGMEM jkl_combo[] = {KC_J, KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM jkl2_combo[] = {KC_BTN1, KC_BTN2, KC_BTN3, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM jk2_combo[] = {KC_BTN1, KC_BTN2, COMBO_END};
const uint16_t PROGMEM rt_combo[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM yu_combo[] = {KC_Y, KC_U, COMBO_END};
combo_t key_combos[] = {
    COMBO(jkl_combo, KC_ENT),
    COMBO(jkl2_combo, KC_ENT),
    COMBO(jk_combo, KC_ESC),
    COMBO(jk2_combo, KC_ESC),
    COMBO(rt_combo, S(KC_9)),
    COMBO(yu_combo, S(KC_0)),
};

bool alt_active = false;
layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    if (alt_active){
        unregister_code(KC_LALT);
        alt_active = false;
    }

    return update_tri_layer_state(state, SYM, NAV, NUM);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //shift+sapace underscore
    if (keycode == KC_SPC && get_mods() == MOD_BIT(KC_LSFT) && record->event.pressed ){
        tap_code16(S(KC_MINS));
        return false;
    }

    //arrow
    if (keycode == MY_ARRO && record->event.pressed ){
        if  (get_mods() == MOD_BIT(KC_LSFT)){
            unregister_code(KC_LSFT);
            tap_code(KC_MINS);
            register_code(KC_LSFT);
        }
        else {
            tap_code(KC_EQL);
        }
        tap_code16(S(KC_DOT));
        return false;
    }

    //easy switcher
    if (layer_state_is(NAV)) {
        if (keycode == LT(SYM, KC_TAB)) {
            if (record->event.pressed && record->tap.count) {
                alt_active = true;
                register_code(KC_LALT);
            }
            return true;
        }
        if (keycode == KC_SPC){
            if  (record->event.pressed && alt_active){
                register_code(KC_LSFT);
                tap_code(KC_TAB);
                unregister_code(KC_LSFT);
                return false;
            }
        }

    }
    return true;
}

#ifdef OLED_ENABLE
#    include "lib/oledkit/oledkit.h"
void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
