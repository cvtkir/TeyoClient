#include <iostream>
#include <string>
#include <thread>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <QApplication>


using boost::asio::ip::tcp;
using json = nlohmann::json;



std::string DEFAULT_ADDRESS = "192.168.0.107";
int DEFAULT_PORT = 42001;



class ChatClient {
public:
	ChatClient(boost::asio::io_context& io_context, std::string& address, int port)
		: socket_(io_context) {
		socket_.connect(tcp::endpoint(boost::asio::ip::make_address(address), port));
		std::cout << "Connected to server" << std::endl;
	}

	void start() {
		//std::thread reader(&ChatClient::read_messages, this);
		control();
		//reader.join();

	}

private:
	tcp::socket socket_;
	unsigned int user_id_ = 0;
	unsigned int chat_id_ = 1;
	bool is_authorized_ = false;

	void control() {
		std::string command;
		while (true) {
			std::getline(std::cin, command);
			if (command == "exit") {
				break;
			}
			else if (command == "signup" || command == "login") {
				if (authorize(command)) {
					std::cout << "Authorized successfully." << std::endl;
				}
				else {
					std::cout << "Authorization failed." << std::endl;
				}
			}
			else if (command == "msg" && is_authorized_) {
				send_message();
			}
			else {
				std::cout << "Available commands: signup, login, msg, exit" << std::endl;
			}
		}
	}

	bool authorize(std::string type) {
		std::string login, password;
		std::cout << "Login: ";
		std::getline(std::cin, login);
		std::cout << "Password: ";
		std::getline(std::cin, password);
		
		json auth_request = {
			{"type", type},
			{"login", login},
			{"password", password}
		};

		std::string serialized = auth_request.dump() + "\n";
		boost::asio::write(socket_, boost::asio::buffer(serialized));
		std::cout << "sent auth request" << std::endl;
		boost::asio::streambuf buffer;
		boost::asio::read_until(socket_, buffer, '\n');
		std::cout << "reading answer" << std::endl;

		std::string response(boost::asio::buffers_begin(buffer.data()), boost::asio::buffers_begin(buffer.data()) + buffer.size());
		buffer.consume(buffer.size());

		json auth_response = json::parse(response);
		if (auth_response["type"] == "auth_success") {
			//user_id_ = auth_response["user_id"];
			std::cout << auth_response["message"] << "\n";
			return is_authorized_ = true;
		}
		else {
			std::cout << auth_response["message"] << "\n";
			return false;
		}
	}

	void send_message() {
		std::string text;
		std::getline(std::cin, text);
		json msg = {
			{"user_id", user_id_},
			{"chat_id", chat_id_},
			{"text", text}
		};
		std::string serialized = msg.dump() + "\n";
		boost::asio::write(socket_, boost::asio::buffer(serialized));
		
	}

	void read_messages() {
		boost::asio::streambuf buffer;
		while (true) {
			boost::asio::read_until(socket_, buffer, '\n');
			std::string message(boost::asio::buffers_begin(buffer.data()), boost::asio::buffers_begin(buffer.data()) + buffer.size());
			buffer.consume(buffer.size());
			json j;
			try {
				j = json::parse(message);
			}
			catch (const json::parse_error& e) {
				std::cerr << "Parse error: " << e.what() << std::endl;
				continue;
			}
			//uint32_t u_id = j.value("user_id", -1);
			//std::cout << "User_" << u_id << ": " << j.value("text", "") << std::endl;
			std::cout << j.value("message", "") << std::endl;
		}
	}
};


int main()
{
	std::string a;
	std::cin >> a;
	std::cout << a << std::endl;
	// try {
	// 	boost::asio::io_context io_context;
	// 	ChatClient client(io_context, DEFAULT_ADDRESS, DEFAULT_PORT);
	// 	client.start();
	// }
	// catch (std::exception& e)
	// {
	// 	std::cerr << e.what() << std::endl;
	// }
}