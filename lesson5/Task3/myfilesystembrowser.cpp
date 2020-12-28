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
		gridLayout->addWidget(treeView,1,0,10,10);
		setMinimumSize(320,480);
		pathLine = new QLineEdit(this);
		connect(pathLine, SIGNAL(returnPressed()), this, SLOT(userpathchange()));
		gridLayout->addWidget(pathLine,0,2,1,7);
		backButton = new QPushButton(this);
		backButton->setText("<-");
		connect(backButton, SIGNAL(clicked()), this, SLOT(goUpDir()));
		gridLayout->addWidget(backButton,0,9,1,1);
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
		  } else {
			  rootPath = new QPushButton(this);
			  rootPath->setText("/");
			  gridLayout->addWidget(rootPath, 0, 0, 1, 2);
			  connect(rootPath, SIGNAL(clicked()), this, SLOT(mainPath()));
			  rebuildModel("/");
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
		{
		   currentPath = str;
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
		QString a = model->item(0)->child(index.row())->text();
		pathLine->setText(currentPath + a);
	}

void MyFileSystemBrowser::enterSubDir(const QModelIndex& index)
	{
		QString tmppath = currentPath;
		QString a = model->item(0)->child(index.row())->text();

		if (a == ".."){
			int from = currentPath.lastIndexOf('/');
			int to = currentPath.lastIndexOf("/",from-1);
				if (from != -1 && to != -1)	tmppath.chop(from-to);
		}else{
			tmppath += a+"/";
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
