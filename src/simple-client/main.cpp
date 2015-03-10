#include <iostream>
#include <boost/asio.hpp>
#include <common/communication/NetworkPackageManager.h>
#include <common/Connection.h>

std::string ask_user(std::string prompt, std::string default_value) {
    std::string value;
    std::cout << prompt << std::flush;
    std::cin >> value;
    if(!std::cin.good()) value = default_value;
    return value;
}

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
    std::cout << "connecting ... " << std::endl;

    Connection connection(1, std::move(socket));

    std::string name = ask_user("your nickname: ", "unnamed");
    PlayerJoinPackage player_join_package;
    player_join_package.set_player_name(name);
    connection.write(player_join_package);

    connection.read([](NetworkPackage & package) {
        std::cout << "answer" << std::endl;
        if(is_package_of_type<PlayerJoinAnswerPackage>(package)) {
             PlayerJoinAnswerPackage & answer = cast_package<PlayerJoinAnswerPackage>(package);
             std::cout << "identity: " << answer.get_identity() << std::endl;
        }
    });
    io_service.run();

    return 0;
}
