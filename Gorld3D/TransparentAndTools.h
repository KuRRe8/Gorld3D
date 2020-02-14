#pragma once
#include "__Utilities.h"
#include <qpushbutton.h>
#include <qstackedlayout.h>
#include <qpainter.h>

//do not inherit from qwidget

class TransparentAndTools
{
public:
	TransparentAndTools(QLayout* parent);
	~TransparentAndTools();

private:
	QWidget* tools_widget;
	QPushButton* select_pushbutton;
	QPushButton* move_pushbutton;
	QPushButton* scale_pushbutton;
	QPushButton* rotate_pushbutton;
	QPushButton* duplicate_pushbutton;
	QPushButton* sink_pushbutton;
	QPushButton* zoom_pushbutton;
	QPushButton* translation_pushbutton;
	QPushButton* mainview_pushbutton;
	QPushButton* orthogonalview_pushbutton;

protected:
	///void paintEvent(QPaintEvent * event)Q_DECL_OVERRIDE;

	public slots:
	void on_select_pushbutton_clicked();
	void on_move_pushbutton_clicked();
	void on_scale_pushbutton_clicked();
	void on_rotate_pushbutton_clicked();
	void on_duplicate_pushbutton_clicked();
	void on_sink_pushbutton_clicked();
	void on_zoom_pushbutton_clicked();
	void on_translation_pushbutton_clicked();
	void on_mainview_pushbutton_clicked();
	void on_orthogonalview_pushbutton_clicked();

};