///////////////////////////////////////////////////////////////////////////
// Programa desenvolvido por Cristiano Teixeira                          //
// https://github.com/ProfessorCristiano                                 //
///////////////////////////////////////////////////////////////////////////
// Versão automática com a ponte Emakefun PS2X&Motor Drive Board v4      //
// biblioteca disponível em:                                             //
// https://github.com/emakefun/MotorDriverBoard                          //
///////////////////////////////////////////////////////////////////////////

//Incluir biblioteca da ponte para servo//
#include "Emakefun_MotorDriver.h"
//iniciar instancias dos objetos dos servos//  
Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_Servo *mServo1 = mMotorDriver.getServo(1); // ombro A     //
Emakefun_Servo *mServo2 = mMotorDriver.getServo(2); // ombro B     //
Emakefun_Servo *mServo3 = mMotorDriver.getServo(3); // ombro C     //
Emakefun_Servo *mServo4 = mMotorDriver.getServo(4); // ombro D     //

Emakefun_Servo *mServo5 = mMotorDriver.getServo(5); // cotovelo A  //
Emakefun_Servo *mServo6 = mMotorDriver.getServo(6); // cotovelo B  //
Emakefun_Servo *mServo7 = mMotorDriver.getServo(7); // cotovelo C  //
Emakefun_Servo *mServo8 = mMotorDriver.getServo(8); // corovelo D  //

/////////////////////
//Variáveis globais//
/////////////////////

int inter=100;      // Intervalo entre os movimentos//

boolean andafrente=false;
boolean andatras=false;
boolean andadireita=false;
boolean andaesquerda=false;
boolean obstaculo=false;


int distancia =100; // distancia geral atual medida em movimento
int distanciaF = 0; // distância FRENTE medida apenas quando traça nova rota
int distanciaA = 0; // distância ATRAS medida apenas quando traça nova rota
int distanciaD = 0; // distância DIREITA medida apenas quando traça nova rota
int distanciaE = 0; // distância ESQUERDA medida apenas quando traça nova rota


/*
// posições armazenadas dos servos //
// segue o mesmo padrão de nomenclatura das variáveis //
// posições dos ombros
//     
//    b\   /a
//      ###
//      ###
//    d/   \c
//
//    posição inicial
//////////////////////////
//     
//    b|   |a
//      ###
//      ###
//    d|   |c
//
//    posição Y
//////////////////////////
//     
//   b_     _a
//      ###
//   c_ ### _d
//        
//
//    posição X
//////////////////////////*/
int oai = 94;     // ombro direito Inicial  //OK
int oay = 138;    // ombro direito frente   //OK
int oax = 56;     // ombro direito atrás    //OK
    
int obi = 90;     // ombro esquerdo Inicial  //OK
int oby = 50;     // ombro esquerdo frente   //OK
int obx = 127;    // ombro esquerdo atrás    //OK

int oci = 94;    // coxa direito Inicial  //OK
int ocy = 58;    // coxa direito frente   //OK
int ocx = 135;   // coxa direito atrás    //OK

int odi = 92;    // coxa esquerdo Inicial  //OK
int ody = 138;   // coxa esquerdo frente   //OK
int odx = 58;    // coxa esquerdo atrás    //OK
    
// posições dos cotovelos e joelhos //

int can  = 90;     // cotovelo direito normal //
int cam  = 100;    // cotovelo direito medio  // 
int caa  = 110;    // cotovelo direito alto   // 
int cab  = 40;     // cotovelo direito baixo  // 
    
int cbn  = 90;     // cotovelo esquerdo normal // 
int cbm  = 80;     // cotovelo esquerdo medio  // 
int cba  = 70;     // cotovelo esquerdo alto   // 
int cbb  = 130;    // cotovelo esquerdo baixo  // 

int ccn  = 90;     // joelho direito normal // 
int ccm  = 80;     // joelho direito medio  // 
int cca  = 70;     // joelho direito alto   // 
int ccb  = 130;    // joelho direito baixo  // 

