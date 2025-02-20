//ROS2 Node Serial Communication control ESP32 LED
//When ROS2 ouput a character to ttyACM0 and ESP32 receive character with switch case do the operation (led blink)
//ESP32 receive character like serial monitor

#include <rclcpp/rclcpp.hpp>
#include <boost/asio.hpp>
#include <string>
#include <chrono>
#include <thread>

using namespace std;
using namespace boost::asio;

class SerialTxNode : public rclcpp::Node {
public:
    SerialTxNode() : Node("serial_tx_node"), io_(), serial_(io_, "/dev/ttyACM0") {
        serial_.set_option(serial_port_base::baud_rate(115200));

        // Timer to send data every 2 seconds
        timer_ = this->create_wall_timer(
            std::chrono::seconds(2),
            std::bind(&SerialTxNode::sendSerialCommand, this)
        );
    }

private:
    io_service io_;
    serial_port serial_;
    rclcpp::TimerBase::SharedPtr timer_;

    void sendSerialCommand() {
        static const std::vector<char> commands = {'R', 'G', 'B', 'O'};
        static size_t index = 0;

        char command = commands[index];
        boost::system::error_code ec;
        write(serial_, buffer(&command, 1), ec);

        if (!ec) {
            RCLCPP_INFO(this->get_logger(), "Sent Command: %c", command);
        } else {
            RCLCPP_ERROR(this->get_logger(), "Serial Write Error: %s", ec.message().c_str());
        }

        index = (index + 1) % commands.size();  // Cycle through R, G, B, O
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SerialTxNode>());
    rclcpp::shutdown();
    return 0;
}
