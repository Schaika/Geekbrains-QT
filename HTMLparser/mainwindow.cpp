#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	{
		handler = new HTMLhandler(this);

		QGridLayout* gridLayout = new QGridLayout;
		scrollArea = new QScrollArea;
		scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		scrollArea->verticalScrollBar();
		gridLayout->addWidget(scrollArea,1,0,9,10);
		imagesContainer = new QGridLayout;
		placeholderWgtScrollArea = new QWidget(scrollArea);

		placeholderWgtScrollArea->setLayout(imagesContainer);
		scrollArea->setWidget(placeholderWgtScrollArea);
		searchbtn = new QPushButton("Search!",this);
		gridLayout->addWidget(searchbtn,0,9,1,1);
		connect(searchbtn,SIGNAL(released()),this,SLOT(doSearch()));

		imagesToShow = new QSpinBox(this);
		imagesToShow->setMaximum(50);
		imagesToShow->setMinimum(1);
		imagesToShow->setValue(3);
		imagesToShow->setToolTip("How many images to show? (1-50)");
		gridLayout->addWidget(imagesToShow,0,8,1,1);

		inputText = new QLineEdit(this);
		gridLayout->addWidget(inputText,0,0,1,8);
		connect(inputText,SIGNAL(returnPressed()),this,SLOT(doSearch()));

		QWidget *wgt = new QWidget(this);
		setCentralWidget(wgt);
		wgt->setLayout(gridLayout);
		placeholderWgtScrollArea->resize(scrollArea->width()-20,this->height());
	}

MainWindow::~MainWindow()
	{

	}

void MainWindow::paintEvent(QPaintEvent* event)
	{
		Q_UNUSED(event)
		placeholderWgtScrollArea->resize(scrollArea->width()-20,rows*270);
	}

void MainWindow::clearList()
	{
		QLayoutItem *child;
		while ((child = imagesContainer->takeAt(0)) != 0) {
			delete child;
		}
	}

void MainWindow::doSearch()
	{
		handler->getHTML(inputText->text(),imagesToShow->value());
		QStringList list = handler->getListOfImages();
		clearList();
		placeholderWgtScrollArea = new QWidget(scrollArea);
		placeholderWgtScrollArea->setLayout(imagesContainer);
		scrollArea->setWidget(placeholderWgtScrollArea);
		int i,x,y;
		for (i = 0; i<list.count(); i++) {
			y=i/3;
			x=i-3*y;
			FrameWgt *item = new FrameWgt(i,list.at(i));
			imagesContainer->addWidget(item,y,x);
		}
		rows = i/3+1;
	}

