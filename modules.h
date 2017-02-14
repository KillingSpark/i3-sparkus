#pragma once

#include "JSON-Builder.h"
#include "util.h"

#include <sstream>
#include <vector>
#include <unistd.h>
#include <ctime>
#include <cstdio>

JSONObject myDate();
JSONObject myWifi();
JSONObject myVolume();
JSONObject myBat();
JSONObject myBacklight();