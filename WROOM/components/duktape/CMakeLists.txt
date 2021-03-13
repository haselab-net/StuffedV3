# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES
	"duktapeEsp32"
)
set(COMPONENT_PRIV_REQUIRES )

file(GLOB COMPONENT_SRCS
  LIST_DIRECTORIES false
  "*.h"
  "*.cpp"
  "*.c"
  "*.S"
  "src/*.c"
  "extras/module-duktape/*.c"
  "examples/debug-trans-socket/*.c"
)
set(COMPONENT_ADD_INCLUDEDIRS "." "./src" "./extras/module-duktape" "./examples/debug-trans-socket")

register_component()
