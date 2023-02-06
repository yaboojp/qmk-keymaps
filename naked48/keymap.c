#include QMK_KEYBOARD_H


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  RGB_RST = SAFE_RANGE
};

#define L_LANG1 LT(MO(1), KC_LNG1)
#define L_LANG2 LT(MO(1), KC_LNG2)
#define R_LANG1 LT(MO(2), KC_LNG1)
#define R_LANG2 LT(MO(2), KC_LNG2)

#define QVOLU LALT(LSFT(KC__VOLUP))
#define QVOLD LALT(LSFT(KC__VOLDOWN))

#define LMOVE LGUI(LSFT(KC_LBRC))
#define RMOVE LGUI(LSFT(KC_RBRC))

#define OS_MUTE LCTL(LSFT(LALT(KC_M)))

#define SFT_ESC MT(MOD_LSFT, KC_ESC)
#define SFT_BSPC MT(MOD_RSFT, KC_BSPC)
#define SFT_SPC MT(MOD_RSFT, KC_SPC)

#define CT_LGRV LCTL(KC_GRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,-----------------------------------------------------|                 |-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
       KC_LCTL,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_ENT,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
      SFT_ESC,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
           MO(_ADJUST),_______, KC_LALT,  KC_LGUI, L_LANG2, XXXXXXX, XXXXXXX, R_LANG1, SFT_SPC, KC_BSPC, KC_LEFT, KC_RIGHT
          //`------------------------------------------------------------------------------------------------------------'
  ),


  [_LOWER] = LAYOUT(
  //,-----------------------------------------------------|                 |-----------------------------------------------------.
      KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
      KC_GRV,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_PLUS, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_EQL,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
          //`------------------------------------------------------------------------------------------------------------'
  ),


  [_RAISE] = LAYOUT(
  //,-----------------------------------------------------|                 |-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                   KC_PGUP, KC_HOME, KC_UP,   KC_END,  XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                   OS_MUTE, LMOVE,   CT_LGRV, RMOVE,   XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
          //`------------------------------------------------------------------------------------------------------------'
  ),


  [_ADJUST] = LAYOUT( /* Base */
  //,-----------------------------------------------------|                 |-----------------------------------------------------.
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   RGB_RST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   RGB_TOG, RGB_MOD, XXXXXXX,LCA(KC_DEL),LALT(KC_PSCR),KC_PSCR,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   RGB_VAD, RGB_VAI, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
               _______, _______, _______, _______, _______,   QK_BOOT,   QK_BOOT, _______, _______, _______, _______, _______
          //`------------------------------------------------------------------------------------------------------------'
  )
};

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  bool result = false;
  switch (keycode) {
    #ifdef RGBLIGHT_ENABLE
      case RGB_MOD:
          if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
      case RGB_RST:
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
    #endif
    default:
      result = true;
      break;
  }

  return result;
}
