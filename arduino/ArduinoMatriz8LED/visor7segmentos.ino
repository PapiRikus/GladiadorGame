//declaramos los pines que seran utilizados  a lo largo de la ejecucion, estos pines activaran diferentes puntos de la matriz
const int a = 6;
const int b = 7;
const int c = 8;
const int d = 9;
const int e = 10;
const int f = 11;
const int g = 12;
const int h = 13;


const int p1 = 2;
const int p2 = 3;
const int p3 = 4;
const int p4 = 5;
const int p5 = A0;
const int p6 = A1;
const int p7 = A2;
const int p8 = A3;
const int fol = A5;

//aqui declaramos var1 y var2 que son la fila y la columna en la matriz de leds, al cambiar los valores lo que hacemos es abilitar los pines del arduino
int var1, var2;

//setup es para la configuracion de lo que se va a trabajar en el arduino
void setup(){
  Serial.begin(9600);
//zona de habilitacion
//habilitamos los puertos para salida de los pulsos de corriente electrica
pinMode(a, OUTPUT);
pinMode(b, OUTPUT);
pinMode(c, OUTPUT);
pinMode(d, OUTPUT);
pinMode(e, OUTPUT);
pinMode(f, OUTPUT);
pinMode(g, OUTPUT);
pinMode(h, OUTPUT);


pinMode(p1, OUTPUT);
pinMode(p2, OUTPUT);
pinMode(p3, OUTPUT);
pinMode(p4, OUTPUT);
pinMode(p5, OUTPUT);
pinMode(p6, OUTPUT);
pinMode(p7, OUTPUT);
pinMode(p8, OUTPUT);

pinMode(fol,OUTPUT);


pinMode(var1,OUTPUT);
pinMode(var2,OUTPUT);
}




int input;
int x[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
int colision = 0;
int condicion = 0;
int cantidadReinas = 0;
//int posiciones[92][8];

void loop(){
/*
en esta parte se encuentra el ciclo de auto repeticion que hace el arduino, este ciclo es obligatorio y necesario dentro de la placa arduino uno
*/
if(Serial.available()>0)              //se activa si el puerto serial esta activo
    {
      
          int w = 0;                  //esta variable se encargara de validar que se hayan leido las 9 posiciones validas en la matriz
          cantidadReinas = 0;         //esta variable lo que realiza es almacenar la cantidad de reinas mostradas en el tablero de la matriz
          while(w < 8){               //este ciclo realiza la lectura de datos hasta que se hayan validado 8 reinas 
           input = Serial.read();     //realiza la lectura constante de los valores enviados al arudino
           
           input = input - 48;        //pasa el valor de numeros ASCI a enteros
           if((input == 0)||(input == 1)||(input == 2)||(input == 3)||(input == 4)||(input == 5)||(input == 6)||(input == 7)){        //revisa que el valor leido sea una posicion en el tablero
           
              x[w] = input;                            //asigna en la fila w la columna de la reina
              cantidadReinas++;                        //como es una reina valida ingresada se le suma en uno la cantida de reinas totales
                                                       //realiza las impresiones en pantalla para poder visualizar los datos
              Serial.print("entrada ");
              Serial.print(w);
              Serial.print(" valor ");
              Serial.println(x[w]);
              w++;
           }else if(input == 8){                                                                                                     //esta condicion se realiza debido a que la reina se ha colocado fuera del area del tablero, sin embargo, la reina exite
             x[w] = input;                            //asigna en la fila w la columna de la reina
             
              Serial.print("entro ");
              Serial.print(w);
              Serial.print(" valor ");
              Serial.println(x[w]);
              w++;
           }
           
        }
        

        Serial.println("listo");
        Serial.println(cantidadReinas);
        //Serial.println(posiciones[posi][0]);
        
        //
   // }
 Serial.println("hola");
    
    //for(int valor = 0; valor < 92;valor++){
      // Serial.println(posiciones[valor][0]);
      for(int m = 0; m<10000;m++){
        for(int var = 0; var<8; var++){
          if(x[var]==0){
              var1 = a;
          }
          if(x[var]==1){
              var1 = f;
          }
          if(x[var]==2){
              var1 = p8;
          }
          if(x[var]==3){
              var1 = d;
          }
          if(x[var]==4){
              var1 = p1;
          }
          if(x[var]==5){
              var1 = p7;
          }
          if(x[var]==6){
              var1 = p2;
          }
          if(x[var]==7){
              var1 = p5;
          }

  
          
          if(var==0){
              var2 = e;
          }
          if(var==1){
              var2 = p3;
          }
          if(var==2){
              var2 = p4;
          }
          if(var==3){
              var2 = b;
          }
          if(var==4){
              var2 = p6;
          }
          if(var==5){
              var2 = c;
          }
          if(var==6){
              var2 = g;
          }
          if(var==7){
              var2 = h;
          }
          

      //En esta seccion lo que vamos a realizar es encender individualmente los leds
       if(x[var]!=8){
         for(int i = 0; i < cantidadReinas;i++){
           if(i!=var){
             if((x[i]== x[var])||(abs(x[i]-x[var])==abs(i-var))){
               condicion = 1;
               break;
             }else{
               condicion = 0;
             }
         }else{
           condicion = 0;
         }
       }
         if(condicion == 1){
           if(colision < 100){
               digitalWrite(var1,HIGH);          //activa la fila del led que vamos a seleccionar
               digitalWrite(var2,LOW);           //activa la columna de leds que seleccionamos para imprimir en la pantalla de leds
                                      //la colision de la fila y la columna activa exactamente el led requerido 
               }if(colision < 2000){
                  
              }else{
                  colision = 0;
              }
         }else{
               digitalWrite(var1,HIGH);          //activa la fila del led que vamos a seleccionar
               digitalWrite(var2,LOW);           //activa la columna de leds que seleccionamos para imprimir en la pantalla de leds
                                      //la colision de la fila y la columna activa exactamente el led requerido 
         }
         colision ++;
       }
      digitalWrite(var1,LOW);
      digitalWrite(var2,HIGH);
      }

   
    }
    //Serial.write(1);
    }
    //}

    }




