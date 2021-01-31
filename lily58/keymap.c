#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern uint8_t is_master;

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

#define L_LANG1 LT(_LOWER, KC_LANG1)
#define L_LANG2 LT(_LOWER, KC_LANG2)
#define R_LANG1 LT(_RAISE, KC_LANG1)
#define R_LANG2 LT(_RAISE, KC_LANG2)

#define QVOLU LALT(LSFT(KC__VOLUP))
#define QVOLD LALT(LSFT(KC__VOLDOWN))

#define LMOVE LGUI(LSFT(KC_LBRC))
#define RMOVE LGUI(LSFT(KC_RBRC))

#define OS_MUTE LCTL(LSFT(LALT(KC_M)))

#define SFT_ESC MT(MOD_LSFT, KC_ESC)
#define SFT_BSPC MT(MOD_RSFT, KC_BSPC)

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
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
  KC_LCTRL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT, \
  SFT_ESC,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC__MUTE, OS_MUTE,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT, \
                        MO(_ADJUST),KC_LALT,KC_LGUI,    L_LANG2,  R_LANG1,  KC_SPC,  SFT_BSPC, MO(_ADJUST) \
),

[_LOWER] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______,_______, _______,  _______,\
  KC_TILD, KC_EXLM,  KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS, \
  KC_GRV,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PIPE, \
  _______,_______,  _______, _______, _______,  _______, _______, _______,  KC_PLUS, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_EQL, \
                             _______, _______, _______, _______, _______,  _______, _______, _______\
),

[_RAISE] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______, \
  KC_ESC,  _______, _______, _______, _______, _______,                    XXXXXXX, KC_HOME, KC_UP,   KC_END,  XXXXXXX, KC_BSPC, \
  _______, _______, _______, _______, _______, _______,                    KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, \
  _______, _______, _______, _______, _______, _______, _______, _______,  KC_PGDN, LMOVE,   CT_LGRV, RMOVE,   XXXXXXX, XXXXXXX, \
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
),

[_ADJUST] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, QVOLD,   QVOLU,   KC__MUTE,XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MRWD, KC_MPLY, KC_MFFD, XXXXXXX, XXXXXXX,\
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
  )
};

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
