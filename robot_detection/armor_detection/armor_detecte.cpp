#include "armor_detecte.h"

namespace armor_detection {
    armor_detecte::armor_detecte(const InputImg &img_origin){
        this->img_origin = img_origin;
    }
    
    armor_detecte::armor_detecte(){}

    void armor_detecte::setImg_origin(const InputImg &img_origin){
        this->img_origin = img_origin;
    }

    void armor_detecte::loadParam(bool enermy_color, bool isParam,
                    int alpha, int beta, int thresh_value,
                    double light_bit_min, double light_bit_max, double light_angle_min, double light_angle_max, double light_area_min, double light_area_max, double light_angle_abs,
                    double armor_bit_min, double armor_bit_max, double armor_area_min, double armor_area_max){
        
        this->enermy_color = enermy_color;
        if(isParam == true){
            // init
            this->alpha = alpha;
            this->beta = beta;
            this->thresh_value = thresh_value;

            // light
            this->light_bit_min = light_bit_min;
            this->light_bit_max = light_bit_max;
            this->light_angle_min = light_angle_min;
            this->light_angle_max = light_angle_max;
            this->light_area_min = light_area_min;
            this->light_area_max = light_area_max;
            this->light_angle_abs = light_angle_abs;

            // armor
            this->armor_bit_min = armor_bit_min;
            this->armor_bit_max = armor_bit_max;
            this->armor_area_min = armor_area_min;
            this->armor_area_max = armor_area_max;
        }
        else if(enermy_color == ENERMY_COLOR_BLUE){
            // init
            this->alpha = 1, this->beta = 50;
            this->thresh_value = 180;
            
            // light
            this->light_bit_min = 13;
            this->light_bit_max = 25;
            this->light_angle_min = -17;
            this->light_angle_max = 17; 
            this->light_area_min = 100;
            this->light_area_max = 10000;
            this->light_angle_abs = 4;

            // armor 
            this->armor_bit_min = 0.3552;
            this->armor_bit_max = 0.7552;
            this->armor_area_min = armor_area_min;
            this->armor_area_max = armor_area_max;
        }
        else{
            // init
            this->alpha = 1, beta = 50;
            this->thresh_value = 180;
            
            // light
            this->light_bit_min = 13;
            this->light_bit_max = 25;
            this->light_angle_min = -17;
            this->light_angle_max = 17; 
            this->light_area_min = 100;
            this->light_area_max = 10000;
            this->light_angle_abs = 4;

             // armor 
            this->armor_bit_min = 0.3552;
            this->armor_bit_max = 0.7552;
            this->armor_area_min = armor_area_min;
            this->armor_area_max = armor_area_max;
        }
    }

    void armor_detecte::init() {

        Mat img_gray, img_HSV, img_sub;
        
        vector<Mat> channels;
        img_origin.convertTo(img_change, -1, alpha, beta);
        cvtColor(img_change, img_HSV, COLOR_BGR2HSV);
        cvtColor(img_change, img_gray, COLOR_BGR2GRAY);

        split(img_change, channels);
        subtract(channels[0], channels[2], img_sub);

        threshold(img_gray, img_thresh, thresh_value, 255, THRESH_BINARY);

        Mat kernal = getStructuringElement(MORPH_RECT, Size(6, 6));  //
        // 闭运算
        dilate(img_sub, img_dilate, kernal, Point(-1, -1), 1);
        erode(img_dilate, img_erode, kernal, Point(-1, -1), 1);
        bitwise_and(img_thresh, img_erode, img_and);

        // 开运算
        //  erode(img_sub, img_erode, kernal, Point(-1, -1), 1);
        //  dilate(img_sub, img_dialte, kernal, Point(-1, -1), 1);
        //  bitwise_and(img_thresh, img_dialte, ans);
        //  vector<Mat> imgs = {img_change, img_thresh, img_dialte, ans};
    }

