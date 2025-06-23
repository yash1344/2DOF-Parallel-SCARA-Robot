/*
 * TTT.cpp
 *
 *  Created on: Jun 4, 2025
 *      Author: vagha
 */

#include "TTT.h"

#include "Shapes/Circle.h"
#include "Shapes/MyTriangle.h"

using namespace std;
TTT::TTT(Coordinate leftTopCorner, float size, QObject *parent) :
		QObject(parent), leftTopCorner(leftTopCorner), size(size) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			grid[i][j] = EMPTY;
		}
	}
}

HolderState TTT::isGameFinished() const {
	// Check each row:
	for (int i = 0; i < 3; ++i) {
		if (grid[i][0] != EMPTY && grid[i][0] == grid[i][1]
				&& grid[i][1] == grid[i][2]) {
			return grid[i][0];
		}
	}
	// Check each column:
	for (int j = 0; j < 3; ++j) {
		if (grid[0][j] != EMPTY && grid[0][j] == grid[1][j]
				&& grid[1][j] == grid[2][j]) {
			return grid[0][j];
		}
	}
	// Check main diagonal:
	if (grid[0][0] != EMPTY && grid[0][0] == grid[1][1]
			&& grid[1][1] == grid[2][2]) {
		return grid[0][0];
	}
	// Check anti‐diagonal:
	if (grid[0][2] != EMPTY && grid[0][2] == grid[1][1]
			&& grid[1][1] == grid[2][0]) {
		return grid[0][2];
	}
	// No winner yet:
	return EMPTY;
}

TTT::~TTT() {
}

const HolderState* TTT::getGrid() const {
	return &grid[0][0];
}

float TTT::getSize() const {
	return size;
}

void TTT::setSize(float size) {
	this->size = size;
}

bool TTT::putOn(int row, int col, HolderState piece) {
	// Check bounds:
	if (row < 0 || row > 2 || col < 0 || col > 2) {
		return false;
	}
	if (grid[row][col] == EMPTY) {
		grid[row][col] = piece;   // ← use assignment, not '=='
		return true;
	}
	return false;
}

void TTT::startGame() {
	isGameOn = true;
	currentPlayer = CROSS;
	movesCount = 0;

	// Clear the grid
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			grid[i][j] = EMPTY;
		}
	}
	cout << endl << "Game Start..." << flush;

	emit moveRequested(currentPlayer);
}
/*

 bool TTT::startGame(std::function<std::optional<Coordinate>()> forMove,
 std::function<void(int, int, HolderState, QVector<QPointF>)> onMove) {
 isGameOn = true;
 HolderState currentPlayer = CROSS;
 int movesCount = 0;

 while (isGameOn) {
 // Ask the current player for a move:
 int row, col;

 // Simple validation loop:
 while (isGameOn) {
 std::cout << std::endl << "Left Click to place." << std::flush;
 std::optional<Coordinate> temp = forMove();
 if (!temp.has_value()) {
 continue;
 }
 Coordinate point = temp.value();

 row = static_cast<int>(std::floor(
 (point - leftTopCorner).X() / (size / 3)));
 col = static_cast<int>(std::floor(
 (point - leftTopCorner).Y() / (size / 3)));

 std::cout << std::endl << row << " , " << col << std::flush;

 if (row < 0 || row > 2 || col < 0 || col > 2) {
 std::cout << std::endl
 << "Out of range. Please enter row and column between 0 and 2."
 << std::flush;
 continue;
 }
 if (grid[row][col] != EMPTY) {
 std::cout << std::endl
 << "Cell already occupied. Choose another cell."
 << std::flush;
 continue;
 }
 break;
 }

 // Place the piece:
 if (putOn(row, col, currentPlayer)) {
 // Invoke the callback:
 if (grid[row][col] == CROSS) {
 MyTriangle triangle(
 leftTopCorner
 + Coordinate((row * (size / 3)) + (size / 6),
 (col * (size / 3)) + (size / 6), 0),
 size / 4, 0);
 //				QVector<QPointF> path = triangle.getPath();
 QVector<QPointF> path;
 path.append(QPointF(100, 100));
 path.append(QPointF(70, 200));
 path.append(QPointF(130, 200));
 path.append(QPointF(100, 100));
 for (const auto &point : path) {
 std::cout << std::endl << point.x() << ", " << point.y()
 << std::flush;
 }
 cout << endl << "before" << flush;
 onMove(row, col, currentPlayer, path);
 cout << endl << "after" << flush;
 }

 if (grid[row][col] == CIRCLE) {
 Circle circle(
 leftTopCorner
 + Coordinate((row * size / 3) + size / 6,
 (col * size / 3) + size / 6, 0),
 size / 8);
 circle.setPainterTransform([](QPainter &painter) { // @suppress("Invalid arguments")
 QPen pen(Qt::PenStyle::SolidLine);
 pen.setWidth(1);
 pen.setColor(QColor(0, 0, 0));
 painter.setPen(pen);
 });

 auto path = circle.getPath(3);
 for (const auto &point : path) {
 std::cout << std::endl << point.x() << ", " << point.y()
 << std::flush;
 }
 onMove(row, col, currentPlayer, path);
 }
 ++movesCount;
 }

 cout << endl << "moved mouse" << flush;

 // Check for a winner:
 HolderState winner = isGameFinished();
 if (winner != EMPTY) {
 std::cout << "\nPlayer " << (winner == CROSS ? "X" : "O")
 << " wins!\n" << std::flush;
 return true;
 }

 // If all 9 moves have been made, it's a draw:
 if (movesCount == 9) {
 std::cout << "\nDraw! No more moves possible.\n" << std::flush;
 return true;
 }

 // Switch player:
 currentPlayer = (currentPlayer == CROSS ? CIRCLE : CROSS);
 }

 // (Unreachable)
 return false;
 }
 */

