#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "LightBar.h"
#include "Armor.h"
#include "Params.h"
#include "Perspective.h"
#include "TRTModule.hpp"
#include "/usr/include/CameraApi.h"
#include <cmath>
#include <tuple>
// #include "serial_send.hpp"
#define OFFSET_BETWEEN_GUN_CAM 0
#define THRESHOLD1 70
#define ARMOR_REAL_WIDTH 55.5
// #include <opencv2/highgui.hpp>
// #include <cvcam>
using namespace cv;
using namespace std;

unsigned char           * g_pRgbBuffer;     //处理后数据缓存区


template<typename T>
T get2lineIPoint(const T& lineOnePt1, const T& lineOnePt2, const T& lineTwoPt1, const T& lineTwoPt2)
{
	double x;
	double y;

	cv::Point2d result(-1,-1);
	double k = (lineOnePt1.y - lineOnePt2.y) / (lineOnePt1.x- lineOnePt2.x);
	double b = lineOnePt1.y - k * lineOnePt1.x;

	double k1 = (lineTwoPt1.y - lineTwoPt2.y) / (lineTwoPt1.x - lineTwoPt2.x);
	double b1 = lineTwoPt1.y - k1 * lineTwoPt1.x;

	x = (b1 - b) / (k - k1);
	y = k * x + b;
	result.x = x;
	result.y = y;

	return result;
}

template<typename T>
inline double get2pointDis(const T& p1, const T& p2){
    return ::pow(
        (::pow((p1.x-p2.x),2)+::pow((p1.y-p2.y),2))
        ,0.5
    );
}


template <typename T1,typename T2>
inline std::pair<double,double> getCenterOffset(const T1&&p,const T2&&c){
    cout << "p.x-c.x,c.y-p.y" << p.x-c.x << " " << c.y-p.y<< endl;
    return std::make_pair(p.x-c.x,c.y-p.y);
}

template<typename T>
float getLinearScale(const T& p0,const T& p1)
{
    return static_cast<float>(ARMOR_REAL_WIDTH/get2pointDis(p0,p1));
}


