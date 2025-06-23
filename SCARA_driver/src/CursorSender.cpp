/*
 * CursorSender.cpp
 *
 *  Created on: May 22, 2025
 *      Author: vagha
 */

#include "CursorSender.h"

CursorSender::CursorSender(boost::asio::io_context &io_context) :
		socket_(io_context), acceptor_(io_context,
				tcp::endpoint(tcp::v4(), 1234)), timer_(io_context) {
	cout << "Server listening on port 1234..." << flush;
	start_accept();
}

void CursorSender::start_accept() {
	acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
		if (!ec) {
			cout << "\nConnected..." << flush;
//			start_send_loop();
		} else {
			cerr << "Accept error: " << ec.message() << endl;
		}
	});
}

void CursorSender::start_send_loop() {
	POINT cursor;
	GetCursorPos(&cursor);
	data_[0] = static_cast<double_t>(cursor.x);
	data_[1] = static_cast<double_t>(cursor.y);

	boost::asio::async_write(socket_, boost::asio::buffer(data_, sizeof(data_)),
			[this](boost::system::error_code ec, std::size_t bytes_sent) {
				if (ec) {
					cerr << "\nError: " << ec.message() << "\n";
					return;
				}
				if (bytes_sent != sizeof(data_)) {
					cerr << "\nWarning: Partial send!" << endl;
					return;
				}

				cout << "\nSent: (" << data_[0] << ", " << data_[1] << ")"
						<< flush;

				// Wait for 10ms and send again
				timer_.expires_after(std::chrono::milliseconds(10));
				timer_.async_wait([this](boost::system::error_code ec) {
					if (!ec) {
						start_send_loop();
					}
				});
			});
}

CursorSender::~CursorSender() {
	acceptor_.close();
	socket_.close();
	timer_.cancel();
}

void CursorSender::send_point(QPoint point) {
	data_[0] = static_cast<double_t>(point.x());
	data_[1] = static_cast<double_t>(point.y());
	boost::asio::async_write(socket_, boost::asio::buffer(data_, sizeof(data_)),
			[this](boost::system::error_code ec, std::size_t bytes_sent) {
				if (ec) {
					cerr << "\nError: " << ec.message() << "\n";
					return;
				}
				if (bytes_sent != sizeof(data_)) {
					cerr << "\nWarning: Partial send!" << endl;
					return;
				}

				cout << "\nSent: (" << data_[0] << ", " << data_[1] << ")"
						<< flush;
			});
}