void TTT::draw(QPainter &painter) const {
	painter.save();

	QPen pen(Qt::PenStyle::DotLine);
	pen.setWidth(1);
	pen.setColor(QColor(0, 0, 0));
	painter.setPen(pen);

	painter.drawLine(
			QPoint(leftTopCorner.X() + (1 * size) / 3, leftTopCorner.Y()),
			QPoint(leftTopCorner.X() + (1 * size) / 3,
					leftTopCorner.Y() + size));
	painter.drawLine(
			QPoint(leftTopCorner.X() + (2 * size) / 3, leftTopCorner.Y()),
			QPoint(leftTopCorner.X() + (2 * size) / 3,
					leftTopCorner.Y() + size));
	painter.drawLine(
			QPoint(leftTopCorner.X(), leftTopCorner.Y() + (1 * size) / 3),
			QPoint(leftTopCorner.X() + size,
					leftTopCorner.Y() + (1 * size) / 3));
	painter.drawLine(
			QPoint(leftTopCorner.X(), leftTopCorner.Y() + (2 * size) / 3),
			QPoint(leftTopCorner.X() + size,
					leftTopCorner.Y() + (2 * size) / 3));

	painter.setPen(Qt::PenStyle::SolidLine);

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (grid[i][j] == CROSS) {
				MyTriangle triangle(
						leftTopCorner
								+ Coordinate((i * size / 3) + size / 6,
										(j * size / 3) + size / 6, 0), size / 4,
						0);
				triangle.draw(painter, TOP_VIEW);
			}

			if (grid[i][j] == CIRCLE) {
				Circle circle(
						leftTopCorner
								+ Coordinate((i * size / 3) + size / 6,
										(j * size / 3) + size / 6, 0),
						size / 8);
				circle.setPainterTransform([](QPainter &painter) { // @suppress("Invalid arguments")
					QPen pen(Qt::PenStyle::SolidLine);
					pen.setWidth(1);
					pen.setColor(QColor(0, 0, 0));
					painter.setPen(pen);
				});
				circle.draw(painter, SIDE_VIEW);
			}
		}
	}

	painter.restore();
}

void TTT::processUserMove(Coordinate point) {
	if (!isGameOn)
		return;

	// Convert point to grid coordinates
	int row = static_cast<int>(std::floor(
			(point - leftTopCorner).X() / (size / 3)));
	int col = static_cast<int>(std::floor(
			(point - leftTopCorner).Y() / (size / 3)));

	cout << endl << "Selected cell: " << row << ", " << col << flush;

	// Validate move
	if (row < 0 || row > 2 || col < 0 || col > 2) {
		cout << endl << "Invalid move: Out of bounds" << flush;
		emit moveRequested(currentPlayer); // Request move again
		return;
	}

	if (grid[row][col] != EMPTY) {
		cout << endl << "Invalid move: Cell occupied" << flush;
		emit moveRequested(currentPlayer); // Request move again
		return;
	}

	// Place the piece
	putOn(row, col, currentPlayer);

	// Generate drawing trajectory
	QVector<QPointF> trajectory;
	if (currentPlayer == CROSS) {
		MyTriangle triangle(
				leftTopCorner
						+ Coordinate((row * size / 3) + size / 6,
								(col * size / 3) + size / 6, 0), size / 4, 0);
		trajectory = triangle.getPath();
	} else {
		Circle circle(
				leftTopCorner
						+ Coordinate((row * size / 3) + size / 6,
								(col * size / 3) + size / 6, 0), size / 8);
		circle.setPainterTransform([](QPainter &painter) {
			QPen pen(Qt::PenStyle::SolidLine);
			pen.setWidth(1);
			pen.setColor(QColor(0, 0, 0));
			painter.setPen(pen);
		});
		trajectory = circle.getPath(3);
	}

	// Notify about placed piece
	emit piecePlaced(row, col, currentPlayer, trajectory);
	movesCount++;

	// Check game status
	HolderState winner = isGameFinished();
	if (winner != EMPTY) {
		emit gameFinished(winner);
		cout << endl << "game finished" << flush;
		isGameOn = false;
		return;
	}

	if (movesCount == 9) {
		emit gameFinished(EMPTY);
		isGameOn = false;
		return;
	}

	// Switch players
	currentPlayer = (currentPlayer == CROSS) ? CIRCLE : CROSS;
	emit moveRequested(currentPlayer);
}

void TTT::setIsGameOn(bool isGameOn) {
	this->isGameOn = isGameOn;
}
