#include <stdio.h>
#include <string.h>

#include "thread.h"
#include "shell.h"
#include "shell_commands.h"
#include "periph/gpio.h"
#include "xtimer.h"

#define UNUSED(x) (void)(x)

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


int start(int argc, char **argv){
	(void)argc;
	(void)argv;
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
					puts("Now the parking lot is occupated.");
					puts("It sends the update on internet");
				}
				else{
					puts("The parking lot is still occupated.");
					puts("No update");
				}
				flag = 1;
			}
			else{
				//printf("posto libero\n");
				if(flag==1){
					puts("Now the parking lot is free.");
					puts("It sends the update on internet");
				}
				else{
					puts("The parking lot is still free.");
					puts("No update");
				}
				flag=0;
			}
		}
		if(flag == 1){ //parking lot occupated
			//puts("Aspetto più tempo");
			xtimer_sleep(10);
		}
		else if(flag == 0){ //parking lot free
			//puts("Controllo più frequentemente");
			xtimer_sleep(5);
		}
		printf("\n");
	}
	return 0;
}

int conn(int argc, char **argv){
	(void)argc;
	(void)argv;
	puts("For the moment the service is not available.");
	return 0;
}

static const shell_command_t commands[] = {
    { "start", "Start the work", start },
	{ "connect", "Start the connection", conn},
    {NULL, NULL, NULL}
};

int main(void)
{
	xtimer_sleep(1);
	puts("Welcome in LIGHTS_ON_PARKING.");
	puts("This is our project to check the situation of a parking lot.");
	puts("Type 'help' to get started.");

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
