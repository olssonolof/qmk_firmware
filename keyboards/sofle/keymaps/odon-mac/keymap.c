#include QMK_KEYBOARD_H
#include "keymap_swedish.h"
#include "oled_tetris.h"
#include "sendstring_swedish.h"


enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NUMPAD
};


enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_PRVWD,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND,
    KC_DLINE,
    MY_TILD,
    MY_BCKT,
    MY_CIRC

};

#define ___X___ _______
#define PRV_WORD_M  LALT(KC_LEFT)
#define NXT_WORD_M  LALT(KC_RGHT)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  ESC |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |    ""              |   Y  |   U  |   I  |   O  |   P  | Å    |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  ESC |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   Ö  |  Ä   |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   -  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt |LCTRL |LOWER | /Enter  /       \Space \  |RAISE | NUMPD| RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */


[_QWERTY] = LAYOUT(
  KC_ESC,   SE_1,   SE_2,    SE_3,    SE_4,    SE_5,                     SE_6,    SE_7,    SE_8,    SE_9,    SE_0,  KC_BSPC,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  SE_ARNG,
  KC_ESC,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, SE_ODIA,  SE_ADIA,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,KC_MPLY,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
                 KC_LGUI,KC_LALT,KC_LCTL, MO(_LOWER), KC_ENT,      KC_SPC,  MO(_RAISE), MO(_NUMPAD), KC_RALT, KC_RGUI
),


