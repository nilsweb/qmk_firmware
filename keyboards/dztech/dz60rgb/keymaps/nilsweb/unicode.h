#include "process_ucis.h"

// Supported Unicode Characters
enum UnicodeAlphas {
  AUML,
  AUML_S,
  OUML,
  OUML_S,
  UUML,
  UUML_S,
  ESZT,
  ESZT_S,
  EURO,
  TADA,
};

// Unicode Mapping Table
const uint32_t PROGMEM unicode_map[] = {
  [AUML] = 0x00E4,
  [AUML_S] = 0x00C4,
  [OUML] = 0x00F6,
  [OUML_S] = 0x00D6,
  [UUML] = 0x00FC,
  [UUML_S] = 0x00DC,
  [ESZT] = 0x00DF,
  [ESZT_S] = 0x1E9E,
  [EURO] = 0x20AC,
  [TADA] = 0x1F389,
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Mnemonic Unicode Mapping Table - Emojis!
const qk_ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
  UCIS_SYM("poop", 0x0001F4A9),
  UCIS_SYM("rofl", 0x1F923),
  UCIS_SYM("tada", 0x1F389),
  UCIS_SYM("+1", 0x1F44D),
  UCIS_SYM("-1", 0x1F44E),
  UCIS_SYM("wink", 0x1F61C),
  UCIS_SYM("savoring", 0x1F60B),
  UCIS_SYM("larr", 0x2190),
  UCIS_SYM("uarr", 0x2191),
  UCIS_SYM("rarr", 0x2192),
  UCIS_SYM("darr", 0x2193)
);
