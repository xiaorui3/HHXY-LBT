#ifndef __SERIAL_H
#define __SERIAL_H

 


  extern uint8_t  RxData_TxPacket[];
	extern  uint8_t  RxData_RxPacket[];
   void uart1_init(void);
   void Usart1_SendByte(uint8_t byte);
   void Serial_SendArray(uint8_t *Array, uint16_t Length);
    void Serial_SendString(char *String) ;
     void parse(void);
		  
		
#endif 