/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  '   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  DEL |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  |   |   !  |   "  |   #  |   $  |   %  |                    |   &  |   /  |   (  |   )  |   =  |   ?  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   `  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   \  |   ~  |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | Shift|  <   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |   ;  |   :  |   '  | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_LOWER] = LAYOUT(
  SE_QUOT,   SE_1,    SE_2,    SE_3,    SE_4,    SE_5,                       SE_6,    SE_7,    SE_8,    SE_9,  SE_0,KC_DEL,
  LALT(KC_7), SE_EXLM, SE_DQUO,  SE_HASH,  SE_DLR,  SE_PERC,                      SE_AMPR, SE_SLSH, SE_LPRN, SE_RPRN, SE_EQL ,SE_QUES,
  _______, MY_BCKT, SE_AT, KC_HASH,  KC_DLR, KC_PERC,                       MY_CIRC, KC_AMPR, SE_ASTR, KC_LPRN, LSA(KC_7), MY_TILD,
  _______, SE_LABK, KC_MINS, KC_PLUS, LSA(KC_8), LSA(KC_9), _______,       _______, SE_LBRC, SE_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,
                       _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
),
/* RAISE
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  |  F10 | F11  |  F12 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  | Ins  | Pscr | Menu |      |      |                    | PGUP | PWrd |  Up  | NWrd | DLine| Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  | LAt  | LCtl |LShift|      | Caps |-------.    ,-------| PGDN | Left | Down | Rigth|  Del | Bspc |
 * |------+------+------+------+------+------|  MUTE  |    |      |------+------+------+------+------+------|
 * |Shift | Undo |  Cut | Copy | Paste|      |-------|    |-------|      | LStr |      | LEnd |      | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11, KC_F12,
  _______,  KC_INS,  KC_PSCR,   KC_APP,  XXXXXXX, XXXXXXX,                        KC_PGUP, PRV_WORD_M,   KC_UP, NXT_WORD_M,KC_DLINE, KC_BSPC,
  _______, KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX, KC_CAPS,                       KC_PGDN,  KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL, KC_BSPC,
  _______,KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, XXXXXXX,  _______,       _______,  XXXXXXX, LGUI(KC_LEFT), XXXXXXX, LGUI(KC_RIGHT),   XXXXXXX, _______,
                         _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
),

/* NUMPAD
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  '   |   1  |   2  |   3  |   4  |   5  |                    |   /  |   7  |   8  |   9  |   *  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  |   |   !  |   "  |   #  |   $  |   %  |                    |   &  |   4  |   5  |   6  |   =  |   ?  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   `  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   1  |   2  |   3  |   \  |   ~  |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | Shift|  <   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   0  |   ;  |   :  |   '  | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_NUMPAD] = LAYOUT(
  SE_QUOT,   SE_1,    SE_2,    SE_3,    SE_4,    SE_5,                       SE_SLSH,    SE_7,    SE_8,    SE_9, SE_ASTR, SE_MINS,
  SE_PIPE, SE_EXLM, SE_DQUO,  SE_HASH,  SE_DLR,  SE_PERC,                      SE_SLSH, SE_4, SE_5, SE_6, SE_EQL , SE_PLUS,
  _______, MY_BCKT, SE_AT, KC_HASH,  SE_DLR, SE_PERC,                       MY_CIRC, SE_1, SE_2, SE_3, SE_BSLS, MY_TILD,
  _______, SE_LABK, KC_MINS, KC_PLUS, SE_LCBR, SE_RCBR, _______,       _______, SE_LBRC, SE_0, KC_SCLN, KC_COLN, KC_BSLS, _______,
                       _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | QK_BOOT|      |QWERTY|    |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |MACWIN|      |      |      |-------.    ,-------|      | VOLDO| MUTE | VOLUP|      |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | PREV | PLAY | NEXT |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  [_ADJUST] = LAYOUT(
  XXXXXXX , XXXXXXX,  XXXXXXX ,  XXXXXXX , XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  QK_BOOT  , XXXXXXX,KC_QWERTY,XXXXXXX,CG_TOGG,XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX , XXXXXXX,CG_TOGG, XXXXXXX,    XXXXXXX,  XXXXXXX,                     XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
  XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
                   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
  )
};



#ifdef OLED_ENABLE

static uint32_t total_char_count                      = 0;
static uint32_t oled_typing_animation_last_keypress   = 0;
static uint32_t master_pet_action_started             = 0;
static uint8_t  oled_typing_animation_cycle           = 0;
static uint8_t  master_pet_action                     = 0;
static const char PROGMEM oled_blank_row[]            = "     ";

#define OLED_TYPING_FRAME_INTERVAL   180
#define OLED_TYPING_ACTIVE_DURATION  1200
#define MASTER_PET_BURST_GAP         350
#define MASTER_PET_VARIANT_HOLD      500
#define MASTER_PET_FRAME_SIZE        96
#define MASTER_PET_PAGE_WIDTH        32
#define MASTER_PET_SOURCE_WIDTH      32
#define MASTER_PET_SOURCE_HEIGHT     24
#define MASTER_PET_AREA_PAGE_COUNT   8
#define MASTER_PET_DRAW_HEIGHT       40
#define MASTER_PET_TOP_MARGIN        2

enum {
    MASTER_PET_ACTION_WALK = 0,
    MASTER_PET_ACTION_RUN,
    MASTER_PET_ACTION_BARK,
    MASTER_PET_ACTION_SNEAK,
    MASTER_PET_ACTION_COUNT,
};

static const char PROGMEM master_pet_blank_page[MASTER_PET_PAGE_WIDTH] = {0};

static const char PROGMEM master_pet_idle[2][MASTER_PET_FRAME_SIZE] = {
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    },
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    },
};

static const char PROGMEM master_pet_walk[2][MASTER_PET_FRAME_SIZE] = {
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80, 0x80, 0x70, 0x08, 0x14, 0x08, 0x90, 0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03, 0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    },
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    },
};

static const char PROGMEM master_pet_run[2][MASTER_PET_FRAME_SIZE] = {
    {
        0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    },
    {
        0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    },
};

static const char PROGMEM master_pet_bark[2][MASTER_PET_FRAME_SIZE] = {
    {
        0x00, 0xc0, 0x20, 0x10, 0xd0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    },
    {
        0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x2c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    },
};

static const char PROGMEM master_pet_sneak[2][MASTER_PET_FRAME_SIZE] = {
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04, 0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09, 0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06, 0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    },
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04, 0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    },
};

static void format_right_aligned_value(uint32_t value, char *buffer, uint8_t width) {
    for (uint8_t i = 0; i < width; i++) {
        buffer[i] = ' ';
    }

    if (width == 0) {
        return;
    }

    if (value == 0) {
        buffer[width - 1] = '0';
        return;
    }

    for (int8_t i = (int8_t)width - 1; i >= 0 && value > 0; i--) {
        buffer[i] = '0' + (value % 10U);
        value /= 10U;
    }
}

static void format_exact_value(uint32_t value, char buffer[6]) {
    format_right_aligned_value(value, buffer, 5);
    buffer[5] = '\0';
}

static void format_total_count(uint32_t value, char buffer[6]) {
    format_right_aligned_value(0, buffer, 5);
    buffer[5] = '\0';

    if (value < 100000UL) {
        format_right_aligned_value(value, buffer, 5);
        return;
    }

    if (value < 1000000UL) {
        format_right_aligned_value(value / 1000UL, buffer, 4);
        buffer[4] = 'K';
        return;
    }

    buffer[0] = '9';
    buffer[1] = '9';
    buffer[2] = '9';
    buffer[3] = 'K';
    buffer[4] = '+';
}

static bool is_counted_char_keycode(uint16_t keycode) {
    if (IS_QK_MODS(keycode)) {
        keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
    }

    switch (keycode) {
        case MY_BCKT:
        case MY_CIRC:
        case MY_TILD:
        case KC_A ... KC_Z:
        case KC_1 ... KC_0:
        case KC_MINS ... KC_SLSH:
        case KC_SPC:
            return true;
        default:
            return false;
    }
}

static void write_oled_row(uint8_t row, const char *text) {
    oled_set_cursor(0, row);
    oled_write(text, false);
}

static void write_oled_row_P(uint8_t row, PGM_P text, bool invert) {
    oled_set_cursor(0, row);
    oled_write_P(text, invert);
}

static void trigger_oled_typing_animation(uint16_t keycode) {
    uint32_t now       = timer_read32();
    bool     new_burst = oled_typing_animation_last_keypress == 0 || timer_elapsed32(oled_typing_animation_last_keypress) > MASTER_PET_BURST_GAP;
    bool     can_swap  = master_pet_action_started == 0 || timer_elapsed32(master_pet_action_started) > MASTER_PET_VARIANT_HOLD;

    if (new_burst || (can_swap && ((oled_typing_animation_cycle + keycode) & 0x03U) == 0U)) {
        master_pet_action         = (uint8_t)((now + ((uint32_t)keycode * 17U) + (total_char_count * 5UL) + ((uint32_t)oled_typing_animation_cycle * 11U)) % MASTER_PET_ACTION_COUNT);
        master_pet_action_started = now;
    }

    oled_typing_animation_last_keypress = now;
    oled_typing_animation_cycle++;
}

static bool is_master_pet_active(void) {
    if (oled_typing_animation_last_keypress == 0) {
        return false;
    }

    return timer_elapsed32(oled_typing_animation_last_keypress) <= OLED_TYPING_ACTIVE_DURATION;
}

static void clear_master_pet_area(uint8_t start_row) {
    for (uint8_t page = 0; page < MASTER_PET_AREA_PAGE_COUNT; page++) {
        oled_set_cursor(0, start_row + page);
        oled_write_raw_P(master_pet_blank_page, MASTER_PET_PAGE_WIDTH);
    }
}

static bool master_pet_pixel_is_set(const char *frame, uint8_t x, uint8_t y) {
    uint8_t byte = pgm_read_byte(&frame[((y / 8U) * MASTER_PET_SOURCE_WIDTH) + x]);
    return (byte & (1U << (y % 8U))) != 0;
}

static void draw_master_pet_frame_scaled(const char *frame, uint8_t start_row) {
    uint8_t draw_y = (start_row * 8U) + MASTER_PET_TOP_MARGIN;

    for (uint8_t x = 0; x < MASTER_PET_SOURCE_WIDTH; x++) {
        for (uint8_t y = 0; y < MASTER_PET_SOURCE_HEIGHT; y++) {
            if (!master_pet_pixel_is_set(frame, x, y)) {
                continue;
            }

            uint8_t scaled_start = (y * MASTER_PET_DRAW_HEIGHT) / MASTER_PET_SOURCE_HEIGHT;
            uint8_t scaled_end   = ((y + 1U) * MASTER_PET_DRAW_HEIGHT) / MASTER_PET_SOURCE_HEIGHT;

            if (scaled_end <= scaled_start) {
                scaled_end = scaled_start + 1U;
            }

            for (uint8_t target_y = scaled_start; target_y < scaled_end; target_y++) {
                oled_write_pixel(x, draw_y + target_y, true);
            }
        }
    }
}

static const char *get_master_pet_idle_frame(void) {
    return master_pet_idle[(timer_read32() / 450U) % 2U];
}

static const char *get_master_pet_active_frame(uint8_t frame) {
    switch (master_pet_action) {
        case MASTER_PET_ACTION_WALK:
            return master_pet_walk[frame];
        case MASTER_PET_ACTION_BARK:
            return master_pet_bark[frame];
        case MASTER_PET_ACTION_SNEAK:
            return master_pet_sneak[frame];
        case MASTER_PET_ACTION_RUN:
        default:
            return master_pet_run[frame];
    }
}

static bool is_oled_idle_timed_out(void) {
#if OLED_TIMEOUT > 0
    return last_input_activity_elapsed() > OLED_TIMEOUT && last_led_activity_elapsed() > OLED_TIMEOUT;
#else
    return false;
#endif
}

static void render_master_typing_animation(uint8_t start_row) {
    clear_master_pet_area(start_row);

    if (is_master_pet_active()) {
        uint8_t frame = (oled_typing_animation_cycle + (timer_elapsed32(oled_typing_animation_last_keypress) / OLED_TYPING_FRAME_INTERVAL)) % 2U;
        draw_master_pet_frame_scaled(get_master_pet_active_frame(frame), start_row);
        return;
    }

    draw_master_pet_frame_scaled(get_master_pet_idle_frame(), start_row);
}

static void render_master_stats(void) {
    char   value_text[6];

    write_oled_row_P(0, PSTR("WPM  "), false);
    format_exact_value(get_current_wpm(), value_text);
    write_oled_row(1, value_text);

    write_oled_row_P(2, oled_blank_row, false);
    write_oled_row_P(3, PSTR("CHARS"), false);
    format_total_count(total_char_count, value_text);
    write_oled_row(4, value_text);

    write_oled_row_P(5, oled_blank_row, false);
    write_oled_row_P(6, oled_blank_row, false);
    write_oled_row_P(7, oled_blank_row, false);
    render_master_typing_animation(8);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    (void)rotation;
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
#if OLED_TIMEOUT > 0
    if (is_oled_idle_timed_out()) {
        oled_off();
        return false;
    }

    oled_on();
#endif

    if (is_keyboard_master()) {
        render_master_stats();
    } else {
        oled_tetris_render();
    }
    return false;
}

#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
    if (record->event.pressed) {
        trigger_oled_typing_animation(keycode);

        if (is_counted_char_keycode(keycode)) {
            total_char_count++;
        }
    }
#endif

    switch (keycode) {
        case MY_BCKT:
            if (record->event.pressed) {
                SEND_STRING("`");
        }
        break;
        case MY_CIRC:
            if (record->event.pressed) {
                SEND_STRING("^");
        }
        break;
        case MY_TILD:
            if (record->event.pressed) {
                SEND_STRING("~");
        }
        break;


        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            return false;
        case KC_PRVWD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                }
            }
            break;
        case KC_NXTWD:
             if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_LSTRT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                     //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_LEND:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            break;
        case KC_DLINE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_BSPC);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_BSPC);
            }
            break;
        case KC_COPY:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_C);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_C);
            }
            return false;
        case KC_PASTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_V);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_V);
            }
            return false;
        case KC_CUT:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_X);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_X);
            }
            return false;
            break;
        case KC_UNDO:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Z);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Z);
            }
            return false;
    }
    return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}

#endif
