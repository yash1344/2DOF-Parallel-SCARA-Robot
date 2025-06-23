/*
 * CursorSender.h
 *
 *  Created on: May 22, 2025
 *      Author: vagha
 */

#ifndef CURSORSENDER_H_
#define CURSORSENDER_H_

#include <boost/asio.hpp>
#include <qpoint.h>
#include <iostream>
#include <windows.h>

using boost::asio::ip::tcp;
using namespace std;

class CursorSender {
public:
	CursorSender(boost::asio::io_context &io_context);
	virtual ~CursorSender();
	void send_point(QPoint point);
	void start_send_loop();
	void start_accept();

private:
	tcp::socket socket_;
	tcp::acceptor acceptor_;
	boost::asio::steady_timer timer_;
	double_t data_[2];
};

#endif /* CURSORSENDER_H_ */
