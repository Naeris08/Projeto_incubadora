#include <DHT.h>

// Definições do Sensor
#define DHTPIN 2       
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);

int bb = 1; // Começa no caso 1 por padrão
int vent = 4;
int resis = 3;
int off = 5;

void setup() {
  Serial.begin(9600); 
  dht.begin();        
  Serial.println("Sistema Iniciado!");
  Serial.println("Digite 1, 2 ou 3 no Monitor Serial para mudar o caso do bebe.");
  
  pinMode(vent, OUTPUT);
  pinMode(resis, OUTPUT);
  pinMode(off, OUTPUT);
}

void loop() {
  // Verifica se o usuário enviou algum dado pelo Monitor Serial
  if (Serial.available() > 0) {
    int valorRecebido = Serial.parseInt(); // Lê o número digitado
    
    // Valida se o número digitado é um caso válido (1, 2 ou 3)
    if (valorRecebido == 1 || valorRecebido == 2 || valorRecebido == 3) {
      bb = valorRecebido; // Atualiza a variável do bebê
      Serial.print("--> Caso do bebe alterado para: ");
      Serial.println(bb);
    }
  }

  // Aguarda 2 segundos entre as leituras do sensor
  delay(2000);

  // Leitura da umidade e temperatura
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Falha ao ler o sensor DHT!");
    return;
  }

  // Imprime os resultados e o caso atual no Monitor Serial
  Serial.print("[Caso "); Serial.print(bb); Serial.print("] ");
  Serial.print("Umidade: "); Serial.print(h); Serial.print(" % \t");
  Serial.print("Temperatura: "); Serial.print(t); Serial.println(" *C");

  // --- CASO 1 ---
  if (bb == 1) {
    if (t < 34 || h > 90) {
      digitalWrite(vent, LOW);   digitalWrite(resis, HIGH);  digitalWrite(off, LOW);
    }
    else if (t > 36 || h < 80) {
      digitalWrite(vent, HIGH);  digitalWrite(resis, LOW);   digitalWrite(off, LOW);
    }
    else {
      digitalWrite(vent, LOW);   digitalWrite(resis, LOW);   digitalWrite(off, HIGH);
    }
  } 

  // --- CASO 2 ---
  else if (bb == 2) {
    if (t < 34 || h > 90) {
      digitalWrite(vent, LOW);   digitalWrite(resis, HIGH);  digitalWrite(off, LOW);
    }
    else if (t > 36 || h < 80) {
      digitalWrite(vent, HIGH);  digitalWrite(resis, LOW);   digitalWrite(off, LOW);
    }
    else {
      digitalWrite(vent, LOW);   digitalWrite(resis, LOW);   digitalWrite(off, HIGH);
    }
  }

  // --- CASO 3 ---
  else if (bb == 3) {
    if (t < 32 || h > 60) {
      digitalWrite(vent, LOW);   digitalWrite(resis, HIGH);  digitalWrite(off, LOW);
    }
    else if (t > 34 || h < 40) {
      digitalWrite(vent, HIGH);  digitalWrite(resis, LOW);   digitalWrite(off, LOW);
    }
    else {
      digitalWrite(vent, LOW);   digitalWrite(resis, LOW);   digitalWrite(off, HIGH);
    }
  } 
}
