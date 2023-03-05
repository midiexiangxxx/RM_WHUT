#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "LightBar.h"
#include "Armor.h"
#include "Params.h"
#include "Perspective.h"
#include "/usr/include/CameraApi.h"
#include <cmath>

#define OFFSET_BETWEEN_GUN_CAM 0

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

int main() {
    // cout << "Hello, World!" << endl;

    // int                     iCameraCounts = 1;
    // int                     iStatus=-1;
    // tSdkCameraDevInfo       tCameraEnumList;
    // int                     hCamera;
    // tSdkCameraCapbility     tCapability;      //设备描述信息
    // tSdkFrameHead           sFrameInfo;
    // BYTE*			        pbyBuffer;
    // // int                     iDisplayFrames = 10000;
    // // IplImage *iplImage = NULL;
    // int                     channel=3;

    // CameraSdkInit(1);

    // //枚举设备，并建立设备列表
    // iStatus = CameraEnumerateDevice(&tCameraEnumList,&iCameraCounts);
	// printf("state = %d\n", iStatus);

	// printf("count = %d\n", iCameraCounts);

    // cout <<hCamera<<endl;
    // //没有连接设备
    // if(iCameraCounts==0){
    //     return -1;
    // }

    // //相机初始化。初始化成功后，才能调用任何其他相机相关的操作接口
    // iStatus = CameraInit(&tCameraEnumList,-1,-1,&hCamera);

    // //初始化失败
	// printf("state = %d\n", iStatus);
    // if(iStatus!=CAMERA_STATUS_SUCCESS){
    //     return -1;
    // }

    // //获得相机的特性描述结构体。该结构体中包含了相机可设置的各种参数的范围信息。决定了相关函数的参数
    // CameraGetCapability(hCamera,&tCapability);

    // //
    // g_pRgbBuffer = (unsigned char*)malloc(tCapability.sResolutionRange.iHeightMax*tCapability.sResolutionRange.iWidthMax*3);
    // //g_readBuf = (unsigned char*)malloc(tCapability.sResolutionRange.iHeightMax*tCapability.sResolutionRange.iWidthMax*3);

    // /*让SDK进入工作模式，开始接收来自相机发送的图像
    // 数据。如果当前相机是触发模式，则需要接收到
    // 触发帧以后才会更新图像。    */
    // CameraPlay(hCamera);

    // if(tCapability.sIspCapacity.bMonoSensor){
    //     channel=1;
    //     CameraSetIspOutFormat(hCamera,CAMERA_MEDIA_TYPE_MONO8);
    // }else{
    //     channel=3;
    //     CameraSetIspOutFormat(hCamera,CAMERA_MEDIA_TYPE_BGR8);
    // }

    // RotatedRect rect = RotatedRect();
    VideoCapture capture("/home/wutrm/Documents/videos/testVideo.mp4");
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



    // while(1)
    // {
    //     if(CameraGetImageBuffer(hCamera,&sFrameInfo,&pbyBuffer,1000) == CAMERA_STATUS_SUCCESS)
	// 	{
	// 	    CameraImageProcess(hCamera, pbyBuffer, g_pRgbBuffer,&sFrameInfo);
		    
	// 	    cv::Mat frame(
	// 				cv::Size(sFrameInfo.iWidth,sFrameInfo.iHeight), 
	// 				sFrameInfo.uiMediaType == CAMERA_MEDIA_TYPE_MONO8 ? CV_8UC1 : CV_8UC3,
	// 				g_pRgbBuffer
	// 				);
	// 		imshow("Opencv Demo", frame);
    //                 c = (char) waitKey(1);
    //         if (c == 27 || frame.empty())
    //         {
    //             cout << "video break." << endl;
    //             break;
    //         }
    //         // imshow("testVideo", frame);

    //         lightBarFinder.findLightBarBlobs(frame, lightBarBlobs, roi_offset);
    //         const int sz = lightBarBlobs.size();
    //         if(!sz){
    //             cout << "*****no armor*****" << endl;
    //         }
    //         else{
    //             for (int i = 1; i < sz; i++){
    //             RotatedRect bar1 = lightBarBlobs[i - 1], bar2 = lightBarBlobs[i];
    //             wutrm::ArmorBlob armor;
    //             armorFinder.getArmor(bar1, bar2, armor);
    //             rectangle(frame, armor.rect, Scalar(0, 255, 0), 2);

    //             Mat imageParams = Mat(armor.corners);
    //             cout<<"four_point"<<imageParams<<endl;

    //             cv::circle(frame,imageParams.at<cv::Point>(0,0),1,(0,0,255));
    //             cv::circle(frame,imageParams.at<cv::Point>(0,1),1,(0,0,255));
    //             cv::circle(frame,imageParams.at<cv::Point>(1,0),1,(0,0,255));
    //             cv::circle(frame,imageParams.at<cv::Point>(1,1),1,(0,0,255));

    //             auto Res = PnPer.PnP(imageParams, cam, dis);
    //             cout << Res.first << endl;
    //             cout << Res.second << endl;
    //             }
    //         }
    //         lightBarBlobs.clear();
    //         imshow("armor", frame);

    //         //在成功调用CameraGetImageBuffer后，必须调用CameraReleaseImageBuffer来释放获得的buffer。
	// 		//否则再次调用CameraGetImageBuffer时，程序将被挂起一直阻塞，直到其他线程中调用CameraReleaseImageBuffer来释放了buffer
	// 		CameraReleaseImageBuffer(hCamera,pbyBuffer);

	// 	}
    // }
    
    while(capture.isOpened())
    {
        capture >> frame;

        c = (char) waitKey(20);
        if (c == 27 || frame.empty())
        {
            cout << "video break." << endl;
            break;
        }
        imshow("testVideo", frame);
        lightBarFinder.findLightBarBlobs(frame, lightBarBlobs, roi_offset);
        for (int i = 1; i < lightBarBlobs.size(); i++)
        {
            RotatedRect bar1 = lightBarBlobs[i - 1], bar2 = lightBarBlobs[i];
            wutrm::ArmorBlob armor;
            armorFinder.getArmor(bar1, bar2, armor);
            // rectangle(frame, armor.rect, Scalar(0, 255, 0), 2);

            Mat imageParams = Mat(armor.corners);
            const auto p0 = armor.corners[0];
            const auto p1 = armor.corners[1];
            const auto p2 = armor.corners[2];
            const auto p3 = armor.corners[3];
            // imshow("corner",imageParams);
                // cv::circle(frame,cv::Point(armor.corners[2]),1,cv::Scalar(0,0,255),3);
            auto Res = PnPer.PnP(imageParams, cam, dis);
            cout << cv::Point(armor.corners[0]) << endl;
            // cout << Res.first << endl;
            cout << Res.second << endl;
            cout << Res.second.cols << " " << Res.second.rows << endl;
            cout << Res.second.ptr<double>(0)[0] << endl;
            // float* Ptr = Res.second.data;
            // cout << *(static_cast<float*>(Ptr))<<endl;
            // cv::circle(frame,cv::Point(frame.cols/2,40),1,cv::Scalar(0,0,255),3);
            cout << "width" << frame.size().width << endl;
            cout << "height" << frame.size().height << endl;
            cout << "cols" << frame.cols << endl;
            cout << "rows" << frame.rows << endl;
            const auto centerP = get2lineIPoint(p0,p2,p1,p3);
            cv::circle(frame,centerP,1,cv::Scalar(0,0,255),3);

            cout<<centerP.x<<endl;
            /*calculating the depth*/
            auto depth = ::pow(
                ::pow(Res.second.ptr<double>(0)[0],2) +
                ::pow(Res.second.ptr<double>(1)[0],2) +
                ::pow(Res.second.ptr<double>(2)[0],2)
            ,0.5);
            cout << "depth" << depth << endl;
        }
        lightBarBlobs.clear();
        imshow("armor", frame);
    }
    
    return 0;
}
