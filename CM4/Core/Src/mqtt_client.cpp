/*
 * mqtt_client.cpp
 *
 *  Created on: Jun 8, 2022
 *      Author: Sven
 */


#include <stdio.h>
#include <string.h>

#include "mqtt_client.h"
#include "lwip.h"

// Constructor
MQTTClient::MQTTClient(ip_addr_t *ipAddr, uint16_t port)
{
  _ipAddr = ipAddr;
  _port = port;
}

void MQTTClient::Connect(mqtt_client_t *client)
{
  mqtt_connect_client_info_t ci;
  err_t err;

  memset(&ci, 0, sizeof(ci)); // Clear client info
  ci.client_id = "stm32 test client";
  err = mqtt_client_connect(client, _ipAddr, _port, mqtt_connection_cb, 0, &ci);

  if (err != ERR_OK)
  {
    // Error
  }
}

void MQTTClient::mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
  err_t err;
  if (status == MQTT_CONNECT_ACCEPTED)
  {
    //printf("mqtt_connection_cb: Successfully connected\n");

    /* Setup callback for incoming publish requests */
    mqtt_set_inpub_callback(client, mqtt_incoming_publish_cb, mqtt_incoming_data_cb, arg);
  }
  else
  {
    //printf("mqtt_connection_cb: Disconnected, reason: %d\n", status);

    /* Its more nice to be connected, so try to reconnect */
    //Connect(client);
  }
}

void MQTTClient::mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags)
{

}

void MQTTClient::mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len)
{

}


