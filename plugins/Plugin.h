#ifndef PLUGIN_H
#define PLUGIN_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "../config.h"


// plugin states
#define PLUGIN_IDLE 0
#define PLUGIN_UPLOADING 1

#define UUID_LENGTH 40


#ifdef DEBUG
#define DEBUG_PLUGIN(...) ets_printf( __VA_ARGS__ )
#else
#define DEBUG_PLUGIN(...)
#endif


// simple device struct for devices without sensor address
struct DeviceStructSingle {
  char uuid[UUID_LENGTH];
};

class Plugin {
public:
  static int8_t count();
  static Plugin* get(int8_t idx);

  Plugin();
  virtual ~Plugin();
  virtual String getName();
  virtual int8_t getSensors();
  virtual int8_t getSensorByAddr(const char* addr_c);
  virtual bool getAddr(char* addr_c, int8_t sensor);
  virtual bool getUuid(char* uuid_c, int8_t sensor);
  virtual bool setUuid(const char* uuid_c, int8_t sensor);
  virtual String getHash(int8_t sensor);
  virtual float getValue(int8_t sensor);
  virtual void getPluginJson(JsonObject* json);
  virtual void getSensorJson(JsonObject* json, int8_t sensor);
  virtual bool saveConfig();
  virtual void loop();
  virtual uint32_t getMaxSleepDuration();

protected:
  uint32_t _timestamp;
  uint32_t _duration;
  uint8_t _status;
  int8_t _devs;
  HTTPClient http;

  virtual void upload();
  bool elapsed(uint32_t duration);

private:
  static int8_t instances;
  static Plugin* plugins[];
};

#endif
