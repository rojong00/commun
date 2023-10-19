#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class MyPublisher : public rclcpp::Node {
public:
  MyPublisher() : Node("PC_publisher") {
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic_test", 10);
    timer_ = this->create_wall_timer(
		    std::chrono::milliseconds(500), std::bind(&MyPublisher::timer_callback, this));
    RCLCPP_INFO(get_logger(), "started");
  }

private:
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  size_t cnt_ = 0;

  void timer_callback() {
    auto msg = std_msgs::msg::String();
    msg.data = "Hello_" + std::to_string(cnt_);
    publisher_->publish(msg);
    RCLCPP_INFO(this->get_logger(), "SEND : %s", msg.data.c_str());
    cnt_++;
  }
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MyPublisher>());
  rclcpp::shutdown();
  return 0;
}

