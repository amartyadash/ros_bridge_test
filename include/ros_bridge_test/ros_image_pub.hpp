#pragma once 

#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>

namespace ariitk::ros_bridge_test {

class ImagePub {
    public:
        void init(ros::NodeHandle& nh);
        void preProcess(cv::Mat& img);
        void run();
        
    private:
        ros::Publisher img_pub_;
        int count_;
        cv::Mat frame_, pre_processed_frame_;
        cv::VideoCapture cap_;
        
};

}//ariitk::ros_bridge_test