#define UsbFrameHead 0x42    // USB通信帧头
#define UsbFrameLengthMin 4  // USB通信帧最短长度（字节）
#define UsbFrameLengthMax 30 // USB通信帧最长长度（字节）

typedef union
{
  uint8_t U8_Buff[2];
  uint16_t U16;
} Bint16_Union;

typedef union
{
  uint8_t U8_Buff[4];
  float Float;
} Bint32_Union;

typedef struct
{
  bool receiveStart;                              // 数据接收开始标志
  uint8_t receiveIndex;                           // 接收序列号
  bool receiveFinished;                           // 接收并校验成功
  uint8_t receiveBuff[UsbFrameLengthMax];         // 临时接收数据区
  uint8_t receiveBuffFinished[UsbFrameLengthMax]; // 校验完成数据区
} Usb_Struct;

