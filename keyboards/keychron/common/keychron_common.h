/* Copyright 2022 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "stdint.h"
#ifdef VIA_ENABLE
#    include "via.h"
#endif
#include "quantum_keycodes.h"

enum custom_keycodes {
    KC_LOPTN = QK_KB_2, // TECH DEBT: Starts at QK_KB_2 to maintain ordering with VIA definitions. See #19884. Revert to QK_KB_0 when VIA catches up with QMK.
    KC_ROPTN,
    KC_LCMMD,
    KC_RCMMD,
    KC_SIRI,
    KC_TASK_VIEW,
    KC_FILE_EXPLORER,
    KC_SCREEN_SHOT,
    KC_CORTANA,

    // Custom
    KC_CHROME,
    KC_OUTLOOK,
    KC_TILIX,
    KC_INTELLIJ,
    KC_MACRO_1,
    KC_MACRO_2
};

#define KC_TASK KC_TASK_VIEW
#define KC_FLXP KC_FILE_EXPLORER
#define KC_SNAP KC_SCREEN_SHOT
#define KC_CRTA KC_CORTANA

// Custom
#define KC_CHRM KC_CHROME
#define KC_OUTL KC_OUTLOOK
#define KC_TILI KC_TILIX
#define KC_IDEA KC_INTELLIJ
#define KC_M_1  KC_MACRO_1
#define KC_M_2  KC_MACRO_2

typedef struct PACKED {
    uint8_t len;
    uint8_t keycode[3];
} key_combination_t;

void housekeeping_task_keychron(void);
bool process_record_keychron(uint16_t keycode, keyrecord_t *record);