int cdn  = 90;     // joelho esquerdo normal // 
int cdm  = 100;    // joelho esquerdo medio  // 
int cda  = 110;    // joelho esquerdo alto   // 
int cdb  = 40;     // joelho esquerdo baixo  // 

int cabfren = 86;  // posição da cabeça para frente
int cablado = 176; // posição da cabeça para lado




//==== DECLARAÇÃO DAS FUNÇÕES ====//
//==== DEU RUIM ====//
//==== Vou mover as funções para antes do setup ====//
/* 

void Verifica();
void Nova_Rota();
int olhaF();
int olhaT();
int olhaD();
int olhaE();
void center_servos();
void deita();
void sobe();
void inclinafrente();
void inclinatras();
void inclinadireita();
void inclinaesquerda();
void anda_frente();
void anda_frente1();
void anda_frente2();
void anda_re();
void anda_direita();
void anda_esquerda();
void gira18_direita(); // 5 movimentos para virar 90°
void gira18_esquerda();
void gingagiroscopio();
void exercicios();
void nao();
*/



 
//============================== FUNÇÕES ============================================// 

/*
void Verifica()
{

if(andafrente==true)
{
  anda_frente();
  distanciaF = olhaF();
  if(distanciaF<=15)
  {
    Nova_Rota();
  }
}


if(andadireita==true)
{
  anda_direita();
  distanciaD = olhaD();
  if(distanciaD<=15)
  {
    Nova_Rota();
  }
}


if(andaesquerda==true)
{
  anda_esquerda();
  distanciaE = olhaE();
  if(distanciaE<=15)
  {
    Nova_Rota();
  }
}

if(andatras==true)
{
  anda_re();
  distanciaA = olhaT();
  if(distanciaA<=15)
  {
    Nova_Rota();
  }
}


}
*/

/* 
void Nova_Rota()
{

  CAB.slowmove(cabfren,vel);
  delay(200);
  CAB.slowmove(cablado,vel);
  delay(200);
   
 
 // aqui tem de verificar todos os lados
  center_servos();
  delay(100);
  
  CAB.slowmove(cabfren,vel);
  distanciaF = olhaF();
  delay(200);
  distanciaA = olhaT();
  delay(200);

  CAB.slowmove(cablado,vel);
  distanciaD = olhaF();
  delay(200);
  distanciaE = olhaT();
  delay(200);


  if(distanciaF>=distanciaA and distanciaF>=distanciaD and distanciaF>=distanciaE)
  {
    andafrente=true;
    andatras=false;
    andadireita=false;
    andaesquerda=false;
  }else
  {
    *//*
    if(distanciaD>=distanciaF and distanciaD>=distanciaA and distanciaD>=distanciaE)
      {
        andafrente=false;
        andatras=false;
        andadireita=true;
        andaesquerda=false;
      }
    else
    {
      if(distanciaE>=distanciaF and distanciaE>=distanciaA and distanciaE>=distanciaD)
      {
         andafrente=false;
         andatras=false;
         andadireita=false;
         andaesquerda=true;
      }
      else
      {
        if(distanciaA>=distanciaF and distanciaA>=distanciaD and distanciaA>=distanciaE)
        {
           andafrente=false;
           andatras=true;
           andadireita=false;
           andaesquerda=false;
        }
        else
        {*/
         /* 
          // fudeu
          andafrente=false;
          andatras=false;
          andadireita=false;
          andaesquerda=false; 
          center_servos();
          gira18_direita();
          gira18_direita();
          gira18_direita();
          gira18_direita();
          gira18_direita();
        //}
       //}
    //}  
  }
  

 
 

}
*/

//==========================================

/*
int readPing() { 
  delay(70);
  int cm;
  cm= sonar.ping_cm(); //erro
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

*/

/* 
int olhaF()
{
  delay(70);
  int cm;
  cm= sonarF.ping_cm(); //erro
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}
 
int olhaT()
{
 delay(70);
  int cm;
  cm= sonarA.ping_cm(); //erro
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}
int olhaD()
{
  delay(70);
  int cm;
  cm= sonarF.ping_cm(); //erro
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}
int olhaE()
{
  delay(70);
  int cm;
  cm= sonarA.ping_cm(); //erro
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}
*/


