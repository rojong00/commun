#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

void msg_callback(const std_msgs::msg::String::SharedPtr msg) {
  RCLCPP_INFO(rclcpp::get_logger("bot_subscriber"), "Received message: %s", msg->data.c_str());
}

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("bot_subscriber");
  auto subscriber = node->create_subscription<std_msgs::msg::String>(
    "topic_test", 10, message_callback);

  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
