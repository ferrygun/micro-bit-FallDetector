#include "MicroBit.h"
MicroBit uBit;

#define EVENT_ID    8888

int counter = 0;
int threshold = 5;
bool counterrun = false;
bool run = true;
int toleranceX = 1500; int toleranceY = 1500; int toleranceZ = 1500;

void onConnected(MicroBitEvent) {
   uBit.display.print("C");
}

void onDisconnected(MicroBitEvent){
   uBit.display.print("D");
}

void onButton(MicroBitEvent e) {
	if (e.value == MICROBIT_BUTTON_EVT_DOWN) {
		uBit.display.clear();
		counterrun = false;
        counter = 0;
        if (!run) run = true;
	}

    if (e.value == MICROBIT_BUTTON_EVT_HOLD) {
		uBit.display.clear();
        MicroBitEvent evt(EVENT_ID, 18);
	}
}

void showHeart() {
	while (1) {
		if (run) {
			while (uBit.accelerometer.getX() > toleranceX) {
				counterrun = true;
			}
			while (uBit.accelerometer.getY() > toleranceY) {
				counterrun = true;
			}
			while (uBit.accelerometer.getZ() > toleranceZ) {
				counterrun = true;
			}

			if (counterrun) {
				uBit.display.print(counter);
				if (counter >= threshold) {
					counterrun = false;
					uBit.display.print('S');
					MicroBitEvent evt(EVENT_ID, 18);
					uBit.sleep(1000);
				} else {
					uBit.sleep(1000);
					counter = counter + 1;
				}
			}
		} 
		
		uBit.sleep(500);    
	}
}

int main() {
    uBit.init();
	uBit.display.scroll("DC");
	create_fiber(showHeart);

	uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_CONNECTED, onConnected);
    uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_DISCONNECTED, onDisconnected);
	uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_EVT_ANY, onButton);
	
    release_fiber();
}