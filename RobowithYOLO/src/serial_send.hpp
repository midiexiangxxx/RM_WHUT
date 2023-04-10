#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include<unistd.h>
namespace sd{
int fd;
unsigned char Start_Byte[1] = {0xFF};             //发送起始帧
unsigned char CRC_Data[8];               //发送缓冲区
float Gimbal_Data[3];

/**
* 功能：根据ModBus规则计算CRC16
* 参数：
*       _pBuf:待计算数据缓冲区,计算得到的结果存入_pBuf的最后两字节
*       _usLen:待计算数据长度(字节数)
* 返回值：16位校验值
*/
void getModbusCRC16(unsigned char *_pBuf, unsigned short int _usLen)
{
    unsigned short int CRCValue = 0xFFFF;           //初始化CRC变量各位为1
    unsigned char i,j;

    for(i=0;i<_usLen;++i)
    {
        CRCValue  ^= *(_pBuf+i);                    //当前数据异或CRC低字节
        for(j=0;j<8;++j)                            //一个字节重复右移8次
        {
            if((CRCValue & 0x01) == 0x01)           //判断右移前最低位是否为1
            {
                 CRCValue = (CRCValue >> 1)^0xA001; //如果为1则右移并异或表达式
            }
            else 
            {
                CRCValue >>= 1;                     //否则直接右移一位
            }           
        }
    }
    CRC_Data[6] = ((CRCValue & 0xFF00) >> 8);
    CRC_Data[7] = (CRCValue & 0x00FF);
    return;            
} 
//float32 转成 2 Byte
/**
 * 功能：将 32 位的 float 乘以 1000 转为 int 并拆成 2 Byte
 * 参数：
 *      msg 要发送的数据
 *      id 数据帧中第几个数据
*/
void Float_To_Byte(float msg,int id)
{
    short temp_int = 1000 * msg;
    unsigned char *Byte = (unsigned char *)&temp_int;
    for(int i=0;i<2;i++)
    {
	CRC_Data[2 * (id - 1) + i] = Byte[1 - i];
    }
    return;
}
//清楚数据包
void Msg_Clear(void)
{
    for(int i=0;i<8;i++)
    {
        CRC_Data[i] = 0;
    }
}
//生成发送数据包
void Msg_To_Data(void)
{
    Msg_Clear();
    Float_To_Byte(Gimbal_Data[0],1);
    Float_To_Byte(Gimbal_Data[1],2);
    Float_To_Byte(Gimbal_Data[2],3);
    getModbusCRC16(CRC_Data,6);
    return;
}
void send()
{
    //打开串口
    fd = open("/dev/ttyUSB0",O_RDWR|O_NOCTTY);
    if(fd < 0)
    {
        perror("open serial port");
    }
    //封装数据
    Msg_To_Data();
    //发送数据
    write(fd,Start_Byte,1);
    int len = write(fd,CRC_Data,8);
    usleep(10000);
    //sleep(1);
    printf("\n%d %d\n",CRC_Data[0],CRC_Data[1]);
    if (len < 0)
    {
  	printf("write data error \n");
    }
    //关闭串口
    printf("$$$$$SENDED$$$$$%.2f   %.2f   %.2f\n",Gimbal_Data[0],Gimbal_Data[1],Gimbal_Data[2]);
    close(fd);
}
}
