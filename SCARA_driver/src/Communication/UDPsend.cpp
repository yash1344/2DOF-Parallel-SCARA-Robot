/*
 * UDPsend.cpp
 *
 *  Created on: Jun 11, 2025
 *      Author: vagha
 */

// udp_send.cpp
#include "UDPsend.h"
#include <iostream>

UDP_send::UDP_send(boost::asio::io_context &io_context,
		unsigned short local_port) :
		socket_(io_context,
				boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(),
						local_port)) {
}

UDP_send::~UDP_send() {
	boost::system::error_code ec;
	socket_.close(ec);
	if (ec) {
		std::cerr << "Error closing socket: " << ec.message() << "\n";
	}
}

void UDP_send::async_send(const boost::asio::const_buffer& buffer,
                          const std::string& host,
                          unsigned short port,
                          SendHandler handler)
{
    // Resolve host:port
    auto resolver = std::make_shared<boost::asio::ip::udp::resolver>(socket_.get_executor());
    resolver->async_resolve(
        boost::asio::ip::udp::v4(),
        host,
        std::to_string(port),
        [this, resolver, buffer, handler]
        (const boost::system::error_code& ec,
         boost::asio::ip::udp::resolver::results_type endpoints)
        {
            if (ec) {
                handler(ec, 0);
                return;
            }

            // Send the buffer. We capture only the resolver here;
            // user must ensure `buffer`'s underlying data outlives this send.
            socket_.async_send_to(
                buffer,
                *endpoints.begin(),
                [handler](const boost::system::error_code& send_ec, std::size_t bytes_sent) {
                    handler(send_ec, bytes_sent);
                }
            );
        }
    );
}
