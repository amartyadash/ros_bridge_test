# ros_bridge_test
A ROS1 image publisher for testing ROS2-ROS1 bridge. 

*Note: This README assumes you have also cloned the `ros2_bridge_test` repository to your ROS2 workspace.

## ROS2-ROS1 Bridge
Make sure you have the [ROS2-ROS1 bridge](https://github.com/ros2/ros1_bridge) installed, either through a binary installation or a source installation.
Follow the steps given in the following documentation to set up the environment needed for the bridge system:- http://ros2docs.org/ros1-bridge/ros1-bridge/

Also make sure that you have not sourced either ROS1 or ROS2 workspaces in your `~/.bashrc` as we will switch between them.

*Note : The following README assumes ROS1 distro : 'Melodic' with workspace name : 'catkin_ws' & ROS2 distro : 'Eloquent' with workspace name : 'dev_ws'.
## Dependencies
The following package has these dependencies:
* roscpp
* sensor_msgs
* cv_bridge
* OpenCV (>3.0)
## Usage
In separate terminals, source both the distro installations and their overlay workspaces and build both the packages.
First in a terminal (Shell A) we will source the ROS1 installation and start up a roscore:

```bash
source /opt/ros/melodic/setup.bash
roscore
```
Then in a second terminal (Shell B), we start the ROS2-ROS1 bridge:
```bash
source /opt/ros/melodic/setup.bash
source /opt/ros/eloquent/local_setup.bash
export ROS_MASTER_URI=http://localhost:11311
ros2 run ros1_bridge dynamic_bridge
```
Now in a third terminal (Shell C), we start up the ROS2 image subscriber:
```bash
export ROS_DISTRO=eloquent
source /opt/ros/$ROS_DISTRO/setup.bash
source ~/dev_ws/install/local_setup.bash
cd ~/dev_ws/src/ros2_bridge_test/etc/    # To store images
ros2 run ros2_bridge_test ros2_bridge_test_node
```
Now in a fourth terminal (Shell D), we start the ROS1 image publisher:
```bash
export ROS_DISTRO=melodic
source /opt/ros/$ROS_DISTRO/setup.bash
source ~/catkin_ws/devel/setup.bash
export ROS_PACKAGE_PATH=/home/user/catkin_ws/src:/opt/ros/melodic/share
rosrun ros_bridge_test ros_bridge_test_node
```
You should see the images getting created in the `etc` folder of the ROS2 package.

