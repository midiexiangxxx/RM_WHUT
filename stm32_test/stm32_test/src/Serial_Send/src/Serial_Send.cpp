#include "ros/ros.h"
#include "serial/serial.h"
#include "Serial_Send/Serial_Send.h"
#include "Serial_Send/Serial_Receive.h"
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>

using namespace std;
#define Start_Byte 0xFF//起始帧
#define Receive_Start_Byte1 0x55
#define Receive_Start_Byte2 0xAA

uint8_t Error_Data[15] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

serial::Serial ser;
Serial_Send::Serial_Send Serial_Send_Msg;
Serial_Send::Serial_Receive Serial_Receive_Msg;
std::vector<uint8_t> Serial_Send_Data;
uint8_t CRC_Data[14];
uint8_t Receive_Buff[7];
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
    Serial_Send_Data.push_back((CRCValue & 0xFF00) >> 8);
    Serial_Send_Data.push_back(CRCValue & 0x00FF);
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
    int temp_int = 1000 * msg;
    uint8_t *Byte = (uint8_t *)&temp_int;
    for(int i = 0;i < 2;i++)
    {
        Serial_Send_Data.push_back(Byte[1 - i]);
        CRC_Data[2*(id - 1) + i] = Byte[1 - i];
    }
    return;
}
//生成发送数据包
void Msg_To_Data(void)
{
    Serial_Send_Data.clear();
    Serial_Send_Data.push_back(Start_Byte);
    Float_To_Byte(Serial_Send_Msg.gimbal_x,1);
    Float_To_Byte(Serial_Send_Msg.gimbal_y,2);
    Float_To_Byte(Serial_Send_Msg.gimbal_z,3);
    Float_To_Byte(Serial_Send_Msg.vx_set,4);
    Float_To_Byte(Serial_Send_Msg.vy_set,5);
    Float_To_Byte(Serial_Send_Msg.wz_set,6);
    getModbusCRC16(CRC_Data,12);
    return;
}
//
void Get_Vel(void)
{
	short temp_short = ((Receive_Buff[0] << 8) | Receive_Buff[1]);
	Serial_Receive_Msg.vx = (float)temp_short / 1000;
	temp_short = ((Receive_Buff[2] << 8) | Receive_Buff[3]);
	Serial_Receive_Msg.vy = (float)temp_short / 1000;
	temp_short = ((Receive_Buff[4] << 8) | Receive_Buff[5]);
	Serial_Receive_Msg.wz = (float)temp_short / 1000;
    return;
}
//
void Judge_Receive(void)
{
    if(Receive_Buff[6] == 0x00)
    {
		Get_Vel();
    }
	else if(Receive_Buff[6] == 0xFF)
	{
		ser.write(Error_Data,15);
	}
	return;
}
//
void Receive_Msg(void)
{	
	ser.read(Receive_Buff,1);
	if(Receive_Buff[0] == Receive_Start_Byte1)
	{
		ser.read(Receive_Buff,1);
		if(Receive_Buff[0] == Receive_Start_Byte2)
		{
			ser.read(Receive_Buff,7);
			Judge_Receive();
		}
	}
	return;
}
//回调函数
void Get_Msg(const Serial_Send::Serial_Send::ConstPtr& Ptr_Msg)
{

    Serial_Send_Msg.gimbal_x = Ptr_Msg->gimbal_x;
    Serial_Send_Msg.gimbal_y = Ptr_Msg->gimbal_y;
    Serial_Send_Msg.gimbal_z = Ptr_Msg->gimbal_z;
    Serial_Send_Msg.vx_set = Ptr_Msg->vx_set;
    Serial_Send_Msg.vy_set = Ptr_Msg->vy_set;
    Serial_Send_Msg.wz_set = Ptr_Msg->wz_set;
    Msg_To_Data();
    ser.write(Serial_Send_Data);
    Receive_Msg();
}

int main(int argc,char** argv)
{
    ros::init(argc,argv,"Serial_Send");
    ros::NodeHandle nh;
    ros::Subscriber sub_all =nh.subscribe<Serial_Send::Serial_Send>("Serial_Send_Msg",1000,Get_Msg);
	ros::Publisher pub_all = nh.advertise<Serial_Send::Serial_Receive>("Serial_Receive_Msg",1000);
	Serial_Receive_Msg.vx = 0;
	Serial_Receive_Msg.vy = 0;
	Serial_Receive_Msg.wz = 0;
    //打开串口
    try
    {
        ser.setPort("/dev/ttyUSB0");//串口号
        ser.setBaudrate(115200);//波特率
        serial::Timeout to = serial::Timeout::simpleTimeout(1000);
        ser.setTimeout(to);
        ser.open();
    }
    catch(const std::exception& e)
    {
        ROS_ERROR_STREAM("Unable to open port ");
        return -1;
    }
    if(ser.isOpen())
    {
        ROS_INFO_STREAM("Serial Port initialized");
    }
    else
    {
        return -1;
    }
	ros::Rate r(1000);
    while (ros::ok())
    {
        pub_all.publish(Serial_Receive_Msg);
        r.sleep();
        ros::spinOnce();
    }
    ser.close();
    return 0;
}
