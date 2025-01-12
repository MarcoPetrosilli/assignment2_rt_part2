#include "rclcpp/rclcpp.hpp"
#include "assignment2_rt_part2/srv/VelService.hpp"

using std::placeholders::_1;

class VelService : public rclcpp::Node
{
public:
  VelService()
  : Node("vel_srv_server")
  {
    service_ = this->create_service<assignment2_rt_part2::srv::vel_service>(
      "VelService",
      std::bind(&vel_service::handle_request, this, _1)
    );
  }

private:
  void handle_request(
    const std::shared_ptr<assignment2_rt_part2::srv::vel_service::Request> request,
    std::shared_ptr<assignment2_rt_part2::srv::vel_service::Response> response)
  {
    response->lin_vel = request->lin_vel;
    RCLCPP_INFO(this->get_logger(), "Incoming request: lin_vel=%ld", request->lin_vel);
    RCLCPP_INFO(this->get_logger(), "Sending response: lin_vel=%ld", response->lin_vel);
  }

  rclcpp::Service<assignment2_rt_part2::srv::vel_service>::SharedPtr service_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<VelService>());
  rclcpp::shutdown();
  return 0;
}

