#pragma once
#include "../../../PIC/env.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
/**
* @brief UART word length constants
*/
typedef enum {
	UART_DATA_5_BITS = 0x0,    /*!< word length: 5bits*/
	UART_DATA_6_BITS = 0x1,    /*!< word length: 6bits*/
	UART_DATA_7_BITS = 0x2,    /*!< word length: 7bits*/
	UART_DATA_8_BITS = 0x3,    /*!< word length: 8bits*/
	UART_DATA_BITS_MAX = 0X4,
} uart_word_length_t;

/**
* @brief UART stop bits number
*/
typedef enum {
	UART_STOP_BITS_1 = 0x1,  /*!< stop bit: 1bit*/
	UART_STOP_BITS_1_5 = 0x2,  /*!< stop bit: 1.5bits*/
	UART_STOP_BITS_2 = 0x3,  /*!< stop bit: 2bits*/
	UART_STOP_BITS_MAX = 0x4,
} uart_stop_bits_t;

/**
* @brief UART peripheral number
*/
typedef enum {
	UART_NUM_0 = 0x0,  /*!< UART base address 0x3ff40000*/
	UART_NUM_1 = 0x1,  /*!< UART base address 0x3ff50000*/
	UART_NUM_2 = 0x2,  /*!< UART base address 0x3ff6e000*/
	UART_NUM_MAX,
} uart_port_t;

/**
* @brief UART parity constants
*/
typedef enum {
	UART_PARITY_DISABLE = 0x0,  /*!< Disable UART parity*/
	UART_PARITY_EVEN = 0x2,     /*!< Enable UART even parity*/
	UART_PARITY_ODD = 0x3      /*!< Enable UART odd parity*/
} uart_parity_t;

/**
* @brief UART hardware flow control modes
*/
typedef enum {
	UART_HW_FLOWCTRL_DISABLE = 0x0,   /*!< disable hardware flow control*/
	UART_HW_FLOWCTRL_RTS = 0x1,   /*!< enable RX hardware flow control (rts)*/
	UART_HW_FLOWCTRL_CTS = 0x2,   /*!< enable TX hardware flow control (cts)*/
	UART_HW_FLOWCTRL_CTS_RTS = 0x3,   /*!< enable hardware flow control*/
	UART_HW_FLOWCTRL_MAX = 0x4,
} uart_hw_flowcontrol_t;

/**
* @brief UART configuration parameters for uart_param_config function
*/
typedef struct {
	int baud_rate;                      /*!< UART baud rate*/
	uart_word_length_t data_bits;       /*!< UART byte size*/
	uart_parity_t parity;               /*!< UART parity mode*/
	uart_stop_bits_t stop_bits;         /*!< UART stop bits*/
	uart_hw_flowcontrol_t flow_ctrl;    /*!< UART HW flow control mode (cts/rts)*/
	uint8_t rx_flow_ctrl_thresh;        /*!< UART HW RTS threshold*/
	bool use_ref_tick;                  /*!< Set to true if UART should be clocked from REF_TICK */
} uart_config_t;

/**
* @brief UART interrupt configuration parameters for uart_intr_config function
*/
typedef struct {
	uint32_t intr_enable_mask;          /*!< UART interrupt enable mask, choose from UART_XXXX_INT_ENA_M under UART_INT_ENA_REG(i), connect with bit-or operator*/
	uint8_t  rx_timeout_thresh;         /*!< UART timeout interrupt threshold (unit: time of sending one byte)*/
	uint8_t  txfifo_empty_intr_thresh;  /*!< UART TX empty interrupt threshold.*/
	uint8_t  rxfifo_full_thresh;        /*!< UART RX full interrupt threshold.*/
} uart_intr_config_t;

/**
* @brief UART event types used in the ring buffer
*/
typedef enum {
	UART_DATA,              /*!< UART data event*/
	UART_BREAK,             /*!< UART break event*/
	UART_BUFFER_FULL,       /*!< UART RX buffer full event*/
	UART_FIFO_OVF,          /*!< UART FIFO overflow event*/
	UART_FRAME_ERR,         /*!< UART RX frame error event*/
	UART_PARITY_ERR,        /*!< UART RX parity event*/
	UART_DATA_BREAK,        /*!< UART TX data and break event*/
	UART_PATTERN_DET,       /*!< UART pattern detected */
	UART_EVENT_MAX,         /*!< UART event max index*/
} uart_event_type_t;

typedef uint32_t TickType_t;
typedef int esp_err_t;

inline int uart_read_bytes(uart_port_t uart_num, uint8_t* buf, uint32_t length, TickType_t ticks_to_wait){
	return 0;
}
inline esp_err_t uart_driver_install(uart_port_t uart_num, int rx_buffer_size, int tx_buffer_size, int queue_size, xQueueHandle* uart_queue, int intr_alloc_flags){
	return 0;
}

inline esp_err_t uart_param_config(uart_port_t uart_num, const uart_config_t *uart_config){
	return 0;
}
inline esp_err_t uart_set_pin(uart_port_t uart_num, int tx_io_num, int rx_io_num, int rts_io_num, int cts_io_num){
	return 0;
}
#define UART_PIN_NO_CHANGE      (-1)         /*!< Constant for uart_set_pin function which indicates that UART pin should not be changed */

inline int uart_write_bytes(uart_port_t uart_num, const char* src, size_t size){
	return 0;
}
inline void uart_flush_input(uart_port_t port){
}
inline void uart_get_buffered_data_len(uart_port_t port, size_t* remain){
	*remain = 0;
}

