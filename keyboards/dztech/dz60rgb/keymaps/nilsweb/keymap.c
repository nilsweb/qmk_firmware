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
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[DEFAULT] = LAYOUT_ANSI(
      KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
      LT(HYPER,KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
      KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC,
      PK_LSUPER, KC_LALT, PK_LCOMMAND, KC_SPC, PK_RCOMMAND, MO(FUNCTION), MO(KEYBOARD), CK_MNEMONIC
    ),

	[HYPER] = LAYOUT_ANSI(
      KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS,
      KC_NO, KC_P7, KC_P8, KC_P9, X(EURO), X(TADA), KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_BTN3, XP(UUML, UUML_S), XP(ESZT, ESZT_S), KC_NO,
      KC_TRNS, KC_P4, KC_P5, KC_P6, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, XP(OUML, OUML_S), XP(AUML, AUML_S), KC_PENT,
      KC_LSFT, KC_P1, KC_P2, KC_P3, KC_P0, KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO, KC_RSFT,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_ACL0, KC_ACL1, KC_ACL2, KC_NO
    ),

	[FUNCTION] = LAYOUT_ANSI(
      KC_NO, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24, KC_SLEP,
      KC_NO, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PWR,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO),

	[KEYBOARD] = LAYOUT_ANSI(
      KC_NO, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO, RGB_TOG, RGB_VAD, RGB_VAI, RGB_RMOD, RGB_MOD, RGB_SPD, RGB_SPI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RESET,
      KC_NO, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, MAGIC_TOGGLE_NKRO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      UC_M_WC, UC_M_OS, UC_M_LN, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO
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
  if (qk_ucis_state.in_progress)
    return process_ucis(keycode, record);

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
