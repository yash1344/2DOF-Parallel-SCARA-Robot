/*
 * TCPsend.h
 *
 *  Created on: Jun 13, 2025
 *      Author: vagha
 */

#ifndef COMMUNICATION_TCPSEND_H_
#define COMMUNICATION_TCPSEND_H_

#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

using SendHandler= std::function<void(void)>;
class TCPsend {
private:
	tcp::socket socket_;
	tcp::acceptor acceptor_;
	boost::system::error_code ec;

public:
	TCPsend(boost::asio::io_context &io_context, int port);
	virtual ~TCPsend();

	void start_accept();
	void async_send(const boost::asio::const_buffer &buffer,
			SendHandler handler);
	bool is_connected();

};

#endif /* COMMUNICATION_TCPSEND_H_ */
