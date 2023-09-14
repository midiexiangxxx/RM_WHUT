#include <iostream>
#include <CameraApi.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/imgproc/types_c.h>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <cstring>

#include "../include/Detector.h"
#include "../include/Perspective.h"
#include "../include/stop_watch.hpp"
#include "../include/uart.hpp"

#include <cmath>
#define PI acos(-1)

// camera
int                     iCameraCounts = 1;
int                     iStatus=-1;
tSdkCameraDevInfo       tCameraEnumList;
int                     hCamera;
tSdkCameraCapbility     tCapability;      //设备描述信息
tSdkFrameHead           sFrameInfo;
BYTE*			        pbyBuffer;
int                     iDisplayFrames = 1000;
IplImage *iplImage = NULL;
int                     channel=3;
unsigned char           * g_pRgbBuffer;     //处理后数据缓存区

// detector
wutrm::DetectorParams dp;
wutrm::ArmorParams ap;
wutrm::LightBarParams lp;
wutrm::CameraParams cp;
wutrm::MVCamera camera(cp);
wutrm::Detector detector(dp, lp, ap);
std::vector<cv::Point2f> centers;
//double last_yaw,last_pitch,last_dist=0.0;
//timer
int frame_count, total_s;
double fps, total_ms;
StopWatch sw;

void frameSolver(cv::Mat & frame, bool show);
bool driverInit();
bool cameraInit();
std::shared_ptr<Driver> driver;
int main() {
    std::cout << "Hello, World!" << std::endl;

    driverInit();

//    std::string video = "/home/lbh/Videos/videos/testVideo.mp4";
//    cv::VideoCapture capture(video);
//    std::cout << capture.isOpened() << std::endl;

    cv::Mat frame;

    cameraInit();

    int count = 0;
    while(true)
    {
        // sp.writeBytes();
        sw.tic();
        count ++;
        if(CameraGetImageBuffer(hCamera,&sFrameInfo,&pbyBuffer,1000) == CAMERA_STATUS_SUCCESS) {
            CameraImageProcess(hCamera, pbyBuffer, g_pRgbBuffer, &sFrameInfo);

            cv::Mat matImage(
                    cvSize(sFrameInfo.iWidth, sFrameInfo.iHeight),
                    sFrameInfo.uiMediaType == CAMERA_MEDIA_TYPE_MONO8 ? CV_8UC1 : CV_8UC3,
                    g_pRgbBuffer
            );
            frame = matImage;
            // imshow("Opencv Demo", matImage);
            //在成功调用CameraGetImageBuffer后，必须调用CameraReleaseImageBuffer来释放获得的buffer。
            //否则再次调用CameraGetImageBuffer时，程序将被挂起一直阻塞，直到其他线程中调用CameraReleaseImageBuffer来释放了buffer
        }
        // std::cout << frame.rows << " " << frame.cols << std::endl;
        if(frame.empty())
        {
            std::cout << "over" << std::endl;
            break;
        }
        frameSolver(frame, true);
        cv::imshow("test", frame);

        int key = cv::waitKey(1);
        if(key == 27)
        {
            std::cout << "shutdown" << std::endl;
            break;
        }

        CameraReleaseImageBuffer(hCamera,pbyBuffer);

        double ms = sw.toc();
        total_ms += ms;
        // std::cout << "stop watch: " << ms << " fps: " << 1000 / ms << std::endl;
        if(total_ms >= 1000)
        {
            total_ms -= 1000;
            total_s ++;
            std::cout << "total time: " << total_s << " fps: " << count << std::endl;
            count = 0;
        }


    }
    return 0;
}

