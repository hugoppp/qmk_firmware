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
#include "Texts.h"
//#include <print.h>
LEADER_EXTERNS();

#define _LONG_PRESS_COMPLEX 15 //basically a layer number, so can't be conflicting with layer number

bool reverse_number_keys = false;

//tap hold prototypes
static void do_lp_tap(uint16_t keycode, keyrecord_t *record);
static void do_lp_hold(uint16_t keycode, keyrecord_t *record);
//advanced tap dance prototypes
int cur_dance_1t_1h (qk_tap_dance_state_t *state);
static bool is_shifted(void);


static bool modLockShiftIgnore = true;
static bool modLockShift = false;
static bool alttabActive = false;

void oneshot_locked_mods_changed_user(uint8_t mods) {
    modLockShift = mods & MOD_MASK_SHIFT;
}
void oneshot_mods_changed_user(uint8_t mods) {
    if (mods & MOD_MASK_SHIFT) modLockShift = false;
}

enum long_press_codes{
    LP_Auml = LT(_LONG_PRESS_COMPLEX, 0),
    LP_Uuml,
    LP_Ouml,
    LP_Eeur,
    LP_Ssz,


    LP_1,
    LP_2,
    LP_3,
    LP_4,
    LP_5,
    LP_6,
    LP_7,
    LP_8,
    LP_9,
    LP_0,
    LP_MINS,
    LP_EQL,
};

enum layer_names {
    l_base,
    l_gaming,
    l_ger,
    l_fn,
    l_rgb
};

enum custom_keycodes {
  TEST = SAFE_RANGE,
  C_PLS,
  C_MIN,
  C_EQL,
  C_EXPL,
  C_REVERSE_NUMBERS,
  C_CAPS_UNDERSCORE,
  C_NLINE,
  C_VLINE,
  C_ALTAB,
};

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

enum unicode_names {
    Au,
    au,
    Ou,
    ou,
    Uu,
    uu
};

const uint32_t PROGMEM unicode_map[] = {
    [Au] =  0x00E4,
    [au] = 0x00C4,
    [Ou] = 0x00D6,
    [Ou] = 0x00F6,
    [Uu] = 0x00D6,
    [Uu] = 0x00FC
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [l_base] = LAYOUT_65_ansi_blocker( /* Base */
        KC_GESC,          LP_1,     LP_2,     LP_3,     LP_4,   LP_5,  LP_6,    LP_7,         LP_8,         LP_9,         LP_0,     LP_MINS,  LP_EQL,   KC_BSPC,   KC_INS,
        KC_TAB,           KC_Q,     KC_W,     LP_Eeur,  KC_R,   KC_T,  KC_Y,    LP_Uuml,      KC_I,         LP_Ouml,      KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLASH, TD(TD_PgUp_Home),
        KC_ENT,   LP_Auml,     LP_Ssz,  KC_D,     KC_F,   KC_G,  KC_H,    KC_J, KC_K, KC_L, KC_SCLN,  KC_QUOT,            KC_ENT,    TD(TD_PgDn_End),
        KC_LSFT,    KC_Z,     KC_X,     KC_C,     KC_V,   KC_B,  KC_N,    KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,  KC_RSFT,		    KC_UP,     TD(TD_PSCREEN_SLEEP),
        KC_LEAD,          KC_LGUI,  KC_LALT,            LT(l_fn,KC_SPC),                        KC_RALT,  KC_RCTRL,                          KC_LEFT, KC_DOWN,   KC_RIGHT
    ),

    [l_ger] = LAYOUT_65_ansi_blocker( /* german layer */
        _______,       _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______,  _______, _______, _______,
        _______,       _______,  _______, LP_Eeur, _______, _______, _______, LP_Uuml, _______, LP_Ouml, _______,     _______,  _______, _______, _______,
        _______,       LP_Auml,  LP_Ssz,  _______, _______, _______, _______, _______, _______, _______, _______,        _______,           _______, _______,
        _______,       _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______,           _______, _______,
        _______,       _______,  _______,                   _______,                   _______, _______,                 _______,           _______, _______
    ),

    [l_gaming] = LAYOUT_65_ansi_blocker( /* Gaming, no tapdancing etc */
        KC_ESC,           KC_1,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,   KC_INS,
        KC_TAB,           KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSLASH, KC_PGUP,
        LT(l_fn,KC_ENT),  KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,    KC_L,     KC_SCLN,  KC_QUOT,           KC_ENT,    KC_PGDOWN,
        KC_LSHIFT,        KC_Z,     KC_X,     KC_C,  KC_V,  KC_B,  KC_N,    KC_M,  KC_COMM, KC_DOT,   KC_SLSH,  KC_RSHIFT,	   	   KC_UP,     TD_PSCREEN_SLEEP,
        KC_LCTL,          KC_LGUI,  KC_LALT,                KC_SPC,                KC_RALT, KC_RCTRL,                     KC_LEFT, KC_DOWN,   KC_RIGHT
    ),

    [l_fn] = LAYOUT_65_ansi_blocker( /* Fn layer */
        KC_GRV,        XXXXXXX,  XXXXXXX, XXXXXXX,  KC_END,       XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  KC_HOME,  C_CAPS_UNDERSCORE, XXXXXXX,  KC_DEL,    XXXXXXX,
        C_ALTAB,       XXXXXXX,  KC_WFWD, KC_PGUP, XXXXXXX,       XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX,  C_NLINE,  KC_MPLY,  XXXXXXX,           XXXXXXX, XXXXXXX,  TG(l_rgb),
        _______,       XXXXXXX,  KC_WBAK, KC_PGDN, SWIN(KC_LEFT), SWIN(KC_RIGHT), KC_LEFT, KC_DOWN, KC_UP,    KC_RIGHT, XXXXXXX,  _______,                    KC_INSERT, TG(l_gaming),
        _______,       XXXXXXX,  XXXXXXX, XXXXXXX, C_VLINE,       KC_MPRV,        KC_MNXT, KC_MUTE, KC_VOLD,  KC_VOLU,  XXXXXXX,  _______,                    KC_VOLU,  KC_MUTE,
        _______,       _______,  _______,                         _______,                          _______,  _______,                               KC_MPRV, KC_VOLD,   KC_MNXT
    ),

    [l_rgb] = LAYOUT_65_ansi_blocker( /* RGB, RESET layer*/
        TG(l_rgb),     RGB_M_P,  RGB_M_B,  RGB_M_R, RGB_M_SW,RGB_M_SN,RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, XXXXXXX,  RGB_SPD, RGB_SPI,   RESET,   RGB_MOD,
        _______,       XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,   RGB_SAI,
        _______,	     XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,          EEP_RST,   RGB_SAD,
        _______,       XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  _______,          RGB_VAI,   RGB_TOG,
        _______,       _______,  _______,                    XXXXXXX,                   _______, _______,                    RGB_HUD, RGB_VAD,   RGB_HUI
    )
};

