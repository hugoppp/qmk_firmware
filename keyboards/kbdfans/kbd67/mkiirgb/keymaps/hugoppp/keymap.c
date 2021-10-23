/* Base layer
* ,--------------------------------------------------------------------------------------------------.
* | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  Backspace  | Del  |
* |-------------------------------------------------------------------------------------------+------+
* | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \     | PgUp |
* |-------------------------------------------------------------------------------------------+------+
* | Backspace|  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |     Enter    | PgDn |
* |-------------------------------------------------------------------------------------------+------+
* | Shift      |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |   RSHIFT   | Up  | PrScr|
* +-------------------------------------------------------------------------┬---┬-------------+------+
* | LCtrl | LGUI | LAlt |               Space                 | RAlt | RCtrl|   | Left  |Down | Right|
* `-------------------------------------------------------------------------┘   └-------------+------´
*/

#include QMK_KEYBOARD_H
#include "config.h"
//#include <print.h>

#define _LONG_PRESS_COMPLEX 15 //basically a layer number, so can't be conflicting with layer number

bool reverse_number_keys = false;

//advanced tap dance prototypes
int cur_dance_1t_1h (qk_tap_dance_state_t *state);

static bool modLockShift = false;

void oneshot_locked_mods_changed_user(uint8_t mods) {
    modLockShift = mods & MOD_MASK_SHIFT;
}
void oneshot_mods_changed_user(uint8_t mods) {
    if (mods & MOD_MASK_SHIFT) modLockShift = false;
}

//Used for advanced tap dance
typedef struct {
  bool is_press_action;
  int state;
} tap;
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};
//^^^^^^^^^^^^^^^^^^^^^^^^

//tap dance function prototypes
void print_sleep(qk_tap_dance_state_t *state, void *user_data);


enum tap_dance{
  TD_PgUp_Home,
  TD_PgDn_End,
  TD_PSCREEN_SLEEP,
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_PgUp_Home]  = ACTION_TAP_DANCE_DOUBLE(KC_PGUP, KC_HOME),
  [TD_PgDn_End]  = ACTION_TAP_DANCE_DOUBLE(KC_PGDN, KC_END),

  [TD_PSCREEN_SLEEP] = ACTION_TAP_DANCE_FN (print_sleep),
};


enum layer_names {
    l_base,
    l_gaming,
    l_fn,
    l_spaceFn,
    l_rgb
};

enum custom_keycodes {
    TEST = SAFE_RANGE,
    C_NLINE,
    C_VLINE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [l_base] = LAYOUT_65_ansi_blocker( /* Base */
        KC_GESC,          KC_1,     KC_2,     KC_3,     KC_4,   KC_5,  KC_6,    KC_7,         KC_8,    KC_9,        KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,   KC_INS,
        KC_TAB,           KC_Q,     KC_W,     KC_E,     KC_R,   KC_T,  KC_Y,    KC_U,         KC_I,    KC_O,        KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLASH, KC_DEL,
        KC_LCTL,          KC_A,     KC_S,     KC_D,     KC_F,   KC_G,  KC_H,    KC_J, KC_K,   KC_L,    KC_SCLN,     KC_QUOT,                      KC_ENT,    C(KC_GRV),
        KC_LSFT,          KC_Z,     KC_X,     KC_C,     KC_V,   KC_B,  KC_N,    KC_M,         KC_COMM, KC_DOT,      KC_SLSH,  KC_RSFT,	          KC_UP,     TD(TD_PSCREEN_SLEEP),
        LT(l_fn,KC_CAPS), KC_LGUI,  KC_LALT,            LT(l_spaceFn,KC_SPC),                 KC_RALT, KC_RCTRL,                         KC_LEFT, KC_DOWN,   KC_RIGHT
    ),

    [l_fn] = LAYOUT_65_ansi_blocker( /* FN */
        KC_GRV,    KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_F11,   KC_F12,  KC_DEL,   KC_HOME,
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______,
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,           _______, TG(l_rgb),
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,           _______, TG(l_gaming),
        _______, _______,  _______,                   _______,                   _______, _______,           _______,           _______, _______
    ),

