#include <iostream>
#include <boost/asio.hpp>

int main(int argc, char *argv[]){

    if(argc != 2) {
        std::cout << "Usage: " << argv[0] << " <server>" << std::endl;
        return 1;
    }

    std::cout << "resolving ... " << std::endl;
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(argv[1], "13477");
    boost::asio::ip::tcp::socket socket(io_service);
    boost::asio::connect(socket, resolver.resolve(query));

    unsigned char commandNr = 0x01;
    unsigned char packageLengthH = 0x00;
    unsigned char packageLengthL = 0x0A;
    unsigned char buffer[] = { commandNr, packageLengthL, packageLengthH, 'C', 'l', 'i', 'e', 'n', 't', 0xCD};

    std::cout << "connecting ... " << std::endl;
    boost::system::error_code ec;
    socket.write_some(boost::asio::buffer(buffer), ec);

    std::vector<char> rb(1024, 0);
    socket.read_some(boost::asio::buffer(rb), ec);
    std::string rbs(rb.begin(), rb.end());
    std::cout << "read: " << rbs << std::endl;
    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
    socket.close();

    io_service.run();
    return 0;
}
