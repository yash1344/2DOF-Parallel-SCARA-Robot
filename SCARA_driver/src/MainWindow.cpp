/*
 * MainWindow.cpp
 *
 *  Created on: May 22, 2025
 *      Author: vagha
 */

#include "MainWindow.h"

#include <iostream>
#include <QVBoxLayout>
#include <QPushButton>
#include <thread>
#include <fstream>

using namespace std;

MainWindow::MainWindow(TCPsend &tcpSend, QWidget *parent) :
		QMainWindow(parent), tcpSend(tcpSend), ttt(
				TTT(Coordinate(340, 170, 0), 120)), persistentTrajectory(
				PersistentTrajectory_SpeedManipulator(nullptr, 5, 5)) {

	tcpSend.start_accept();
	path_buffer = new QVector<QPointF>();
	persistentTrajectory = PersistentTrajectory_SpeedManipulator(path_buffer,
			120, 3);

	// Create widgets
	m_canvas = new DrawingCanvas(&ttt, path_buffer, this);
	m_clearButton = new QPushButton("Clear Canvas", this);
	m_startGameButton = new QPushButton("Start game", this);

	// Setup layout
	QWidget *centralWidget = new QWidget(this);
	QVBoxLayout *layout = new QVBoxLayout(centralWidget);
	layout->addWidget(m_canvas);
	layout->addWidget(m_clearButton);
	layout->addWidget(m_startGameButton);

	setCentralWidget(centralWidget);

	// Connect signal and slot
	connect(m_clearButton, &QPushButton::clicked, m_canvas,
			&DrawingCanvas::clear);

	connect(&ttt, &TTT::moveRequested, this, &MainWindow::handleMoveRequest);
	connect(&ttt, &TTT::gameFinished, this, &MainWindow::handleGameEnd);
	connect(&ttt, &TTT::piecePlaced, this, &MainWindow::handlePiecePlaced);

	// Start game button
	connect(m_startGameButton, &QPushButton::clicked, this, [this]() {
		// Reconnect signals to new TTT instance
		ttt.startGame();
	});

// Window settings
	setWindowTitle("Qt Drawing App");
	resize(800, 600);

	startSendingData();
}

void MainWindow::handleMoveRequest(HolderState player) {
	// Set up canvas to capture next click
	Coordinate point = m_canvas->getPoint();
	ttt.processUserMove(point);
}

void MainWindow::handleGameEnd(HolderState winner) {
	// Show game result

	if (winner == EMPTY) {
		cout << endl << "Game ended in a draw!" << flush;
	} else if (winner == CROSS) {
		cout << endl << "X Wins" << flush;
	} else {
		cout << endl << "O Wins" << flush;
	}
}

void MainWindow::handlePiecePlaced(int row, int col, HolderState state,
		QVector<QPointF> trajectory) {
	// Add trajectory to path buffer
	{
		std::lock_guard<std::mutex> lock(path_mutex);
		m_canvas->getPathBuffer()->append(trajectory);
	}
	m_canvas->update();
}

DrawingCanvas*& MainWindow::getMCanvas() {
	return m_canvas;
}

TTT& MainWindow::getTtt() {
	return ttt;
}

MainWindow::~MainWindow() {
	m_canvas->deleteLater();
	m_clearButton->deleteLater();
	m_startGameButton->deleteLater();
	delete path_buffer;
	path_buffer = nullptr;
}

void MainWindow::startSendingData() {
	std::thread path_transmitting_thread(
			[this]() {

				double time = 0;

				while (true) {
					std::unique_lock<std::mutex> lock(path_mutex);

					if (path_buffer->isEmpty()) {
						lock.unlock();
						std::this_thread::sleep_for(500ms);
						continue;
					}

					auto newPoint = persistentTrajectory.getNewPoint2();

					if (newPoint) {
						time += newPoint.value().first;
						auto system_center =
								m_canvas->getWorkSpace().getSystemCenter();
						double_t x = newPoint.value().second.x()
								- system_center.X();
						double_t y = newPoint.value().second.y()
								- system_center.Y();
						double_t point[3] = { time, -x, -y };
						lock.unlock();  // Unlock before sending
						m_canvas->update();

						this->tcpSend.async_send(
								boost::asio::buffer(point, sizeof(point)),
								[](auto...) {
//									cout << endl << "sent";
								}
						);
					} else {
						lock.unlock();
						std::this_thread::sleep_for(10ms);
					}
				}
			});
	path_transmitting_thread.detach();
}