void keyboard_post_init_user(void) { // Runs boot tasks for keyboard
  //layer_on(l_ger);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        //COMPLEX SHORT LONG PRESS
        case LT(_LONG_PRESS_COMPLEX, 0) ... LT(_LONG_PRESS_COMPLEX, 0xff):
            if (record->event.pressed) {
                if (record->tap.count == 0)
                    {
                      do_lp_hold(keycode, record);
                      return false;
                    }
                else
                    {
                      do_lp_tap(keycode, record);
                      return false;
                    }
            }
            break;

        //snake case with shift tap hold
        case LT(l_fn,KC_SPC):
            if (record->event.pressed)
            {
                /* if (record->tap.count != 0 && (modLockShiftIgnore || !modLockShift) && get_mods() & MOD_MASK_SHIFT) { */
                /*   tap_code16(KC_UNDERSCORE); */
                /*   return false; */
                /* } */
            } else {
              if (alttabActive){
                unregister_code(KC_LALT);
                alttabActive = false;
              }
            }
            break;

        //switch snake case
        case C_CAPS_UNDERSCORE:
            if (record->event.pressed)
                modLockShiftIgnore = !modLockShiftIgnore;
            break;

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
                return false;
            }
            break;

      case C_ALTAB:
            if (record->event.pressed) {
              if (!alttabActive) {
                alttabActive = true;
                register_code(KC_LALT);
              }
              register_code(KC_TAB);
            } else {
              unregister_code(KC_TAB);
            }
            break;
    }
    return true;
};

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_TWO_KEYS(KC_M, KC_M) {
      SEND_STRING(PRIVATE_MAIL);
    }
    SEQ_TWO_KEYS(KC_M, KC_N) {
      SEND_STRING(HAW_MAIL);
    }

    SEQ_ONE_KEY(KC_COMM) {
      reverse_number_keys = !reverse_number_keys;
    }
    SEQ_ONE_KEY(KC_DOT) {
      layer_invert(l_ger);
    }
    SEQ_ONE_KEY(KC_SLSH) {
      layer_invert(l_gaming);
    }
  }
}

//Auto repeat on 1x tap 1x hold
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    /* case LP_Auml: */
    /* case LP_Uuml: */
    /* case LP_Ouml: */
    /* case LP_Eeur: */
    /* case LP_Ssz: */
    case LT(_LONG_PRESS_COMPLEX, 0) ... LT(_LONG_PRESS_COMPLEX, 0xff):
      print ("fore hold yes\n");
      return true;
    default:
      return false;
  }
}

