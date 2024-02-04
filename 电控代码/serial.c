#include "main.h"
#include "serial.h"
   uint8_t  RxData_TxPacket[10];
   uint8_t  RxData_1;
  // uint8_t  get_yaw1,get_pith, get_kh;
 void uart1_init(void){
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Initstructure;
	
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Initstructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Initstructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Initstructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
  GPIO_Initstructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	 GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1);
	 
	USART_InitTypeDef USART_Initstructure;
	USART_Initstructure.USART_BaudRate = 9600;
	USART_Initstructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Initstructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_Initstructure.USART_Parity = USART_Parity_No;
	USART_Initstructure.USART_StopBits = USART_StopBits_2;
	USART_Initstructure.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART1,&USART_Initstructure);
	USART_Cmd(USART1,ENABLE);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		
	NVIC_InitTypeDef  NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
//	DMA_InitTypeDef  DMA_InitStructure;
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);
//	DMA_DeInit(DMA1_Stream5); 
//  DMA_InitStructure.DMA_Channel = DMA_Channel_4;  //通道选择
//  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32_t)&(USART1->DR);//DMA外设地址****************************
//  DMA_InitStructure.DMA_Memory0BaseAddr = (u32_t)RXBuff;//DMA 存储器0地址 内存地址
//  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//外设到存储器模式*******************************
//  DMA_InitStructure.DMA_BufferSize = RX_BUF_SIZE;//数据传输量 
//  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设非增量模式
//  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//存储器增量模式
//  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//外设数据长度:8位
//  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//存储器数据长度:8位
//  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// 使用普通模式 ********************************
//  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//中等优先级**********
//  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
//  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;//***************
//  DMA_InitStructure.DMA_MemoryBurst = DMA_Mode_Normal;
//  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//外设突发单次传输
//	
//  DMA_Init(DMA1_Stream1, &DMA_InitStructure);//初始化DMA1 Stream5	
//	DMA_ITConfig(DMA1_Stream5,DMA_IT_TC,ENABLE);
//	DMA_Cmd(DMA1_Stream1,ENABLE);
	
}

/*发送一个字节*/
void Usart1_SendByte(uint8_t byte){
	USART_SendData(USART1,byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	
}

void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
	uint16_t i;
	for (i = 0; i < Length; i ++)
	{
		
		Usart1_SendByte(Array[i]);
	}
}


/*发送字符串*/
void Serial_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		Usart1_SendByte(String[i]);
	}
}




 uint8_t Serial_GetrxFlag(void)
 {
		if(RxData_1==1)
		{
			RxData_1=0;
		  return 1;
		}
		return 0;
 }

   uint8_t  RxData ;

  union 
 {
	 float get_yaw;
unsigned char u_yaw[4];
 }sendyaw;
 union 
 {
	 float get_pith;
	unsigned char u_pith[4];
 }sendpith;
 union 
 {
	 float get_kh;
	 unsigned char u_kh[2];
 }sendkh;

 
	void parse(void)
{
 sendyaw.u_yaw[0]=RxData_TxPacket[0];
 sendyaw.u_yaw[1]=RxData_TxPacket[1];
 sendyaw.u_yaw[2]=RxData_TxPacket[2];
 sendyaw.u_yaw[3]=RxData_TxPacket[3];
 sendpith.u_pith[0]=RxData_TxPacket[4];	
 sendpith.u_pith[1]=RxData_TxPacket[5];
 sendpith.u_pith[2]=RxData_TxPacket[6];
 sendpith.u_pith[3]=RxData_TxPacket[7];
 sendkh.u_kh[0]=RxData_TxPacket[8];
 sendkh.u_kh[1]=RxData_TxPacket[9];
}
 
 


void USART1_IRQHandler(void)
{  
	
	static uint8_t RxState=0;   
	static int i=0;
    
if( USART_GetFlagStatus(USART1,USART_IT_RXNE)==SET)
{      
			
		RxData=USART_ReceiveData(USART1);
		if(RxState==0)
{     
	if(RxData==0xED)
	{
	RxState=1;
	i=0;
	}
} 
else if(RxState==1)
	{			
	RxData_TxPacket[i++] = RxData;
		
	if(i>=10)
	{	
	parse();
	RxState=2; 
	}
	
	}
	else if(RxState==2)
	{                                                                                   
	if(RxData==0xEC)
	RxState=0;
	RxData_1=1;
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);	 
	}
	}
	
}		 
