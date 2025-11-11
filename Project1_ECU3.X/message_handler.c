
#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"

unsigned long int timer_count;
//volatile unsigned char led_state = LED_OFF, status = e_ind_off;
unsigned char event[9][3] = {"ON", "GN", "G1", "G2", "G3", "G4", "G5", "Gr", "C_"};

void display_labels(void) {
    clcd_print("SP", LINE1(0));
    clcd_print("GR", LINE1(4));
    clcd_print("RPM", LINE1(8));
    clcd_print("IND", LINE1(13));
}

void handle_speed_data(uint8_t *data, uint8_t len) {
    //Implement the speed function
    clcd_putch(data[0], LINE2(0));    
    clcd_putch(data[1], LINE2(1));

}

void handle_gear_data(uint8_t *data, uint8_t len) {
    //Implement the gear function
    if(*data < 9)
        clcd_print(event[*data], LINE2(4));
}

void handle_rpm_data(uint8_t *data, uint8_t len)
{
    //Implement the rpm function
    clcd_print(data, LINE2(8));
}

/*
void handle_engine_temp_data(uint8_t *data, uint8_t len) {
    //Implement the temperature function
}
*/

void handle_indicator_data(uint8_t *data, uint8_t len) {
    //Implement the indicator function
    int indicator = *data;
    
    if(timer_count <= 10000)
    {
        if(indicator == e_ind_off) 
        {
            LEFT_IND_OFF();
            RIGHT_IND_OFF();
            clcd_putch(' ', LINE2(14));
            clcd_putch(' ', LINE2(15));
        }
        else if(indicator == e_ind_left)
        {
            LEFT_IND_ON();
            RIGHT_IND_OFF();
            clcd_putch('<', LINE2(14));
            clcd_putch(' ', LINE2(15));
        }
        else if(indicator == e_ind_right)
        {
            LEFT_IND_OFF();
            RIGHT_IND_ON();
            clcd_putch(' ', LINE2(14));
            clcd_putch('>', LINE2(15));
        }
        else if(indicator == e_ind_hazard)
        {
            RIGHT_IND_ON();
            LEFT_IND_ON();
            clcd_putch('<', LINE2(14));
            clcd_putch('>', LINE2(15));
        }
    }
    else
    {
        LEFT_IND_OFF();
        RIGHT_IND_OFF();
        
        clcd_putch(' ', LINE2(14));
        clcd_putch(' ', LINE2(15));
    }
}

void process_canbus_data() {
    //process the CAN bus data
    uint8_t data[5];
    uint8_t len = 0;
    uint16_t msg_id;
    static int c_flag = 0;
    
    can_receive(&msg_id, data, &len);
    if(c_flag == 0)
    {
        if (msg_id == SPEED_MSG_ID) {
            handle_speed_data(data, len);
        } else if (msg_id == GEAR_MSG_ID) {
            handle_gear_data(data, len);
            if(*data == 8)
            {
                c_flag = 1;
                
                clcd_clear();
                clcd_print("Collision !", LINE1(0));
                clcd_print("Vehicle Damaged", LINE2(0));
            }
        } else if (msg_id == RPM_MSG_ID) {
            handle_rpm_data(data, len);
        } else if (msg_id == INDICATOR_MSG_ID) {
            handle_indicator_data(data, len);
        }
    }
    else
    {
        if (msg_id == GEAR_MSG_ID) {
            if(*data != 8)
            {
                c_flag = 0;
                clcd_clear();
                
                display_labels();
            }
        }
    }
}