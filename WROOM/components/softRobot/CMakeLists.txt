# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES 
  "esp_adc_cal"
  "duktapeEsp32"
  "nvs_flash"
  "esp32snippets"
)
set(COMPONENT_PRIV_REQUIRES )

file(GLOB COMPONENT_SRCS
  LIST_DIRECTORIES false
  "*.h"
  "*.cpp"
  "*.c"
  "*.S"
)
set(COMPONENT_ADD_INCLUDEDIRS ".")

register_component()