int main(int argc,char** argv) {
    cout << "Hello, World!" << endl;


    const cv::Scalar colors[3] = {{255, 0, 0}, {0, 0, 255}, {0, 255, 0}};

    string onnx_file = "/home/wutrm/Documents/RobowithYOLO/src/asset/model-opt-4.onnx";
    TRTModule model(onnx_file);
    int cnt_useless = -1;
	

    int                     iCameraCounts = 1;
    int                     iStatus=-1;
    tSdkCameraDevInfo       tCameraEnumList;
    int                     hCamera;
    tSdkCameraCapbility     tCapability;      //设备描述信息
    tSdkFrameHead           sFrameInfo;
    BYTE*			        pbyBuffer;
    // int                     iDisplayFrames = 10000;
    // IplImage *iplImage = NULL;
    int                     channel=3;

    CameraSdkInit(1);

    //枚举设备，并建立设备列表
    iStatus = CameraEnumerateDevice(&tCameraEnumList,&iCameraCounts);
	printf("state = %d\n", iStatus);

	printf("count = %d\n", iCameraCounts);

    cout <<hCamera<<endl;
    //没有连接设备
    if(iCameraCounts==0){
	cout<<"return -1"<<endl;
        return -1;
    }

    //相机初始化。初始化成功后，才能调用任何其他相机相关的操作接口
    iStatus = CameraInit(&tCameraEnumList,-1,-1,&hCamera);

    //初始化失败
	printf("state = %d\n", iStatus);
    if(iStatus!=CAMERA_STATUS_SUCCESS){
        return -1;
    }

    //获得相机的特性描述结构体。该结构体中包含了相机可设置的各种参数的范围信息。决定了相关函数的参数
    CameraGetCapability(hCamera,&tCapability);

    //
    g_pRgbBuffer = (unsigned char*)malloc(tCapability.sResolutionRange.iHeightMax*tCapability.sResolutionRange.iWidthMax*3);
    //g_readBuf = (unsigned char*)malloc(tCapability.sResolutionRange.iHeightMax*tCapability.sResolutionRange.iWidthMax*3);

    /*让SDK进入工作模式，开始接收来自相机发送的图像
    数据。如果当前相机是触发模式，则需要接收到
    触发帧以后才会更新图像。    */
    CameraPlay(hCamera);

    if(tCapability.sIspCapacity.bMonoSensor){
        channel=1;
        CameraSetIspOutFormat(hCamera,CAMERA_MEDIA_TYPE_MONO8);
    }else{
        channel=3;
        CameraSetIspOutFormat(hCamera,CAMERA_MEDIA_TYPE_BGR8);
    }

    RotatedRect rect = RotatedRect();
    // VideoCapture capture("/home/wutrm/Documents/videos/testVideo.mp4");
    // VideoCapture capture = VideoCapture(0);
    Mat frame;
    char c;

    wutrm::LightBarFinder lightBarFinder;
    wutrm::LightBarBlobs lightBarBlobs;
    Point2f roi_offset;
    //lightBarFinder.setEnemyColor(1);

    wutrm::ArmorFinder armorFinder;
    wutrm::ArmorBlobs armorBlobs;

    wutrm::Perspective PnPer;
    Mat cam = PnPer.cameraMatrixParams(), dis = PnPer.distCoeffsParams();



    while(1)
    {
        if(CameraGetImageBuffer(hCamera,&sFrameInfo,&pbyBuffer,1000) == CAMERA_STATUS_SUCCESS)
		{
		    CameraImageProcess(hCamera, pbyBuffer, g_pRgbBuffer,&sFrameInfo);
		    
		    cv::Mat frame(
					cv::Size(sFrameInfo.iWidth,sFrameInfo.iHeight), 
					sFrameInfo.uiMediaType == CAMERA_MEDIA_TYPE_MONO8 ? CV_8UC1 : CV_8UC3,
					g_pRgbBuffer
					);
			imshow("Opencv Demo", frame);
                    c = (char) waitKey(1);
            if (c == 27 || frame.empty())
            {
                cout << "video break." << endl;
                break;
            }
            // imshow("testVideo", frame);
            auto detections = model(frame);
            cv::Mat im2show = frame.clone();
            if (detections.empty()) {
                cnt_useless += 1;
                std::cout<<"No enemy detected!------"<<cnt_useless<<endl;
                // fmt::print(fmt::fg(fmt::color::blue), "No enemy detected!");
            }
            else {

                cnt_useless = -1;
                
                for (const auto &b: detections) {
                    std::cout<<b.pts[0]<<" "<<b.pts[1]<<endl;
                    cv::line(im2show, b.pts[0], b.pts[1], colors[2], 2);
                    cv::line(im2show, b.pts[1], b.pts[2], colors[2], 2);
                    cv::line(im2show, b.pts[2], b.pts[3], colors[2], 2);
                    cv::line(im2show, b.pts[3], b.pts[0], colors[2], 2);
                    cv::putText(im2show, std::to_string(b.tag_id), b.pts[0], cv::FONT_HERSHEY_SIMPLEX, 1, colors[b.color_id]);

                }
            }
           imshow("detect", im2show);
            
            

            //在成功调用CameraGetImageBuffer后，必须调用CameraReleaseImageBuffer来释放获得的buffer。
			//否则再次调用CameraGetImageBuffer时，程序将被挂起一直阻塞，直到其他线程中调用CameraReleaseImageBuffer来释放了buffer
			CameraReleaseImageBuffer(hCamera,pbyBuffer);
            // sd::send();
	}
    }
    
    // while(capture.isOpened())
    // {
    //     capture >> frame;

    //     c = (char) waitKey(20);
    //     if (c == 27 || frame.empty())
    //     {
    //         cout << "video break." << endl;
    //         break;
    //     }
    //     imshow("testVideo", frame);
    //     lightBarFinder.findLightBarBlobs(frame, lightBarBlobs, roi_offset);
    //     for (int i = 1; i < lightBarBlobs.size(); i++)
    //     {
    //         RotatedRect bar1 = lightBarBlobs[i - 1], bar2 = lightBarBlobs[i];
    //         wutrm::ArmorBlob armor;
    //         armorFinder.getArmor(bar1, bar2, armor);
    //         // rectangle(frame, armor.rect, Scalar(0, 255, 0), 2);

    //         Mat imageParams = Mat(armor.corners);
    //         const auto p0 = armor.corners[0];
    //         const auto p1 = armor.corners[1];
    //         const auto p2 = armor.corners[2];
    //         const auto p3 = armor.corners[3];
    //         // imshow("corner",imageParams);
    //             // cv::circle(frame,cv::Point(armor.corners[2]),1,cv::Scalar(0,0,255),3);
    //         auto Res = PnPer.PnP(imageParams, cam, dis);
    //         cout << cv::Point(armor.corners[0]) << endl;
    //         // cout << Res.first << endl;
    //         cout << Res.second << endl;
    //         cout << Res.second.cols << " " << Res.second.rows << endl;
    //         cout << Res.second.ptr<double>(0)[0] << endl;
    //         // float* Ptr = Res.second.data;
    //         // cout << *(static_cast<float*>(Ptr))<<endl;
    //         // cv::circle(frame,cv::Point(frame.cols/2,40),1,cv::Scalar(0,0,255),3);
    //         cout << "width" << frame.size().width << endl;
    //         cout << "height" << frame.size().height << endl;
    //         cout << "cols" << frame.cols << endl;
    //         cout << "rows" << frame.rows << endl;
    //         const auto centerP = get2lineIPoint(p0,p2,p1,p3);
    //         cv::circle(frame,centerP,1,cv::Scalar(0,0,255),3);

    //         cout<<centerP.x<<endl;
    //         /*calculating the depth*/
    //         auto depth = ::pow(
    //             ::pow(Res.second.ptr<double>(0)[0],2) +
    //             ::pow(Res.second.ptr<double>(1)[0],2) +
    //             ::pow(Res.second.ptr<double>(2)[0],2)
    //         ,0.5);
    //         cout << "depth" << depth << endl;
    //     }
    //     lightBarBlobs.clear();
    //     imshow("armor", frame);
    // }
    
    return 0;
}