    [l_gaming] = LAYOUT_65_ansi_blocker( /* Gaming, no tapdancing etc */
        KC_ESC,              KC_1,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,   KC_INS,
        KC_TAB,              KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSLASH, KC_DEL,
        KC_LCTL,             KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,    KC_L,     KC_SCLN,  KC_QUOT,           KC_ENT,    KC_PGDOWN,
        KC_LSHIFT,           KC_Z,     KC_X,     KC_C,  KC_V,  KC_B,  KC_N,    KC_M,  KC_COMM, KC_DOT,   KC_SLSH,  KC_RSHIFT,         KC_UP,     TD_PSCREEN_SLEEP,
        LT(l_fn,KC_CAPS),    KC_LGUI,  KC_LALT,                KC_SPC,                KC_RALT, KC_RCTRL,                     KC_LEFT, KC_DOWN,   KC_RIGHT
    ),

    [l_spaceFn] = LAYOUT_65_ansi_blocker( /* Space Fn layer */
        KC_GRV,   XXXXXXX,       XXXXXXX,       XXXXXXX, KC_END,  XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  KC_HOME,  _______,  XXXXXXX, _______,  _______,
        _______,  XXXXXXX,       KC_WFWD,       KC_PGUP, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX,  C_NLINE,  KC_MPLY,  XXXXXXX,  XXXXXXX, XXXXXXX,  _______,
        _______,  XXXXXXX,       KC_WBAK,       KC_PGDN, KC_ENT,  KC_BSPC,        KC_LEFT, KC_DOWN, KC_UP,    KC_RIGHT, XXXXXXX,  _______,           _______,  _______,
        _______,  C(G(KC_LEFT)), C(G(KC_RGHT)), XXXXXXX, C_VLINE, KC_MPRV,        KC_MNXT, KC_MUTE, KC_VOLD,  KC_VOLU,  XXXXXXX,  _______,           KC_VOLU,  KC_MUTE,
        _______,  _______,       _______,                         _______,                          _______,  _______,                      KC_MPRV, KC_VOLD,  KC_MNXT
    ),

    [l_rgb] = LAYOUT_65_ansi_blocker( /* RGB, RESET layer*/
        TG(l_rgb),     RGB_M_P,  RGB_M_B,  RGB_M_R, RGB_M_SW,RGB_M_SN,RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, XXXXXXX,  RGB_SPD, RGB_SPI,   RESET,   RGB_MOD,
        _______,       XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,   RGB_SAI,
        _______,	   XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,          EEP_RST,   RGB_SAD,
        _______,       XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  _______,          RGB_VAI,   RGB_TOG,
        _______,       _______,  _______,                    XXXXXXX,                   _______, _______,                    RGB_HUD, RGB_VAD,   RGB_HUI
    )
};

void keyboard_post_init_user(void) { // Runs boot tasks for keyboard
  //layer_on(l_ger);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        //new line below; +shift new line above
        case C_NLINE:
            if (record->event.pressed){
                if (get_mods() & MOD_MASK_SHIFT) {
                  clear_mods();
                  unregister_code(MOD_LSFT);
                  tap_code(KC_HOME);
                  tap_code(KC_ENTER);
                  tap_code(KC_UP);
                }
                else {
                  tap_code(KC_END);
                  tap_code(KC_ENTER);
                }
                return false;
            }
            break;

        //select line
        case C_VLINE:
            if (record->event.pressed){
                tap_code(KC_HOME);
                tap_code16(S(KC_END));
                tap_code16(S(KC_RIGHT));
                return false;
            }
            break;
    }
    return true;
}

//////////////////////////////////////////////////////////////////////                  Custom Functions                  //////////////////////////////////////////////////////////////////////

///  Custom Tap Dances  ///
    // 1x = leadr, 2x = print, 3x = sleep //
    void print_sleep(qk_tap_dance_state_t *state, void *user_data) {
        switch (state->count)
        {
            case (1): tap_code(KC_PSCREEN);          break;
            case (2): tap_code(KC_SYSTEM_SLEEP);     break;
            case (3): tap_code(KC_SYSTEM_POWER);     break;
        }
    };
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^           Custom Functions             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//////////////////////////////////////////////////////////////////////           Advanced Tap Dance           //////////////////////////////////////////////////////////////////////
int cur_dance_1t_1h (qk_tap_dance_state_t *state) {
    if (!state->pressed)  return SINGLE_TAP;
    else return SINGLE_HOLD;
};

