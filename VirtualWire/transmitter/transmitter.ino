// transmitter.pde
//
// Simple example of how to use VirtualWire to transmit messages
// Implements a simplex (one-way) transmitter with an TX-C1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: transmitter.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>

const int led_trans_pin = 11;
const int transmit_pin = 12;
const int receive_pin = 13;

void setup()
{
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_setup(2000);
    pinMode(led_trans_pin, OUTPUT);
}

int count = 1;

void loop()
{
  
  char msg[10];
  
  digitalWrite(led_trans_pin, HIGH);

  sprintf(msg, "teste%d", count);
  
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx(); 
  digitalWrite(led_trans_pin, LOW);
  count++;
  delay(1000);
}
