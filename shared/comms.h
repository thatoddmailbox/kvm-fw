#ifndef _SHARED_COMMS_H
#define _SHARED_COMMS_H

#define BASE_I2C_ADDRESS 0x42

#define BASE_COMMAND_GET_STATE 0x00
#define BASE_COMMAND_SET_HDMI_A (0x01 << 2)
#define BASE_COMMAND_SET_HDMI_B (0x02 << 2)
#define BASE_COMMAND_SET_USB (0x03 << 2)

#endif