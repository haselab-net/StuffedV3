# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES
  "console"
  "fatfs"
  "json"
  "mdns"
  "nvs_flash"
  "pthread"
  "espfs"
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
