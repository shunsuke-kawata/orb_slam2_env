#include<math.h>
#include<opencv2/core/core.hpp>

using namespace std;

float calcDistance(cv::Mat point1, cv::Mat point2){
    float distance = sqrt(pow(point2.at<float>(0)-point1.at<float>(0),2)+pow(point2.at<float>(1)-point1.at<float>(1),2)+pow(point2.at<float>(2)-point1.at<float>(2),2));
    return distance;
};