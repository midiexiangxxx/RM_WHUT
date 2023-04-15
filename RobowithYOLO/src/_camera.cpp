
 // Standard includes
#include <stdio.h>
#include <string.h>

// ZED include
#include <sl/Camera.hpp>

// OpenCV include (for display)
#include <opencv2/opencv.hpp>

// Using std and sl namespaces
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

int main(int argc, char **argv) {
    
    // Create a ZED Camera object
    Camera zed;

    sl::InitParameters init_parameters;
    init_parameters.sdk_verbose = true;
    init_parameters.camera_resolution= sl::RESOLUTION::HD720;
    init_parameters.depth_mode = sl::DEPTH_MODE::NONE; // no depth computation required here
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
    Mat zed_image;

    // Initialise camera setting
    switchCameraSettings();

    // Capture new images until 'q' is pressed
    char key = ' ';
    while (key != 'q') {
        // Check that a new image is successfully acquired
        returned_state = zed.grab();
        if (returned_state == ERROR_CODE::SUCCESS) {
            // Retrieve left image
            zed.retrieveImage(zed_image, VIEW::LEFT);

            // Convert sl::Mat to cv::Mat (share buffer)
            cv::Mat cvImage = cv::Mat((int) zed_image.getHeight(), (int) zed_image.getWidth(), CV_8UC4, zed_image.getPtr<sl::uchar1>(sl::MEM::CPU));


            //Display the image
            cv::imshow(win_name, cvImage);
        }else {
            print("Error during capture : ", returned_state);
            break;
        }
        
        key = cv::waitKey(10);

    }

    // Exit
    zed.close();
    return EXIT_SUCCESS;
}

/**
    This function toggles between camera settings
 **/
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

/**
    This function displays help
 **/

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
