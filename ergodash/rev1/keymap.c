#include QMK_KEYBOARD_H


#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

#define EISU LALT(KC_GRV)
#define KC_QVOLU LALT(LSFT(KC__VOLUP))
#define KC_QVOLD LALT(LSFT(KC__VOLDOWN))

#define L_LANG1 LT(_LOWER, KC_LANG1)
#define L_LANG2 LT(_LOWER, KC_LANG2)
#define R_LANG1 LT(_RAISE, KC_LANG1)
#define R_LANG2 LT(_RAISE, KC_LANG2)

#define QVOLU LALT(LSFT(KC__VOLUP))
#define QVOLD LALT(LSFT(KC__VOLDOWN))

#define LMOVE LGUI(LSFT(KC_LBRC))
#define RMOVE LGUI(LSFT(KC_RBRC))

#define CT_LGRV LCTL(KC_GRV)

#define LGUI_1 LGUI(KC_1)
#define LGUI_2 LGUI(KC_2)
#define LGUI_3 LGUI(KC_3)
#define LGUI_4 LGUI(KC_4)
#define LGUI_5 LGUI(KC_5)
#define LGUI_6 LGUI(KC_6)
#define LGUI_7 LGUI(KC_7)
#define LGUI_8 LGUI(KC_8)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX,                        KC_QVOLU, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXXXXXX,                        KC_QVOLD, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,                        KC_RBRC,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    L_LANG2,                        R_LANG1,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT, \
    KC_MRWD, KC_MPLY, KC_MFFD, KC_LALT,          KC_LGUI, L_LANG2 ,XXXXXXX,       XXXXXXX,R_LANG1,  KC_SPC,            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
  ),

  [_LOWER] = LAYOUT(
    KC_TILD, _______, _______, _______, _______, _______, _______,                        _______,_______, _______, _______, _______, _______,   KC_BSLS, \
    KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,                        _______,KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,   KC_PIPE,  \
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LCBR,                        KC_RCBR,KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      _______, \
    _______, _______, _______, _______, KC_EQL,  KC_PLUS, _______,                        _______, _______,_______, _______, _______,  _______, _______, \
    _______, _______, _______, _______,          _______, _______,_______,        _______,_______, _______,          _______, _______, _______, _______   \
  ),

  [_RAISE] = LAYOUT(
    _______, _______, _______, _______, _______, _______,_______,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    _______, _______, _______, _______, _______, _______,_______,                       XXXXXXX, XXXXXXX, LMOVE,   CT_LGRV, RMOVE,   XXXXXXX, XXXXXXX,  \
    _______, _______, _______, _______, _______, _______,KC_LCBR,                       KC_RCBR, KC_PGUP, KC_HOME, KC_UP,   KC_END,  XXXXXXX, XXXXXXX,     \
    _______, _______, _______, _______, _______, _______,_______,                       XXXXXXX , KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,XXXXXXX, XXXXXXX,     \
    _______, _______, _______, _______,          _______, _______,_______,        _______,_______, _______,          _______, _______, _______, _______   \
  ),

  [_ADJUST] = LAYOUT(
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI,_______,                       _______, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______, \
    _______, _______, BL_TOGG, BL_BRTG, BL_INC , BL_DEC ,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______,          _______,_______,_______,       _______,_______, _______,          _______, _______, _______, _______  \
  )
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
         print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
