#pragma once

#include <QtWidgets/QWidget>
#include <QPainter>
#include <QPixmap>
#include <QImage>
#include <QTextEdit>

#include "ui_MainWidget.h"
#include "Solver/utils.hpp"
#include "Solver/solver.hpp"

#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080
#define BTN_WIDTH 150
#define BTN_HEIGHT 30

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = Q_NULLPTR);

	void mousePressEvent(QMouseEvent *event);

	void paintEvent(QPaintEvent *);

private:
    Ui::MainWidgetClass ui;

	// Point data
	std::vector<Point> pts;

	// display
	QPixmap* screen;
	QPainter* screen_painter;

	QTextEdit* random_pnum_text;

public slots:
	void ClearPoints();

	void SolveAndOutput();

	void GenerateRandomPoints();
};
