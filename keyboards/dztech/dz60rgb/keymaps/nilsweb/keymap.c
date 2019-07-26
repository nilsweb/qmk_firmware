//
// DZ60RGB Configuration
// Copyright (C) Nils Weber - @nilsweb
//

#include QMK_KEYBOARD_H
#include "unicode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


enum Layer {
  DEFAULT = 0,
  HYPER,
  HYPER2,
  FUNCTION,
  KEYBOARD,
};

enum PlatformKeycodes {
    PK_LCOMMAND = SAFE_RANGE,
    PK_RCOMMAND,
    PK_LSUPER,
    PK_RSUPER,
    PK__COUNT,
};

enum CustomKeycodes {
  CK_MNEMONIC = PK__COUNT,
  CK__COUNT,
  DYNAMIC_MACRO_RANGE,
};

// This inlcude has to come after DYNAMIC_MACRO_RANGE is defined!
#include "dynamic_macro.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[DEFAULT] = LAYOUT_ANSI(
      KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
      MO(HYPER), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
      KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC,
      PK_LSUPER, KC_LALT, PK_LCOMMAND, KC_SPC, PK_RCOMMAND, MO(FUNCTION), MO(KEYBOARD), CK_MNEMONIC
    ),

	[HYPER] = LAYOUT_ANSI(
      KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______,
      MO(HYPER2), _______, _______, UK_EURO, _______, _______, _______, UK_UUML, _______, UK_OUML, _______, DYN_MACRO_PLAY1, DYN_MACRO_PLAY2, DYN_REC_STOP,
      _______, UK_AUML, UK_ESZT, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, _______, _______,
      _______, _______, _______, _______, _______, KC_BTN2, KC_BTN3, _______, _______, _______, _______, _______,
      _______, _______, _______, KC_BTN1, _______, _______, _______, _______
    ),

	[HYPER2] = LAYOUT_ANSI(
      _______, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24, _______,
      _______, KC_P7, KC_P8, KC_P9, _______, _______, _______, _______, _______, _______, _______, DYN_REC_START1, DYN_REC_START2, _______,
      _______, KC_P4, KC_P5, KC_P6, _______, _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______, _______, _______,
      _______, KC_P1, KC_P2, KC_P3, KC_P0, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______
    ),

	[FUNCTION] = LAYOUT_ANSI(
      XXXXXXX, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24, KC_SLEP,
      XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PWR,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX),

	[KEYBOARD] = LAYOUT_ANSI(
      XXXXXXX, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, RGB_TOG, RGB_VAD, RGB_VAI, RGB_RMOD, RGB_MOD, RGB_SPD, RGB_SPI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,
      XXXXXXX, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MAGIC_TOGGLE_NKRO,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      UC_M_WC, UC_M_OS, UC_M_LN, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX
    )

};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Mapping table custom keycodes -> actual keycodes
// Table for Mac/Linux and Windows

enum Platform {
  WINDOWS = 0,
  MACOS,
  LINUX,
  UNSUPPORTED,
};

int8_t getPlatform(void)
{
  switch (get_unicode_input_mode()) {
    case UC_OSX:
      return MACOS;
    case UC_LNX:
      return LINUX;
    case UC_WIN:
    case UC_WINC:
      return WINDOWS;
    default:
      return UNSUPPORTED;
  }
}

// Helper macros to easily declare platform-specific keys
#define AUTO_UP_DOWN(keycode)     if (record->event.pressed) SEND_STRING(SS_DOWN(keycode)); else SEND_STRING(SS_UP(keycode))
#define AUTO_UD_MAC_WIN(mac,win)  if (getPlatform() == MACOS) AUTO_UP_DOWN(mac); else AUTO_UP_DOWN(win)

bool processPlatformKeys(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode) {
    case PK_LCOMMAND:
      AUTO_UD_MAC_WIN(X_LGUI, X_LCTRL);
      break;
    case PK_RCOMMAND:
      AUTO_UD_MAC_WIN(X_RGUI, X_RCTRL);
      break;
    case PK_LSUPER:
      AUTO_UD_MAC_WIN(X_LCTRL, X_LGUI);
      break;
    case PK_RSUPER:
      AUTO_UD_MAC_WIN(X_RCTRL, X_RGUI);
      break;
  }

  return false;
}


bool processCustomKeys(uint16_t keycode, keyrecord_t *record)
{
  if (!record->event.pressed) return false;

  switch (keycode) {
    case CK_MNEMONIC:
      qk_ucis_start();
      // SEND_STRING("Unsupported at the moment...");
      break;
  }

  return false;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  // Process mnemonic unicode input (if activated).
  if (qk_ucis_state.in_progress)
    return process_ucis(keycode, record);

  // Process dynamic macros (if activated).
  if (!process_record_dynamic_macro(keycode, record))
    return false;

  // Let "standard" keys be handled by QMK.
  if (keycode < SAFE_RANGE) return true;

  // Handle platform specific keys.
  if (keycode < PK__COUNT)
    return processPlatformKeys(keycode, record);

  // Handle custom keys.
  if (keycode < CK__COUNT)
    return processCustomKeys(keycode, record);

  // No custom keycode. Proceed as normal.
  return true;
}
