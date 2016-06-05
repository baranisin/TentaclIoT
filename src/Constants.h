#ifndef IOTIVITY_BAKALARKA_CONSTANTS_H
#define IOTIVITY_BAKALARKA_CONSTANTS_H

#include <string>

using namespace std;

static const int RANDOMLY_AVALAIBLE_PORT = 0;
static const string ALL_AVALAIBLE_INTERFACES = "0.0.0.0";
static const string FALSE_STRING_RETURN_VALUE = "FALSE";

static const string OIC_LIGHT_TYPE = "oic.r.light";
static const string OIC_TEMPERATURE_TYPE = "oic.r.temperaturesensor";
static const string OIC_SCENE_TYPE = "oic.scene";

static const string VIRTUAL_INTERFACE = "oic.if.virtual.server";
static const string BASELINE_INTERFACE = "oic.if.baseline";
static const string ACTUATOR_INTERFACE = "oic.if.a";
static const string SWITCH_INTERFACE = "ocf.r.switch.binary";
static const string SENSOR_INTERFACE = "oic.if.s";
static const string CUSTOM_INTERFACE = "lib.custom";

static const string TURN_ON_SERVICE_NAME = "turn_on";
static const string TURN_OFF_SERVICE_NAME = "turn_off";
static const string RAISE_BRIGHTNESS_SERVICE_NAME = "raise_brightness";
static const string LOW_BRIGHTNESS_SERVICE_NAME = "low_brightness";
static const string GET_BRIGHTNESS_SERVICE_NAME = "get_brightness";
static const string SET_BRIGHTNESS_SERVICE_NAME = "set_brightness";
static const string EMPTY_STRING = "";
static const string NAME_FORBIDDEN_CHARS = "`~!@#$%^&*()=[]{};:'|\\/.><?";
static const string DEFAULT_STRING = "DEFAULT";
static const char REPLACEMENT_CHAR = '.';
static const char SPACE_CHAR = ' ';
static const char REPLACEMENT_FOR_SPACE = '_';
static const int MAX_RES_WITH_SAME_NAME = 20;
static const int SECONDS_TO_SLEEP_TEST = 2;
static const int SECONDS_TO_SLEEP_DISCOVERY = 1;
static const int MIN_RANGE_TO_WAIT = 50;
static const int MAX_RANGE_TO_WAIT = 1000;
static const vector<string> EMPTY_STRING_VECTOR = vector<string>{};


#endif //IOTIVITY_BAKALARKA_CONSTANTS_H
