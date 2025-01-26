/*                                                                                                                       
 *   FDI Femur pierna izquierda delantera = 2                                                                                                                       
 *   TDI Tibia pierna izquierda delantera = 3 
 *   FDD Femur pierna derecha delantera = 4 
 *   TDD Tibia pierna derecha delantera = 5 
 *   FTI Femur pierna izquierda trasera = 6
 *   TTI Tibia pierna izquierda trasera = 7
 *   FTD Femur pierna derecha trasera = 8                                                                                                                                                                                                                                                                                                                                                           
 *   TTD Tibia pierna derecha trasera = 9 
 *   HEAD cabeza = 10 
 */
#include "AsyncServoLib.h"
AsyncServo servos[9];    

int velocidad = 400;   //150  250  400
int vel_pose = 1500;   
boolean flag = true;
boolean flag_flexion=false;
char command = 'S';      // creo la variable de lectura del bluetooth y la inicializo en 'S'


int FDI = 1500;   //Femur Delantero Izquierdo
int TDI = 850;    //Tibia Delantera Izquierda
int FDD = 310;    //Femur Delantero Derecho  
int TDD = 950;    //Tibia Delantera Derecha
int FTI = 1500;   //Femur Trasero Izquierdo
int TTI = 890;    //Tibia Trasera Izquierda
int FTD = 400;    //Femur Trasero Derecho      
int TTD = 1040;   //Tibia Trasera Derecha   
int HEAD = 850;   //Cabeza

void setup() {
  
  Serial.begin(9600);
  delay(100);
      
  for(int i=0; i<9; i++){                 //Asignamos servomotores a pines del Arduino
     servos[i].Attach(i+2);               //Iniciamos con el pin 2 hasta el 10
     delay(100);
  }

  for(int i=0; i<9; i++){                 
     servos[i].SetOutput(500, 1500, 2400); //Configuramos minimo, medio, máximo             
     delay(100);
  }

  delay(5000); 
  pose_inicio();  
  delay(5000);   
   
}

