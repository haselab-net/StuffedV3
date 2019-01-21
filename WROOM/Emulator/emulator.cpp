#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "../main/UdpCom.h"


extern "C" {
//*	//	hasefone
	char hostAddress[] = { 192, 168, 43, 253 };
	char subnetMask[] = { 255, 255, 255,0 };
//*/
/*	//	haselab
	int hostAddress[] = { 192, 168, 91, 253 };
	int subnetMask[] = { 255, 255, 255,0 };
	//*/

/*	//	edurome
int hostAddress[] = { 10, 1, 254, 253 };
int subnetMask[] = { 255, 255, 252,0 };
//*/

/*	//	Home
int hostAddress[] = { 192, 168, 12, 253 };
int subnetMask[] = { 255, 255, 255,0 };
//*/

	void app_main();
	void mainTask(void*) {
		app_main();
	}
	void wifiMan() {}
	/* Variables used in the creation of the run time stats time base.  Run time
	stats record how much time each task spends in the Running state. */
	long long llInitialRunTimeCounterValue = 0LL, llRunTimeStatsDivisor = 0LL;

	void vApplicationMallocFailedHook(void)
	{
		const unsigned long ulLongSleep = 1000UL;

		/* Can be implemented if required, but probably not required in this
		environment and running this demo. */
		taskDISABLE_INTERRUPTS();
		for (;; )
		{
			Sleep(ulLongSleep);
		}
	}
	void vAssertCalled(void) {
		const unsigned long ulLongSleep = 1000UL;

		taskDISABLE_INTERRUPTS();
		for (;; )
		{
			Sleep(ulLongSleep);
		}
	}
	unsigned long ulMainGetRunTimeCounterValue(void)
	{
		LARGE_INTEGER liCurrentCount;
		unsigned long ulReturn;

		/* What is the performance counter value now? */
		QueryPerformanceCounter(&liCurrentCount);

		/* Subtract the performance counter value reading taken when the
		application started to get a count from that reference point, then
		scale to a 32 bit number. */
		ulReturn = (unsigned long)((liCurrentCount.QuadPart - llInitialRunTimeCounterValue) / llRunTimeStatsDivisor);

		return ulReturn;
	}
	void vMainConfigureTimerForRunTimeStats(void)
	{
		LARGE_INTEGER liPerformanceCounterFrequency, liInitialRunTimeValue;

		/* Initialise the variables used to create the run time stats time base.
		Run time stats record how much time each task spends in the Running
		state. */

		if (QueryPerformanceFrequency(&liPerformanceCounterFrequency) == 0)
		{
			llRunTimeStatsDivisor = 1;
		}
		else
		{
			/* How many times does the performance counter increment in 10ms? */
			llRunTimeStatsDivisor = liPerformanceCounterFrequency.QuadPart / 1000LL;

			/* What is the performance counter value now, this will be subtracted
			from readings taken at run time. */
			QueryPerformanceCounter(&liInitialRunTimeValue);
			llInitialRunTimeCounterValue = liInitialRunTimeValue.QuadPart;
		}
	}
	void vApplicationIdleHook(void)
	{
		const unsigned long ulMSToSleep = 5;

		/* Sleep to reduce CPU load, but don't sleep indefinitely in case there are
		tasks waiting to be terminated by the idle task. */
		Sleep(ulMSToSleep);
	}

	static void prvCheckTimerCallback(xTimerHandle xTimer)
	{
		/* The parameter is not used in this case. */
		(void)xTimer;

		/* Check the standard demo tasks are running without error.   Latch the
		latest reported error in the pcStatusMessage character pointer.  The latched
		string can be viewed using the embedded web server and the command line
		interpreter.  This project is really to demonstrate the lwIP stack - so very
		few tasks are created - and those that are created are created purely so
		there is something to view. */
	}


#define LWIP_PORT_INIT_IPADDR(addr)   IP4_ADDR((addr), hostAddress[0], hostAddress[1], hostAddress[2], hostAddress[3])
#define LWIP_PORT_INIT_GW(addr)       IP4_ADDR((addr), 192,168,12,1)
#define LWIP_PORT_INIT_NETMASK(addr)  IP4_ADDR((addr), subnetMask[0], subnetMask[1], subnetMask[2], subnetMask[3])

	/* The period at which the check timer will expire, in ms, provided no errors
	have been reported by any of the standard demo tasks.  ms are converted to the
	equivalent in ticks using the portTICK_RATE_MS constant. */
#define mainCHECK_TIMER_PERIOD_MS			( 3000UL / portTICK_RATE_MS )

	static xTimerHandle xCheckTimer = NULL;
	void taskPrint(void*);
	xQueueHandle queuePrint;
	
	void main() {
		tcpip_init(NULL, NULL);
		/* Create and start the check timer, as described at the top of this file. */
		xCheckTimer = xTimerCreate((const signed char *) "CheckTimer",/* A text name, purely to help debugging. */
			(mainCHECK_TIMER_PERIOD_MS),		/* The timer period, in this case 3000ms (3s). */
			pdTRUE,								/* This is an auto-reload timer, so xAutoReload is set to pdTRUE. */
			(void *)0,						/* The ID is not used, so can be set to anything. */
			prvCheckTimerCallback				/* The callback function that inspects the status of all the other tasks. */
		);

		/* Sanity check that the timer was created. */
		configASSERT(xCheckTimer);

		/* Start the check timer. */
		xTimerStart(xCheckTimer, 0UL);


		ip_addr_t xIPAddr, xNetMask, xGateway;
		extern err_t ethernetif_init(struct netif *xNetIf);
		static struct netif xNetIf;

		/* Set up the network interface. */
		ip_addr_set_zero(&xGateway);
		ip_addr_set_zero(&xIPAddr);
		ip_addr_set_zero(&xNetMask);

		LWIP_PORT_INIT_GW(&xGateway);
		LWIP_PORT_INIT_IPADDR(&xIPAddr);
		LWIP_PORT_INIT_NETMASK(&xNetMask);
		printf("Starting lwIP, local interface IP is %s\n", ip_ntoa(&xIPAddr));

		netif_set_default(netif_add(&xNetIf, &xIPAddr, &xNetMask, &xGateway, NULL, ethernetif_init, tcpip_input));
		netif_set_up(&xNetIf);

		xTaskCreate(mainTask, "main", 1024*8, NULL, 2, NULL);
		queuePrint = xQueueCreate(100, sizeof(char*));
		xTaskCreate(taskPrint, "print", 1024 * 4, NULL, configMAX_PRIORITIES - 1, NULL);


		/* Start the scheduler itself.	never return */
		vTaskStartScheduler();
	}
}
void taskPrint(void*) {
	while (1) {
		char* str;
		xQueueReceive(queuePrint, &str, portMAX_DELAY);
		OutputDebugStringA(str);
		free(str);
	}
}
extern "C" {
	void logVprintf(const char* format, va_list va) {
		char buf[1024];
		vsprintf(buf, format, va);
		char* str =  (char*)malloc(strlen(buf) + 1);
		strcpy(str, buf);
		xQueueSend(queuePrint, &str, 100);
	}
	void logPrintf(const char* fmt, ...) {
		va_list va;
		va_start(va, fmt);
		logVprintf(fmt, va);
		va_end(va);
	}
}
void espVprintf(const char* lv, const char* tag, const char* format, va_list va) {
	char buf[1024];
	sprintf(buf, "%s:%s ", lv, tag);
	vsprintf(buf + strlen(buf), format, va);
	logPrintf("%s\r\n", buf);
}

void ESP_LOGI(const char* tag, const char* fmt, ...){
	va_list va;
    va_start(va, fmt);
	espVprintf("I", tag, fmt, va);
	va_end(va);
}
void ESP_LOGW(const char* tag, const char* fmt, ...){
	va_list va;
	va_start(va, fmt);
	espVprintf("W", tag, fmt, va);
	va_end(va);
}
void ESP_LOGE(const char* tag, const char* fmt, ...){
	va_list va;
	va_start(va, fmt);
	espVprintf("E", tag, fmt, va);
	va_end(va);
}
