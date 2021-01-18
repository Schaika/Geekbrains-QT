#include "myfilesystembrowser.h"
#include <QDir>
MyFileSystemBrowser::MyFileSystemBrowser(QWidget* parent, QStandardItemModel* model) : QWidget(parent), model(model)
	{
		gridLayout = new QGridLayout(this);
		this->setLayout(gridLayout);
		treeView = new QTreeView(this);
		treeView->setHeaderHidden(true);
		treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
		connect(treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(itemSelected(QModelIndex)));
		connect(treeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(enterSubDir(QModelIndex)));
		gridLayout->addWidget(treeView,1,0,30,30);
		setMinimumSize(320,480);
		pathLine = new QLineEdit(this);
		connect(pathLine, SIGNAL(returnPressed()), this, SLOT(userpathchange()));
		gridLayout->addWidget(pathLine,0,2,1,27);
		backButton = new QPushButton(this);
		backButton->setText("<-");
		connect(backButton, SIGNAL(clicked()), this, SLOT(goUpDir()));
		gridLayout->addWidget(backButton,0,29,1,1);

		searchLine = new QLineEdit(this);
		connect(searchLine, SIGNAL(returnPressed()), this, SLOT(doSearch()));
		searchLine->setPlaceholderText(tr("Поиск..."));
		gridLayout->addWidget(searchLine,31,1,1,30);

		stop_reset = new QPushButton(this);
		stop_reset->setText("Stop");
		stop_reset->setMaximumWidth(45);
		stop_reset->setDisabled(true);
		connect(stop_reset, SIGNAL(clicked()), this, SLOT(stopSearch()));
		gridLayout->addWidget(stop_reset,31,0,1,1);

		curSearchPath = new QLabel("placeholder text",this);
		curSearchPath->setVisible(false);
		curSearchPath->setDisabled(true);
		curSearchPath->setAlignment(Qt::AlignRight);

		Search = new SearchThread;
		connect(Search, SIGNAL(found(QStandardItem*)), this, SLOT(addResult(QStandardItem*)));
		connect(Search, SIGNAL(searchEnded()), this, SLOT(searchEnded()));
		connect(Search, SIGNAL(updateCurrentFolder(QString)), this, SLOT(updateCurrentFolder(QString)));
		if(QSysInfo::productType() == "windows")
		  {
			  rootSelection = new QComboBox(this);
			  QFileInfoList list = QDir::drives();
			  QFileInfoList::const_iterator listdisk = list.begin();
			  int amount = list.count();
			  for (int i = 0; i < amount; i++)
			  {
				  rootSelection->addItem(listdisk->path());
				  listdisk++;
			  }
			  if (amount > 0)
			  {
				  rebuildModel(list.at(0).path());
			  }
			  gridLayout->addWidget(rootSelection, 0, 0, 1, 2);
			  connect(rootSelection, SIGNAL(activated(int)), this, SLOT(diskChange(int)));
			  pathbutton = rootSelection;
		  } else {
			  rootPath = new QPushButton(this);
			  rootPath->setText("/");
			  gridLayout->addWidget(rootPath, 0, 0, 1, 2);
			  connect(rootPath, SIGNAL(clicked()), this, SLOT(mainPath()));
			  rebuildModel("/");
			  pathbutton = rootPath;
		  }
	}


void MyFileSystemBrowser::setModel(QStandardItemModel* newModel)
	{
		treeView->setModel(newModel);
		treeView->expandAll();
		model = newModel;
	}

void MyFileSystemBrowser::rebuildModel(QString str)
	{
		showingResults = false;
		Search->stop();
		Search->terminate();
		Search->wait();
		stop_reset->setText(tr("Stop"));
		stop_reset->setDisabled(true);
		curSearchPath->setVisible(false);

		{
		   currentPath = str;
		   delete model;
		   QStandardItemModel *model = new QStandardItemModel(this);
		   QList<QStandardItem*> items;
		   items.append(new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DriveHDIcon)), str));
		   model->appendRow(items);


		   QDir dir(str);
		   dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Dirs);
		   QStringList list = dir.entryList();
		   int amount = list.count();
		   QList<QStandardItem*>folders;
		   for (int i = 0; i < amount; i++)
		   {
			   if (list.at(i)!="."){
			   QStandardItem* f = new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DirIcon)), list.at(i));
			   folders.append(f);
			   }
		   }

		   items.at(0)->appendRows(folders);

		   dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Files);
		   list = dir.entryList();
		   amount = list.count();
		   QList<QStandardItem*>files;
		   for (int i = 0; i < amount; i++)
		   {
			   QStandardItem* f = new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon)), list.at(i));
			   files.append(f);
		   }

		   items.at(0)->appendRows(files);
		   setModel(model);
		}
	}