void pose_inicio(){
    servos[0].write(FDI);  
    delay(20); 
    servos[1].write(TDI);
    delay(20);
    servos[2].write(FDD);   
    delay(20); 
    servos[3].write(TDD); 
    delay(20); 
    servos[4].write(FTI);   
    delay(20);
    servos[5].write(TTI);
    delay(20);
    servos[6].write(FTD);       
    delay(20); 
    servos[7].write(TTD);
    delay(20);
    servos[8].write(HEAD);   
    delay(20); 
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

void fin_ciclo()
{
  flag = true;  
}


//*********************************************************************************
//Inicio función Adelante
//*********************************************************************************

void adelante()
{    
     flag=false; 
     step3();
     servos[8].Move(HEAD-200, velocidad);       //Cabeza
     servos[2].Move(FDD-100, velocidad);        //femur delantero derecho  
     servos[4].Move(FTI+100, velocidad);        //femur trasero izquierdo  
     servos[3].Move(TDD+100, velocidad);        //tibia delantera derecha     
     servos[5].Move(TTI-100, velocidad, step2); //tibia trasera izquierda  
}

void step2()
{
     step7();  
     servos[8].Move(HEAD+200, velocidad);       //Cabeza
     servos[0].Move(FDI-100, velocidad);        //femur delantero izquierdo
     servos[6].Move(FTD+100, velocidad);        //femur trasero derecho
     servos[1].Move(TDI-100, velocidad);        //tibia delantera izquierda
     servos[7].Move(TTD+100, velocidad, fin_ciclo); //tibia trasera derecha
}

void step3()
{
     servos[0].Move(FDI+100, velocidad/4);        //femur delantero izquierdo
     servos[6].Move(FTD-100, velocidad/4, step4); //femur trasero derecho                   
}

void step4()
{
     servos[1].Move(TDI+100, velocidad/4);         //tibia delantera izquierda 
     servos[7].Move(TTD-100, velocidad/4, step5);  //tibia trasera derecha   
}

void step5()
{
     servos[0].Move(FDI-100, velocidad/4);         //femur delantero izquierdo
     servos[6].Move(FTD+100, velocidad/4, step6);  //femur trasero derecho
}

void step6()
{
     servos[1].Move(TDI, velocidad/4);             //tibia delantera izquierda 
     servos[7].Move(TTD, velocidad/4);              //tibia trasera derecha 
}


void step7()
{
     servos[2].Move(FDD-100, velocidad/4);           //femur delantero derecho
     servos[4].Move(FTI+100, velocidad/4, step8);    //femur trasero izquierdo            
}

void step8()
{
     servos[3].Move(TDD-100, velocidad/4);           //tibia delantera derecha
     servos[5].Move(TTI+100, velocidad/4, step9);    //tibia trasera izquierda      
}

void step9()
{
     servos[2].Move(FDD+100, velocidad/4);           //femur delantero derecho
     servos[4].Move(FTI-100, velocidad/4, step10);   //femur trasero izquierdo 
}

void step10()
{
     servos[3].Move(TDD, velocidad/4);               //tibia delantera derecha
     servos[5].Move(TTI, velocidad/4);               //tibia trasera izquierda
}

//*********************************************************************************
//Final función adelante 
//*********************************************************************************

//*********************************************************************************
//Inicio función atrás
//*********************************************************************************

void atras()
{    
     flag=false; 
     step21();
     servos[8].Move(HEAD-200, velocidad);       //Cabeza
     servos[2].Move(FDD+100, velocidad);        //femur delantero derecho  
     servos[4].Move(FTI-100, velocidad);        //femur trasero izquierdo  
     servos[3].Move(TDD-100, velocidad);        //tibia delantera derecha     
     servos[5].Move(TTI+100, velocidad, step20); //tibia trasera izquierda  
}

void step20()
{
     step25();  
     servos[8].Move(HEAD+200, velocidad);       //Cabeza
     servos[0].Move(FDI-100, velocidad);        //femur delantero izquierdo
     servos[6].Move(FTD+100, velocidad);        //femur trasero derecho
     servos[1].Move(TDI+100, velocidad);        //tibia delantera izquierda
     servos[7].Move(TTD-100, velocidad, fin_ciclo); //tibia trasera derecha
}

void step21()
{
     servos[0].Move(FDI+100, velocidad/4);         //femur delantero izquierdo
     servos[6].Move(FTD-100, velocidad/4, step22); //femur trasero derecho                   
}

void step22()
{
     servos[1].Move(TDI+100, velocidad/4);         //tibia delantera izquierda 
     servos[7].Move(TTD-100, velocidad/4, step23);  //tibia trasera derecha   
}

void step23()
{
     servos[0].Move(FDI-100, velocidad/4);         //femur delantero izquierdo
     servos[6].Move(FTD+100, velocidad/4, step24);  //femur trasero derecho
}

void step24()
{
     servos[1].Move(TDI, velocidad/4);             //tibia delantera izquierda 
     servos[7].Move(TTD, velocidad/4);              //tibia trasera derecha 
}


void step25()
{
     servos[2].Move(FDD-100, velocidad/4);           //femur delantero derecho
     servos[4].Move(FTI+100, velocidad/4, step26);    //femur trasero izquierdo            
}

void step26()
{
     servos[3].Move(TDD-100, velocidad/4);           //tibia delantera derecha
     servos[5].Move(TTI+100, velocidad/4, step27);    //tibia trasera izquierda      
}

void step27()
{
     servos[2].Move(FDD+100, velocidad/4);           //femur delantero derecho
     servos[4].Move(FTI-100, velocidad/4, step28);   //femur trasero izquierdo 
}

void step28()
{
     servos[3].Move(TDD, velocidad/4);               //tibia delantera derecha
     servos[5].Move(TTI, velocidad/4);               //tibia trasera izquierda
}

//*********************************************************************************
//Final función atrás 
//*********************************************************************************


//*********************************************************************************
//Inicio función derecha
//*********************************************************************************

void derecha()
{    
     flag=false; 
     step31();
     servos[8].Move(HEAD-200, velocidad);        //Cabeza
     servos[2].Move(FDD-10, velocidad);          //femur delantero derecho  
     servos[4].Move(FTI+100, velocidad);         //femur trasero izquierdo  
     servos[3].Move(TDD+10, velocidad);          //tibia delantera derecha     
     servos[5].Move(TTI-100, velocidad, step30); //tibia trasera izquierda  
}

void step30()
{
     step35();  
     servos[8].Move(HEAD+200, velocidad);       //Cabeza
     servos[0].Move(FDI-100, velocidad);        //femur delantero izquierdo
     servos[6].Move(FTD+10, velocidad);        //femur trasero derecho
     servos[1].Move(TDI-100, velocidad);        //tibia delantera izquierda
     servos[7].Move(TTD+10, velocidad, fin_ciclo); //tibia trasera derecha
}

void step31()
{
     servos[0].Move(FDI+100, velocidad/4);        //femur delantero izquierdo
     servos[6].Move(FTD-10, velocidad/4, step32); //femur trasero derecho                   
}

void step32()
{
     servos[1].Move(TDI+100, velocidad/4);         //tibia delantera izquierda 
     servos[7].Move(TTD-10, velocidad/4, step33);  //tibia trasera derecha   
}

void step33()
{
     servos[0].Move(FDI-100, velocidad/4);         //femur delantero izquierdo
     servos[6].Move(FTD+10, velocidad/4, step34);  //femur trasero derecho
}

void step34()
{
     servos[1].Move(TDI, velocidad/4);             //tibia delantera izquierda 
     servos[7].Move(TTD, velocidad/4);              //tibia trasera derecha 
}


void step35()
{
     servos[2].Move(FDD-10, velocidad/4);           //femur delantero derecho
     servos[4].Move(FTI+100, velocidad/4, step36);    //femur trasero izquierdo            
}

void step36()
{
     servos[3].Move(TDD-10, velocidad/4);           //tibia delantera derecha
     servos[5].Move(TTI+100, velocidad/4, step37);    //tibia trasera izquierda      
}

void step37()
{
     servos[2].Move(FDD+10, velocidad/4);           //femur delantero derecho
     servos[4].Move(FTI-100, velocidad/4, step38);   //femur trasero izquierdo 
}

void step38()
{
     servos[3].Move(TDD, velocidad/4);               //tibia delantera derecha
     servos[5].Move(TTI, velocidad/4);               //tibia trasera izquierda
}

//*********************************************************************************
//Final función derecha
//*********************************************************************************

//*********************************************************************************
//Inicio función izquierda
//*********************************************************************************

void izquierda()
{    
     flag=false; 
     step41();
     servos[8].Move(HEAD-200, velocidad);       //Cabeza
     servos[2].Move(FDD-100, velocidad);        //femur delantero derecho  
     servos[4].Move(FTI+10, velocidad);         //femur trasero izquierdo  
     servos[3].Move(TDD+100, velocidad);        //tibia delantera derecha     
     servos[5].Move(TTI-10, velocidad, step40); //tibia trasera izquierda  
}

void step40()
{
     step45();  
     servos[8].Move(HEAD+200, velocidad);       //Cabeza
     servos[0].Move(FDI-10, velocidad);        //femur delantero izquierdo
     servos[6].Move(FTD+100, velocidad);        //femur trasero derecho
     servos[1].Move(TDI-10, velocidad);        //tibia delantera izquierda
     servos[7].Move(TTD+100, velocidad, fin_ciclo); //tibia trasera derecha
}

void step41()
{
     servos[0].Move(FDI+10, velocidad/4);          //femur delantero izquierdo
     servos[6].Move(FTD-100, velocidad/4, step42); //femur trasero derecho                   
}

void step42()
{
     servos[1].Move(TDI+10, velocidad/4);         //tibia delantera izquierda 
     servos[7].Move(TTD-100, velocidad/4, step43);  //tibia trasera derecha   
}

void step43()
{
     servos[0].Move(FDI-10, velocidad/4);         //femur delantero izquierdo
     servos[6].Move(FTD+100, velocidad/4, step44);  //femur trasero derecho
}

void step44()
{
     servos[1].Move(TDI, velocidad/4);             //tibia delantera izquierda 
     servos[7].Move(TTD, velocidad/4);              //tibia trasera derecha 
}


void step45()
{
     servos[2].Move(FDD-100, velocidad/4);           //femur delantero derecho
     servos[4].Move(FTI+10, velocidad/4, step46);    //femur trasero izquierdo            
}

void step46()
{
     servos[3].Move(TDD-100, velocidad/4);           //tibia delantera derecha
     servos[5].Move(TTI+10, velocidad/4, step47);    //tibia trasera izquierda      
}

void step47()
{
     servos[2].Move(FDD+100, velocidad/4);           //femur delantero derecho
     servos[4].Move(FTI-10, velocidad/4, step48);   //femur trasero izquierdo 
}

void step48()
{
     servos[3].Move(TDD, velocidad/4);               //tibia delantera derecha
     servos[5].Move(TTI, velocidad/4);               //tibia trasera izquierda
}

//*********************************************************************************
//Final función izquierda
//*********************************************************************************

//*********************************************************************************
//Inicio función sentado
//*********************************************************************************
void sentado()
{         
       flag=false;
       servos[0].Move(FDI+200, vel_pose);              //femur delantero izquierdo 
       servos[1].Move(TDI+700, vel_pose);              //tibia delantera izquierda  
       servos[2].Move(FDD-200, vel_pose);              //femur delantero derecho      
       servos[3].Move(TDD-700, vel_pose);              //tibia delantera derecha   
       servos[4].Move(FTI+200, vel_pose);              //femur trasero izquierdo
       servos[5].Move(TTI+700, vel_pose);              //tibia trasera izquierda    
       servos[6].Move(FTD-200, vel_pose);              //femur trasero derecho   
       servos[7].Move(TTD-700, vel_pose, fin_ciclo);   //tibia trasera derecha           
}
//*********************************************************************************
//Final función sentado
//*********************************************************************************

//*********************************************************************************
//Inicio función parado
//*********************************************************************************
void parado()
{         
       flag=false;
       servos[0].Move(FDI, vel_pose);              //femur delantero izquierdo 
       servos[1].Move(TDI, vel_pose);              //tibia delantera izquierda  
       servos[2].Move(FDD, vel_pose);              //femur delantero derecho      
       servos[3].Move(TDD, vel_pose);              //tibia delantera derecha   
       servos[4].Move(FTI, vel_pose);              //femur trasero izquierdo
       servos[5].Move(TTI, vel_pose);              //tibia trasera izquierda    
       servos[6].Move(FTD, vel_pose);              //femur trasero derecho   
       servos[7].Move(TTD, vel_pose, fin_ciclo);   //tibia trasera derecha           
}
//*********************************************************************************
//Final función parado
//*********************************************************************************

//*********************************************************************************
//Inicio función Flexion
//*********************************************************************************
void flexion()
{         
       flag=false;
       servos[1].Move(750, vel_pose);              //tibia delantera izquierda       
       servos[3].Move(750, vel_pose);              //tibia delantera derecha        
       servos[7].Move(750, vel_pose, step50);      //tibia trasera derecha            
}

void step50()
{ 
     servos[4].Move(1600, vel_pose);             //femur trasero izquierdo
     servos[5].Move(200, vel_pose, step51);      //tibia trasera izquierda 
}

void step51()
{ 
     servos[1].Move(950, vel_pose);               //tibia delantera izquierda -- bajo pata izquierda delantera
     servos[3].Move(850, vel_pose);                //tibia delantera derecha -- levanto pata delantera derecha        
     servos[7].Move(850, vel_pose, step52);       //tibia trasera derecha -- levanto pata trasera derecha      
}

void step52()
{
  servos[6].Move(200, vel_pose);                    //femur trasero derecho 
  servos[7].Move(1500, vel_pose, step53);           //tibia trasera derecha    
}

void step53()
{
  servos[1].Move(850, vel_pose, step54);                     //tibia delantera izquierda -- normalizo pata izquierda
}

void step54(){
     flag_flexion=false;
     servos[0].Move(1600, velocidad);         //femur delantero izquierdo        
     servos[2].Move(100, velocidad);          //femur delantero derecho         
     servos[1].Move(1400, velocidad);         //tibia delantera izquierda        
     servos[3].Move(300, velocidad, step55);  //tibia delantera derecha        
}

void step55(){
     servos[0].Move(1400, velocidad);            //femur delantero izquierdo       
     servos[2].Move(300, velocidad);             //femur delantero derecho         
     servos[1].Move(650, velocidad);             //tibia delantera izquierda       
     servos[3].Move(1050, velocidad, step56);    //tibia delantera derecha        
}

void step56(){
  flag_flexion = true;
  flag=false;
}
//*********************************************************************************
//Final función Flexion
//*********************************************************************************

//*********************************************************************************
//Inicio función Estirado
//*********************************************************************************
void estirado()
{         
       flag=false;
       servos[0].Move(FDI-1000, vel_pose);         //femur delantero izquierdo
       servos[1].Move(TDI-300, vel_pose, step60);  //tibia delantera izquierda                
}

void step60()
{ 
       servos[2].Move(FDD+1000, vel_pose);          //femur delantero derecho       
       servos[3].Move(TDD+300, vel_pose, step61);   //tibia delantera derecha  
}

void step61()
{  
       servos[4].Move(FTI-500, vel_pose);             //femur trasero izquierdo    
       servos[5].Move(TTI-500, vel_pose);             //tibia trasera izquierda     
       servos[6].Move(FTD+500, vel_pose);             //femur trasero derecho
       servos[7].Move(TTD+500, vel_pose, fin_ciclo);  //tibia trasera derecha      
}

//*********************************************************************************
//Final función Estirado
//*********************************************************************************

void loop() {  

     if (Serial.available()>0) {         // leo el puerto serial   
       command=Serial.read();            // si hay un dato lo cargo en la variable command          
     }

     if (command == 'F') {               // si recibo 'F' voy hacia adelante       
          if(flag==true){             
             adelante();
          }
     } 

     if (command == 'B') {               // si recibo 'B' voy hacia atrás      
          if(flag==true){             
             atras();
          }
     }

     if (command == 'R') {               // si recibo 'R' voy hacia la derecha      
          if(flag==true){             
             derecha();
          }
     }

     if (command == 'L') {               // si recibo 'L' voy hacia la izquierda      
          if(flag==true){             
             izquierda();
          }
     }

     if (command == 'H') {               // si recibo 'H'     
          if(flag==true){             
             sentado();
          }
     }

     if (command == 'I') {               // si recibo 'I'   
          if(flag==true){             
             parado();
          }
     }

     if (command == 'J') {               // si recibo 'J'     
          if(flag==true && flag_flexion==false){             
             flexion();
          }
          if(flag==false && flag_flexion==true){
             step54();
          }
     }

     if (command == 'K') {               // si recibo 'K'    
          if(flag==true){             
             estirado();
          }
     }

     if (command == 'P') {               // si recibo 'P' 
             flag=true;     
             flag_flexion=false;          
             parado();    
     }

     actualiza_servos();
     delay(10);              
}
