/**
* This file is part of ORB-SLAM2.
*
* Copyright (C) 2014-2016 Raúl Mur-Artal <raulmur at unizar dot es> (University of Zaragoza)
* For more information see <https://github.com/raulmur/ORB_SLAM2>
*
* ORB-SLAM2 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM2 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ORB-SLAM2. If not, see <http://www.gnu.org/licenses/>.
*/


#include<iostream>
#include<algorithm>
#include<fstream>
#include<chrono>

#include<ros/ros.h>
#include <cv_bridge/cv_bridge.h>

#include<opencv2/core/core.hpp>

#include"../../../include/System.h"

using namespace std;

class ImageGrabber
{
public:
    ImageGrabber(ORB_SLAM2::System* pSLAM):mpSLAM(pSLAM){}

    void GrabImage(const sensor_msgs::ImageConstPtr& msg);

    ORB_SLAM2::System* mpSLAM;

};

chrono::high_resolution_clock::time_point start_time;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Mono");
    ros::start();

    if(argc != 3)
    {
        cerr << endl << "Usage: rosrun ORB_SLAM2 Mono path_to_vocabulary path_to_settings" << endl;        
        ros::shutdown();
        return 1;
    }    

    //現在時刻を取得
    start_time = chrono::high_resolution_clock::now();

    // 時刻をミリ秒単位に変換
    chrono::time_point<chrono::high_resolution_clock, chrono::seconds> start_time_s = chrono::time_point_cast<chrono::seconds>(start_time);

    // ミリ秒単位の値を取得
    auto value = start_time_s.time_since_epoch();

    // ミリ秒単位の値を表示
    cout << "現在時刻(秒）: " << value.count() << endl;
    
    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    cout<<"Systemの呼び出しとコンストラクタの実行"<<endl;
    ORB_SLAM2::System SLAM(argv[1],argv[2],ORB_SLAM2::System::MONOCULAR,true);

    cout<<"ImageGrabberのコンストラクタの実行"<<endl;
    ImageGrabber igb(&SLAM);

    ros::NodeHandle nodeHandler;
    cout<<"GrabImage関数の呼び出し"<<endl;
    //ここから経過時間を取得すれば良い
    ros::Subscriber sub = nodeHandler.subscribe("/camera/image_raw", 1, &ImageGrabber::GrabImage,&igb);
    cout<<"GrabImage関数の呼び出し後"<<endl;

    ros::spin();

    // Stop all threads
    SLAM.Shutdown();

    // Save camera trajectory
    cout<<"Saving"<<endl;
    SLAM.SaveKeyFrameTrajectoryTUM("KeyFrameTrajectory.txt");

    ros::shutdown();

    return 0;
}

void ImageGrabber::GrabImage(const sensor_msgs::ImageConstPtr& msg)
{
    cout<<"GrabImageの実行"<<endl;
    // Copy the ros image message to cv::Mat.
    cv_bridge::CvImageConstPtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvShare(msg);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }
    mpSLAM->TrackMonocular(cv_ptr->image,cv_ptr->header.stamp.toSec());
}


