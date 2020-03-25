#include <ros_bridge_test/ros_image_pub.hpp>

using namespace ariitk::ros_bridge_test;

int main(int argc, char** argv) {
    
    ros::init(argc, argv, "ros_bridge_test_node");
    ros::NodeHandle nh;

    ImagePub img_publisher;

    img_publisher.init(nh);

    ros::Rate loop_rate(10);

    while(ros::ok()) {
        img_publisher.run();
        ros::spinOnce();
        loop_rate.sleep();
    }
    
    return 0;
}
        
