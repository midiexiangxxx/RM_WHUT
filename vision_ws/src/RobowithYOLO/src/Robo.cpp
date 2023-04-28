#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "LightBar.h"
#include "Armor.h"
#include "Params.h"
#include "Perspective.h"
#include "TRTModule.hpp"
// #include "Camera.hpp"
#include <queue>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <geometry_msgs/Twist.h>

#include <cmath>
#include <tuple>
#include <stdio.h>
#include <string.h>
#include <sl/Camera.hpp>
#include <fmt/format.h>
#include <fmt/color.h>
#include <Eigen/Dense>

#define OFFSET_BETWEEN_GUN_CAM 0
#define THRESHOLD1 70
#define ARMOR_REAL_WIDTH 55.5

using namespace cv;
using namespace std;
using namespace sl;

void switchCameraSettings();
void print(string msg_prefix, ERROR_CODE err_code = ERROR_CODE::SUCCESS, string msg_suffix = "");
void parseArgs(int argc, char **argv,sl::InitParameters& param);
VIDEO_SETTINGS camera_settings_ = VIDEO_SETTINGS::BRIGHTNESS;
string str_camera_settings = "BRIGHTNESS";
int step_camera_setting = 1;
bool led_on = true;

bool selectInProgress = false;
sl::Rect selection_rect;
cv::Point origin_rect;

static void onMouse(int event, int x, int y, int, void*)
{
    switch (event)
    {
        case cv::EVENT_LBUTTONDOWN:
        {
            origin_rect = cv::Point(x, y);
            selectInProgress = true;
            break;
        }

    case cv::EVENT_LBUTTONUP:
        {
            selectInProgress = false;
            break;
        }

    case cv::EVENT_RBUTTONDOWN:
        {
            //Reset selection
            selectInProgress = false;
            selection_rect = sl::Rect(0,0,0,0);
            break;
        }
    }

    if (selectInProgress)
    {
        selection_rect.x = MIN(x, origin_rect.x);
        selection_rect.y = MIN(y, origin_rect.y);
        selection_rect.width = abs(x - origin_rect.x) + 1;
        selection_rect.height = abs(y - origin_rect.y) + 1;
    }
}

geometry_msgs::Twist Serial_Send_Msg;


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

float filter_sum_yaw = 0;
float filter_sum_pitch = 0;
std::queue<float> mid_filter_yaw;
std::queue<float> mid_filter_pitch;



Eigen::MatrixXf T_rc(4,4);
const int nn = 91.5; //机械数据
const int mm = 77;
float IMUalpha = 0.; // IMU数据
float IMUbeta = 0.;
Eigen::Vector4f camera_co;
Eigen::Vector4f world_co;
const float Wcmos = 5.376;
const float Hcmos = 3.04;
const int W = 1280;
const int H = 720;
const float focal = 2.12;



void update_MatrixT()
{
    T_rc << sin(IMUalpha) , -cos(IMUalpha) * sin(IMUbeta) , cos(IMUalpha) * cos(IMUbeta) , mm * cos(IMUalpha) * cos(IMUbeta) - nn * cos(IMUalpha) * sin(IMUbeta) + 60 * sin(IMUalpha) , 
           -cos(IMUalpha) , -sin(IMUalpha) * sin(IMUbeta) , sin(IMUalpha) * cos(IMUbeta) , mm * sin(IMUalpha) * cos(IMUbeta) - nn * sin(IMUalpha) * sin(IMUbeta) - 60 * cos(IMUalpha) , 
                0      ,         cos(IMUbeta)       ,         sin(IMUbeta)      ,                    mm * sin(IMUbeta) + nn * cos(IMUbeta)                          ,
                0      ,            0            ,             0          ,                                   1                                         ;
}
void update_Vector_W()
{
    world_co = T_rc * camera_co;
}

void getIMUdata()
{
    IMUalpha = 0.;
    IMUbeta = 0.;
}


