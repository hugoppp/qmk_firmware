#define FORCE_NKRO
#define TAPPING_TERM_PER_KEY
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 500


#define CUSTOM_TAPPING_TERM_MIN 125
#define TAPPING_TERM 200


//#define RGBLIGHT_ANIMATIONS



//#define RETRO_TAPPING
// #define LCPO_KEYS KC_LCTL, KC_LSFT, KC_LBRC //lCtrl -> {
// #define RCPC_KEYS KC_RCTL, KC_RSFT, KC_RBRC //rCtrl -> }
// #define LAPO_KEYS KC_LALT, KC_LSFT, KC_COMM //lAlt  -> <
// #define RAPC_KEYS KC_RALT, KC_RSFT, KC_DOT  //rAlt  -> >

//FAST TYPE FIXES
#define IGNORE_MOD_TAP_INTERRUPT


#undef PERMISSIVE_HOLD
//#define PERMISSIVE_HOLD_PER_KEY
#undef PREVENT_STUCK_MODIFIERS

#define TAPPING_FORCE_HOLD //enable repeating by taphold 
#define TAPPING_FORCE_HOLD_PER_KEY

#define ONESHOT_TAP_TOGGLE 2  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 2000  /* Time (in ms) before the one shot key is released */

#define UNICODE_SELECTED_MODES UC_WINC

//#define NO_ACTION_ONESHOT //disables oneshot mods

