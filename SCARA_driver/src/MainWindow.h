/*
 * MainWindow.h
 *
 *  Created on: May 22, 2025
 *      Author: vagha
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_
#include <qmainwindow.h>
#include <qpushbutton.h>
#include <mutex>

#include "DrawingCanvas.h"
#include "Path_Manipulators/PersistentTrajectorySpeedManipulator.h"
#include "TTT.h"

class MainWindow: public QMainWindow {
Q_OBJECT

public:
	MainWindow(TCPsend &tcpSend, QWidget *parent = nullptr);
	~MainWindow();
	DrawingCanvas*& getMCanvas();
	TTT& getTtt();
	void startSendingData();

private:
	DrawingCanvas *m_canvas;
	QPushButton *m_clearButton;
	QPushButton *m_startGameButton;
	TCPsend &tcpSend;
	TTT ttt;

	QVector<QPointF> *path_buffer;
	std::mutex path_mutex;

	PersistentTrajectory_SpeedManipulator persistentTrajectory;

private slots:
	void handleMoveRequest(HolderState player);
	void handleGameEnd(HolderState winner);
	void handlePiecePlaced(int row, int col, HolderState state,
			QVector<QPointF> trajectory);
};

#endif /* MAINWINDOW_H_ */
