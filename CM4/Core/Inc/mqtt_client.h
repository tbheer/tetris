/*
 * mqtt_client.h
 *
 *  Created on: Jun 8, 2022
 *      Author: Sven
 */

#ifndef INC_MQTT_CLIENT_H_
#define INC_MQTT_CLIENT_H_

#include "lwip/apps/mqtt.h"
#include "lwip/apps/mqtt_priv.h"

class MQTTClient
{
public:
  MQTTClient(ip_addr_t *ipAddr, uint16_t port);

private:
  void Connect(mqtt_client_t * client);
  static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status);
  static void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len);
  static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags);

  mqtt_client_t _client;
  uint16_t _port;
  ip_addr_t * _ipAddr;
};



#endif /* INC_MQTT_CLIENT_H_ */
