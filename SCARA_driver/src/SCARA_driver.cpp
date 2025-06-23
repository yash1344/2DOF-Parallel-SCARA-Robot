//============================================================================
// Name        : SCARA_driver.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
//#include <winsock2.h>
//#include <windows.h> // For GetCursorPos

#include "CursorSender.h"
#include <QApplication>
#include <thread>

#include "Communication/UDPsend.h"
#include "MainWindow.h"
#include "Shapes/Circle.h"

using boost::asio::ip::tcp;
using namespace std;

int main(int argc, char *argv[]) {
	boost::asio::io_context io_context;
	TCPsend tcpSender(io_context, 1234);
	std::thread t1([&io_context]() {
		io_context.run();
	});

	QApplication a(argc, argv);
	MainWindow w(tcpSender);
	w.show();

//	UDP_send udp(io_context, 1234);
//	uint16_t data_[2] = { 0, 0 };
//
//	boost::asio::const_buffer buf(data_, sizeof(data_));
//	while (true) {
//		udp.async_send(buf, "192.168.137.1", 1234,
//				[](const boost::system::error_code &ec, std::size_t bytes) {
//					if (ec)
//						std::cerr << "Send failed: " << ec.message() << "\n";
//					else
//						std::cout << "Sent " << bytes << " bytes\n";
//				}
//		);
//		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//		data_[0]++;
//		data_[1]++;
//		cout << endl << "(" << data_[0] << ", " << data_[1] << ")";
//	}
	return a.exec();
}