int main(int argc,char** argv) {
    cout << "Hello, World!" << endl;
    ros::init(argc,argv,"shooter");
    ros::NodeHandle nh;
    ros::Publisher pub_shot = nh.advertise<geometry_msgs::Twist>("shooter",10);


    // Create a ZED Camera object
    Camera zed;

    sl::InitParameters init_parameters;
    init_parameters.depth_mode = DEPTH_MODE::ULTRA; // Use ULTRA depth mode
    init_parameters.coordinate_units = UNIT::MILLIMETER; // Use millimeter units (for depth measurements)
    init_parameters.sdk_verbose = true;
    init_parameters.camera_resolution= sl::RESOLUTION::HD720;
    // init_parameters.depth_mode = sl::DEPTH_MODE::NONE; // no depth computation required here
    parseArgs(argc,argv, init_parameters);

    // Open the camera
    auto returned_state = zed.open(init_parameters);
    if (returned_state != ERROR_CODE::SUCCESS) {
        print("Camera Open", returned_state, "Exit program.");
        return EXIT_FAILURE;
    }
    
    cv::String win_name = "Camera Control";
    cv::namedWindow(win_name, cv::WINDOW_NORMAL);
    cv::setMouseCallback(win_name, onMouse);

    // Print camera information
    auto camera_info = zed.getCameraInformation();
    cout << endl;
    cout <<"ZED Model                 : "<<camera_info.camera_model << endl;
    cout <<"ZED Serial Number         : "<< camera_info.serial_number << endl;
    cout <<"ZED Camera Firmware       : "<< camera_info.camera_configuration.firmware_version <<"/"<<camera_info.sensors_configuration.firmware_version<< endl;
    cout <<"ZED Camera Resolution     : "<< camera_info.camera_configuration.resolution.width << "x" << camera_info.camera_configuration.resolution.height << endl;
    cout <<"ZED Camera FPS            : "<< zed.getInitParameters().camera_fps << endl;

    // Create a Mat to store images
    sl::Mat zed_image;
    // Create a Mat to store depth
    sl::Mat Depth_image;
    // Initialise camera setting
    // for depth_value
    float depth_value=0;
    // for focal lenth of right eye
    // float focal_right_x = sl::calibration_params.right_cam.fx;


    const cv::Scalar colors[3] = {{255, 0, 0}, {0, 0, 255}, {0, 255, 0}};

    string onnx_file = "/home/rmua/RobowithYOLO/src/asset/model-opt-4.onnx";
    TRTModule model(onnx_file);
    int cnt_useless = -1;


    RotatedRect rect = RotatedRect();
    // VideoCapture capture = VideoCapture(0);
    cv::Mat frame;
    char c;

    wutrm::LightBarFinder lightBarFinder;
    wutrm::LightBarBlobs lightBarBlobs;
    Point2f roi_offset;
    //lightBarFinder.setEnemyColor(1);

    wutrm::ArmorFinder armorFinder;
    wutrm::ArmorBlobs armorBlobs;
    // wutrm::Perspective PnPer;
    // cv::Mat cam = PnPer.cameraMatrixParams(), dis = PnPer.distCoeffsParams();
    
	char key = ' ';

    bool game_start_flag = false;
    do
    {
        ros::param::get("game_start",game_start_flag);
    }
    while(!game_start_flag);

    bool color_set = false;
    while(!ros::param::has("color"));
    ros::param::get("color",color_set);
    // std::cout << color_set;
    while (key != 'q') {
	ros::Time start = ros::Time::now();
        // Check that a new image is successfully acquired
        returned_state = zed.grab();
        if (returned_state == ERROR_CODE::SUCCESS) {
            // Retrieve left image
            zed.retrieveImage(zed_image, VIEW::LEFT);
            zed.retrieveMeasure(Depth_image, MEASURE::DEPTH); // Retrieve depth
            // Convert sl::Mat to cv::Mat (share buffer)
            cv::Mat cvImage = cv::Mat((int) zed_image.getHeight(), (int) zed_image.getWidth(), CV_8UC4, zed_image.getPtr<sl::uchar1>(sl::MEM::CPU));

	    	auto detections = model(cvImage);

	    	cv::Mat im2show = cvImage.clone();
            if (detections.empty()) {
                cnt_useless += 1;
                std::cout<<"No enemy detected!------"<<cnt_useless<<endl;
                Serial_Send_Msg.linear.z = 0;
                fmt::print(fmt::fg(fmt::color::red), "[!INFO!] Don't Send!!" );
                pub_shot.publish(Serial_Send_Msg);
                ros::Time end = ros::Time::now();
                // fmt::print(fmt::fg(fmt::color::blue), "No enemy detected!");

            }
            else {

                cnt_useless = -1;
                int cnt_robot = 0;
                for (const auto &b: detections) {
                    // if(color_set == b.color_id) continue;
                    std::cout << "-----robot_aromr:" << cnt_robot << "----- \n";
                    cnt_robot ++;
                    std::cout<<b.pts[0]<<" "<<b.pts[1]<<endl;
                    cv::line(im2show, b.pts[0], b.pts[1], colors[2], 2);
                    cv::line(im2show, b.pts[1], b.pts[2], colors[2], 2);
                    cv::line(im2show, b.pts[2], b.pts[3], colors[2], 2);
                    cv::line(im2show, b.pts[3], b.pts[0], colors[2], 2);
                    auto _p0 = b.pts[0];
                    auto _p1 = b.pts[1];
                    auto _p2 = b.pts[2];
                    auto _p3 = b.pts[3];
                    const auto centerP = get2lineIPoint(_p0,_p2,_p1,_p3);
                    cv::circle(im2show,centerP,1,cv::Scalar(0,0,255),3);
                    const cv::Point centerC = std::move(cv::Point(im2show.cols/2,im2show.rows/2));
                    cv::circle(im2show,centerC,1,cv::Scalar(0,0,255),3);
                    cv::putText(im2show, std::to_string(b.tag_id), b.pts[0], cv::FONT_HERSHEY_SIMPLEX, 1, colors[!b.color_id]);
                    // cv::putText(im2show, std::to_string(centerP.x), centerP, cv::FONT_HERSHEY_SIMPLEX, 1, colors[!b.color_id]);
                    // cv::putText(im2show, std::to_string(centerP.y), centerP, cv::FONT_HERSHEY_SIMPLEX, 1, colors[!b.color_id]);
                    std::cout << "centerP: [" << centerP.x << ", " << centerP.y << " ]\n";
                    Depth_image.getValue(centerP.x,centerP.y,&depth_value);
                    depth_value = (depth_value > 500) ? depth_value  : 500;
                    auto [u,v] = getCenterOffset(std::move(centerP), std::move(centerC));

                    const auto scale = getLinearScale(_p0, _p1);
                    auto yaw = -u * scale * 1.5 / depth_value;
                    auto pitch = v * scale * 1.5 / depth_value;


                    auto camera_x = sqrt(depth_value * depth_value - yaw * depth_value * yaw * depth_value - pitch * depth_value * pitch * depth_value);
                    // camera_co << camera_x , yaw * depth_value , pitch * depth_value , 1 ;
                    camera_co << (depth_value + focal) / focal * Wcmos / W * u , (depth_value + focal) / focal * Hcmos / H * v , depth_value + focal , 1 ;
                    getIMUdata();
                    update_MatrixT();
                    update_Vector_W();
                    fmt::print(fmt::fg(fmt::color::red), "**************\n[INFO] MatrixT: \n" );
                    std::cout << T_rc << std::endl;
                    fmt::print(fmt::fg(fmt::color::red), "[INFO] Vector_C: \n" );
                    std::cout << camera_co << std::endl;
                    fmt::print(fmt::fg(fmt::color::red), "[INFO] Vector_W: \n" );
                    std::cout << world_co << std::endl;
                    auto world_depth = world_co(0);
                    auto world_yaw = world_co(1);
                    auto world_pitch = world_co(2);
                    auto real_yaw = std::atan(world_yaw / world_depth);
                    auto real_pitch = std::atan(world_pitch / world_depth);
                    fmt::print(fmt::fg(fmt::color::blue), "CenterP's Depth: " + std::to_string(depth_value) + '\n');



                    cout << "confidence-----" << b.confidence << endl;
                    cout << "centerC: [" << centerC.x << ", " << centerC.y << " ]\n";
                    // cout << "pitch: " << pitch << ", yaw: " << yaw << '\n';
                    // fmt::print(fmt::fg(fmt::color::green), "[INFO] color_set: \n" );
                    // cout << color_set << "   " << !color_set << endl;
                    // fmt::print(fmt::fg(fmt::color::green), "[INFO] b.color_id: \n" );
                    // cout << b.color_id << endl;
                    if(color_set != b.color_id) {
                    Serial_Send_Msg.linear.x = real_yaw;
                    Serial_Send_Msg.linear.y = real_pitch;
                    Serial_Send_Msg.linear.z = 1;
                    

/*
scale limit

                    if(Serial_Send_Msg.linear.x > 0.1){
                    Serial_Send_Msg.linear.x = 0.1;
                    }
                    if(Serial_Send_Msg.linear.x < -0.1){
                    Serial_Send_Msg.linear.x = -0.1;
                    }
                    if(Serial_Send_Msg.linear.y > 0.5){
                    Serial_Send_Msg.linear.y = 0.5;
                    }
                    if(Serial_Send_Msg.linear.y < -0.5){
                    Serial_Send_Msg.linear.y = -0.5;
                    }
*/
/*
medium filter

					mid_filter_yaw.push(Serial_Send_Msg.linear.x);
					mid_filter_pitch.push(Serial_Send_Msg.linear.y);
					filter_sum_yaw += mid_filter_yaw.back();
					filter_sum_pitch += mid_filter_pitch.back();
					if(mid_filter_yaw.size() == 40) {
						//mid_filter_yaw.push(Serial_Send_Msg.linear.x);
						//filter_sum_yaw += mid_filter_yaw
						Serial_Send_Msg.linear.x = filter_sum_yaw / 10;
						Serial_Send_Msg.linear.y = filter_sum_pitch / 10;
						filter_sum_yaw -= mid_filter_yaw.front();
						mid_filter_yaw.pop();
						filter_sum_pitch -= mid_filter_pitch.front();
						mid_filter_pitch.pop();
						
					}
				*/	
					
                    pub_shot.publish(Serial_Send_Msg);
                    ros::Time end = ros::Time::now();
                    ROS_INFO("frequence:%.2f",1/(start.toSec()-end.toSec()));
                    //sleep(1);
                    }
                    else {
                        Serial_Send_Msg.linear.z = 0;
                        fmt::print(fmt::fg(fmt::color::red), "[!INFO!] Don't Send!!" );
                        pub_shot.publish(Serial_Send_Msg);
                        ros::Time end = ros::Time::now();
                    }
                }
            }
           //imshow("detect", im2show);

            //Display the image
            //cv::imshow(win_name, cvImage);
        }else {
            print("Error during capture : ", returned_state);
            break;
        }
        
        key = cv::waitKey(10);

    }

    // Exit
    zed.close();

    
    return 0;
}



