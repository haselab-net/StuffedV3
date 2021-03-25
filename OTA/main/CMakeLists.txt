idf_component_register(SRCS "main.cpp" "ota_flash.cpp" "wifi.cpp"
                    INCLUDE_DIRS ""
                    EMBED_TXTFILES ../server_certs/ca_cert.pem)
set(COMPONENT_REQUIRES
  "esp32"
  "espfs"
)
