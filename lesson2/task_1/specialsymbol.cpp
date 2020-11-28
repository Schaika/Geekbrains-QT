#include "specialsymbol.h"
#include <QVector>

SpecialSymbol::SpecialSymbol()
	{
		str = "";
	}
QString SpecialSymbol::getText(){
		return str;
	}
bool SpecialSymbol::checkValid(QString * txt, qint32 from){
		bool valid = false;
		QString cut = "";
		qint32 to = txt->indexOf("#",from+2);
		if (to == -1) return valid;
		cut = txt->mid(from,to-from+1);
		QVector<QString> vec = {
			"#@C#","©",
			"#@RUB#","₽",
			"#@EUR#","€",
			"#@%%#","‰",
			"#@R#","®"

		};
		const int iterator = vec.indexOf(cut);
		if ( iterator != -1){
			txt->remove(from,vec.at(iterator).length());
			txt->insert(from,vec.at(iterator+1));
			valid = true;
		}
		return valid;
	}
bool SpecialSymbol::changes(QString txt){
		bool isChanged = false;
		qint32 index = 0;

		while (true){
		qint32 fnd = txt.indexOf("#@",index);
		if (fnd == -1) break;
		index = fnd + 1;
		isChanged = checkValid(&txt,fnd);
		}
		str = txt;
		return isChanged;
	}
