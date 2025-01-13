#include "rclcpp/rclcpp.hpp"
#include "assignment2_1_rt/srv/stop_service.hpp" // Include del servizio
#include "rclcpp_action/rclcpp_action.hpp"
#include "assignment2_1_rt/action/planning.hpp"  // Include dell'azione

using StopService = assignment2_1_rt::srv::StopService; // Nuovo nome del servizio
using PlanningAction = assignment2_1_rt::action::Planning;

class StopServiceNode : public rclcpp::Node
{
public:
    StopServiceNode() : Node("stop_service")
    {
        // Creazione del server del servizio
        service_ = this->create_service<StopService>(
            "stop_service",
            std::bind(&StopServiceNode::stop_robot, this, std::placeholders::_1, std::placeholders::_2));

        // Creazione del client per l'azione
        action_client_ = rclcpp_action::create_client<PlanningAction>(this, "/reaching_goal");

        RCLCPP_INFO(this->get_logger(), "Stop service node has been started.");
    }

private:
    rclcpp::Service<StopService>::SharedPtr service_;
    rclcpp_action::Client<PlanningAction>::SharedPtr action_client_;

    void stop_robot(const std::shared_ptr<StopService::Request> /*request*/,
                    const std::shared_ptr<StopService::Response> /*response*/)
    {
        // Aspetta che il server dell'azione sia disponibile
        if (!action_client_->wait_for_action_server(std::chrono::seconds(5)))
        {
            RCLCPP_ERROR(this->get_logger(), "Action server not available.");
            return;
        }

        // Cancella l'azione corrente
        action_client_->async_cancel_all_goals();

        RCLCPP_INFO(this->get_logger(), "Robot has been stopped.");
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<StopServiceNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

