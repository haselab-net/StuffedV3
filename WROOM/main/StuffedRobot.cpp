#include "StuffedRobot.h"

extern "C" void setup() {
	// put your setup code here, to run once:
	//Serial.begin(115200);
#ifdef MODULETEST
	  testCommand();
#endif
	// We start by connecting to a WiFi network
	  uarts.Init();
	  printf("Init uarts finished.  ");
	  printf("Motor:%d Force:%d", uarts.GetNTotalMotor(), uarts.GetNTotalForce());
	  ets_delay_us(500*1000);
	  udpCom.Init();
	  printf("Init udp finished.\n");
}

extern "C" void loop() {
	udpCom.ExecCommand();
	uarts.Loop();
}