    void armor_detecte::contours() {
        RotatedRect rect;
        vector<vector<Point>> points;
        contours_rects.clear();
        
        findContours(img_and, points, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        for (auto p : points) {
            rect = minAreaRect(p);
            contours_rects.push_back(rect);
        }
    }

    void armor_detecte::contours_to_light() {
        vector<RotatedRect> rects_select;
        float angle, angle_abs;
        int m = -1, n = 1;

        light_rects.clear();
        // 根据长宽比 角度 面积筛选
        for (int i = 0; i < contours_rects.size(); i++) {
            double area = contours_rects[i].size.area();
            double bit = min(contours_rects[i].size.width, contours_rects[i].size.height) /
                        max(contours_rects[i].size.width, contours_rects[i].size.height);
            double angle = contours_rects[i].angle;
            if (bit * 100 > light_bit_min && bit * 100 < light_bit_max &&
                    angle > light_angle_min && angle < light_angle_max &&
                    area > light_area_min && area < light_area_max)
                rects_select.push_back(contours_rects[i]);
        }

        // 根据角度差筛选
        for (int i = 0; i < rects_select.size(); i++) {
            angle = rects_select[i].angle;
            m = -1;
            for (int j = i + 1; j < rects_select.size(); j++){
                angle_abs = std::abs(angle - rects_select[j].angle);
                if (angle_abs < 1e-3)//选到相同的
                    continue;
                if (angle_abs < light_angle_abs){
                    m = j;
                }
            }
            if (m == -1)
                continue;
            light_rects.push_back(rects_select[i]), light_rects.push_back(rects_select[m]);
        }
    }

    void armor_detecte::light_to_armor() {
        float point_distance, armor_angle, armor_bit, armor_area, height, point_tan;

        armor_rects.clear();
        for (int i = 0; i < light_rects.size(); i++){
            for (int j = i + 1; j < light_rects.size(); j++)
            {

                point_distance = sqrt(
                    pow(light_rects[j].center.y - light_rects[i].center.y, 2) +
                    pow(light_rects[j].center.x - light_rects[i].center.x, 2));
                height = max(light_rects[j].size.width, light_rects[j].size.height);
                armor_bit = height / point_distance;
                if (armor_bit * 100 < armor_bit_min || armor_bit * 100 > armor_bit_max)
                    continue;

                if (armor_area < armor_area_min || armor_area > armor_area_max)
                    continue;
                    
                Point2f center(
                    (light_rects[j].center.x + light_rects[i].center.x) / 2,
                    (light_rects[j].center.y + light_rects[i].center.y) / 2);

                armor_angle =
                    std::atan(
                        (light_rects[j].center.y - light_rects[i].center.y) /
                        (light_rects[j].center.x - light_rects[i].center.x)) /
                    _PI_ * 180;
                
                // if (armor_angle > 17 || armor_angle < -17)
                //     continue;

                RotatedRect rect(center, Size2f(point_distance, height), armor_angle);
                armor_rects.push_back(rect);
            }
        }
    }
    void armor_detecte::drawContours(){
        for(auto rect:light_rects){
            Point2f* points = new Point2f[4];
            rect.points(points);
             for (int i = 0; i < 4; i++)
                line(img_origin, points[i], points[(i + 1) % 4], Scalar(0, 0, 255), 2);
        }            
    }

    void armor_detecte::drawrotate() {
        int i = 0;
        double area, bit;
        double x, y;
        string str_x, str_y;

        for (auto rect : armor_rects) {
            Point2f* points = new Point2f[4];
            rect.points(points);
            for (int i = 0; i < 4; i++)
                line(img_origin, points[i], points[(i + 1) % 4], Scalar(0, 0, 255), 2);
            circle(img_origin, rect.center, rect.size.width / 20, Scalar(5, 198, 0), -1);

            bit = min(rect.size.width, rect.size.height) / max(rect.size.width, rect.size.height);
            area = rect.size.area();
            putText(img_origin, to_string(rect.angle).substr(0, 5),
                    Point(points[0].x, points[0].y), FONT_HERSHEY_COMPLEX, 0.5,
                    Scalar(0, 1, 255));

            i++;
        }
    }

    void armor_detecte::showImg(){
        vector<Mat> imgs = {img_change, img_thresh, img_erode, img_and};
        four_to_one(imgs, img_combination);
        imshow("img_combination", img_combination);
        imshow("img", img_origin);
    }

    void armor_detecte::four_to_one(const vector<cv::Mat>& imgs, OutputImg& ans) {
        int height = imgs[0].rows;
        int width = imgs[0].cols;
        cv::Mat img_combination_;
        vector<Mat> img_channels;
        cv::Mat img = Mat::zeros(Size(width * 2, height * 2), imgs[0].type());
        for (int i = 0, j = 0, k = 0; i < 4; i++) {
            if (imgs[i].channels() == 1) {
                img_channels.clear();
                img_channels.push_back(imgs[i]);
                img_channels.push_back(imgs[i]);
                img_channels.push_back(imgs[i]);
                merge(img_channels, img_combination_);
                img_combination_.copyTo(
                    img(Rect(width * j, height * k, width, height)));
                img_combination_.release();
            } else
                imgs[i].copyTo(img(Rect(width * j, height * k, width, height)));
            if (i != 1)
                j++;
            else
                j = 0, k++;
        }
        img.copyTo(ans);
    }
}  // namespace armor_detection