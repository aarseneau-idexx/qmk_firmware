MCU = RP2040
BOOTLOADER = rp2040

OLED_ENABLE = yes
OLED_DRIVER = SSD1306
OCEAN_DREAM_ENABLE = no
WPM_ENABLE = yes

OPT_DEFS += -DHAL_USE_I2C=TRUE

ENCODER_MAP_ENABLE = yes
LTO_ENABLE = yes
OLED_ENABLE = yes

NKRO_ENABLE = yes

ifeq ($(strip $(OLED_ENABLE)), yes)
    ifdef OCEAN_DREAM_ENABLE
        ifeq ($(strip $(OCEAN_DREAM_ENABLE)), yes)
            SRC += ocean_dream.c
            OPT_DEFS += -DOCEAN_DREAM_ENABLE
        endif
    endif
    ifndef OCEAN_DREAM_ENABLE
        SRC += ocean_dream.c
        OPT_DEFS += -DOCEAN_DREAM_ENABLE
    endif
endif