//Tapping term per key. use whole keycode
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LP_1 ... LP_EQL:
         /* print("term: 250\n"); */
         return 200;

    case LP_Auml:
    case LP_Ouml:
    case LP_Uuml:
    case LP_Eeur:
    case LP_Ssz:
         /* print("term: 250\n"); */
         return 350;

    case LCTL_T(KC_J):
    case RSFT_T(KC_K):
    case LSFT_T(KC_D):
    case LALT_T(KC_L):
    case OSM(MOD_LSFT):
         /* print("term: 400\n"); */
         return 180;

    case LCTL_T(KC_ENT):
         /* print("term: 150\n"); */
         return 150;

    case LT(l_fn,KC_SPC):
         /* print("term: 300\n"); */
         return 180;

    default:
         /* print("term: default\n"); */
         return TAPPING_TERM;
  }
};

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(_LONG_PRESS_COMPLEX, 0) ... LT(_LONG_PRESS_COMPLEX, 0xff):
            print("------ permmissiv hold false -------\n");
            return false;
        default:
            print("permmissiv hold true\n");
            return true;
    }
}



//////////////////////////////////////////////////////////////////////                  Custom Functions                  //////////////////////////////////////////////////////////////////////

///     SHORT LONG PRESS     ///
    static void do_lp_tap(uint16_t keycode, keyrecord_t *record) {
        if (!reverse_number_keys){
            // number -> number
            switch (keycode){
                case LP_1 ... LP_0:     tap_code(keycode - LP_1 + KC_1); return;
                case LP_MINS:           tap_code(KC_MINS); return;
                case LP_EQL:            tap_code(KC_EQL); return;
                case LP_Ssz:            tap_code(KC_S); return;
                case LP_Eeur:            tap_code(KC_E); return;
            }
        }
        else
        {
            // number -> fkey
            switch (keycode){
                case LP_1 ... LP_0:     tap_code(keycode - LP_1 + KC_F1); return;
                case LP_MINS:           tap_code(KC_F11); return;
                case LP_EQL:            tap_code(KC_F12); return;
            }
        }

        switch (keycode) {
            // A O U -> A O U
            case LP_Auml:           tap_code(KC_A);    return;
            case LP_Uuml:           tap_code(KC_U);    return;
            case LP_Ouml:           tap_code(KC_O);    return;
        }
    };

    static void do_lp_hold(uint16_t keycode, keyrecord_t *record) {
        if (reverse_number_keys){
            // number -> number
            switch (keycode)
            {
                case LP_1 ... LP_0:     tap_code(keycode - LP_1 + KC_1); return;
                case LP_MINS:           tap_code(KC_MINS); return;
                case LP_EQL:            tap_code(KC_EQL); return;
            }
        }
        else
        {
            // number -> fkey
            switch (keycode){
                case LP_1 ... LP_0:    tap_code(keycode - LP_1 + KC_F1); return;
                case LP_MINS:          tap_code(KC_F11); return;
                case LP_EQL:           tap_code(KC_F12); return;
            }
        }

        switch(keycode){
            case LP_Auml:
                if (is_shifted())
                    send_unicode_string("Ä");
                else
                    send_unicode_string("ä");           /*register_code(KC_RALT);   tap_code(KC_A);   unregister_code(KC_RALT); return; //Ä*/
                return;
            case LP_Uuml:
                if (is_shifted())
                    send_unicode_string("Ü");
                else
                    send_unicode_string("ü");          /*register_code(KC_RALT);   tap_code(KC_U);   unregister_code(KC_RALT); return; //Ü*/
                return;
            case LP_Ouml:
                if (is_shifted())
                    send_unicode_string("Ö");
                else
                    send_unicode_string("ö");          /*register_code(KC_RALT);   tap_code(KC_O);   unregister_code(KC_RALT); return; //Ö*/
                return;
            case LP_Eeur: send_unicode_string("€"); return;          /* register_code(KC_RALT);   tap_code(KC_E);   unregister_code(KC_RALT); return; //Ö*/
            case LP_Ssz:  send_unicode_string("ß"); return;          /* register_code(KC_RALT);   tap_code(KC_1);   unregister_code(KC_RALT); return; //Ö*/
        }
    };

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

///  Custom Advanced Tap Dances  ///
    /*instanalize an instance of 'tap' for the 'x' tap dance. */
    /* static tap xtap_state = { */
    /* .is_press_action = true, */
    /* .state = 0 */
    /* }; */

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^           Custom Functions             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//////////////////////////////////////////////////////////////////////           Advanced Tap Dance           //////////////////////////////////////////////////////////////////////
int cur_dance_1t_1h (qk_tap_dance_state_t *state) {
    if (!state->pressed)  return SINGLE_TAP;
    else return SINGLE_HOLD;
};


// helper function
 static bool is_shifted(){
     bool shift = get_mods() & MOD_MASK_SHIFT;
     bool caps = IS_HOST_LED_ON(USB_LED_CAPS_LOCK);
     return shift || caps;
 }
