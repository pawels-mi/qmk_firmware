#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "quantum/send_string/send_string.h"
#include "quantum/process_keycode/process_tap_dance.h"

// Tap Dance declarations
typedef struct {
    const char *cmd;
} qk_tap_dance_payload;

#define ACTION_TAP_DANCE_CUSTOM(user_fn, cmd) \
    { .fn = {NULL, user_fn, NULL}, .user_data = (void *)&((qk_tap_dance_payload){cmd}), }

enum {
    TD_M1, TD_M2, TD_M3, TD_M4, TD_M5
};

void tap_dance_handler(tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_payload *payload = (qk_tap_dance_payload *) user_data;

    send_string(payload->cmd);
    if (state->count == 1) {
        SEND_STRING("1" SS_TAP(X_ENTER));
    } else if (state->count == 2) {
        SEND_STRING("2" SS_TAP(X_ENTER));
        reset_tap_dance(state);
    }
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_M1] = ACTION_TAP_DANCE_CUSTOM(tap_dance_handler, "m1_"),
    [TD_M2] = ACTION_TAP_DANCE_CUSTOM(tap_dance_handler, "m2_"),
    [TD_M3] = ACTION_TAP_DANCE_CUSTOM(tap_dance_handler, "m3_"),
    [TD_M4] = ACTION_TAP_DANCE_CUSTOM(tap_dance_handler, "m4_"),
    [TD_M5] = ACTION_TAP_DANCE_CUSTOM(tap_dance_handler, "m5_"),
};


