/* HFeasy

Copyright (c) 2019 Luis Alves

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "hfeasy.h"

#ifdef HAS_WIFI_LED

static hftimer_handle_t led_timer;
static char led_actions[30];
static uint8_t led_idx = 0;

static inline void USER_FUNC set_led(uint8_t st)
{
	if (st)
		hfgpio_fset_out_low(GPIO_LED);
	else
		hfgpio_fset_out_high(GPIO_LED);
}


static void USER_FUNC led_timer_handler(hftimer_handle_t timer)
{
	struct hfeasy_state *state = config_get_state();

	if (state->cfg.wifi_led == LED_CONFIG_OFF) {
		set_led(0);
		return;
	}	

	switch (led_actions[led_idx]) {
		case LED_ACTION_END:
			led_idx = 0;
			break;
		
		case LED_ACTION_ON:
			set_led(1);
			led_idx++;
			hftimer_change_period(timer, 10);
			break;
		
		case LED_ACTION_OFF:
			set_led(0);
			led_idx++;
			hftimer_change_period(timer, 10);
			break;
		
		case LED_ACTION_DELAY100:
			led_idx++;
			hftimer_change_period(timer, 100);
			break;
		case LED_ACTION_DELAY200:
			led_idx++;
			hftimer_change_period(timer, 200);
			break;
		case LED_ACTION_DELAY500:
			led_idx++;
			hftimer_change_period(timer, 500);
			break;
		case LED_ACTION_DELAY1000:
			led_idx++;
			hftimer_change_period(timer, 1000);
			break;
		
		case LED_ACTION_REPEAT:
			led_idx = 0;
			hftimer_change_period(timer, 10);
			break;
		default:
			led_idx++;
			hftimer_change_period(timer, 10);
			break;
	}
}

void USER_FUNC led_ctrl(char *a)
{
	struct hfeasy_state *state = config_get_state();
	
	if (state->cfg.wifi_led == LED_CONFIG_OFF) {
		set_led(0);
		return;
	}
	
	hftimer_stop(led_timer);
	strcpy(led_actions, a);
	led_idx = 0;
	hftimer_change_period(led_timer, 10);
}

void USER_FUNC led_init(void)
{
	led_idx = 0;
	strcpy(led_actions, "");
	led_timer = hftimer_create("led", 1, false, HFTIMER_ID_LED, led_timer_handler, 0);
}

#else
void USER_FUNC led_ctrl(char *a)
{
}
void USER_FUNC led_init(void)
{
}
#endif
