/*                                                                                                                       
 *   pierna izquierda delantera = 2 3                                                                                                                      
 *   pierna derecha delantera = 4 5 
 *   pierna izquierda trasera = 6 7 
 *   pierna derecha trasera = 8 9                                                                                                                                                                                                                                                                                                                                                            
 *   cabeza = 10
 */

#include "AsyncServoLib.h"
AsyncServo servos[9];    

int velocidad = 3000;   //mínimo 50, maximo 300
int vel_pose = 600;   

int FDI = 850;   //Femur Delantero Izquierdo
int TDI = 850;    //Tibia Delantera Izquierda

int FDD = 850;    //Femur Delantero Derecho
int TDD = 850;    //Tibia Delantera Derecha

int FTI = 850;    //Femur Trasero Izquierdo
int TTI = 850;    //Tibia Trasera Izquierda

int FTD = 850;    //Femur Trasero Derecho
int TTD = 850;    //Tibia Trasera Derecha 

int medio_cabeza = 850; //Servo cabeza

int FDI_inicio = 1400;   //Femur Delantero Izquierdo
int TDI_inicio = 850;    //Tibia Delantera Izquierda

int FDD_inicio = 300;    //Femur Delantero Derecho
int TDD_inicio = 850;    //Tibia Delantera Derecha

int FTI_inicio = 1400;    //Femur Trasero Izquierdo
int TTI_inicio = 850;    //Tibia Trasera Izquierda

int FTD_inicio = 300;    //Femur Trasero Derecho
int TTD_inicio = 850;    //Tibia Trasera Derecha 

void setup() {
  
  delay(1000);
  Serial.begin(9600);
     
  for(int i=0; i<9; i++){                 //Asignamos servomotores a pines del Arduino
     servos[i].Attach(i+2);               //Iniciamos con el pin 2 hasta el 10
     delay(100);
  }

  servos[0].SetOutput(500, 1600, 2500); 
  delay(100);
  servos[1].SetOutput(500, 1500, 2500);
  delay(100);
  servos[2].SetOutput(500, 1500, 2500);
  delay(100);
  servos[3].SetOutput(500, 1630, 2500);
  delay(100);
  servos[4].SetOutput(500, 1550, 2500);
  delay(100);
  servos[5].SetOutput(500, 1500, 2500);
  delay(100);
  servos[6].SetOutput(500, 1600, 2500);
  delay(100);
  servos[7].SetOutput(500, 1450, 2500);
  delay(100);
  servos[8].SetOutput(500, 1500, 2500);
  delay(100);



  delay(5000); 

  pose_configuracion();   
  delay(5000); 
  pose_inicio();
  
//  prueba_servos();
  
  delay(5000);
  
}

void pose_configuracion(){
    servos[0].write(FDI);   
    servos[1].write(TDI);
    servos[2].write(FDD);    
    servos[3].write(TDD);  
    servos[4].write(FTI);   
    servos[5].write(TTI);
    servos[6].write(FTD);        
    servos[7].write(TTD);
    servos[8].write(medio_cabeza);    
}

void pose_inicio(){
    servos[0].write(FDI_inicio);  
    delay(20); 
    servos[1].write(TDI_inicio);
    delay(20);
    servos[2].write(FDD_inicio);   
    delay(20); 
    servos[3].write(TDD_inicio); 
    delay(20); 
    servos[4].write(FTI_inicio);   
    delay(20);
    servos[5].write(TTI_inicio);
    delay(20);
    servos[6].write(FTD_inicio);       
    delay(20); 
    servos[7].write(TTD_inicio);
    delay(20);
    servos[8].write(medio_cabeza);   
    delay(20); 
}

void prueba_servos(){
  step1();
}



//*********************************************************************************
//Prueba servos
//*********************************************************************************
void step1()
{                      
       servos[0].Move(FDI-400, velocidad, step2);   //femur delantero izquierdo  
}

void step2(){   
       servos[0].Move(FDI+400, velocidad, step3);  //femur delantero izquierdo  
}

void step3()
{  
     servos[0].Move(FDI, velocidad, step4);        //femur delantero izquierdo    
}

void step4(){
     servos[1].Move(TDI+400, velocidad, step5);         //tibia delantera izquierda    
}

void step5(){
     servos[1].Move(TDI-400, velocidad, step6);         //tibia delantera izquierda    
}

void step6(){
     servos[1].Move(TDI, velocidad, step7);         //tibia delantera izquierda
}

void step7()
{                      
       servos[2].Move(FDD-400, velocidad, step8);   
}

void step8(){   
       servos[2].Move(FDD+400, velocidad, step9); 
}

void step9()
{  
     servos[2].Move(FDD, velocidad, step10);           
}

void step10(){
     servos[3].Move(TDD+400, velocidad, step11);           
}

void step11(){
     servos[3].Move(TDD-400, velocidad, step12);         
}

void step12(){
     servos[3].Move(TDD, velocidad, step13);         
}

void step13()
{                      
       servos[4].Move(FTI-400, velocidad, step14);   
}

void step14(){   
       servos[4].Move(FTI+400, velocidad, step15); 
}

void step15()
{  
     servos[4].Move(FTD, velocidad, step16);           
}

void step16(){
     servos[5].Move(TTI+400, velocidad, step17);           
}

void step17(){
     servos[5].Move(TTI-400, velocidad, step18);         
}

void step18(){
     servos[5].Move(TTI, velocidad, step19);         
}

void step19()
{                      
       servos[6].Move(FTD-400, velocidad, step20);   
}

void step20(){   
       servos[6].Move(FTD+400, velocidad, step21); 
}

void step21()
{  
     servos[6].Move(FTD, velocidad, step22);           
}

void step22(){
     servos[7].Move(TTD+400, velocidad, step23);           
}

void step23(){
     servos[7].Move(TTD-400, velocidad, step24);         
}

void step24(){
     servos[7].Move(TTD, velocidad, step1);         
}

void actualiza_servos() { 
     servos[0].Update();      // Actualizamos movimiento de servomotores     
     servos[1].Update();
     servos[2].Update();
     servos[3].Update();
     servos[4].Update();
     servos[5].Update();
     servos[6].Update();
     servos[7].Update();
     servos[8].Update();            
}

void loop() { 
     actualiza_servos();
     delay(10);           
}
