#include <esp_partition.h>

#ifndef COREDUMP_FLASH_MAGIC_START
#define COREDUMP_FLASH_MAGIC_START 0xE32C04EDUL
#endif

static esp_partition_t *core_part;

static void getCoreDumpPartition() {
    if (core_part) {    // partition already cached
        return;
    }

    // find partition
    core_part = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_COREDUMP, NULL);
    if (!core_part) {
        printf("No core dump partition found! \n");
        return;
    }
}

void readCoreDump() {
    // TODO need implementation for reading from pxt side
}

uint8_t haveUnmarkedCoreDump() {
    getCoreDumpPartition();
    if (!core_part) {
        return 0;
    }

   uint32_t start_num;
   spi_flash_read(core_part->address, &start_num, 4);
   if (start_num == COREDUMP_FLASH_MAGIC_START) {
       return 1;
   }
   else {
       return 0;
   }
}

void markCoreDump() {
    getCoreDumpPartition();
    if (!core_part) {
        return;
    }

    uint32_t mark_num = 0;
    spi_flash_write(core_part->address, &mark_num, 4);
}
