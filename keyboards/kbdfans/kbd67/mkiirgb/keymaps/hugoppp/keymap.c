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
* 
* Layer Switching:
* CAPS/SPACE hold -> Fn layer
* Fn()
* 
* 
* FN keys
* g -> -     TODO
* h -> +     TODO
* n -> !     TODO
* b -> =     TODO
* m -> "     TODO
*
* J -> Ctrl / (
* K -> Shft / )
* L -> Alt / {
* 
* e,s,d,f -> arrow keys
* q,e     -> home, end
* 
* 
* ASCII Keys:
* Fn(a) -> ä Ä XP(aUml,AUml) 
* Fn(o) -> ö Ö XP(oUml,OUml)
* Fn(u) -> ü Ü XP(uUml,UUml)
* 
* Tap Mods:
* J -> Ctrl 
* K -> Shft
* L -> Alt
* 
* Tap Dance Keys:
* PgUp 2x = Home
* PgDn 2x = End  
* PrSr 2x = Sleep
* 
*/

#include QMK_KEYBOARD_H
#include "config.h"
#include "Texts.h"
LEADER_EXTERNS();

#define _LONG_PRESS_COMPLEX 15 //basically a layer number, so can't be conflicting with layer number

bool reverse_number_keys = false;

//tap hold prototypes
static void do_lp_tap(uint16_t keycode, keyrecord_t *record);
static void do_lp_hold(uint16_t keycode, keyrecord_t *record);
//advanced tap dance prototypes
int cur_dance_1t_1h (qk_tap_dance_state_t *state);



enum long_press_codes{
    LP_Auml = LT(_LONG_PRESS_COMPLEX, 0),
    LP_Uuml,
    LP_Ouml,

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

    // LP_F1,
    // LP_F2,
    // LP_F3,
    // LP_F4,
    // LP_F5,
    // LP_F6,
    // LP_F7,
    // LP_F8,
    // LP_F9,
    // LP_F10,
    // LP_F11,
    // LP_F12,
};

enum layer_names {
    l_base,
    l_gaming,
    //l_fKeys,
    l_num,
    l_fn,
    l_rgb
};

// enum unicode_names {
// 	AUml,
// 	aUml,
// 	UUml,
// 	uUml,
// 	OUml,
// 	oUml
// };

enum custom_keycodes {
  TEST = SAFE_RANGE,
  C_PLS,
  C_MIN,
  C_EQL,
  C_EXPL,
  C_REVERSE_NUMBERS
};

// const uint32_t PROGMEM unicode_map[] = {
// 	[AUml]  = 0x00C4,  // Ä
// 	[aUml]  = 0x00E4,  // ä

// 	[UUml] = 0x00DC,  // Ü
// 	[uUml] = 0x00FC,  // ü

// 	[OUml]  = 0x00D6, // Ö
// 	[oUml]  = 0x00F6, // ö
// };

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

void open_bracket_finished (qk_tap_dance_state_t *state, void *user_data);
void open_bracket_reset (qk_tap_dance_state_t *state, void *user_data);

void close_bracket_finished (qk_tap_dance_state_t *state, void *user_data);
void close_bracket_reset (qk_tap_dance_state_t *state, void *user_data);

void openSql_bracket_finished (qk_tap_dance_state_t *state, void *user_data);
void openSql_bracket_reset (qk_tap_dance_state_t *state, void *user_data);

// void lctl_lead_bracket_finished (qk_tap_dance_state_t *state, void *user_data);
// void lctl_lead_bracket_reset (qk_tap_dance_state_t *state, void *user_data);

// void rctl_lead_bracket_finished (qk_tap_dance_state_t *state, void *user_data);
// void rctl_lead_bracket_reset (qk_tap_dance_state_t *state, void *user_data);

void ralt_lead_bracket_reset (qk_tap_dance_state_t *state, void *user_data);
void ralt_lead_bracket_finished (qk_tap_dance_state_t *state, void *user_data);

void lalt_lead_bracket_reset (qk_tap_dance_state_t *state, void *user_data);
void lalt_lead_bracket_finished (qk_tap_dance_state_t *state, void *user_data);

enum tap_dance{
  TD_PgUp_Home,
  TD_PgDn_End,
  TD_PSCREEN_SLEEP,
  X_CTL_BRK,
  X_SHIFT_BRK,
  X_ALT_BRK,
//   X_LCTL_LEAD,
//   X_RCTL_LEAD,  
  X_LALT_LEAD,
  X_RALT_LEAD
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_PgUp_Home]  = ACTION_TAP_DANCE_DOUBLE(KC_PGUP, KC_HOME),
  [TD_PgDn_End]  = ACTION_TAP_DANCE_DOUBLE(KC_PGDN, KC_END),

  [TD_PSCREEN_SLEEP] = ACTION_TAP_DANCE_FN (print_sleep),

  [X_CTL_BRK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, open_bracket_finished, open_bracket_reset),
  [X_SHIFT_BRK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, close_bracket_finished, close_bracket_reset),
  [X_ALT_BRK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, openSql_bracket_finished, openSql_bracket_reset),

//   [X_LCTL_LEAD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lctl_lead_bracket_finished, lctl_lead_bracket_reset),
//   [X_RCTL_LEAD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rctl_lead_bracket_finished, rctl_lead_bracket_reset),

  [X_LALT_LEAD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lalt_lead_bracket_finished, lalt_lead_bracket_reset),
  [X_RALT_LEAD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ralt_lead_bracket_finished, ralt_lead_bracket_reset),
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [l_base] = LAYOUT_65_ansi_blocker( /* Base */
        KC_ESC,           LP_1,     LP_2,     LP_3,     LP_4,   LP_5,  LP_6,    LP_7,         LP_8,         LP_9,         LP_0,     LP_MINS,  LP_EQL,   KC_BSPC,   KC_DEL,
        KC_TAB,           KC_Q,     KC_W,     KC_E,     KC_R,   KC_T,  KC_Y,    LP_Uuml,      KC_I,         LP_Ouml,      KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLASH, TD_PgUp_Home, 
        LT(l_fn,KC_BSPC), LP_Auml,  KC_S,     KC_D,     KC_F,   KC_G,  KC_H,    LCTL_T(KC_J), LSFT_T(KC_K), LALT_T(KC_L), KC_SCLN,  KC_QUOT,            KC_ENT,    TD_PgDn_End, 
        KC_LSHIFT,        KC_Z,     KC_X,     KC_C,     KC_V,   KC_B,  KC_N,    KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,  KC_RSHIFT,		    KC_UP,     TD_PSCREEN_SLEEP,
        KC_LCTL,          KC_LGUI,  X_LALT_LEAD,            LT(l_fn,KC_SPC),                  X_RALT_LEAD,  KC_RCTRL,                          KC_LEFT, KC_DOWN,   KC_RIGHT
    ),

    [l_gaming] = LAYOUT_65_ansi_blocker( /* Gaming, no tapdancing etc */
        KC_ESC,           KC_1,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,   KC_DEL,
        KC_TAB,           KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSLASH, KC_PGUP, 
        LT(l_fn,KC_BSPC), KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,    KC_L,     KC_SCLN,  KC_QUOT,           KC_ENT,    KC_PGDOWN, 
        KC_LSHIFT,        KC_Z,     KC_X,     KC_C,  KC_V,  KC_B,  KC_N,    KC_M,  KC_COMM, KC_DOT,   KC_SLSH,  KC_RSHIFT,	   	   KC_UP,     TD_PSCREEN_SLEEP,
        KC_LCTL,          KC_LGUI,  KC_LALT,                KC_SPC,                KC_RALT, KC_RCTRL,                     KC_LEFT, KC_DOWN,   KC_RIGHT
    ),

    // [l_fKeys] = LAYOUT_65_ansi_blocker( /* F Keys layer, toggle on for debugging */
    //     _______,        LP_F1,   LP_F2,   LP_F3,  LP_F4,   LP_F5,   LP_F6,   LP_F7,   LP_F8,   LP_F9,   LP_F10,   LP_F11,   LP_F12,  _______, _______,
    //     _______,       _______,  _______, _______,_______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______,
    //     _______,       _______,  _______, _______,_______, _______, _______, _______, _______, _______, _______,  _______,           _______, _______,
    //     _______,       _______,  _______, _______,_______, _______, _______, _______, _______, _______, _______,  _______,           _______, _______,
    //     _______,       _______,  _______,                  _______,                   _______, _______,           _______,           _______, _______
    // ),

    [l_num] = LAYOUT_65_ansi_blocker( /* Numpad layer */
        _______,       _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______,  _______, _______, _______,
        _______,       _______,  _______, _______, _______, _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_PLUS,     _______,  _______, _______, _______,
        _______,       _______,  _______, _______, _______, _______, _______, KC_KP_1, KC_KP_2, KC_KP_3, _______,        _______,           _______, _______,
        _______,       _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______,           _______, _______,
        _______,       _______,  _______,                   _______,                   _______, _______,                 _______,           _______, _______
    ),

    [l_fn] = LAYOUT_65_ansi_blocker( /* Fn layer */
        KC_GRV,        KC_F1,    KC_F2,     KC_F3,   KC_F4,   KC_F5,   KC_F6, KC_F7,          KC_F8,        KC_F9,         KC_F10,   KC_F11,  KC_F12,  _______,   TG(l_rgb),
        _______,       _______,  KC_HOME,   KC_UP,  KC_END, _______, _______, _______,         _______,     _______,       _______,  _______, _______, _______,   _______,
        _______,       _______,  KC_LEFT, KC_DOWN,KC_RIGHT, C_MIN  , C_PLS  , X_CTL_BRK,      X_SHIFT_BRK,  X_ALT_BRK,     _______,  _______,          KC_INSERT, _______,
        _______,       _______,  KC_CUT , KC_COPY, KC_PSTE, C_EQL  , C_EXPL, _______,         _______,      _______,       _______,  _______,          KC_VOLU,   KC_MUTE,
        _______,       _______,  _______,                   _______,                          _______,      _______,                          KC_MPRV, KC_VOLD,   KC_MNXT
    ),

    [l_rgb] = LAYOUT_65_ansi_blocker( /* RGB, RESET layer*/
        TG(l_rgb),     XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  RGB_SPD, RGB_SPI,   RESET,   RGB_MOD,
        _______,       XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,   RGB_SAI,
        _______,	   XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,          EEP_RST,   RGB_SAD,
        _______,       XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  _______,          RGB_VAI,   RGB_TOG,
        _______,       _______,  _______,                    _______,                   _______, _______,                    RGB_HUD, RGB_VAD,   RGB_HUI
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        //COMPLEX SHORT LONG PRESS
        case LT(_LONG_PRESS_COMPLEX, 0) ... LT(_LONG_PRESS_COMPLEX, 0xff):
            if (record->event.pressed) {
                if (record->tap.count == 0)
                    { do_lp_hold(keycode, record); return false; }
                else
                    { do_lp_tap(keycode, record); return false; }
            }
        case C_EXPL: SEND_STRING("!"); return false;
        case C_EQL: SEND_STRING("="); return false;
        case C_MIN: SEND_STRING("-"); return false;
        case C_PLS: SEND_STRING("+"); return false;
        case KC_SPC:
            if (record->event.pressed) 
            {
                if (get_mods() & MOD_MASK_SHIFT) { register_code16(KC_UNDERSCORE); return false; }
            } 
            else 
            {
                if (get_mods() & MOD_MASK_SHIFT) { unregister_code16(KC_UNDERSCORE); return false; }
            }
            return true;
    }
    return true;
};

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_THREE_KEYS(KC_H, KC_U, KC_G) {
      SEND_STRING(PRIVATE_MAIL);
    }
    SEQ_THREE_KEYS(KC_H, KC_U, KC_H) {
      SEND_STRING(HAW_MAIL);
    }

    SEQ_ONE_KEY(KC_COMM) {
    //   tap_code16(TG(l_fKeys));
      reverse_number_keys = !reverse_number_keys;
      //tap_code16(C_REVERSE_NUMBERS);
    }
    SEQ_ONE_KEY(KC_DOT) {
      layer_invert(l_num);
    }
    SEQ_ONE_KEY(KC_SLSH) {
      layer_invert(l_gaming);
    }
  }
}

