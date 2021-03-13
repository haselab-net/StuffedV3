# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES 
	"partition_table"
	"softRobot"
  "esp_http_client"
  "app_update"
  "esp_https_ota"
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

set(COMPONENT_EMBED_TXTFILES ../../server_certs/ca_cert.pem)


register_component()