enum layers{
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    FN1,
    FN2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_tkl_f13_ansi(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    KC_MUTE,  KC_SNAP,  KC_SIRI,  RGB_MOD,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD, KC_ROPTN, MO(MAC_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_tkl_f13_ansi(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,     RGB_TOG,  KC_KP_7,      KC_KP_8,        KC_KP_9,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  KC_KP_4,      KC_KP_5,        KC_KP_6,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  KC_KP_1,      KC_KP_2,        KC_KP_3,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,                KC_KP_0,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  KC_KP_PLUS,   KC_KP_MINUS,    KC_KP_ASTERISK),

    [WIN_BASE] = LAYOUT_tkl_f13_ansi(
    /*  ESC             F1          F2          F3              F4              F5          F6          F7          F8          F9          F10             F11         F12         KNOB        PRINT       MIC         RGB         */
        KC_ESC,         KC_F1,      KC_F2,      KC_F3,          KC_F4,          KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,         KC_F11,     KC_F12,     KC_MUTE,    KC_PSCR,    RGB_VAI,    RGB_MOD,
    /*  TILDE           1           2           3               4               5           6           7           8           9           0               MINUS       EQUAL       BACKSP      INS         HOME        PAGE_UP     */
        KC_GRV,         KC_1,       KC_2,       KC_3,           KC_4,           KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,           KC_MINS,    KC_EQL,     KC_BSPC,    KC_INS,     KC_HOME,    KC_PGUP,
    /*  TAB             Q           W           E               R               T           Y           U           I           O           P               L.BRACKET   R.BRACKET   BACKSLSH    DEL         END         PAGE_DN     */
        LT(FN2, KC_TAB),KC_Q,       KC_W,       KC_E,           KC_R,           KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,           KC_LBRC,    KC_RBRC,    KC_BSLS,    KC_DEL,     KC_END,     KC_PGDN,
    /*  CAPS            A           S           D               F               G           H           J           K           L           SEMI COLN       QUOT                    ENTER                                           */
        MO(FN1),        KC_A,       KC_S,       KC_D,           KC_F,           KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,        KC_QUOT,                KC_ENT,
    /*  SHIFT           Z           X           C               V               B           N           M           COMMA       DOT         SLASH                                   SHIFT                   UP                      */
        KC_LSFT,        KC_Z,       KC_X,       KC_C,           KC_V,           KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,                                KC_RSFT,                KC_UP,
    /*  CTRL            WIN         ALT                                     SPACE                                               ALT         WIN             FN                      CTRL        LEFT        DOWN        RIGHT       */
        KC_LCTL,        KC_LWIN,    KC_LALT,                                KC_SPC,                                             KC_RALT,    KC_RWIN,        MO(FN1),                KC_RCTL,    KC_LEFT,    KC_DOWN,    KC_RGHT),

    [FN1] = LAYOUT_tkl_f13_ansi(
    /*  ESC             F1          F2          F3              F4              F5          F6          F7          F8          F9          F10             F11         F12         KNOB        PRINT       MIC         RGB         */
        _______,        KC_BRID,    KC_BRIU,    KC_TASK,        KC_FLXP,        RGB_VAD,    RGB_VAI,    KC_MPRV,    KC_MPLY,    KC_MNXT,    KC_MUTE,        KC_VOLD,    KC_VOLU,    RGB_TOG,    KC_KP_7,    KC_KP_8,    KC_KP_9,
    /*  TILDE           1           2           3               4               5           6           7           8           9           0               MINUS       EQUAL       BACKSP      INS         HOME        PAGE_UP     */
        _______,        C(KC_1),    C(KC_2),    C(KC_3),        C(KC_4),        _______,    _______,    _______,    _______,    _______,    _______,        _______,    _______,    _______,    KC_KP_4,    KC_KP_5,    KC_KP_6,
    /*  TAB             Q           W           E               R               T           Y           U           I           O           P               L.BRACKET   R.BRACKET   BACKSLSH    DEL         END         PAGE_DN     */
        _______,        _______,    C(KC_W),    _______,        C(KC_R),        C(KC_T),    _______,    KC_BSPC,    KC_DEL,     _______,    _______,        _______,    _______,    _______,    KC_KP_1,    KC_KP_2,    KC_KP_3,
    /*  CAPS            A           S           D               F               G           H           J           K           L           SEMI COLN       QUOT                    ENTER                                           */
        _______,        C(KC_A),    C(KC_S),    _______,        C(KC_F),        _______,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   KC_HOME,        KC_END,                 _______,
    /*  SHIFT           Z           X           C               V               B           N           M           COMMA       DOT         SLASH                                   SHIFT                   UP                      */
        _______,        C(KC_Z),    C(KC_X),    C(KC_C),        C(KC_V),        _______,    S(KC_INS),  _______,    _______,    _______,    _______,                                _______,                KC_KP_0,
    /*  CTRL            WIN         ALT                                     SPACE                                               ALT         WIN             FN                      CTRL        LEFT        DOWN        RIGHT       */
        _______,        _______,    KC_LCTL,                                LSFT_T(KC_ENT),                                     MO(FN2),    _______,        _______,                _______,    KC_KP_PLUS, KC_KP_MINUS,KC_KP_ASTERISK),

    [FN2] = LAYOUT_tkl_f13_ansi(
    /*  ESC             F1          F2          F3              F4              F5          F6          F7          F8          F9          F10             F11         F12         KNOB        PRINT       MIC         RGB         */
        _______,        _______,    _______,    _______,        _______,        _______,    _______,    _______,    _______,    _______,    _______,        _______,    _______,    _______,    KC_NUM,     _______,    _______,
    /*  TILDE           1           2           3               4               5           6           7           8           9           0               MINUS       EQUAL       BACKSP      INS         HOME        PAGE_UP     */
        _______,        KC_CHRM,    KC_TILI,    KC_OUTL,        KC_IDEA,        _______,    _______,    _______,    _______,    _______,    _______,        _______,    _______,    _______,    _______,    _______,    _______,
    /*  TAB             Q           W           E               R               T           Y           U           I           O           P               L.BRACKET   R.BRACKET   BACKSLSH    DEL         END         PAGE_DN     */
        _______,        KC_M_1,     KC_M_2,     _______,        _______,        _______,    _______,    C(KC_U),    _______,    _______,    _______,        _______,    _______,    _______,    _______,    _______,    _______,
    /*  CAPS            A           S           D               F               G           H           J           K           L           SEMI COLN       QUOT                    ENTER                                           */
        KC_CAPS,        TD(TD_M1),  TD(TD_M2),  TD(TD_M3),      TD(TD_M4),      TD(TD_M5),  _______,    _______,    _______,    C(KC_L),    _______,        _______,                _______,
    /*  SHIFT           Z           X           C               V               B           N           M           COMMA       DOT         SLASH                                   SHIFT                   UP                      */
        _______,        _______,    _______,    _______,        _______,        _______,    _______,    _______,    _______,    _______,    _______,                                _______,                _______,
    /*  CTRL            WIN         ALT                                     SPACE                                               ALT         WIN             FN                      CTRL        LEFT        DOWN        RIGHT       */
        _______,        _______,    _______,                                _______,                                            _______,    _______,        _______,                _______,    _______,    _______,    _______),

};

#define NO__LED -1, 0, 0
/**
 * Template
*/
    // [W2] = {
    //     {
    //         /*  ESC             F1              F2              F3              F4              F5              F6              F7              F8              F9              F10             F11             F12             KNOB            PRINT           MIC                 */
    //         {RGB_OFF},          {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {NO__LED},      {RGB_OFF},      {RGB_OFF},
    //     }, {
    //         /*  TILDE           1               2               3               4               5               6               7               8               9               0               MINUS           EQUAL           BACKSP          INS             HOME                */
    //         {RGB_OFF},          {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},
    //     }, {
    //         /*  TAB             Q               W               E               R               T               Y               U               I               O               P               L.BRACKET       R.BRACKET       BACKSLSH        DEL             END                 */
    //         {RGB_OFF},          {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},
    //     }, {
    //         /*  CAPS            A               S               D               F               G               H               J               K               L               SEMI COLN       QUOT            PAGE_DOWN       ENTER           RGB             PAGE_UP             */
    //         {RGB_OFF},          {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},
    //     }, {
    //         /*  SHIFT                           Z               X               C               V               B               N               M               COMMA           DOT             SLASH                           SHIFT           RIGHT           UP                  */
    //         {RGB_OFF},          {NO__LED},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {NO__LED},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},
    //     }, {
    //         /*  CTRL            WIN             ALT                                                             SPACE                                                           ALT             WIN             FN              CTRL            LEFT            DOWN                */
    //         {RGB_OFF},          {RGB_OFF},      {RGB_OFF},      {NO__LED},      {NO__LED},      {NO__LED},      {RGB_OFF},      {NO__LED},      {NO__LED},      {NO__LED},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},
    //     }
    // }


const uint8_t RGBCOLORS [5][MATRIX_ROWS][MATRIX_COLS + 1][3] = {
    [FN1] = {
        {
            /*  ESC             F1              F2              F3              F4              F5              F6              F7              F8              F9              F10             F11             F12             KNOB            PRINT           MIC                 */
            {RGB_WHITE},        {RGB_GOLD},     {RGB_GOLD},     {RGB_GOLD},     {RGB_GOLD},     {RGB_GOLD},     {RGB_GOLD},     {RGB_GOLD},     {RGB_GOLD},     {RGB_GOLD},     {RGB_GOLD},     {RGB_GOLD},     {RGB_GOLD},     {NO__LED},      {RGB_WHITE},    {RGB_WHITE},
        }, {
            /*  TILDE           1               2               3               4               5               6               7               8               9               0               MINUS           EQUAL           BACKSP          INS             HOME                */
            {RGB_OFF},          {RGB_RED},      {RGB_RED},      {RGB_RED},      {RGB_RED},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_WHITE},    {RGB_WHITE},
        }, {
            /*  TAB             Q               W               E               R               T               Y               U               I               O               P               L.BRACKET       R.BRACKET       BACKSLSH        DEL             END                 */
            {RGB_OFF},          {RGB_OFF},      {RGB_MAGENTA},  {RGB_OFF},      {RGB_MAGENTA},  {RGB_MAGENTA},  {RGB_OFF},      {RGB_RED},      {RGB_RED},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_WHITE},    {RGB_WHITE},
        }, {
            /*  CAPS            A               S               D               F               G               H               J               K               L               SEMI COLN       QUOT            PAGE_DOWN       ENTER           RGB             PAGE_UP             */
            {RGB_OFF},          {RGB_MAGENTA},  {RGB_MAGENTA},  {RGB_OFF},      {RGB_MAGENTA},  {RGB_OFF},      {RGB_YELLOW},   {RGB_YELLOW},   {RGB_YELLOW},   {RGB_YELLOW},   {RGB_GREEN},    {RGB_GREEN},    {RGB_WHITE},    {RGB_OFF},      {RGB_WHITE},    {RGB_WHITE},
        }, {
            /*  SHIFT                           Z               X               C               V               B               N               M               COMMA           DOT             SLASH                           SHIFT           RIGHT           UP                  */
            {RGB_OFF},          {NO__LED},      {RGB_MAGENTA},  {RGB_MAGENTA},  {RGB_MAGENTA},  {RGB_MAGENTA},  {RGB_OFF},      {RGB_MAGENTA},  {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {NO__LED},      {RGB_OFF},      {RGB_WHITE},    {RGB_WHITE},
        }, {
            /*  CTRL            WIN             ALT                                                             SPACE                                                           ALT             WIN             FN              CTRL            LEFT            DOWN                */
            {RGB_OFF},          {RGB_OFF},      {RGB_WHITE},    {NO__LED},      {NO__LED},      {NO__LED},      {RGB_WHITE},    {NO__LED},      {NO__LED},      {NO__LED},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_WHITE},    {RGB_WHITE},
        }
    },
    [FN2] = {
        {
            /*  ESC             F1              F2              F3              F4              F5              F6              F7              F8              F9              F10             F11             F12             KNOB            PRINT           MIC                 */
            {RGB_OFF},          {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {NO__LED},      {RGB_OFF},      {RGB_OFF},
        }, {
            /*  TILDE           1               2               3               4               5               6               7               8               9               0               MINUS           EQUAL           BACKSP          INS             HOME                */
            {RGB_OFF},          {RGB_RED},      {RGB_WHITE},    {RGB_BLUE},     {RGB_ORANGE},   {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},
        }, {
            /*  TAB             Q               W               E               R               T               Y               U               I               O               P               L.BRACKET       R.BRACKET       BACKSLSH        DEL             END                 */
            {RGB_OFF},          {RGB_MAGENTA},  {RGB_MAGENTA},  {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_MAGENTA},  {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},
        }, {
            /*  CAPS            A               S               D               F               G               H               J               K               L               SEMI COLN       QUOT            PAGE_DOWN       ENTER           RGB             PAGE_UP             */
            {RGB_WHITE},        {RGB_GREEN},    {RGB_GREEN},    {RGB_GREEN},    {RGB_GREEN},    {RGB_GREEN},    {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_MAGENTA},  {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},
        }, {
            /*  SHIFT                           Z               X               C               V               B               N               M               COMMA           DOT             SLASH                           SHIFT           RIGHT           UP                  */
            {RGB_OFF},          {NO__LED},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {NO__LED},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},
        }, {
            /*  CTRL            WIN             ALT                                                             SPACE                                                           ALT             WIN             FN              CTRL            LEFT            DOWN                */
            {RGB_OFF},          {RGB_OFF},      {RGB_OFF},      {NO__LED},      {NO__LED},      {NO__LED},      {RGB_OFF},      {NO__LED},      {NO__LED},      {NO__LED},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},      {RGB_OFF},
        }
    }
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][1][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [FN1]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [FN2]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
};
#endif // ENCODER_MAP_ENABLE

