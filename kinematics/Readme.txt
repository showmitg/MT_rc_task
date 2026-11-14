# Task C3: 2-DOF MiniArm IK Solver

ROS2 node (miniarm_MT_node) that calculates joint 1 and joint 2 servo angles for a 2-DOF arm using Law of Cos.

## Math & Diagram: hand calculation in "handwritten_calculation_0.jpeg" and "handwritten_calculation_1.jpeg" (verified with test point (15, 10)).
## Subscribes: "/miniarm/target" ("geometry_msgs/msg/Vector3") - target (x, y) in cm.
## Publishes: "/miniarm/angles" ("geometry_msgs/msg/Vector3") - Joint-1 ("x") and Joint-2 ("y") in degrees.

## Extra Checks Added
 Reach Check: Ignores points outside "1.5 cm" to "29.5 cm"
 Servo Limit Check: Rejects any calculated angle outside "0" to "180" degrees to protect the arm servos.

## How to Run
bash
colcon build --packages-select miniarm_MT
source install/setup.bash
ros2 run miniarm_MT miniarm_MT_node
