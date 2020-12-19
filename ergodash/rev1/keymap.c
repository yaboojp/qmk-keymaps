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

#define KC_LLANG1 LT(_LOWER, KC_LANG1)
#define KC_LLANG2 LT(_LOWER, KC_LANG2)
#define KC_RLANG1 LT(_RAISE, KC_LANG1)
#define KC_RLANG2 LT(_RAISE, KC_LANG2)

#define KC_QVOLU LALT(LSFT(KC__VOLUP))
#define KC_QVOLD LALT(LSFT(KC__VOLDOWN))

#define KC_LMOVE LGUI(LSFT(KC_LBRC))
#define KC_RMOVE LGUI(LSFT(KC_RBRC))

#define KC_SCS1 LGUI(LSFT(LCTL(KC_9)))
#define KC_SCS2 LGUI(LSFT(KC_9))

#define KC_CTLGRV LCTL(KC_GRV)

#define KC_GUI_1 LGUI(KC_1)
#define KC_GUI_2 LGUI(KC_2)
#define KC_GUI_3 LGUI(KC_3)
#define KC_GUI_4 LGUI(KC_4)
#define KC_GUI_5 LGUI(KC_5)
#define KC_GUI_6 LGUI(KC_6)
#define KC_GUI_7 LGUI(KC_7)
#define KC_GUI_8 LGUI(KC_8)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


  [_QWERTY] = LAYOUT( \
    _______, _______, _______, _______, _______, _______, _______,                        _______,  _______, _______, _______, _______, _______, _______, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______,                        _______,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    _______,                        _______,  KC_H,    KC_J,    KC_K,    KC_L,    KC_COLN, KC_ENT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LLANG2,                      KC_RLANG1,KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT, \
    _______, _______, KC_LALT, KC_LALT,          KC_LGUI, KC_LLANG2,_______,      _______,KC_RLANG1,KC_SPC,           KC_BSPC, KC_ESC,  _______, _______  \
  ),

  [_LOWER] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______, _______, \
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,                         _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, \
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,                         _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
    _______, KC_GUI_1,KC_GUI_2,KC_GUI_3,KC_GUI_4,KC_GUI_5,_______,                         _______, KC_GUI_6,KC_GUI_7,KC_GUI_8, _______,KC_QUES, KC_DQUO, \
    _______, _______, _______, _______,          _______, _______,_______,         _______,_______, _______,          _______, _______, _______, _______  \
  ),

  [_RAISE] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______, _______, \
    _______, KC_GRV,  KC_BSLS, KC_EQL,  KC_PIPE, KC_PLUS, _______,                         _______, _______, KC_LMOVE,KC_CTLGRV,KC_RMOVE,_______, KC_UNDS, \
    _______, KC_TILD, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, _______,                         _______, KC_PGUP, KC_HOME, KC_UP,    KC_END,  KC_SCLN, _______, \
    _______, _______, _______, _______, _______, _______, _______,                         _______, KC_PGDN, KC_LEFT, KC_DOWN,  KC_RGHT, KC_QUES, KC_DQUO, \
    _______, _______, _______, _______,          _______, _______,_______,         _______,_______, _______,          _______,  _______, _______, _______  \
  ),

  [_ADJUST] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______, _______, \
    _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, _______,                         _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, BL_TOGG, BL_BRTG, BL_INC , BL_DEC , _______,                         _______, KC_MRWD, KC_MPLY, KC_MFFD, _______, _______, _______, \
    _______, KC_SCS1, KC_SCS2, _______, _______, _______, _______,                         _______, KC__MUTE,KC_QVOLD,KC_QVOLU,_______, _______, _______, \
    _______, _______, _______, _______,          _______, _______,_______,         _______,_______, _______,          _______, _______, _______, _______  \
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