//Auto repeat on 1x tap 1x hold
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LP_Auml:
    case LP_Uuml:
    case LP_Ouml:
      return true;
    default:
      return false;
  }
}

//Tapping term per key. use whole keycode
uint16_t get_tapping_term(uint16_t keycode) {
  switch (keycode) {
    case LP_1 ... LP_EQL:
        return CUSTOM_TAPPING_TERM_FOR_NUMBERS;
    case LP_Auml:
    case LP_Ouml:
    case LP_Uuml:
        return CUSTOM_TAPPING_TERM_FOR_UMLAUTE;
    default:
        return TAPPING_TERM;
  }
};

//////////////////////////////////////////////////////////////////////                  Custom Functions                  //////////////////////////////////////////////////////////////////////

///     SHORT LONG PRESS     ///
    static void do_lp_tap(uint16_t keycode, keyrecord_t *record) {
        if (!reverse_number_keys){
            // number -> number
            switch (keycode){
                case LP_1 ... LP_0:     tap_code(keycode - LP_1 + KC_1); return;
                case LP_MINS:           tap_code(KC_MINS); return;
                case LP_EQL:            tap_code(KC_EQL); return;  
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

            // // number -> number
            // case LP_1 ... LP_0:     tap_code(keycode - LP_1 + KC_1); return;
            // case LP_MINS:           tap_code(KC_MINS); return;
            // case LP_EQL:            tap_code(KC_EQL); return;        
            
            // // fkey -> fkey 
            // case LP_F1 ... LP_F10:  tap_code(keycode - LP_F1 + KC_1); return;
            // case LP_F11:            tap_code(KC_F11); return;
            // case LP_F12:            tap_code(KC_F12); return;
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
            case LP_Auml:           register_code(KC_RALT);   tap_code(KC_Q);   unregister_code(KC_RALT); return; //Ä
            case LP_Uuml:           register_code(KC_RALT);   tap_code(KC_Y);   unregister_code(KC_RALT); return; //Ü
            case LP_Ouml:           register_code(KC_RALT);   tap_code(KC_P);   unregister_code(KC_RALT); return; //Ö
            // A O U -> Ä Ö Ü
            // case LP_Auml:           process_unicodemap(XP(aUml,AUml), record);    return;
            // case LP_Uuml:           process_unicodemap(XP(aUml,AUml), record);    return;
            // case LP_Ouml:           process_unicodemap(XP(aUml,AUml), record);    return;

            // // number -> fkey
            // case LP_1 ... LP_0:     tap_code(keycode - LP_1 + KC_F1); return;
            // case LP_MINS:           tap_code(KC_F11); return;
            // case LP_EQL:            tap_code(KC_F12); return;            

            // // fkey -> number             
            // case LP_F1 ... LP_F10:  tap_code(keycode - LP_1 + KC_1); return;
            // case LP_F11:            tap_code(KC_MINS); return;
            // case LP_F12:            tap_code(KC_EQL); return;
        }
    };

///  Custom Tap Dances  ///
    // 1x = leadr, 2x = print, 3x = sleep //
    void print_sleep(qk_tap_dance_state_t *state, void *user_data) {
        switch (state->count)
        {
            case (1): tap_code(KC_PSCREEN);          break;
            case (2): tap_code(KC_SYSTEM_SLEEP);     break;
        }
    };

///  Custom Advanced Tap Dances  ///
    /*instanalize an instance of 'tap' for the 'x' tap dance. */    
    static tap xtap_state = {
    .is_press_action = true,
    .state = 0
    };

    /* send '(' on tap, 'ctrl' hold */
    void open_bracket_finished (qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance_1t_1h(state);
        switch (xtap_state.state) {
            case SINGLE_TAP: SEND_STRING("(");
            case SINGLE_HOLD: register_code(KC_LCTRL); break;
        }
    }
    void open_bracket_reset (qk_tap_dance_state_t *state, void *user_data) {
        switch (xtap_state.state) {
            //case SINGLE_TAP: unregister_code(KC_X); break;
            case SINGLE_HOLD: unregister_code(KC_LCTRL); break;
        }
    }

    /* send ')' on tap, 'shift' hold */
    void close_bracket_finished (qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance_1t_1h(state);
        switch (xtap_state.state) {
            case SINGLE_TAP: SEND_STRING(")");
            case SINGLE_HOLD: register_code(KC_LSHIFT); break;
        }   
    }
    void close_bracket_reset (qk_tap_dance_state_t *state, void *user_data) {
        switch (xtap_state.state) {
            //case SINGLE_TAP: unregister_code(KC_X); break;
            case SINGLE_HOLD: unregister_code(KC_LSHIFT); break;
        }
    }

    /* send '{' on tap, 'alt' hold */
    void openSql_bracket_finished (qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance_1t_1h(state);
        switch (xtap_state.state) {
            case SINGLE_TAP: SEND_STRING("{");
            case SINGLE_HOLD: register_code(KC_LALT); break;
        }
    }
    void openSql_bracket_reset (qk_tap_dance_state_t *state, void *user_data) {
        switch (xtap_state.state) {
            //case SINGLE_TAP: unregister_code(KC_X); break;
            case SINGLE_HOLD: unregister_code(KC_LSHIFT); break;
        }
    }    

    // /* send 'KC_LEAD' on tap, LCTL on Hold*/
    // void lctl_lead_bracket_finished (qk_tap_dance_state_t *state, void *user_data) {
    // xtap_state.state = cur_dance_1t_1h(state);
    //     switch (xtap_state.state) {
    //         case SINGLE_TAP: register_code16(KC_LEAD); break;
    //         case SINGLE_HOLD: register_code(KC_LCTL); break;
    //     }
    // }
    // void lctl_lead_bracket_reset (qk_tap_dance_state_t *state, void *user_data) {
    //     switch (xtap_state.state) {
    //         case SINGLE_TAP: unregister_code16(KC_LEAD); break;
    //         case SINGLE_HOLD: unregister_code(KC_LCTL); break;
    //     }
    // }
    // /* send 'KC_LEAD' on tap, RCTL on Hold*/
    // void rctl_lead_bracket_finished (qk_tap_dance_state_t *state, void *user_data) {
    // xtap_state.state = cur_dance_1t_1h(state);
    //     switch (xtap_state.state) {
    //         case SINGLE_TAP: register_code16(KC_LEAD); break;
    //         case SINGLE_HOLD: register_code(KC_RCTL); break;
    //     }
    // }
    // void rctl_lead_bracket_reset (qk_tap_dance_state_t *state, void *user_data) {
    //     switch (xtap_state.state) {
    //         case SINGLE_TAP: unregister_code16(KC_LEAD); break;
    //         case SINGLE_HOLD: unregister_code(KC_RCTL); break;
    //     }
    // }

    /* send 'KC_LEAD' on tap, RALT on Hold*/
    void lalt_lead_bracket_finished (qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance_1t_1h(state);
        switch (xtap_state.state) {
            case SINGLE_TAP: register_code16(KC_LEAD); break;
            case SINGLE_HOLD: register_code(KC_LALT); break;
        }
    }
    void lalt_lead_bracket_reset (qk_tap_dance_state_t *state, void *user_data) {
        switch (xtap_state.state) {
            case SINGLE_TAP: unregister_code16(KC_LEAD); break;
            case SINGLE_HOLD: unregister_code(KC_LALT); break;
        }
    }
    /* send 'KC_LEAD' on tap, RALT on Hold*/
    void ralt_lead_bracket_finished (qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance_1t_1h(state);
        switch (xtap_state.state) {
            case SINGLE_TAP: register_code16(KC_LEAD); break;
            case SINGLE_HOLD: register_code(KC_RALT); break;
        }
    }
    void ralt_lead_bracket_reset (qk_tap_dance_state_t *state, void *user_data) {
        switch (xtap_state.state) {
            case SINGLE_TAP: unregister_code16(KC_LEAD); break;
            case SINGLE_HOLD: unregister_code(KC_RALT); break;
        }
    }
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^           Custom Functions             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//////////////////////////////////////////////////////////////////////           Advanced Tap Dance           //////////////////////////////////////////////////////////////////////
int cur_dance_1t_1h (qk_tap_dance_state_t *state) {
    if (!state->pressed)  return SINGLE_TAP;
    else return SINGLE_HOLD;
};


// helper function
// static bool is_shifted(){
//     bool shift = unicode_saved_mods & MOD_MASK_SHIFT;
//     bool caps = IS_HOST_LED_ON(USB_LED_CAPS_LOCK);
//     return shift ^ caps;
// }