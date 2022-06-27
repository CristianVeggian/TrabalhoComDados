#define A3 17
#define volt 5

int modo;
int leitura;
int contador = 0;
int letra[8];
int tamanho;
char conteudo;

void setup() {
  
  pinMode(A3, OUTPUT);
  Serial.begin(9600);
  delay(10000);
}

void loop() {

  delay(500);
  leitura = analogRead(A3);
  
  if(leitura > volt){
    letra[0] = 1;
    
    delay(500);
    leitura = analogRead(A3);
    
    if(leitura > volt)
      modo = 1;
    else 
      modo = 0;
      
    letra[1] = modo;

    for(int i = 2; i < 8; i++){
      delay(500);
      leitura = analogRead(A3);
      if(leitura > volt)
        letra[i] = 1;
      else
        letra[i] = 0;   
    }

    tamanho = binarioToInteiro(letra, 6);
    Serial.println(tamanho);

    for(int i = 0; i < tamanho; i++){
       for(int k = 0; k < 8; k++){
          delay(500);
          leitura = analogRead(A3);
          if(leitura > volt)
            letra[i] = 1;
          else
            letra[i] = 0;
      }
      conteudo = binarioToInteiro(letra,8);
      Serial.print(conteudo);
    }
  
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

int binarioToInteiro(int *binario, int tam){
  double somador = 0;
  int contador = 0;

  for(int i = 7; i >= 8 - tam; i--, contador++){
    if(binario[i] == 1){
      somador += pow(2, contador);
    }
  }
  
  return somador+1;
}


void modeLevel(int bit){
  
}

void modeInvert(int bit){

}