void parseArgs(int argc, char **argv,sl::InitParameters& param)
{
    if (argc > 1 && string(argv[1]).find(".svo")!=string::npos) {
        // SVO input mode not available in camera control
	cout<<"SVO Input mode is not available for camera control sample"<<endl;
    } else if (argc > 1 && string(argv[1]).find(".svo")==string::npos) {
        string arg = string(argv[1]);
        unsigned int a,b,c,d,port;
        if (sscanf(arg.c_str(),"%u.%u.%u.%u:%d", &a, &b, &c, &d,&port) == 5) {
            // Stream input mode - IP + port
            string ip_adress = to_string(a)+"."+to_string(b)+"."+to_string(c)+"."+to_string(d);
            param.input.setFromStream(sl::String(ip_adress.c_str()),port);
            cout<<"[Sample] Using Stream input, IP : "<<ip_adress<<", port : "<<port<<endl;
        }
        else  if (sscanf(arg.c_str(),"%u.%u.%u.%u", &a, &b, &c, &d) == 4) {
            // Stream input mode - IP only
            param.input.setFromStream(sl::String(argv[1]));
            cout<<"[Sample] Using Stream input, IP : "<<argv[1]<<endl;
        }
        else if (arg.find("HD2K")!=string::npos) {
            param.camera_resolution = sl::RESOLUTION::HD2K;
            cout<<"[Sample] Using Camera in resolution HD2K"<<endl;
        } else if (arg.find("HD1080")!=string::npos) {
            param.camera_resolution = sl::RESOLUTION::HD1080;
            cout<<"[Sample] Using Camera in resolution HD1080"<<endl;
        } else if (arg.find("HD720")!=string::npos) {
            param.camera_resolution = sl::RESOLUTION::HD720;
            cout<<"[Sample] Using Camera in resolution HD720"<<endl;
        } else if (arg.find("VGA")!=string::npos) {
            param.camera_resolution = sl::RESOLUTION::VGA;
            cout<<"[Sample] Using Camera in resolution VGA"<<endl;
        }
    } else {
        // Default
    }
}
void switchCameraSettings() {
    camera_settings_ = static_cast<VIDEO_SETTINGS>((int)camera_settings_ + 1);

    // reset to 1st setting
    if (camera_settings_ == VIDEO_SETTINGS::LED_STATUS)
        camera_settings_ = VIDEO_SETTINGS::BRIGHTNESS;

    // increment if AEC_AGC_ROI since it using the overloaded function
    if (camera_settings_==VIDEO_SETTINGS::AEC_AGC_ROI)
        camera_settings_ = static_cast<VIDEO_SETTINGS>((int)camera_settings_ + 1);
    
    // select the right step
    step_camera_setting = (camera_settings_ == VIDEO_SETTINGS::WHITEBALANCE_TEMPERATURE) ? 100 : 1;

    // get the name of the selected SETTING
    str_camera_settings = string(sl::toString(camera_settings_).c_str());
    
    print("Switch to camera settings: ", ERROR_CODE::SUCCESS, str_camera_settings);
}
void print(string msg_prefix, ERROR_CODE err_code, string msg_suffix) {
    cout <<"[Sample]";
    if (err_code != ERROR_CODE::SUCCESS)
        cout << "[Error] ";
    else
        cout<<" ";
    cout << msg_prefix << " ";
    if (err_code != ERROR_CODE::SUCCESS) {
        cout << " | " << toString(err_code) << " : ";
        cout << toVerbose(err_code);
    }
    if (!msg_suffix.empty())
        cout << " " << msg_suffix;
    cout << endl;
}