void frameSolver(cv::Mat & frame, bool show = true)
{
    auto armors = detector.detectResult(frame);
    if(armors.empty())
    {
        centers.clear();
    }
    else
    {
        for(auto & armor : armors)
        {   
            cv::Point2f center = armor.center;
            double x_img = 640 - center.x, y_img = center.y - 512;
            if(x_img < 25 && x_img > -25) x_img = 0;
            if(y_img < 25 && y_img > -25) y_img = 0;
            std::cout << x_img << " " << y_img << std::endl;
            wutrm::PnP pnp(camera, armor);
            centers.push_back(armor.center);
            if(!show) continue;
            // std::cout << "         " << armor.realHeight <<" " << armor.realLength << std::endl;
            std::cout << std::endl << "rp: ";
            for(auto rp : pnp.rotationMatrix)
            {
                std::cout << rp << " ";
            }
            std::cout << std::endl << "tp:       ";
            double temp[3];
            int cnt = 0;
            for(auto tp : pnp.translationMatrix)
            {
                std::cout << tp << "       ";
                temp[cnt] = tp;
                cnt ++;

            }
            double yaw = -atan2(temp[0], temp[2]), pitch = -atan2(temp[1], temp[2]);
            if(pitch < 0.035 && pitch > -0.035) pitch = 0;
            double dist = sqrt(temp[0] * temp[0] + temp[1] * temp[1] + temp[2] * temp[2]);
            driver->shoot_angle(x_img, y_img, dist);
            /*driver->shoot_angle(yaw-last_yaw, pitch-last_pitch, dist-last_dist);
            last_yaw = yaw;
            last_pitch = pitch;
            last_dist = dist;*/
            std::cout << std::endl << "yaw: " << yaw * 180 / PI << "    pitch: " << pitch * 180 / PI << "    dist: " << dist << std::endl;
            // std::cout << std::endl << "dist: " << pnp.imageDistance << std::endl;
        }
        // 1std::cout << armors[0].center << std::endl;
        for(auto center : centers)
        {
            cv::circle(frame, center, 1, CV_RGB(255, 0, 0), 1);
        }
    }
}

bool cameraInit()
{


    CameraSdkInit(1);

    //枚举设备，并建立设备列表
    iStatus = CameraEnumerateDevice(&tCameraEnumList,&iCameraCounts);
    printf("state = %d\n", iStatus);

    printf("count = %d\n", iCameraCounts);
    //没有连接设备
    if(iCameraCounts==0){
        return false;
    }

    //相机初始化。初始化成功后，才能调用任何其他相机相关的操作接口
    iStatus = CameraInit(&tCameraEnumList,-1,-1,&hCamera);

    CameraSetAeExposureRange(hCamera, 1000, 5000);

    //初始化失败
    printf("state = %d\n", iStatus);
    if(iStatus!=CAMERA_STATUS_SUCCESS){
        return false;
    }

    //获得相机的特性描述结构体。该结构体中包含了相机可设置的各种参数的范围信息。决定了相关函数的参数
    CameraGetCapability(hCamera,&tCapability);
    std::cout << tCapability.iFrameSpeedDesc << std::endl;

    //
    g_pRgbBuffer = (unsigned char*)malloc(tCapability.sResolutionRange.iHeightMax*tCapability.sResolutionRange.iWidthMax*3);
    //g_readBuf = (unsigned char*)malloc(tCapability.sResolutionRange.iHeightMax*tCapability.sResolutionRange.iWidthMax*3);

    /*让SDK进入工作模式，开始接收来自相机发送的图像
    数据。如果当前相机是触发模式，则需要接收到
    触发帧以后才会更新图像。    */
    CameraPlay(hCamera);

    /*其他的相机参数设置
    例如 CameraSetExposureTime   CameraGetExposureTime  设置/读取曝光时间
         CameraSetImageResolution  CameraGetImageResolution 设置/读取分辨率
         CameraSetGamma、CameraSetConrast、CameraSetGain等设置图像伽马、对比度、RGB数字增益等等。
         本例程只是为了演示如何将SDK中获取的图像，转成OpenCV的图像格式,以便调用OpenCV的图像处理函数进行后续开发
    */

    if(tCapability.sIspCapacity.bMonoSensor){
        channel=1;
        CameraSetIspOutFormat(hCamera,CAMERA_MEDIA_TYPE_MONO8);
    }else{
        channel=3;
        CameraSetIspOutFormat(hCamera,CAMERA_MEDIA_TYPE_BGR8);
    }

    return true;
}

bool driverInit()
{
/*
    serial port libaorun
*/
    // static boost::asio::io_service ios;
    // boost::asio::serial_port sp(ios, "/dev/ttyUSB0");
    // sp.set_option(boost::asio::serial_port::baud_rate(115200));

/*
    serial port pxx
*/
    // USB转串口的设备名为 / dev/ttyUSB0
    driver = std::make_shared<Driver>("/dev/ttyUSB0", BaudRate::BAUD_115200);
	if (driver == nullptr)
	{
		std::cout << "Create uart-driver error!" << std::endl;
		return false;
	}
	// 串口初始化，打开串口设备及配置串口数据格式
	int ret = driver->open();
	if (ret != 0)
	{
		std::cout << "Uart open failed!" << std::endl;
		return false;
	}
        return true;
}