//== centralizar Servos==//

void center_servos()
{
  mServo1->writeServo(oai);                  
  mServo2->writeServo(obi);
  mServo3->writeServo(oci);
  mServo4->writeServo(odi);

  mServo5->writeServo(can);
  mServo6->writeServo(cbn);
  mServo7->writeServo(ccn);
  mServo8->writeServo(cdn);
}

//======================================================================

void deita()
{
  mServo1->writeServo(oai);                  
  mServo2->writeServo(obi);
  mServo3->writeServo(oci);
  mServo4->writeServo(odi);

  mServo5->writeServo(cab);
  mServo6->writeServo(cbb);
  mServo7->writeServo(ccb);
  mServo8->writeServo(cdb);

  
}

//======================================================================//

void sobe()
{
  mServo1->writeServo(oai);                  
  mServo2->writeServo(obi);
  mServo3->writeServo(oci);
  mServo4->writeServo(odi);

  mServo5->writeServo(caa);
  mServo6->writeServo(cba);
  mServo7->writeServo(cca);
  mServo8->writeServo(cda);
}

void inclinafrente()
{
  mServo1->writeServo(oai);                  
  mServo2->writeServo(obi);
  mServo3->writeServo(oci);
  mServo4->writeServo(odi);

  mServo5->writeServo(cab);
  mServo6->writeServo(cbb);
  mServo7->writeServo(cca);
  mServo8->writeServo(cda);
}

void inclinatras()
{
  mServo1->writeServo(oai);                  
  mServo2->writeServo(obi);
  mServo3->writeServo(oci);
  mServo4->writeServo(odi);

  mServo5->writeServo(caa);
  mServo6->writeServo(cba);
  mServo7->writeServo(ccb);
  mServo8->writeServo(cdb);
}

void inclinadireita()
{
  mServo1->writeServo(oai);                  
  mServo2->writeServo(obi);
  mServo3->writeServo(oci);
  mServo4->writeServo(odi);

  mServo5->writeServo(cab);
  mServo6->writeServo(cba);
  mServo7->writeServo(ccb);
  mServo8->writeServo(cda);
}

void inclinaesquerda()
{
  mServo1->writeServo(oai);                  
  mServo2->writeServo(obi);
  mServo3->writeServo(oci);
  mServo4->writeServo(odi);

  mServo5->writeServo(caa);
  mServo6->writeServo(cbb);
  mServo7->writeServo(cca);
  mServo8->writeServo(cdb);
}

void exercicios()
{
center_servos();
delay(100);
//nao();
//delay(500);
deita();
delay(500);
sobe();
delay(500);
deita();
delay(500);
sobe();
delay(500);
deita();
delay(500);
sobe();
delay(500);
inclinafrente();
delay(500);
inclinatras();
delay(500);
inclinadireita();
delay(500);
inclinaesquerda();
delay(500);
center_servos();
delay(100);
}

/* 
void nao()
{
   mServo5->writeServo(cabfren);
  delay(200);
   mServo5->writeServo(cablado);
  delay(200);
   mServo5->writeServo(cabfren);
  delay(200);
   mServo5->writeServo(cablado);
  delay(200);
   mServo5->writeServo(cabfren);
  delay(200);
   mServo5->writeServo(cablado);
  delay(200);
   mServo5->writeServo(cabfren);
  delay(200);
}
*/

