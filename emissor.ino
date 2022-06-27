#define A0 14
#define D 6

String palavra;
int modo = 0; // 0 = Level, 1= Invert
int nivel = HIGH;
int letra[8];

void setup() {
  // put your setup code here, to run once:
  
  pinMode(A0, INPUT);
  pinMode(D, OUTPUT);
  Serial.begin(9600);
  digitalWrite(D, HIGH);

}

void loop() {
  
  if(Serial.available() > 0){
    palavra = Serial.readString();
    
    int tam = palavra.length();      
    
    //Converte o tamanho em binário
    for(int k = 7; k > 2; k--){
      letra[k] = tam %2;
        tam = tam/2;
    }
    letra[1] = modo;
    letra[0] = 1;

    /*10000011*/
    
    for(int k = 0; k < 8; k++){
        delay(500); //espera 1 sec
        modeLevel(letra[k]);
        digitalWrite(D, nivel);
    }
    
    for(int i = 0; i < palavra.length(); i++){
      binario(i, palavra);
      for(int k = 0; k < 8; k++){
         delay(500); //espera 1 sec
         if(modo == 0){
            modeLevel(letra[k]);
            digitalWrite(D, nivel);
         }else{
            modeInvert(letra[k]);
            digitalWrite(D, nivel);
         }
      }
    }
    
    delay(500); //espera 1 sec
    digitalWrite(D, HIGH);
    
  }
  
 }



/*
Primeiro Pacote de Dados:
Modo de Execução + Tamanho da String
01111111

Podemos mandar mensagens de até
128 caracteres (1 caractere é igual a 1 byte)


Ola -> O, L, A
O = 79
L = 76
A = 65

79 = 01001111
76 = 01001100
65 = 01000001

*/

void binario(int indice, String palavra){
  int aux;
  
  aux = (int) palavra[indice];
  
  for(int k = 7; k > -1; k--){
     letra[k] = aux%2;
     aux = aux/2;   
  }
}

void modeLevel(int bit){
  if(bit == 0)
    nivel = HIGH;
  else //bit == 1
    nivel = LOW;
}

void modeInvert(int bit){
  if(bit == 0)
    nivel = nivel;
  else{ //bit == 1
    if(nivel == LOW)
      nivel = HIGH;
    else //level == HIGH
      nivel = LOW;
  }
}
