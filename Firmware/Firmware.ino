#include <Servo.h>

#define pinSensorOeste A0                                                   //pino de entrada do sensor oeste;
#define pinSensorLeste A1                                                    //pino de entrada do sensor leste;
#define pinServoHorizontal 8                                                //pino de sinal para o servomotor;
#define pinAlimentacao 7                                                    //pino de alimentação para os sensores;

Servo servoHorizontal;                                                      //instanciação do servmotor;

int anguloHorizontal = 90;                                                  //ângulo inicial do servomotor;

void setup() {
  pinMode(pinSensorOeste, INPUT);                                           //setando entrada do sensor oeste;
  pinMode(pinSensorLeste, INPUT);                                           //setando entrada do sensor leste;
  pinMode(pinAlimentacao, OUTPUT);                                          //setando saída 5V para alimentação dos sensores;
  servoHorizontal.attach(pinServoHorizontal);                               //setando o pino de saída para o servomotor;

  Serial.begin(9600);                                                       //inicializando comuicação serial para acompanhamento dos valores pelo computador;
}

void loop() {
  digitalWrite(pinAlimentacao, HIGH);                                       //alimentando os sensores com 5V;
  servoHorizontal.write(constrain(anguloHorizontal, 0, 180));               //escrevendo o ângulo no motor (entre 0 e 180);
  delay(100);                                                               //ele reajusta o ângulo a cada 100 milissegundos;
  anguloHorizontal += comparaHorizontal(anguloHorizontal);                  //lógica que atribui o novo ângulo à variável "anguloHorizontal";
  Serial.print(analogRead(pinSensorOeste));                                 //imprimindo o valor do sensor oeste no monitor serial;
  Serial.print(", ");                                                       //separa as impressões por uma vírgula;
  Serial.println(analogRead(pinSensorLeste));                               //imprimindo o valor do sensor leste no monitor serial;
}

double comparaHorizontal(int valor) {                                       //função responsável por incrementar e decrementar o ângulo do servomotor;
  int oeste = analogRead(pinSensorOeste);                                   //faz a leitura do sensor oeste e armazena na variável "oeste";
  int leste = analogRead(pinSensorLeste);                                   //faz a leitura do sensor oeste e armazena na variável "leste";

  if (abs(oeste - leste) > 50) {                                            //se o valor absoluto da diferença entre os sensores for maior que 50, então ele recalibra o motor da seguinte forma:
    if (oeste > leste) {                                                    //se o o valor so sensor oeste for maior que o do leste, ele retorna 1 para incrementar o valor anterior, na função loop();
      return 1;
    } else if (oeste < leste) {                                             //e se o o valor so sensor leste for maior que o do oeste, ele retorna -1 para decrementar o valor anterior, na função loop();
      return -1;
    }
  } else {                                                                  //se a diferença entre eles não for maior que 50, então não há necessidade de reajuste;
    return 0;
  }
}
