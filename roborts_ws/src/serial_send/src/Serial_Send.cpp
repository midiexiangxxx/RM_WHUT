#include "ros/ros.h"
#include "serial/serial.h"
#include "serial_send/Serial_Send.h"

#define Start_Byte 0x5A             //起始帧

serial::Serial ser;
uint8_t Send_Buff[24];               //发送缓冲区
float last_yaw=0.0;
float last_pitch=0.0;

typedef union
{
    float float_data;
    uint8_t byte_data[4];
}Float_Byte;

typedef struct
{
    Float_Byte vx_set;
    Float_Byte vy_set;
    Float_Byte wz_set;
    Float_Byte yaw_add;
    Float_Byte pitch_add;
    uint8_t mode;
}ROS_Msg_t;
float timer=0.0;
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
//生成发送数据包
void Msg_To_Data(void)
{
    Send_Buff[0] = Start_Byte;
    
    Send_Buff[1] = ros_msg.vx_set.byte_data[0];
    Send_Buff[2] = ros_msg.vx_set.byte_data[1];
    Send_Buff[3] = ros_msg.vx_set.byte_data[2];
    Send_Buff[4] = ros_msg.vx_set.byte_data[3];

    Send_Buff[5] = ros_msg.vy_set.byte_data[0];
    Send_Buff[6] = ros_msg.vy_set.byte_data[1];
    Send_Buff[7] = ros_msg.vy_set.byte_data[2];
    Send_Buff[8] = ros_msg.vy_set.byte_data[3];

    Send_Buff[9] = ros_msg.wz_set.byte_data[0];
    Send_Buff[10] = ros_msg.wz_set.byte_data[1];
    Send_Buff[11] = ros_msg.wz_set.byte_data[2];
    Send_Buff[12] = ros_msg.wz_set.byte_data[3];

    Send_Buff[13] = ros_msg.yaw_add.byte_data[0];
    Send_Buff[14] = ros_msg.yaw_add.byte_data[1];
    Send_Buff[15] = ros_msg.yaw_add.byte_data[2];
    Send_Buff[16] = ros_msg.yaw_add.byte_data[3];

    Send_Buff[17] = ros_msg.pitch_add.byte_data[0];
    Send_Buff[18] = ros_msg.pitch_add.byte_data[1];
    Send_Buff[19] = ros_msg.pitch_add.byte_data[2];
    Send_Buff[20] = ros_msg.pitch_add.byte_data[3];
    
    Send_Buff[21] = ros_msg.mode;


    
    //ROS_INFO("yaw :%d %d %d %d",Send_Buff[9],Send_Buff[10],Send_Buff[11],Send_Buff[12]);
    //ROS_INFO("pitch :%d %d %d %d",Send_Buff[17],Send_Buff[18],Send_Buff[19],Send_Buff[20]);
    getModbusCRC16(Send_Buff + 1,21);
    return;
}


//回调函数
void Get_Msg(const serial_send::Serial_Send::ConstPtr& Ptr_Msg)
{

    ros_msg.vx_set.float_data = Ptr_Msg->vx_set;
    ros_msg.vy_set.float_data = Ptr_Msg->vy_set;
    
    ros_msg.wz_set.float_data = -Ptr_Msg->wz_set;

    if ((Ptr_Msg->yaw_add != last_yaw) || (Ptr_Msg->pitch_add !=last_pitch))
    {
    	ros_msg.yaw_add.float_data = Ptr_Msg->yaw_add;
    	ros_msg.pitch_add.float_data = Ptr_Msg->pitch_add;
    }
    else{
        ros_msg.yaw_add.float_data=0.0;
        ros_msg.pitch_add.float_data=0.0;
    }

   // ros_msg.pitch_add.float_data = Ptr_Msg->pitch_add;
    //ros_msg.pitch_add.float_data = 0.2617;
    //ros_msg.yaw_add.float_data = Ptr_Msg->yaw_add;
    //ros_msg.pitch_add.float_data = Ptr_Msg->pitch_add;
    if(ros_msg.wz_set.float_data == 0)
    {
        ros_msg.wz_set.float_data = Ptr_Msg->yaw_add*(-2.0);
    }
    /*if (fabs(ros_msg.pitch_add.float_data) <0.1)      
    {
         ros_msg.pitch_add.float_data=0.0;
    }*/
    //ros_msg.pitch_add.float_data = Ptr_Msg->pitch_add;
    last_yaw=Ptr_Msg->yaw_add;
    last_pitch=Ptr_Msg->pitch_add;

    ros_msg.mode = Ptr_Msg->mode;
    //ros_msg.mode = 0x00;
     

    //ROS_INFO("yaw:%f",Ptr_Msg->yaw_add);
    //ROS_INFO("pitch:%f",Ptr_Msg->pitch_add);
    ROS_INFO("Mode:%d",ros_msg.mode);

    ROS_INFO("vx:%f",ros_msg.vx_set.float_data);
    ROS_INFO("vy:%f" ,ros_msg.vy_set.float_data);
    //ROS_INFO("wz:%f",ros_msg.wz_set.float_data);
    if(ros_msg.yaw_add.float_data != 0.000000)
    {
        //ROS_INFO("Mode:%d",ros_msg.mode);
        ROS_INFO("yaw:%f",ros_msg.yaw_add.float_data);
        ROS_INFO("pitch:%f",ros_msg.pitch_add.float_data);
	
    }
    //spinn(ros_msg.yaw_add.float_data);
    
    /*
    for(int i=0;i<24;i++)
    {
	ROS_INFO("%x",Send_Buff[i]);
    }
    */
    //ROS_INFO("vx:%f",ros_msg.vx_set.float_data);
    static ros::Time start_time = ros::Time::now();
    static ros::Time now_time = ros::Time::now();
    now_time = ros::Time::now();
    static int shoot_flag = 0;
    if((now_time - start_time).toSec() > 0.5)
    {
        if((now_time - start_time).toSec() > 3)
        {
            if((ros_msg.mode & 0x80) == 0x80)
            {
                ros_msg.mode = 0x10;
                start_time = ros::Time::now();
                shoot_flag = 1;
            }
        }
    }
    else
    {
        if(shoot_flag == 1)
        {
            ros_msg.mode = 0x10;
        }
    }
    Msg_To_Data();
    ser.write(Send_Buff,24); 
    memset(Send_Buff,0,24);
	
}

int main(int argc,char** argv)
{
    ros::init(argc,argv,"Serial_Send");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<serial_send::Serial_Send>("Serial_Send_Msg",1000,Get_Msg);
    
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
	ros::Rate r(100);
	while(ros::ok())
	{
		ros::spinOnce();
		r.sleep();
	}
    ser.close();
    return 0;
}
