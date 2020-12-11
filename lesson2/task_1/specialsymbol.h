#ifndef SPECIALSYMBOL_H
#define SPECIALSYMBOL_H
#include <QString>

class SpecialSymbol
{
	QString str = "";
	bool checkValid(QString *,qint32);
public:
	SpecialSymbol();
	bool changes(QString);
	QString getText();
};

#endif // SPECIALSYMBOL_H
