#include "ros/ros.h"
#include "serial/serial.h"
#include "serial_send/Serial_Receive.h"

#define Start_Byte 0x5A             //起始帧

serial::Serial ser;
uint8_t Receive_Buff[15];               //接收缓冲区

typedef union
{
    float float_data;
    uint8_t byte_data[4];
}Float_Byte;

typedef struct
{
    Float_Byte vx;
    Float_Byte vy;
    Float_Byte wz;
}ROS_Msg_t;

ROS_Msg_t ros_msg;
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
    *(_pBuf + _usLen) = (CRCValue & 0xFF00) >> 8;
    *(_pBuf + _usLen + 1) = (CRCValue & 0x00FF);
    return;
} 

void Serial_Ros(serial_send::Serial_Receive *Serial_Receive)
{
    uint8_t CRC1 = Receive_Buff[14];
    uint8_t CRC2 = Receive_Buff[15];
    getModbusCRC16(Receive_Buff + 1,13);
    if(CRC1 == Receive_Buff[14] && CRC2 == Receive_Buff[15])
    {
        ros_msg.vx.byte_data[0] = Receive_Buff[1];
        ros_msg.vx.byte_data[1] = Receive_Buff[2];
        ros_msg.vx.byte_data[2] = Receive_Buff[3];
        ros_msg.vx.byte_data[3] = Receive_Buff[4];

        ros_msg.vy.byte_data[0] = Receive_Buff[5];
        ros_msg.vy.byte_data[1] = Receive_Buff[6];
        ros_msg.vy.byte_data[2] = Receive_Buff[7];
        ros_msg.vy.byte_data[3] = Receive_Buff[8];

        ros_msg.wz.byte_data[0] = Receive_Buff[9];
        ros_msg.wz.byte_data[1] = Receive_Buff[10];
        ros_msg.wz.byte_data[2] = Receive_Buff[11];
        ros_msg.wz.byte_data[3] = Receive_Buff[12];

        Serial_Receive->vx = ros_msg.vx.float_data;
        Serial_Receive->vy = ros_msg.vy.float_data;
        Serial_Receive->wz = ros_msg.wz.float_data;
    }
}

int main(int argc,char **argv)
{
    ros::init(argc,argv,"Serial_Receive");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<serial_send::Serial_Receive>("Serial_Receive",1000);
    serial_send::Serial_Receive Serial_Receive;
    //打开串口
    try
    {
        ser.setPort("/dev/car");//串口号
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
        ROS_INFO_STREAM("Serial Port initialized");
    else
        return -1;
    ros::Rate loop_rate(100);
    while(ros::ok())
    {
        size_t n = ser.available();
        if(n != 0)
        {
            n = ser.read(Receive_Buff,n);
            if(Receive_Buff[0] == Start_Byte)
                Serial_Ros(&Serial_Receive);
            pub.publish(Serial_Receive);
            nh.setParam("color",((Receive_Buff[13] & 0x01) == 0x01));
            nh.setParam("game_start",((Receive_Buff[13] & 0x02) == 0x02));
        }
        loop_rate.sleep();
    }
    return 0;
}
