# Description
    - The system includes: 8051 microcontroller, 8 LM35 sensors, led 7-segment, ADC0808.
    - 8051 reads temperature from 8 LM35 sensors by ADC sequentially, then displays on led-7segment (first digit indicates channel, remaining digits indicate temperature value). Finally, system sends that value to terminal HTerm by UART protocol.

# Software
    - Keil C IDE
    - Proteus
    - HTerm
    - Virtual Serial Port Driver

# Source:
    - main:         folder contains source code (contains 2 libraries for ADC0808 and led 7-seg)
    - P1:           simulates operation of system
    - schematic:    result of simulation
    - requirement:  requirement of system
    - Instruction:  instructs steps of set up simulation