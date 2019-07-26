// NOTE: Remember to update COMBO_COUNT in config.h when adding/removing combos!
enum Combos {
  CC_ESC,
  CC_TAB,
  CC__COUNT,
};

const uint16_t PROGMEM cc_esc[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM cc_tab[] = {KC_D, KC_F, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [CC_ESC] = COMBO(cc_esc, KC_ESC),
  [CC_TAB] = COMBO(cc_tab, KC_TAB),
};
