SLEEP_LED_ENABLE = no
NKRO_ENABLE = yes
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes
UNICODEMAP_ENABLE = yes
COMBO_ENABLE = yes

# Enable UCIS support in tandem with UNICODEMAP
SRC += $(QUANTUM_DIR)/process_keycode/process_ucis.c
