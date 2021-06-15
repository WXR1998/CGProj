#include <stdlib.h>
#include <iostream>
#include <string>
#include <cctype>
#include <time.h>

#include <QPushButton>
#include <QTextEdit>
#include <QMouseEvent>
#include <QDebug>
#include <QPen>
#include "MainWidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

	// set widget size
	this->setFixedSize(WIN_WIDTH, WIN_HEIGHT);

	screen = new QPixmap(WIN_WIDTH, WIN_HEIGHT);
	screen->fill(Qt::white);

	screen_painter = new QPainter(screen);

	QPushButton* solve_button = new QPushButton("Solve", this); solve_button->resize(BTN_WIDTH, BTN_HEIGHT);
	QPushButton* clear_button = new QPushButton("Clear", this); clear_button->resize(BTN_WIDTH, BTN_HEIGHT); clear_button->move(BTN_WIDTH, 0);
	random_pnum_text = new QTextEdit(this); random_pnum_text->resize(BTN_WIDTH, BTN_HEIGHT); random_pnum_text->move(2 * BTN_WIDTH, 0);
	QPushButton* random_gen_button = new QPushButton("Random Generation", this); random_gen_button->resize(BTN_WIDTH + 60, BTN_HEIGHT); random_gen_button->move(3 * BTN_WIDTH, 0);

	connect(clear_button, &QPushButton::clicked, this, &MainWidget::ClearPoints);
	connect(solve_button, &QPushButton::clicked, this, &MainWidget::SolveAndOutput);
	connect(random_gen_button, &QPushButton::clicked, this, &MainWidget::GenerateRandomPoints);
}


void MainWidget::mousePressEvent(QMouseEvent *event)
{
	QPoint pos = event->pos();
	int x = pos.x() % 2 == 0 ? pos.x() : pos.x() + 1;
	int y = pos.y() % 2 == 0 ? pos.y() : pos.y() + 1;
	Point pt = Point(x, y);
	pts.push_back(pt);

	QPen pen(Qt::red);
	pen.setWidth(10);
	screen_painter->setPen(pen);
	screen_painter->drawPoint(QPoint(x, y));
	printf("pts size: %zd\n", pts.size());
	this->update();
}

void MainWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawPixmap(0, 0, *screen);
}

void MainWidget::ClearPoints()
{
	screen->fill(Qt::white);
	screen_painter->drawPixmap(0, 0, *screen);
	pts.clear();
	this->update();
	printf("pts size: %zd\n", pts.size());
}

void MainWidget::SolveAndOutput()
{
	// solve 
	printf("print points:\n");
	for (auto p : pts)
	{
		p.print();
	}
	// using solver (with bug on Win 10)
	//RectAnnulusSolver solver = RectAnnulusSolver(pts);
	//Annulus result = solver.solve();
	//printf("solved\n");

	// manually define the result
	Annulus result;
	result.setPoints(Point(300, 400), Point(400, 500));
	result.setRects(Rect(500, 500, 600, 600), Rect(300, 300, 700, 700));
	result.setType(NORMAL);

	// draw result
	QPen pen(Qt::green);
	pen.setWidth(10);
	screen_painter->setPen(pen);
	switch (result.type)
	{
	case L_SHAPED_1:
		screen_painter->drawLine(QPoint(result.a.x, result.a.y), QPoint(WIN_WIDTH - 1, result.a.y));
		screen_painter->drawLine(QPoint(result.a.x, result.a.y), QPoint(result.a.x, 0));
		screen_painter->drawLine(QPoint(result.b.x, result.b.y), QPoint(WIN_WIDTH - 1, result.b.y));
		screen_painter->drawLine(QPoint(result.b.x, result.b.y), QPoint(result.b.x, 0));
		break;
	case L_SHAPED_2:
		screen_painter->drawLine(QPoint(result.a.x, result.a.y), QPoint(0, result.a.y));
		screen_painter->drawLine(QPoint(result.a.x, result.a.y), QPoint(result.a.x, 0));
		screen_painter->drawLine(QPoint(result.b.x, result.b.y), QPoint(0, result.b.y));
		screen_painter->drawLine(QPoint(result.b.x, result.b.y), QPoint(result.b.x, 0));
		break;
	case L_SHAPED_3:
		screen_painter->drawLine(QPoint(result.a.x, result.a.y), QPoint(0, result.a.y));
		screen_painter->drawLine(QPoint(result.a.x, result.a.y), QPoint(result.a.x, WIN_HEIGHT - 1));
		screen_painter->drawLine(QPoint(result.b.x, result.b.y), QPoint(0, result.b.y));
		screen_painter->drawLine(QPoint(result.b.x, result.b.y), QPoint(result.b.x, WIN_HEIGHT - 1));
		break;
	case L_SHAPED_4:
		screen_painter->drawLine(QPoint(result.a.x, result.a.y), QPoint(WIN_WIDTH - 1, result.a.y));
		screen_painter->drawLine(QPoint(result.a.x, result.a.y), QPoint(result.a.x, WIN_HEIGHT - 1));
		screen_painter->drawLine(QPoint(result.b.x, result.b.y), QPoint(WIN_WIDTH - 1, result.b.y));
		screen_painter->drawLine(QPoint(result.b.x, result.b.y), QPoint(result.b.x, WIN_HEIGHT - 1));
		break;
	case STRIPE_HORIZONTAL:
		screen_painter->drawLine(QPoint(0, result.a.y), QPoint(WIN_WIDTH - 1, result.a.y));
		screen_painter->drawLine(QPoint(0, result.b.y), QPoint(WIN_WIDTH - 1, result.b.y));
		break;
	case STRIPE_VERTICAL:
		screen_painter->drawLine(QPoint(result.a.x, 0), QPoint(result.a.x, WIN_HEIGHT - 1));
		screen_painter->drawLine(QPoint(result.b.x, 0), QPoint(result.b.x, WIN_HEIGHT - 1));
		break;
	default:
		const Rect& inner = result.inner, &outer = result.outer;
		screen_painter->drawRect(inner.x1, inner.y1, inner.x2 - inner.x1, inner.y2 - inner.y1);
		screen_painter->drawRect(outer.x1, outer.y1, outer.x2 - outer.x1, outer.y2 - outer.y1);
		break;
	}

	this->update();
}

void MainWidget::GenerateRandomPoints()
{
	std::string str = random_pnum_text->toPlainText().toStdString();
	bool is_digit = true;
	for (auto c : str) {
		if (!std::isdigit(c)) {
			is_digit = false;
			break;
		}
	}
	if (!is_digit)
	{
		std::cerr << "Input text is not a number. Please input it again.\n";
		return;
	}
	
	int pnum = std::stoi(str);
	printf("Generating %d points randomly...\n");

	pts.clear();
	screen->fill(Qt::white);
	screen_painter->drawPixmap(0, 0, *screen);
	QPen pen(Qt::red);
	pen.setWidth(10);
	screen_painter->setPen(pen);
	srand((unsigned int)time(0));
	for (int i = 0; i < pnum; i++)
	{
		int x = rand() % WIN_WIDTH;
		int y = rand() % WIN_HEIGHT;
		x = x % 2 == 0 ? x : x + 1;
		y = y % 2 == 0 ? y : y + 1;
		
		screen_painter->drawPoint(x, y);
		pts.push_back(Point(x, y));
	}

	this->update();
}