//======================================================================//
//======== funciona ========//
//======================================================================//
void anda_frente()
{
  Serial.write ("Passo 01");
//01     
//  obi\   _oax*
//      ###
//      ###_
//  odi/    ocx*
//
  mServo5->writeServo(cab); delay(inter);//
  mServo1->writeServo(oax); delay(inter);//
  mServo5->writeServo(can); delay(inter);//
  //mServo2->writeServo(obi); delay(inter);
  mServo7->writeServo(ccb); delay(inter);//
  mServo3->writeServo(ocx); delay(inter);//
  mServo7->writeServo(ccn); delay(inter);//
  //mServo4->writeServo(odi); delay(inter); 


Serial.write ("Passo 02");
//02     
//  obi\   |oay*
//      ###
//      ###_
//  odi/    ocx
//
  mServo5->writeServo(cab); delay(inter);//
  mServo1->writeServo(oay); delay(inter);//
  mServo5->writeServo(can); delay(inter);//
  
  //mServo2->writeServo(obi); delay(inter);
  //mServo3->writeServo(ocx); delay(inter);
  //mServo4->writeServo(odi); delay(inter);


Serial.write ("Passo 03");
//03     
//  obx_   /oai
//      ###
//      ###
//  ody|   \oci
//
  mServo1->writeServo(oai); //
  mServo2->writeServo(obx); //
  mServo3->writeServo(oci); //
  mServo4->writeServo(ody); //
  delay(inter);


Serial.write ("Passo 04");
//04     
//  obx_   /oai
//      ###
//     _###
// *odx    \oci
//
  //mServo1->writeServo(oai); delay(inter);
  //mServo2->writeServo(obx); delay(inter);
  //mServo3->writeServo(oci); delay(inter);

  mServo8->writeServo(cdb); delay(inter);//
  mServo4->writeServo(odx); delay(inter);//
  mServo8->writeServo(cdn); delay(inter);//

Serial.write ("Passo 05");
//05     
// *oby|   /oai
//      ###
//     _###
//  odx    \oci
//
  //mServo1->writeServo(oai); delay(inter);
  mServo6->writeServo(cbb); delay(inter);//
  mServo2->writeServo(oby); delay(inter);//
  mServo6->writeServo(cbn); delay(inter);//
  //mServo3->writeServo(oci); delay(inter);
  //mServo4->writeServo(odx); delay(inter);


Serial.write ("Passo 06");
//06     
//  obi\   _oax
//      ###
//      ###
//  odi/   |ocy
//
  mServo1->writeServo(oax); //
  mServo2->writeServo(obi); //
  mServo3->writeServo(ocy); //
  mServo4->writeServo(odi); //
  delay(inter);


//     
//  obi\   _oax
//      ###
//      ###_
//  odi/    ocx
//
  //mServo1->writeServo(oax); delay(inter);
  //mServo2->writeServo(obi); delay(inter);
  //mServo7->writeServo(ccb); delay(inter);//
  //mServo3->writeServo(ocx); delay(inter);//
  //mServo7->writeServo(ccn); delay(inter);//
  //mServo4->writeServo(odi); delay(inter);       
}
//======================================================================//


//======================================================================//
//======================================================================//
//======================================================================//
//======================================================================//
//======================================================================//
void anda_re()
{
  
}

void anda_direita()
{
  
}
  
void anda_esquerda()
{
  


}

void gira18_direita()
{

//0     
//  obi\   /oai
//      ###
//      ###
//  odi/   \oci
//
  mServo1->writeServo(oai); delay(inter);//
  mServo2->writeServo(obi); delay(inter);//
  mServo3->writeServo(oci); delay(inter);//
  mServo4->writeServo(odi); delay(inter);// 
//1     
//  obi\   _oax*
//      ###
//      ###
//  odi/   \oci
//
  mServo5->writeServo(cab); delay(inter);//
  mServo1->writeServo(oax); delay(inter);//
  mServo5->writeServo(can); delay(inter);//
  //mServo2->writeServo(obi); delay(inter);
  //mServo3->writeServo(oci); delay(inter);
  //mServo4->writeServo(odi); delay(inter); 

//2     
//  obi\   _oax
//      ###
//      ###
//  odi/   |ocy*
//
  //mServo1->writeServo(oax); delay(inter);
  //mServo2->writeServo(obi); delay(inter);
  mServo7->writeServo(ccb); delay(inter);//
  mServo3->writeServo(ocy); delay(inter);//
  mServo7->writeServo(ccn); delay(inter);//
  //mServo4->writeServo(odi); delay(inter); 

//3     
//  obi\   _oax
//      ###
//     _###
// *odx    |ocy
//
  //mServo1->writeServo(oax); delay(inter);
  //mServo2->writeServo(obi); delay(inter);
  //mServo3->writeServo(ocy); delay(inter);
  mServo8->writeServo(cdb); delay(inter);//
  mServo4->writeServo(odx); delay(inter);//
  mServo8->writeServo(cdn); delay(inter);// 

//4     
// *oby|   _oax
//      ###
//     _###
//  odx    |ocy
//
  //mServo1->writeServo(oax); delay(inter);
  mServo6->writeServo(cbb); delay(inter);//
  mServo2->writeServo(oby); delay(inter);//
  mServo6->writeServo(cbn); delay(inter);//
  //  mServo3->writeServo(ocy); delay(inter);
  //mServo4->writeServo(odx); delay(inter);  

//5     
//  obi\   /oai
//      ###
//      ###
//  odi/   \oci
//
  mServo1->writeServo(oai); //
  mServo2->writeServo(obi); //
  mServo3->writeServo(oci); //
  mServo4->writeServo(odi); //
  delay(inter);  
}


