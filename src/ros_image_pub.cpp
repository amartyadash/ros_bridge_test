#include <ros_bridge_test/ros_image_pub.hpp>

namespace ariitk::ros_bridge_test {

void ImagePub::init(ros::NodeHandle& nh) {
    img_pub_ = nh.advertise<sensor_msgs::Image>("bridge_image",10);
    time_ = ros::WallTime::now();
    cap_.open(0);
    count_ = 0;
}

void ImagePub::preProcess(cv::Mat& img) {
    cv::cvtColor(img, pre_processed_frame_, CV_BGR2GRAY); 
    cv::putText(pre_processed_frame_, std::to_string(count_), cv::Point(100,100),  CV_FONT_HERSHEY_PLAIN, 3, cv::Scalar(0, 0, 255), 3, 8, false);

}

void ImagePub::run(const ros::WallTimerEvent& event) {
    cap_ >> frame_;
    time_ = ros::WallTime::now();
    ROS_ASSERT(frame_.empty()!=true);
    preProcess(frame_);
    ROS_ASSERT(pre_processed_frame_.empty()!=true);
    
    cv_bridge::CvImage converted_frame_;
    converted_frame_.encoding = sensor_msgs::image_encodings::MONO8;
    converted_frame_.header.stamp = ros::Time::now();
    converted_frame_.image = pre_processed_frame_;
    
    std::cout << "Time rn (ros::Time::now()) : " << converted_frame_.header.stamp << std::endl;
    img_pub_.publish(converted_frame_.toImageMsg());
    
    
    count_++;
}

}// namespace ariitk::ros_bridge_test