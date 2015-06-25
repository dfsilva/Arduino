/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Example for Getting Started with nRF24L01+ radios. 
 *
 * This is an example of how to use the RF24 class.  Write this sketch to two 
 * different nodes.  Put one of the nodes into 'transmit' mode by connecting 
 * with the serial monitor and sending a 'T'.  The ping node sends the current 
 * time to the pong node, which responds by sending the value back.  The ping 
 * node can then see how long the whole cycle took.
 */

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

//
// Hardware configuration
//

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10 

RF24 radio(9,10);


const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

typedef enum { role_ping_out = 1, role_pong_back } role_e;

const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};

role_e role = role_pong_back;

void setup(void)
{

  Serial.begin(57600);
  printf_begin();
  printf("\n\rRF24/examples/GettingStarted/\n\r");
  printf("ROLE: %s\n\r",role_friendly_name[role]);
  printf("*** PRESS 'T' to begin transmitting to the other node\n\r");
  radio.begin();
  radio.setRetries(15,15);

  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
      
  radio.startListening();
  radio.printDetails();
}

void loop(void)
{
  if (role == role_ping_out){
    radio.stopListening();
    
    char msg[40] = "tipo:temp,val:22";
    unsigned long time = millis();
    printf("Enviando agora %s...",msg);
    
    bool ok = radio.write(&msg, strlen(msg) );
    
    if (ok)
      printf("Ok, enviado");
    else
      printf("Falou envio.\n\r");

    radio.startListening();
    
    unsigned long started_waiting_at = millis();
    bool timeout = false;
    while ( ! radio.available() && ! timeout )
      if (millis() - started_waiting_at > 200 )
        timeout = true;
    if ( timeout ){
      printf("Falha na resposta.\n\r");
    }else{
      unsigned long got_time;
      radio.read(&got_time, sizeof(unsigned long) );
      printf("Resposta %lu, tempo de ida e volta: %lu\n\r", got_time, millis()-got_time);
    }
    delay(1000);
  }

  if ( role == role_pong_back ){
    // if there is data ready
    if ( radio.available()){
      unsigned long got_time;
      bool done = false;
      while (!done){
        done = radio.read( &got_time, sizeof(unsigned long) );
        printf("Recebido %lu...",got_time);
	      delay(20);
      }
      
      radio.stopListening();
      // Send the final one back.
      radio.write( &got_time, sizeof(unsigned long) );
      printf("Sent response.\n\r");
      radio.startListening();
    }
  }

  if ( Serial.available() )
  {
    char c = toupper(Serial.read());
    if ( c == 'T' && role == role_pong_back )
    {
      printf("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK\n\r");

      // Become the primary transmitter (ping out)
      role = role_ping_out;
      radio.openWritingPipe(pipes[0]);
      radio.openReadingPipe(1,pipes[1]);
    }
    else if ( c == 'R' && role == role_ping_out )
    {
      printf("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK\n\r");
      
      // Become the primary receiver (pong back)
      role = role_pong_back;
      radio.openWritingPipe(pipes[1]);
      radio.openReadingPipe(1,pipes[0]);
    }
  }
}
// vim:cin:ai:sts=2 sw=2 ft=cpp
