/*Notas de trabajo
    

para agregar el encoder:
    usar un timer con ISR 
    implementar funcion de gray a int
    ver como incorporar al menu

display
    buscar librerias porque paja-> son una verga 
    hay un ejemplo de raspberry
    probar ahora correr un programa, cambie el cmake para agregar el .c del ejemplo
    y deje el .h de la libreria custom.
*/

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "header.h" 

//
#define I2C_PORT i2c0
//sensor de temperatura
static int addr_Temp_Sense = 0x48;
    //iniciar el Sensor de temperatura
void init_temp_sensor(){
    sleep_ms(1000);
    uint8_t reg=0x00;//0x00 (only read) temp - 0x01 (read/write) conf
    uint8_t i2c_in[1];
    uint8_t i2c_out[2];
    i2c_out[0]=0x01;
    i2c_out[1]=0x01;
    int ret;
    printf("\n Control 1  init tep sense\n");
    i2c_write_blocking(I2C_PORT, addr_Temp_Sense, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, addr_Temp_Sense, i2c_in, 1, false);
    printf("\n Control 2  init tep sense, init temp %d\n",i2c_in[0]);
    /*
    if(ret==PICO_ERROR_GENERIC){
        while(1){
            printf("\n pico error generic");

        }
    }*/

}
    //leer sensor de temperatura
float read_temperature() {
    uint8_t command = 0x00;  //registro de temperatura
    uint8_t temperature_data;
    
    i2c_write_blocking(i2c0, addr_Temp_Sense, &command, 1, true);  // Write command
    i2c_read_blocking(i2c0, addr_Temp_Sense, &temperature_data, 1, false);  // Read temperature
    
    float temperatura = (float)temperature_data;  // Convertimos a float
    return temperatura;
}
    
//display I2C


    //inicio del main

int main(){
    stdio_init_all();
    //inicio del bus i2c
        i2c_init(I2C_PORT, 100*1000);
        gpio_set_function(20,GPIO_FUNC_I2C);//SDA
        gpio_set_function(21,GPIO_FUNC_I2C);//SCL
        gpio_pull_up(20);
        gpio_pull_up(21);
    
    sleep_ms(5000);
    
    //variables 
    float temperature;

    //main while
    while (1) {
        
        temperature = read_temperature();
        printf("\nTemperature: %.2f°C\n", temperature);
        sleep_ms(1000);
        
    }
    return 0;
}
    //funciones 

