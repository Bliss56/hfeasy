#ifndef _HFEASY_H_
#define _HFEASY_H_

#include <hsf.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "gpio.h"
#include "httpd.h"
#include "mqttcli.h"
#include "buzzer.h"
#include "timer.h"
#include "config.h"
#include "led.h"


#define HFEASY_VERSION_MAJOR	0
#define HFEASY_VERSION_MINOR	7


#if defined (__HFEASY_PLUG__)
#define HAS_WIFI_LED
#define HAS_PUSH_BUTTON
#endif

#if defined (__HFEASY_MODULE__)
#define HAS_BUZZER
#define HAS_TOGGLE_BUTTON
#endif

#if defined(__HFEASY_DIMMER__)
#define HAS_WIFI_LED
#define HAS_PUSH_BUTTON
#endif



enum {
	HFTIMER_ID_DEBOUNCE = 0,
	HFTIMER_ID_RECOVERY,
	HFTIMER_ID_BUZZER,
	HFTIMER_ID_RESET,
	HFTIMER_ID_LED,
	HFTIMER_ID_DIMMER,
	HFTIMER_ID_UP,
	HFTIMER_ID_DN
};

#endif
