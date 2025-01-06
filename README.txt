This project involves the development of a ROS2 node in C++ to interface with a simulation of a mobile robot. The simulation environment, including its nodes and software components, is pre-provided.
The main objective of the node is to control the robot to follow a specific motion pattern: moving straight until reaching specific coordinate thresholds, at which point the robot turns and resumes straight motion in the opposite direction. This behavior is repeated in a loop. A class named PositionBasedMotion was implemented within the node. This class subscribes to the /odom topic to obtain the robot's current position and publishes velocity commands to the /cmd_vel topic to control the robot's movement. The implemented logic ensures that when the robot's x-coordinate is less than 1 or greater than 9, an angular velocity (-1 or 1, depending on the direction) is applied to make the robot turn, while in other cases, only linear velocity is applied to maintain straight motion.
Following the choosen node architecture we have that the main function is minimal, focusing on initializing the ROS2 environment, creating the node using the PositionBasedMotion class, launching the node, and keeping it active (spin()) until termination. Finally, the ROS2 runtime is shut down, and resources are cleaned up (shutdown()). This approach ensures an efficient and maintainable implementation while achieving the desired motion behavior for the mobile robot.

Istruction to install and run the software:

Get into ROS2 workspace, in the src folder, and clone the repo with the given url:

	cd ~/<workspace_folder>/src
	git clone <repo-url> assignment2_rt_part2

Now get back to the workspace folder:

	cd ..

Then, compile the workspace with te following command:

	colcon build
	source install/local_setup.bash

If all is gone well, is possibile to run the software by opening a new tab and run the following command:

	ros2 launch src/assignment2_rt_part2/launch/gazebo.launch.py
	
This command will launch de whole software, in that launch file will be launched:
	- the position based motion controller node
	- the mobile robot simulation
	