void gira18_esquerda()
{
 //0     
//  obi\   /oai
//      ###
//      ###
//  odi/   \oci
//
  mServo1->writeServo(oai); delay(inter);//
  mServo2->writeServo(obi); delay(inter);//
  mServo3->writeServo(oci); delay(inter);//
  mServo4->writeServo(odi); delay(inter);// 
//1     
// *obx_   /oai
//      ###
//      ###
//  odi/   \oci
//
  //mServo1->writeServo(oai); delay(inter);
  mServo6->writeServo(cbb); delay(inter);//
  mServo2->writeServo(obx); delay(inter);//
  mServo6->writeServo(cbn); delay(inter);//
  //mServo3->writeServo(oci); delay(inter);
  //mServo4->writeServo(odi); delay(inter); 

//2     
//  obx_   |oay*
//      ###
//      ###
//  odi/   \oci
//
  mServo5->writeServo(cab); delay(inter);//
  mServo1->writeServo(oay); delay(inter);//
  mServo5->writeServo(can); delay(inter);//
  //mServo2->writeServo(obx); delay(inter);
  //mServo3->writeServo(oci); delay(inter);
  //mServo4->writeServo(odi); delay(inter); 

//3     
//  obx_   |oay
//      ###
//      ###_
//  odi/    ocx*
//
  //mServo1->writeServo(oay); delay(inter);
  //mServo2->writeServo(obx); delay(inter);
  mServo7->writeServo(ccb); delay(inter);//
  mServo3->writeServo(ocx); delay(inter);//
  mServo7->writeServo(ccn); delay(inter);//
  //mServo4->writeServo(odi); delay(inter);//
   

//4     
// obx _   |oay
//      ###
//      ###_
// *ody|    ocx
//
  //mServo1->writeServo(oay); delay(inter);
  //mServo2->writeServo(obx); delay(inter); 
  //mServo3->writeServo(ocx); delay(inter);
  mServo8->writeServo(cdb); delay(inter);//
  mServo4->writeServo(ody); delay(inter);//
  mServo8->writeServo(cdn); delay(inter);//
//5     
//  obi\   /oai
//      ###
//      ###
//  odi/   \oci
//
  mServo1->writeServo(oai); //
  mServo2->writeServo(obi); //
  mServo3->writeServo(oci); //
  mServo4->writeServo(odi); //
  delay(inter);  
}

void gingagiroscopio()
{
  
}

//=================== SETUP =========================================================//
void setup() {
  delay(4000);
  mMotorDriver.begin(50);
  Serial.begin(9600);
  Serial.write ("Inicio");

  
  mServo1->writeServo(oai);
  mServo2->writeServo(obi);
  mServo3->writeServo(oci);
  mServo4->writeServo(odi);

  mServo5->writeServo(can);
  mServo6->writeServo(cbn);
  mServo7->writeServo(ccn);
  mServo8->writeServo(cdn);
  
}
//============================== LOOP ===============================================//
void loop() 
{
anda_frente();

}



//==========================================//
//================== FIM ===================//
//==========================================//
