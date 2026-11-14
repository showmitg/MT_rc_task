#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/vector3.hpp>
#include <cmath>

using namespace std;

rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr angles_pub;

// segment lengths in cm
double l1 = 14.0;
double l2 = 15.5;

void target_callback(const geometry_msgs::msg::Vector3::SharedPtr msg)
{
    double x = msg->x;
    double y = msg->y;

    // distance from base to target
    double d = sqrt(x * x + y * y);

    // check work area and arm reach (1.5 cm to 29.5 cm)
    if (x < 0 || y < 0 || d < 1.5 || d > 29.5) {
        cout << "target out of reach" << endl;
        return;
    }

    // triangle angles in degrees
    double gamma = atan2(y, x) * 180.0 / M_PI;
    double alpha = acos((l1 * l1 + d * d - l2 * l2) / (2.0 * l1 * d)) * 180.0 / M_PI;
    double beta  = acos((l1 * l1 + l2 * l2 - d * d) / (2.0 * l1 * l2)) * 180.0 / M_PI;

    // convert to servo angles (0 to 180 deg)
    double joint1 = 180.0 - (gamma + alpha);
    double joint2 = 180.0 - beta;

    if (joint1 < 0 || joint1 > 180 || joint2 < 0 || joint2 > 180) {
        cout << "servo angle out of range" << endl;
        return;
    }

    geometry_msgs::msg::Vector3 out;
    out.x = joint1;
    out.y = joint2;
    angles_pub->publish(out);

    cout << "joint 1: " << joint1 << " deg, joint 2: " << joint2 << " deg" << endl;
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("ik_solver_node");

    angles_pub = node->create_publisher<geometry_msgs::msg::Vector3>("/miniarm/angles", 10);
    auto target_sub = node->create_subscription<geometry_msgs::msg::Vector3>("/miniarm/target", 10, target_callback);

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}