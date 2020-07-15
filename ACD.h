#ifndef ADC_H_
#define ADC_H_
#include "ADC_cfg.h"
#include "STD.h"
#include "ATMEGA32_Regs.h"

#define ADC_DISABLE 0
#define ADC_ENABLE  1

#define ADC_VREF_VCC               0
#define ADC_VREF_AREF              1
#define ADC_VREF_INTERNA_VOLTAGE   2

#define ADC_RIGHT_ADJUST  0
#define ADC_LEFT_ADJUST   1

#define ADC_CHANNEL_0     0
#define ADC_CHANNEL_1     1
#define ADC_CHANNEL_2     2
#define ADC_CHANNEL_3     3
#define ADC_CHANNEL_4     4
#define ADC_CHANNEL_5     5
#define ADC_CHANNEL_6     6
#define ADC_CHANNEL_7     7

#define ADC_AUTO_TRIGGER    0

#define ADC_RIGHT_ADJUST    0
#define ADC_LIFT_ADJUST     1

#define ADC_PRESC_2       0
#define ADC_PRESC_4       1
#define ADC_PRESC_8       2
#define ADC_PRESC_16      3
#define ADC_PRESC_32      4
#define ADC_PRESC_64      5
#define ADC_PRESC_128     6

/* ********************ADC_AUTO_TRIGGER_SOURCE****************** */
#define ADC_FREE_RUNNING_MODE   0
#define EXTERNAL_INTERRUPT      1

#define ADC_INTERRUPT_DISABLE    0
#define ADC_INTERRUPT_ENABLE     1


void ADC_INIT(void);
void ADC_READ (uint16* read);
void ADC_CHANGE_CHANNEL (uint8 channel);


#endif