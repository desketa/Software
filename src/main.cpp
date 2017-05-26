#include "mbed.h"
#include "OpenChair.h"

AnalogIn potX(PA_0);
AnalogIn potY(PA_1);
Serial pc(SERIAL_TX, SERIAL_RX);
OpenChair chair(PC_12,PD_2,PC_10,PC_11,60,150); //50,150

int main() {

    pc.baud(115200);
    double valueX;
    double valueY;

    while (1){
//      valueX= (double) (potX.read()*2-1);
//      valueY= (double) (potY.read()*2-1);


      motor1.putc(00);//Start byte
      motor1.putc(0x000);
      motor1.format(8,SerialBase::None,2); //Expects 9bit, 1stop, receives 8bit,2stop -> MSB=first stop bit=1
      motor1.putc(0x050);
      motor1.format(9);
      motor1.putc(0x000);
      motor1.putc(0x050);
      if(motOn==1) motor1.putc(0x55);//End byte
      if(motOn==0) motor1.putc(0x00);//End byte
      motor1.putc(91);
      motor1.putc(91);


//      chair.drive(valueX, valueY, 1);
      wait_ms(50);
    }
}
