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
	QLineEdit *pathLine;
private slots:
	void diskChange(int index);
	void mainPath();
	void itemSelected(const QModelIndex &index);
	void enterSubDir(const QModelIndex &index);
	void userpathchange();
	void goUpDir();
private:
	QStandardItemModel *model;
	QString currentPath;
signals:

};

#endif // MYFILESYSTEMBROWSER_H
