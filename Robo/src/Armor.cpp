#include <Armor.h>

using namespace wutrm;

double dis_Euclid(const Point2f &p1, const Point2f &p2)
{
    Point2f diff = p1 - p2;
    return sqrt(diff.x * diff.x + diff.y * diff.y);
}

bool ArmorFinder::judgeArmor(const ArmorBlob &armorBlob) {
    Point2f p_ul = armorBlob.corners[0],    p_ur = armorBlob.corners[1],
            p_dl = armorBlob.corners[3],    p_dr = armorBlob.corners[2];
    double  up = dis_Euclid(p_ul, p_ur),    down = dis_Euclid(p_dl, p_dr),
            left = dis_Euclid(p_ul, p_dl),  right = dis_Euclid(p_ur, p_dr);

    double armor_ratio = ((up + down) / 2) + ((left + right) / 2);

    if (ArmorDetectParam::show_armor_info)
    {
        cout << "ARMOR INFO:" << endl;
        cout << "armor ratio: " << armor_ratio << endl;
        cout << "ARMOR INFO END." << endl;
    }

    double ratio_max = ArmorDetectParam::armor_ratio_max;
    double ratio_min = ArmorDetectParam::armor_ratio_min;

    return armor_ratio <= ratio_max && armor_ratio >= ratio_min;

}

bool ArmorFinder::matchTwoLightBar(const RotatedRect &l, const RotatedRect &r) {
    status = checkAngleDiff(l, r) && checkHeightDiff(l, r);
    return status;
}

bool ArmorFinder::getArmor(const RotatedRect &l, const RotatedRect &r, ArmorBlob &armor) {
    if (!matchTwoLightBar(l, r)) return false;

    Point2f points[4], p_ul, p_ur, p_dl, p_dr;
    double height = fmax(l.size.width, l.size.height);
    armor.rect = Rect(l.center.x, l.center.y - height / 2,
                        r.center.x - l.center.x, height);


    l.points(points);
    p_ul = points[0], p_ur = points[1], p_dl = points[3], p_dr = points[2];
    if (l.angle > 45)
    {
        armor.corners[0] = (p_ul + p_ur) / 2;
        armor.corners[3] = (p_dl + p_dr) / 2;
    }
    else
    {
        armor.corners[0] = (p_ur + p_dr) / 2;
        armor.corners[3] = (p_ul + p_dl) / 2;
    }

    r.points(points);
    p_ul = points[0], p_ur = points[1], p_dl = points[3], p_dr = points[2];
    if (r.angle > 45)
    {
        armor.corners[1] = (p_ul + p_ur) / 2;
        armor.corners[2] = (p_dl + p_dr) / 2;
    }
    else
    {
        armor.corners[1] = (p_ur + p_dr) / 2;
        armor.corners[2] = (p_ul + p_dl) / 2;
    }

    if (armor.corners[0].y > armor.corners[2].y || armor.corners[1].y > armor.corners[3].y)
    {
        return false;
    }

    Point2f left_light  = armor.corners[0] - armor.corners[3],
            right_light = armor.corners[2] - armor.corners[1],
            center_diff = l.center - r.center;

    double  l_x = left_light.x,     l_y = left_light.y,
            r_x = right_light.x,    r_y = right_light.y,
            c_x = center_diff.x,    c_y = center_diff.y;

    double  left_length         = sqrt(l_x * l_x + l_y * l_y),
            right_length        = sqrt(r_x * r_x + r_y * r_y),
            center_diff_length  = sqrt(c_x * c_x + c_y * c_y),
            rectangle_likely    = (l_x * c_x + l_y * c_y) / (left_length * center_diff_length);
            rectangle_likely   += (r_x * c_x + r_y * c_y) / (right_length * center_diff_length);
    double  length_ratio = MAX(left_length, right_length) / MIN(left_length, right_length);

    double  len_ratio   = ArmorDetectParam::light_bar_length_ratio,
            ret_likely  = ArmorDetectParam::rectangle_likely;
    if (length_ratio > len_ratio || fabs(rectangle_likely) > ret_likely)
    {
        return false;
    }

    int armor_area = armor.rect.size().area();
    int area_max = ArmorDetectParam::armor_area_max, area_min = ArmorDetectParam::armor_area_min;
    if (armor_area < area_min || armor_area > area_max)
    {
        return false;
    }
    if(ArmorDetectParam::show_armor_info)
    {

        // TODO show info
        cout << "ARMOR INFO:" << endl;
        cout << "armor area: " << armor_area << endl;
        cout << "ARMOR INFO END." << endl;
    }

    return true;
}

double ArmorFinder::getAngle(const RotatedRect &rotatedRect) {
    double w = rotatedRect.size.width, h = rotatedRect.size.height, angle = rotatedRect.angle;
    // TODO show info
    return w > h ? angle - 90 : angle;
}

bool ArmorFinder::checkAngleDiff(const RotatedRect &l, const RotatedRect &r) {
    double angle_l = getAngle(l), angle_r = getAngle(r), diff = abs(angle_l - angle_r);
    double diff_max = ArmorDetectParam::angle_diff_max;
    // TODO show info
    return diff < diff_max;
}

bool ArmorFinder::checkHeightDiff(const RotatedRect &l, const RotatedRect &r) {
    Point2f diff = l.center - r.center;
    // TODO show info
    return abs(diff.y) < ArmorDetectParam::light_bar_center_diff;
}
