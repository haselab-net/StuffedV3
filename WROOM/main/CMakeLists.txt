idf_component_register(SRCS "main.cpp" "monitor.cpp"
                    INCLUDE_DIRS "")
set(COMPONENT_REQUIRES
  "esp32"
  "duktapeEsp32"
  "duktape"
  "espfs"
  "websocketServer"
)
