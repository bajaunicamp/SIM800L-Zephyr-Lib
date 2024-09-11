// Esse programa de expemplo printa "Hello World!" no LOG no momento em que o led pisca

#include "zephyr/device.h"
#include "zephyr/sys/printk.h"
#include "zephyr/logging/log.h"
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include "SIM800L.h"


LOG_MODULE_REGISTER();

const struct gpio_dt_spec *const led = &(const struct gpio_dt_spec)GPIO_DT_SPEC_GET(DT_NODELABEL(led0), gpios);

int main(){
  init_server(11547, TIM);

  while(1){
    send_server("oi");
    k_msleep(1);
  }
}
