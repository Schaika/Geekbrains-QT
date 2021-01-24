#ifndef QTEXTEDIT_CUSTOM_H
#define QTEXTEDIT_CUSTOM_H

#include "filestatus.h"

#include <QTextEdit>
class QTextEdit_custom : public QTextEdit
{
	Q_OBJECT
public:
	explicit QTextEdit_custom(QWidget *parent = nullptr);
	explicit QTextEdit_custom(const QString &text, QWidget *parent = nullptr);
	filestatus filestatus;
};

#endif // QTEXTEDIT_CUSTOM_H
