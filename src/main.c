#include "zephyr/device.h"
#include "zephyr/sys/printk.h"
#include "zephyr/logging/log.h"
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include "SIM800L.h"


LOG_MODULE_REGISTER();

int main(){
  init_server(11547, TIM);

  while(1){
    send_server("oi");
    k_msleep(1);
  }
}
