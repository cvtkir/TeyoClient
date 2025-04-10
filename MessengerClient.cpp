#include <iostream>
#include <string>
#include <thread>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>

using boost::asio::ip::tcp;
using json = nlohmann::json;


#define BUFFER_SIZE 1024

const std::string DEFAULT_ADDRESS = "192.168.0.107";
const int DEFAULT_PORT = 42001;

void read_messages(tcp::socket& socket) {
	boost::asio::streambuf buffer;
	while (true) {
		boost::asio::read_until(socket, buffer, '\n');
		std::string message(boost::asio::buffers_begin(buffer.data()),
			boost::asio::buffers_begin(buffer.data()) + buffer.size());
		buffer.consume(buffer.size());
		std::cout << "Message: " << message << std::endl;
	}
}

int main()
{
	try {
		boost::asio::io_context io_context;
		ChatClient client(io_context, DEFAULT_ADDRESS, DEFAULT_PORT);
		client.start();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

class ChatClient {
public:
	ChatClient(boost::asio::io_context& io_context, const std::string& address, int port)
		: socket_(io_context) {
		socket_.connect(tcp::endpoint(boost::asio::ip::make_address(address), port));
		std::cout << "Connected to server" << std::endl;
	}

	void start() {
		if (authorize()) {
			std::thread reader(&ChatClient::read_messages, this);
			send_messages();
			reader.join();
		}
	}

private:
	tcp::socket socket_;
	unsigned int user_id_ = 0;
	unsigned int chat_id_ = 1;

	bool authorize() {
		std::string login, password;
		std::cout << "Login: ";
		std::getline(std::cin, login);
		std::cout << "Password";
		std::getline(std::cin, password);

		json auth_request = {
			{"type", "auth"},
			{"login", login},
			{"password", password}
		};

		std::string serialized = auth_request.dump() + "\n";
		boost::asio::write(socket_, boost::asio::buffer(serialized));

		boost::asio::streambuf buffer;
		boost::asio::read_until(socket_, buffer, '\n');

		std::string response(boost::asio::buffers_begin(buffer.data()), boost::asio::buffers_begin(buffer.data()) + buffer.size());
		buffer.consume(buffer.size());

		json auth_response = json::parse(response);
		if (auth_response["type"] == "auth_success") {
			user_id_ = auth_response["user_id"];
			std::cout << "Authorized successfully. Your user_id is " << user_id_ << "\n";
			return true;
		}
		else {
			std::cout << "Authorization failed.\n";
			return false;
		}
	}

	void send_messages() {
		std::string text;
		while (std::getline(std::cin, text)) {
			json msg = {
				{"user_id", user_id_},
				{"chat_id", chat_id_},
				{"text", text}
			};
			std::string serialized = msg.dump() + "\n";
			boost::asio::write(socket_, boost::asio::buffer(serialized));
		}
	}

	void read_messages() {
		boost::asio::streambuf buffer;
		while (true) {
			boost::asio::read_until(socket_, buffer, '\n');
			std::string message(boost::asio::buffers_begin(buffer.data()), boost::asio::buffers_begin(buffer.data()) + buffer.size());
			buffer.consume(buffer.size());
			std::cout << "Message: " << message << std::endl;
		}
	}
};