/*
whe have:
- 2 inputs
    (1)hombremuerto: when this pin is low --> stops. to run it must be at high.
      this is for saefty
    (2)cambiarmarcha: change speed. we have 3 steeps in loop
                ->- marcha1 -> marcha2 --> marcha3 -->-
               |--------------------<------------<-----|

- 2 outputs
    (1)ledmarcha1
    (2)ledmarcha2
        ledmarcha1 = 1 & ledmarcha2 = 0  ---> speed 1;
        ledmarcha1 = 0 & ledmarcha2 = 1  ---> speed 2;
        ledmarcha1 = 1 & ledmarcha2 = 1  ---> speed 3;

*/

#include "mbed.h"
#include "OpenChair.h"

DigitalIn hombremuerto(D2);   //Pulsador Hombre muerto
DigitalIn cambiarmarcha(D3);  // Pulsador incrementar marchas
DigitalOut ledmarcha1(D4);    //led indicador marcha 1 metida
DigitalOut ledmarcha2(D5);    //led indicador marcha 2 metida
//DigitalOut ledmarcha3(D6);    //led indicador marcha 3 metida


Serial pc(SERIAL_TX, SERIAL_RX);
OpenChair chair(PC_12,PD_2,PC_10,PC_11,60,150); //50,150


void acelera(int);
void frena(int);
void manten(void);

int marcha1 = 9,
    marcha2 = 3,
    marcha3 = 3;
int marcha = 0;
double Ma = 0, Mb = 0;


//####################################################################
//                   MAIN
//####################################################################
int main() {
ledmarcha1.write(0);
ledmarcha2.write(0);
//ledmarcha3.write(0);


    pc.baud(115200);

    while(1){
          pc.printf("%f \t %d\n", hombremuerto, marcha);

          //the pin of "hombremuerto" must be at HIGH.
          if( hombremuerto == 1 ){
          pc.printf("hombre muerto habilitado \t");

            //if we press the button "cambiarmarcha" to change speed
            if (cambiarmarcha == 1)  {

                  //if we are in speed0 (stopped) --> we change to speed1
                   if (marcha == 0){
                        marcha = 1;
                        ledmarcha1.write(1);
                        ledmarcha2.write(0);
                        //ledmarcha3.write(0);
                        pc.printf("MARCHA 1\n");
                        acelera(marcha1);  }

                    //if we are in speed1 --> we change to speed2
                    else if (marcha == 1){
                        marcha = 2;
                        ledmarcha1.write(0);
                        ledmarcha2.write(1);
                        //ledmarcha3.write(0);
                        pc.printf("MARCHA 2\n");
                        acelera(marcha2);  }

                    //if we are in speed2 --> we change to speed3
                    else if (marcha == 2){
                        marcha = 3;
                        ledmarcha1.write(1);
                        ledmarcha2.write(1);
                        pc.printf("MARCHA 3\n");
                        acelera(marcha3); }

                    //if we are in speed3 --> we change to speed1 (LOOP)
                    else if (marcha == 3){
                        marcha = 1;
                        ledmarcha1.write(1);
                        ledmarcha2.write(0);
                        //ledmarcha3.write(0);
                        pc.printf("MARCHA 1\n");
                        frena(marcha2+marcha3);         }

                    //OTHERWISE IS AN ERROR
                    else{
                        pc.printf("- - - - ERROR - - - - \n");
                        }
                    }

          //stopped
          else{
            pc.printf("mantementos\n");
            manten();
          }
        }

        //we stops
        else{
            pc.printf("hombre muerto no pulsado. Paramos.\n");

            if(marcha == 1){
                marcha = 0;
                ledmarcha1.write(0);
                ledmarcha2.write(0);
                //ledmarcha3.write(0);
                frena(marcha1);   }

            else if(marcha == 2){
                marcha = 0;
                ledmarcha1.write(0);
                ledmarcha2.write(0);
                //ledmarcha3.write(0);
                frena(marcha1+marcha2);  }

            else if(marcha == 3){
                marcha = 0;
                ledmarcha1.write(0);
                ledmarcha2.write(0);
                //ledmarcha3.write(0);
                frena(marcha1+marcha2+marcha3);  }

            else{
                chair.writeMotor1(0,0);
                chair.writeMotor2(0,0);  }
            }


  wait_ms(300);
  }
}

//------------------------------------------

//decrease the speed
void frena(int z){

  for(int i=0; i<z; i++){
      pc.printf("%d f\n", i);
      chair.writeMotor1( 65480, (int)1); //65460
      chair.writeMotor2( 65590, (int)1); //65610
      wait_ms(90);//250
      }
}


//increase the speed
void acelera(int z){

  for(int i=0; i<(2*z); i++){
      pc.printf("%d a\n", i);
      chair.writeMotor1( 65565, (int)1); //65565
      chair.writeMotor2( 65505, (int)1); //65505
      wait_ms(100);//250
      }
}


//holds speed
void manten(void){
  chair.writeMotor1( 0, (int)1);
  chair.writeMotor2( 0, (int)1);
}
