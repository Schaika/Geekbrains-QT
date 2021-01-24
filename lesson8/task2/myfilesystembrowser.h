#ifndef MYFILESYSTEMBROWSER_H
#define MYFILESYSTEMBROWSER_H

#include <QWidget>
#include <QGridLayout>
#include <QTreeView>
#include <QComboBox>
#include <QPushButton>
#include <QStandardItemModel>
#include <QApplication>
#include <QLineEdit>
#include <QThread>
#include <QLabel>
#include <QPaintEvent>
#include "searchthread.h"
class MyFileSystemBrowser : public QWidget
{
	Q_OBJECT
public:
	explicit MyFileSystemBrowser(QWidget *parent = nullptr,QStandardItemModel *model = nullptr);
	void clearTree();
	QStandardItemModel *getCurrentModel() const{
			return model;
		}
	void setModel(QStandardItemModel *newModel);
	void rebuildModel(QString str);
private:
	QGridLayout *gridLayout;
	QTreeView *treeView;
	QComboBox *rootSelection;
	QPushButton *rootPath;
	QPushButton *backButton;
	QPushButton *stop_reset;
	QLineEdit *pathLine;
	QLineEdit *searchLine;
	SearchThread *Search;
	QWidget *pathbutton;
	QList<QStandardItem*> searchResults;
	bool showingResults = false;
	QLabel *curSearchPath;
private slots:
	void diskChange(int index);
	void mainPath();
	void itemSelected(const QModelIndex &index);
	void enterSubDir(const QModelIndex &index);
	void userpathchange();
	void goUpDir();
	void doSearch();
	void addResult(QStandardItem*);
	void stopSearch();
	void searchEnded();
	void updateCurrentFolder(QString);
private:
	QStandardItemModel *model;
	QString currentPath;
protected:
	void paintEvent(QPaintEvent *event) override;
signals:

};

#endif // MYFILESYSTEMBROWSER_H
