#include<math.h>
#include<opencv2/core/core.hpp>

using namespace std;

float calcDistance(cv::Mat cameraPosition, cv::Mat highestPoint){
    float distance = sqrt((highestPoint.at<float>(0)-cameraPosition.at<float>(0),2)+pow(highestPoint.at<float>(1)-cameraPosition.at<float>(1),2)+pow(highestPoint.at<float>(2)-cameraPosition.at<float>(2),2));
    return distance;
};