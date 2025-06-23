/*
 * TCPsend.cpp
 *
 *  Created on: Jun 13, 2025
 *      Author: vagha
 */

#include "TCPsend.h"
using namespace std;

TCPsend::TCPsend(boost::asio::io_context &io_context, int port) :
		socket_(io_context), acceptor_(io_context,
				tcp::endpoint(tcp::v4(), port)) {
	start_accept();
}

TCPsend::~TCPsend() {
	acceptor_.close();
	socket_.close();
}

void TCPsend::start_accept() {
	cout << endl << "Server Running on 1234." << flush;
	acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
		if (!ec) {
			cout << "\nConnected..." << flush;
		} else {
			cerr << "Accept error: " << ec.message() << endl << flush;
		}
	});
}

void TCPsend::async_send(const boost::asio::const_buffer &buffer,
		SendHandler handler) {

	if (is_connected()) {
		boost::asio::async_write(socket_, buffer,
				[this, buffer, handler](boost::system::error_code ec,
						std::size_t bytes_sent) {
					if (ec) {
						cerr << endl << "\nError: " << ec.message();
						return;
					}
					if (bytes_sent != buffer.size()) {
						cerr << "\nWarning: Partial send!" << flush;
						return;
					}

					handler();
				});
	}
}

bool TCPsend::is_connected() {
	socket_.remote_endpoint(ec);
	return socket_.is_open() && !ec;
}
