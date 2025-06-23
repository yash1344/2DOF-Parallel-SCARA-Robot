/*
 * TTT.h
 *
 *  Created on: Jun 4, 2025
 *      Author: vagha
 */

#ifndef TTT_H_
#define TTT_H_
#include <qobject.h>
#include <qpainter.h>
#include <iostream>
#include <functional>
#include <optional>

#include "Coordinate.h"
enum HolderState {
	CROSS, CIRCLE, EMPTY
};

class TTT: public QObject {
Q_OBJECT
private:
	bool isGameOn = false;
	Coordinate leftTopCorner;
	float size;
	HolderState grid[3][3];
	HolderState currentPlayer = CROSS;
	int movesCount = 0;

	HolderState isGameFinished() const;
	bool putOn(int row, int col, HolderState piece);

signals:
	void moveRequested(HolderState player);
	void gameFinished(HolderState winner);
	void piecePlaced(int row, int col, HolderState state,
			QVector<QPointF> trajectory);

public slots:
	void processUserMove(Coordinate point);

public:
	explicit TTT(Coordinate leftTopCorner, float size,
			QObject *parent = nullptr);
	virtual ~TTT();
	const HolderState* getGrid() const;
	float getSize() const;
	void setSize(float size);

//	bool startGame(std::function<std::optional<Coordinate>()> forMove,
//			std::function<void(int, int, HolderState, QVector<QPointF>)> onMove);
	void startGame();
	void draw(QPainter &painter) const;
	void setIsGameOn(bool isGameOn);
};

#endif /* TTT_H_ */
