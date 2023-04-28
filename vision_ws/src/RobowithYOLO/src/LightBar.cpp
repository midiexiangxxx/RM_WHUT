#include <LightBar.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace wutrm;

LightBarFinder::LightBarFinder() {
    int erode_x = DetectParam::erode_index[0], erode_y = DetectParam::erode_index[1];
    int dilate_x = DetectParam::dilate_index[0], dilate_y = DetectParam::dilate_index[1];
    kernel_erode = getStructuringElement(MORPH_RECT, Size(erode_x, erode_y));
    kernel_dilate = getStructuringElement(MORPH_RECT, Size(dilate_x, dilate_y));
}

bool LightBarFinder::findLightBarBlobs(const Mat &frame,
                                       LightBarBlobs &lightBarBlobs,
                                       const Point2f &roi_offset) {
    if(frame.empty()) return false;

    int mode = GRAY;
    Mat mat;
    vector<Mat> channels;
    vector<vector<Point>> contours;
    vector<vector<Point>> true_contours;
    vector<vector<Point>> false_contours;
    Mat hsv1, hsv2, color_part;
    Mat gray;  //转化得到的灰度图
    if(mode == GRAY)
    {
        cvtColor(frame, gray, COLOR_BGR2GRAY);  //转化为灰度图
        threshold(gray, mat, DetectParam::binary_threshold, 255, THRESH_BINARY);  //二值化

        erode(mat, mat, kernel_erode);  //消除噪点 腐蚀
        dilate(mat, mat, kernel_dilate);  //膨胀

    }

    vector<Vec4i> hierarchy;
    findContours(mat, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_NONE);
    int draw_flag[contours.size()];
    for(int i=0; i<contours.size(); i++)
    {
        if(contours[i].size() <= 10 || hierarchy[i][3] >= 0) continue;  //不能有父轮廓
        const RotatedRect &rotatedRect = minAreaRect(contours[i]);
        // cout << i << " " << rotatedRect.size.width << " " << rotatedRect.size.height << " ... ";

        if(isValidLightBarBlob(rotatedRect) && isRightColor(frame, rotatedRect))
        {
            draw_flag[i] = 1;
            true_contours.emplace_back(contours[i]);
            if(ArmorDetectParam::show_light_bar_info)
            {
                double w = rotatedRect.size.width, h = rotatedRect.size.height;
                double area = rotatedRect.size.area();
                double angle = rotatedRect.angle;
                cout << "LIGHT BAR INFO:" << endl;
                cout << "light bar ratio: " << MAX(w, h) / MIN(w, h) << endl;
                cout << "light bar area : " << area << endl;
                cout << "light bar angle: " << (w > h ? angle - 90 : angle) << endl;
                cout << "LIGHT BAR INFO END." << endl << endl;

            }

            RotatedRect roi = RotatedRect(rotatedRect.center + roi_offset,
                                          rotatedRect.size,
                                          rotatedRect.angle);
            lightBarBlobs.emplace_back(roi);
        }
        else
        {
            draw_flag[i] = 0;
            false_contours.emplace_back(contours[i]);
        }

    }
    if (ArmorDetectParam::show_thresh)
    {
        cout << "win" << endl;
        for(auto i : lightBarBlobs)
        {
            if (lightBarBlobs.size() > 2) cout << lightBarBlobs.size() << " ";
        }

        // imshow("thresh", mat);  // TODO DEBUG_MODE

        waitKey(1);
    }

    sort(lightBarBlobs.begin(), lightBarBlobs.end(),
         [](const RotatedRect &a, const RotatedRect &b) -> bool
    {
        if (a.center.x != b.center.x)
            return a.center.x < b.center.x;
        return a.center.y > b.center.y;
    });

    Scalar false_color = Scalar(0, 0, 255), true_color = Scalar(0, 255, 0);
    drawContours(frame, false_contours, -1, false_color, 2);
    drawContours(frame, true_contours, -1, true_color, 2);
    // imshow("light bar", frame);

    return lightBarBlobs.size() >= 2;

}

bool LightBarFinder::isValidLightBarBlob(const RotatedRect &rotateRect) {
    double w = rotateRect.size.width, h = rotateRect.size.height;
    double angle = w > h ? rotateRect.angle - 90 : rotateRect.angle;
    double aspect_ratio = MAX(w, h) / MIN(w, h);
    double area = rotateRect.size.area();
    if (checkAspectRatio(aspect_ratio) && checkArea(area) && checkAngle(angle))
    {
        if (!checkRatioAndArea(aspect_ratio, area)) //面积较大时，比例会更加严格
        {
            return false;
        }
        return true;
    }
    return false;
}

bool LightBarFinder::checkAspectRatio(const double &ratio) {  //判断长宽比是否满足要求
    double ratio_max = ArmorDetectParam::light_bar_ratio_max;
    double ratio_min = ArmorDetectParam::light_bar_ratio_min;
    return ratio <= ratio_max && ratio >= ratio_min;
}

bool LightBarFinder::checkArea(const double &area) {
    double area_max = ArmorDetectParam::light_bar_area_max;
    double area_min = ArmorDetectParam::light_bar_area_min;
    return area <= area_max && area >= area_min;
}

bool LightBarFinder::checkAngle(const double &angle) {
    double angle_max = ArmorDetectParam::light_bar_angle_max;
    double angle_min = ArmorDetectParam::light_bar_angle_min;
    return angle <= angle_max && angle >= angle_min;
}

bool LightBarFinder::checkRatioAndArea(const double &ratio, const double &area) {
    // TODO 设置阈值，在Area较大时对Ratio的要求应更加严格
    return true;
}

bool LightBarFinder::isRightColor(const Mat &frame, const RotatedRect &rotatedRect) {
    Rect rect = rotatedRect.boundingRect();
    rect.x = rect.x < 0 ? 0 : (rect.x > frame.cols ? frame.cols : rect.x);
    rect.y = rect.y < 0 ? 0 : (rect.y > frame.rows ? frame.rows : rect.y);
    rect.width = rect.x + rect.width > frame.cols ? frame.cols - rect.x : rect.width;
    rect.height = rect.y + rect.height > frame.rows ? frame.rows - rect.y : rect.height;

    Scalar roi_color_bgr_mean = mean(frame(rect));
    if (enemy_color == BLUE)
    {
        return roi_color_bgr_mean[0] > roi_color_bgr_mean[2] &&
               roi_color_bgr_mean[0] > roi_color_bgr_mean[1];
    }
    else
    {
        return roi_color_bgr_mean[2] > roi_color_bgr_mean[0] &&
               roi_color_bgr_mean[2] > roi_color_bgr_mean[1];
    }
}

