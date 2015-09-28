#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(9,10);

const uint64_t pipes[2] = {0xABCDABCD72LL,0xABCDABCD71LL};

typedef enum { role_ping_out = 1, role_pong_back } role_e;

const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};

role_e role = role_pong_back;

int valor = 0;

void setup(void)
{

  Serial.begin(57600);
  printf_begin();
  printf("\n\rRF24/examples/GettingStarted/\n\r");
  printf("ROLE: %s\n\r",role_friendly_name[role]);
  printf("*** PRESS 'T' to begin transmitting to the other node\n\r");
  radio.begin();

  radio.enableDynamicPayloads();
  
  radio.setRetries(15,15);

  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
      
  radio.startListening();
  radio.printDetails();
}

void loop(void){
  if (role == role_ping_out){
    radio.stopListening();
    
    char msg[40];

    sprintf(msg, "id:%d,T:temp,value:%i",1,(valor++));
    
    unsigned long time = millis();
    printf("Enviando agora %s\n\r",msg);
    
    bool ok = radio.write(&msg, strlen(msg));
    
    if (ok)
      printf("Ok, enviado, vai aguardar resposta\n\r");
    else
      printf("Falhou envio.\n\r");

    radio.startListening();
    
    unsigned long started_waiting_at = millis();
    bool timeout = false;
    while ( ! radio.available() && ! timeout )
      if (millis() - started_waiting_at > 10000 )
        timeout = true;
    if ( timeout ){
      printf("Timeout na resposta.\n\r");
    }else{
      unsigned long got_time;
      radio.read(&got_time, sizeof(unsigned long) );
      printf("Resposta %lu, tempo de ida e volta: %lu\n\r", got_time, millis()-got_time);
    }
    delay(1000);
  }

  if ( role == role_pong_back ){
 
    if ( radio.available()){
      char msg[40] = "";
      int len = radio.getDynamicPayloadSize();
      radio.read( &msg, len ); 
      
      printf("Recebido %s...\n\r",&msg);
      
      radio.stopListening();
      
      printf("Enviando resposta %s\n\r",msg);
      bool okResposta = radio.write(&msg, strlen(msg));
      if(okResposta)
        printf("Resposta enviada.\n\r");
      else
        printf("Erro ao enviar resposta\n\r");
      radio.startListening();
    }
  }

  if ( Serial.available() )
  {
    char c = toupper(Serial.read());
    if ( c == 'T' && role == role_pong_back )
    {
      printf("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK\n\r");
      role = role_ping_out;
      radio.openWritingPipe(pipes[0]);
      radio.openReadingPipe(1,pipes[1]);
    }
    else if ( c == 'R' && role == role_ping_out )
    {
      printf("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK\n\r");
      role = role_pong_back;
      radio.openWritingPipe(pipes[1]);
      radio.openReadingPipe(1,pipes[0]);
    }
  }
}

