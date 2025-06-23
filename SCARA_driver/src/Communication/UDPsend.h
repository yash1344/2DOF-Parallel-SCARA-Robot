/*
 * UDPsend.h
 *
 *  Created on: Jun 11, 2025
 *      Author: vagha
 */

#ifndef COMMUNICATION_UDPSEND_H_
#define COMMUNICATION_UDPSEND_H_

// udp_send.hpp
#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <functional>

class UDP_send {
public:
	using SendHandler = std::function<void(const boost::system::error_code& ec, std::size_t bytes_sent)>;

	/// Create and (optionally) bind to a local UDP port. If local_port==0, the OS picks one.
	UDP_send(boost::asio::io_context &io_context,
			unsigned short local_port = 0);

	~UDP_send();

	/// Asynchronously send `message` to (host, port).
	/// Handler is called when the send completes (or fails).
	void async_send(const boost::asio::const_buffer& buffer, const std::string &host,
			unsigned short port, SendHandler handler);

private:
	boost::asio::ip::udp::socket socket_;
};

#endif /* COMMUNICATION_UDPSEND_H_ */
