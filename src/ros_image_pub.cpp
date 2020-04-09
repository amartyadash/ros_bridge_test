#include <ros_bridge_test/ros_image_pub.hpp>

namespace ariitk::ros_bridge_test {

void ImagePub::init(ros::NodeHandle& nh) {
    img_pub_ = nh.advertise<sensor_msgs::Image>("bridge_image",20);
    initial_time_ = ros::WallTime::now();
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
    time_diff_ = (time_ - initial_time_).toNSec()*1e-6*1e-3;

    ROS_ASSERT(frame_.empty()!=true);
    preProcess(frame_);
    ROS_ASSERT(pre_processed_frame_.empty()!=true);
    
    cv_bridge::CvImage converted_frame_;
    converted_frame_.encoding = sensor_msgs::image_encodings::MONO8;
    converted_frame_.header.stamp = ros::Time::now();
    converted_frame_.image = pre_processed_frame_;
    std::stringstream ss;
    ss <<  count_;
    converted_frame_.header.frame_id = ss.str();
    std::cout << converted_frame_.header.frame_id << " " << "Time rn : " << time_diff_<< std::endl;
    img_pub_.publish(converted_frame_.toImageMsg());
    
    time_ = ros::WallTime::now();
    count_++;
}

}// namespace ariitk::ros_bridge_test