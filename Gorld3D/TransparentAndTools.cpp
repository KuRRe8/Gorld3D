#include "TransparentAndTools.h"

TransparentAndTools::TransparentAndTools(QLayout* parent)
{
	Q_ASSERT(getMainWindow());

	tools_widget = new QWidget(getMainWindow());
	tools_widget->setFixedWidth(60);
	QPalette pa1(tools_widget->palette());
	pa1.setColor(QPalette::Background, Qt::white);
	tools_widget->setAutoFillBackground(true);
	tools_widget->setPalette(pa1);
	
	//new
	QVBoxLayout* vLayout = new QVBoxLayout(tools_widget);

	select_pushbutton = new QPushButton(Q_NULLPTR);
	move_pushbutton = new QPushButton(Q_NULLPTR);
	scale_pushbutton = new QPushButton(Q_NULLPTR);
	rotate_pushbutton = new QPushButton(Q_NULLPTR);
	duplicate_pushbutton = new QPushButton(Q_NULLPTR);
	sink_pushbutton = new QPushButton(Q_NULLPTR);
	zoom_pushbutton = new QPushButton(Q_NULLPTR);
	translation_pushbutton = new QPushButton(Q_NULLPTR);
	mainview_pushbutton = new QPushButton(Q_NULLPTR);
	orthogonalview_pushbutton = new QPushButton(Q_NULLPTR);


	QPushButton *allSelect = new QPushButton;

	allSelect->setStyleSheet("QPushButton{border-image: url(:/1.png) 0 0 0 0;border:none;color:rgb(255, 255, 255);}"
		"QPushButton:hover{background-color: rgb(20, 62, 134);border:none;color:rgb(255, 255, 255);}"
		"QPushButton:checked{background-color: rgb(20, 62, 134);border:none;color:rgb(255, 255, 255);}");

	select_pushbutton->setFixedSize(QSize(36, 36));
	move_pushbutton->setFixedSize(QSize(36, 36));
	scale_pushbutton->setFixedSize(QSize(36, 36));
	rotate_pushbutton->setFixedSize(QSize(36, 36));
	duplicate_pushbutton->setFixedSize(QSize(36, 36));
	sink_pushbutton->setFixedSize(QSize(36, 36));
	zoom_pushbutton->setFixedSize(QSize(36, 36));
	translation_pushbutton->setFixedSize(QSize(36, 36));
	mainview_pushbutton->setFixedSize(QSize(36, 36));
	orthogonalview_pushbutton->setFixedSize(QSize(36, 36));

	select_pushbutton->setIcon(QIcon(".//icons//window//pointer_icon_unactivated.png"));
	select_pushbutton->setIconSize(QSize(36, 36));
	move_pushbutton->setIcon(QIcon(".//icons//window//move_icon_activated.png"));
	move_pushbutton->setIconSize(QSize(36, 36));
	scale_pushbutton->setIcon(QIcon(".//icons//window//scale_icon_unactivated.png"));
	scale_pushbutton->setIconSize(QSize(36, 36));
	rotate_pushbutton->setIcon(QIcon(".//icons//window//rotate_icon_unactivated.png"));
	rotate_pushbutton->setIconSize(QSize(36, 36));
	duplicate_pushbutton->setIcon(QIcon(".//icons//window//duplicate_icon_unactivated.png"));
	duplicate_pushbutton->setIconSize(QSize(36, 36));
	sink_pushbutton->setIcon(QIcon(".//icons//window//sink_icon_activated.png"));
	sink_pushbutton->setIconSize(QSize(36, 36));
	zoom_pushbutton->setIcon(QIcon(".//icons//window//zoom_icon_activated.png"));
	zoom_pushbutton->setIconSize(QSize(36, 36));
	translation_pushbutton->setIcon(QIcon(".//icons//window//translation_icon_unactivated.png"));
	translation_pushbutton->setIconSize(QSize(36, 36));
	mainview_pushbutton->setIcon(QIcon(".//icons//window//mainview_icon_activated.png"));
	mainview_pushbutton->setIconSize(QSize(36, 36));
	orthogonalview_pushbutton->setIcon(QIcon(".//icons//window//orthogonal_icon_activated.png"));
	orthogonalview_pushbutton->setIconSize(QSize(36, 36));

	///
	vLayout->addWidget(select_pushbutton);
	vLayout->addWidget(move_pushbutton);
	vLayout->addWidget(scale_pushbutton);
	vLayout->addWidget(rotate_pushbutton);
	vLayout->addWidget(duplicate_pushbutton);
	vLayout->addWidget(sink_pushbutton);
	vLayout->addWidget(zoom_pushbutton);
	vLayout->addWidget(translation_pushbutton);
	vLayout->addWidget(mainview_pushbutton);
	vLayout->addWidget(orthogonalview_pushbutton);

	tools_widget->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint);
	parent->addWidget(tools_widget);
}

TransparentAndTools::~TransparentAndTools()
{

}

///void TransparentAndTools::paintEvent(QPaintEvent* event)
///{
///	QPainter painter(this);
///	QPen pen;
///	pen.setColor(QColor(255, 255, 255, 0));
///	painter.setPen(pen);
///	painter.setBrush(QBrush(QColor(255, 255, 255, 0)));
///	painter.drawRect(rect());
///	return QWidget::paintEvent(event);
///}

void TransparentAndTools::on_select_pushbutton_clicked()
{

}
void TransparentAndTools::on_move_pushbutton_clicked()
{

}
void TransparentAndTools::on_scale_pushbutton_clicked()
{

}
void TransparentAndTools::on_rotate_pushbutton_clicked()
{

}
void TransparentAndTools::on_duplicate_pushbutton_clicked()
{

}
void TransparentAndTools::on_sink_pushbutton_clicked()
{

}
void TransparentAndTools::on_zoom_pushbutton_clicked()
{

}
void TransparentAndTools::on_translation_pushbutton_clicked()
{

}
void TransparentAndTools::on_mainview_pushbutton_clicked()
{

}
void TransparentAndTools::on_orthogonalview_pushbutton_clicked()
{

}
