# Vinnie

A simple implementation of NLGL or L1-Guidance for a the TI-RSLK mobile robot. It uses wheel odometry to update it's position relative to it's starting point to it is prone to drift. Adding xbee communication and integrating it with an indoor position system is the next future work. After that is supporting path following of splines and Dubin's paths.

# Demonstration
The robot is told to follow a straight line starting defined by the waypoints W0 = [0,1], W1 = [1,2]. The initial position of the robot is [0,0] with its forward direction along the positive x-axis.

https://user-images.githubusercontent.com/64291228/163904899-5fa1abc1-188a-41ec-9e55-b1703a780bd1.mp4
