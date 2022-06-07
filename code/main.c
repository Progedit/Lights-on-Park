#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "thread.h"
#include "shell.h"
#include "shell_commands.h"
#include "periph/gpio.h"
#include "xtimer.h"
#include "fmt.h"
#include "msg.h"

#if IS_USED(MODULE_PERIPH_RTC)
#include "periph/rtc.h"
#else
#include "timex.h"
#include "ztimer.h"
#endif

#include "net/loramac.h"
#include "semtech_loramac.h"

#if IS_USED(MODULE_SX127X)
#include "sx127x.h"
#include "sx127x_netdev.h"
#include "sx127x_params.h"
#endif

#if IS_USED(MODULE_SX126X)
#include "sx126x.h"
#include "sx126x_netdev.h"
#include "sx126x_params.h"
#endif

/* Messages are sent every 20s to respect the duty cycle on each channel */
#define PERIOD_S            (20U)

#define SENDER_PRIO         (THREAD_PRIORITY_MAIN - 1)
static kernel_pid_t sender_pid;
static char sender_stack[THREAD_STACKSIZE_MAIN / 2];

static semtech_loramac_t loramac;
#if IS_USED(MODULE_SX127X)
static sx127x_t sx127x;
#endif
#if IS_USED(MODULE_SX126X)
static sx126x_t sx126x;
#endif
#if !IS_USED(MODULE_PERIPH_RTC)
static ztimer_t timer;
#endif

#define UNUSED(x) (void)(x)

//lora
static const char *message = "free";

static uint8_t deveui[LORAMAC_DEVEUI_LEN];
static uint8_t appeui[LORAMAC_APPEUI_LEN];
static uint8_t appkey[LORAMAC_APPKEY_LEN];


static void _send_message(void)
{
    printf("Sending: %s\n", message);
    /* Try to send the message */
    uint8_t ret = semtech_loramac_send(&loramac,
                                       (uint8_t *)message, strlen(message));
    if (ret != SEMTECH_LORAMAC_TX_DONE)  {
        printf("Cannot send message '%s', ret code: %d\n", message, ret);
        return;
    }
}

static void *sender(void *arg)
{
    (void)arg;

    msg_t msg;
    msg_t msg_queue[8];
    msg_init_queue(msg_queue, 8);

    while (1) {
        msg_receive(&msg);

        /* Trigger the message send */
        _send_message();
    }

    /* this should never be reached */
    return NULL;
}


//ultrasonic
gpio_t trigger_pin = GPIO_PIN(PORT_A, 10); //PIN BOARD = D2
gpio_t echo_pin = GPIO_PIN(PORT_B, 5); //PIN BOARD = D4

volatile uint32_t echo_time_start;
volatile uint32_t echo_time;

void echo_cb(void* arg){
    UNUSED(arg);
	//printf("%s: got interrupt\n", __func__);
	int val = gpio_read(echo_pin);
	uint32_t echo_time_stop;

	if(val){
		// got rising edge -> start time measuring
		echo_time_start = xtimer_now_usec();
	} else{
		// got falling edge -> stop time measuring
		echo_time_stop = xtimer_now_usec();
		echo_time = echo_time_stop - echo_time_start;
	}
}



int main(void)
{
	xtimer_sleep(1);
	puts("Welcome in LIGHTS_ON_PARKING.");
	puts("This is our project to check the situation of a parking lot.");
	puts("LoRaWAN Class A low-power application");

	    // Convert identifiers and application key 
    fmt_hex_bytes(deveui, CONFIG_LORAMAC_DEV_EUI_DEFAULT);
    fmt_hex_bytes(appeui, CONFIG_LORAMAC_APP_EUI_DEFAULT);
    fmt_hex_bytes(appkey, CONFIG_LORAMAC_APP_KEY_DEFAULT);

    // Initialize the radio driver 
#if IS_USED(MODULE_SX127X)
    sx127x_setup(&sx127x, &sx127x_params[0], 0);
    loramac.netdev = &sx127x.netdev;
    loramac.netdev->driver = &sx127x_driver;
#endif

#if IS_USED(MODULE_SX126X)
    sx126x_setup(&sx126x, &sx126x_params[0], 0);
    loramac.netdev = &sx126x.netdev;
    loramac.netdev->driver = &sx126x_driver;
#endif

    // Initialize the loramac stack 
    semtech_loramac_init(&loramac);
    semtech_loramac_set_deveui(&loramac, deveui);
    semtech_loramac_set_appeui(&loramac, appeui);
    semtech_loramac_set_appkey(&loramac, appkey);

    // Use a fast datarate, e.g. BW125/SF7 in EU868 
    semtech_loramac_set_dr(&loramac, LORAMAC_DR_5);

    // Start the Over-The-Air Activation (OTAA) procedure to retrieve the
     // generated device address and to get the network and application session
    // keys.
     //
    puts("Starting join procedure");
    if (semtech_loramac_join(&loramac, LORAMAC_JOIN_OTAA) != SEMTECH_LORAMAC_JOIN_SUCCEEDED) {
        puts("Join procedure failed");
        return 1;
    }
    puts("Join procedure succeeded");

    // start the sender thread 
    sender_pid = thread_create(sender_stack, sizeof(sender_stack),
                               SENDER_PRIO, 0, sender, NULL, "sender");

    // trigger the first send 
    //msg_t msg;
    //msg_send(&msg, sender_pid);

	gpio_init(trigger_pin, GPIO_OUT);
	gpio_init_int(echo_pin, GPIO_IN_PD, GPIO_BOTH, &echo_cb, NULL);

	int flag = 0; //0 if the parking lot is free, 1 otherwise
	uint32_t distance;
	while(1){
		echo_time = 0;
		gpio_clear(trigger_pin);
		xtimer_usleep(20);
		gpio_set(trigger_pin);

		xtimer_usleep(100*1000);

		//printf("echo_time=%ld\n", echo_time);
		if(echo_time > 0){
			distance = echo_time/58;
			//printf("distance=%ldcm\n", distance);
			if(distance < 10){
				//printf("posto occupato\n");
				if(flag == 0){
					puts("Now the parking lot is occupied.");
					puts("It sends the update on internet");
					message = "occupied";
					msg_t msg;
    				msg_send(&msg, sender_pid);
				}
				else{
					puts("The parking lot is still occupied.");
					puts("No update");
				}
				flag = 1;
			}
			else{
				//printf("posto libero\n");
				if(flag==1){
					puts("Now the parking lot is free.");
					puts("It sends the update on internet");
					message = "free";
					msg_t msg;
    				msg_send(&msg, sender_pid);
				}
				else{
					puts("The parking lot is still free.");
					puts("No update");
				}
				flag=0;
			}
		}
		if(flag == 1){ //parking lot occupied
			//puts("Aspetto più tempo");
			xtimer_sleep(10);
		}
		else if(flag == 0){ //parking lot free
			//puts("Controllo più frequentemente");
			xtimer_sleep(5);
		}
	}

    return 0;
}