void housekeeping_task_user(void) {
    housekeeping_task_keychron();
}

void open_app(char *app_name) {
    SEND_STRING(SS_TAP(X_LGUI));
    wait_ms(200);
    send_string(app_name);
    SEND_STRING(SS_TAP(X_ENTER));
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_M_1: // Copy, Open Chrome, Open new tab, Paste, Enter
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_C) SS_UP(X_LCTL));
                open_app("chrome");
                wait_ms(800);
                SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_T) SS_UP(X_LCTL));
                wait_ms(200);
                SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_V) SS_UP(X_LCTL));
                wait_ms(200);
                SEND_STRING(SS_TAP(X_ENTER));
            }
            return false;  // Skip all further processing of this key
        case KC_M_2: // Go to address bar, Copy, Esc
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_F6));
                wait_ms(50);
                SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_C) SS_UP(X_LCTL));
                wait_ms(50);
                SEND_STRING(SS_TAP(X_ESC));
            }
            return false;  // Skip all further processing of this key
        case KC_CHRM:
            if (record->event.pressed) {
                open_app("chrome");
            }
            return false;  // Skip all further processing of this key
        case KC_OUTL:
            if (record->event.pressed) {
                open_app("outlook");
            }
            return false;  // Skip all further processing of this key
        case KC_TILI:
            if (record->event.pressed) {
                open_app("tilix");
            }
            return false;  // Skip all further processing of this key
        case KC_IDEA:
            if (record->event.pressed) {
                open_app("intellij");
            }
            return false;  // Skip all further processing of this key
    }

    return process_record_keychron(keycode, record);
}

bool rgb_matrix_indicators_user(void) {
    if (get_highest_layer(layer_state) > WIN_BASE) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                const uint8_t *rgb = RGBCOLORS[layer][row][col];
                if (index != NO_LED && rgb[0] >= 0) {
                    rgb_matrix_set_color(index, rgb[0], rgb[1], rgb[2]);
                } else if (rgb[0] < 0) {
                    rgb_matrix_set_color(index, RGB_OFF);
                }
            }
        }
    }
    return true;
}
