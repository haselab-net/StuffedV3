# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES
  "spi_flash"
  "duktape"
  "spiffs"
  "espfs"
  "mqtt"
  "nvs_flash"
  "esp_http_client"
  "json"
  "esp32snippets"
  "softRobot"
)
set(COMPONENT_PRIV_REQUIRES )

file(GLOB COMPONENT_SRCS
  LIST_DIRECTORIES false
  "*.h"
  "*.cpp"
  "*.c"
  "*.S"
)
set(COMPONENT_ADD_INCLUDEDIRS "." "./include")

register_component()
