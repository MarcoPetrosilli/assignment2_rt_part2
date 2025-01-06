#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/odometry.hpp"

class PositionBasedMotion : public rclcpp::Node
{
public:
    PositionBasedMotion()
    : Node("PositionBasedMotion")
    {
    
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

        subscription_ = this->create_subscription<nav_msgs::msg::Odometry>(
            "/odom",
            10,
            std::bind(&PositionBasedMotion::odometryListenerCallback, this, std::placeholders::_1));
    }

private:
    void odometryListenerCallback(const nav_msgs::msg::Odometry::SharedPtr msg)
    {
        auto position = msg->pose.pose.position;
        auto orientation = msg->pose.pose.orientation;

        /*RCLCPP_INFO(this->get_logger(), "Position: x=%.2f, y=%.2f, z=%.2f", position.x, position.y, position.z);
        RCLCPP_INFO(this->get_logger(), "Orientation: x=%.2f, y=%.2f, z=%.2f, w=%.2f",
                    orientation.x, orientation.y, orientation.z, orientation.w);*/

        geometry_msgs::msg::Twist vel;

        // Motion logic
        if (position.x > 9.0)
        {
            vel.linear.x = 1.0;
            vel.angular.z = 1.0;
        }
        else if (position.x < 1.0)
        {
            vel.linear.x = 1.0;
            vel.angular.z = -1.0;
        }
        else
        {
            vel.linear.x = 1.0;
            vel.angular.z = 0.0;
        }

        // Publish velocity
        publisher_->publish(vel);
        RCLCPP_INFO(this->get_logger(), "Publishing: linear.x=%.2f, angular.z=%.2f", vel.linear.x, vel.angular.z);
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PositionBasedMotion>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

