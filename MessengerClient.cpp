#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;
using namespace std;

#define DEFAULT_ADDRESS "192.168.0.107"
#define DEFAULT_PORT 42001
#define BUFFER_SIZE 1024

void read_messages(tcp::socket& socket) {
	boost::asio::streambuf buffer;
	while (true) {
		boost::asio::read_until(socket, buffer, '\n');
		string message(boost::asio::buffers_begin(buffer.data()),
			boost::asio::buffers_begin(buffer.data()) + buffer.size());
		buffer.consume(buffer.size());
		cout << "Message: " << message << endl;
	}
}

int main()
{
	try {
		boost::asio::io_context io_context;
		tcp::socket socket(io_context);

		socket.connect(tcp::endpoint(boost::asio::ip::make_address(DEFAULT_ADDRESS), DEFAULT_PORT));
		cout << "Connected to server" << endl;

		std::thread reader(read_messages, std::ref(socket));

		string message;
		while (true)
		{
			getline(cin, message);
			boost::asio::write(socket, boost::asio::buffer(message + "\n"));
		}

	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
	}

}