void MyFileSystemBrowser::diskChange(int index)
	{
		QFileInfoList list = QDir::drives();
		rebuildModel(list.at(index).path());
	}

void MyFileSystemBrowser::mainPath()
	{
		rebuildModel("/");
	}

void MyFileSystemBrowser::itemSelected(const QModelIndex &index)
	{
		QString a;
		if (showingResults)
		{
			a = model->item(0)->child(index.row())->toolTip();
		}else{
			a = model->item(0)->child(index.row())->text();
		}
		pathLine->setText(a);
	}

void MyFileSystemBrowser::enterSubDir(const QModelIndex& index)
	{
		QString tmppath = currentPath;


		if (model->item(0)->child(index.row())->text() == ".."){
			int from = currentPath.lastIndexOf('/');
			int to = currentPath.lastIndexOf("/",from-1);
				if (from != -1 && to != -1)	tmppath.chop(from-to);
		}else{

			if (showingResults)
			{
				tmppath = model->item(0)->child(index.row())->toolTip()+"/";
			}else{
				tmppath += model->item(0)->child(index.row())->text()+"/";
			}

		}
		QFileInfo target(tmppath);
			if (target.isDir()){
				currentPath = tmppath;
				rebuildModel(currentPath);
				pathLine->setText(currentPath);
			}
	}

void MyFileSystemBrowser::userpathchange()
	{
		QString tmppath = pathLine->text();
			if (tmppath.back() != "/") tmppath.append("/");
		QFileInfo target(tmppath);
			if (target.isDir()){
				currentPath = tmppath;
				rebuildModel(currentPath);
				pathLine->setText(currentPath);
			}
	}

void MyFileSystemBrowser::goUpDir()
	{
		QString tmppath = currentPath;
			int from = currentPath.lastIndexOf('/');
			int to = currentPath.lastIndexOf("/",from-1);
			if (from != -1 && to != -1)	tmppath.chop(from-to);

		QFileInfo target(tmppath);
			if (target.isDir()){
				currentPath = tmppath;
				rebuildModel(currentPath);
				pathLine->setText(currentPath);
			}
	}

void MyFileSystemBrowser::doSearch()
	{
		Search->stop();
		Search->terminate();
		Search->wait();
		delete model;
		QStandardItemModel *model = new QStandardItemModel(this);
		searchResults.clear();
		searchResults.append(new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DriveHDIcon)), currentPath));
		model->appendRow(searchResults);
		setModel(model);
		showingResults = true;

		Search->setPath(currentPath);
		Search->whatToSearch(searchLine->text());
		Search->start();
		stop_reset->setText(tr("Stop"));
		stop_reset->setDisabled(false);
		curSearchPath->setVisible(true);
	}

void MyFileSystemBrowser::addResult(QStandardItem* f)
	{

		searchResults.at(0)->appendRow(f);
		//setModel(getCurrentModel());
	}

void MyFileSystemBrowser::stopSearch()
	{
		if (Search->isActive()){
		Search->stop();
		Search->terminate();
		Search->wait();

		stop_reset->setText(tr("Reset"));
		curSearchPath->setVisible(false);
		}else{
			showingResults = false;
			rebuildModel(currentPath);
			stop_reset->setText(tr("Stop"));
			stop_reset->setDisabled(true);
		}
	}

void MyFileSystemBrowser::searchEnded()
	{
		stop_reset->setText(tr("Reset"));
		curSearchPath->setVisible(false);
	}

void MyFileSystemBrowser::updateCurrentFolder(QString str)
	{
		curSearchPath->setText(str);
	}

void MyFileSystemBrowser::paintEvent(QPaintEvent* event)
	{
		Q_UNUSED(event)
		int ax = treeView->geometry().x()+3;
		int ay = searchLine->geometry().y()-searchLine->height()-3;
		int aw = treeView->width()-6;
		int ah = searchLine->height();
		curSearchPath->setGeometry(ax,ay,aw,ah);
	}
