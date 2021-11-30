set(COMPONENT_SRCS "brownout.cpp" "main.cpp" "monitor.cpp")
set(COMPONENT_ADD_INCLUDEDIRS "")

register_component(  "esp32"
"duktapeEsp32"
"duktape"
"espfs"
"websocketServer"
"softRobot"
)
