#ifndef __QDarkPlastiqueStyle_h__
#define __QDarkPlastiqueStyle_h__

#include <QtGui/QPlastiqueStyle>

class QDarkPlastiqueStyle : public QPlastiqueStyle
{
	Q_OBJECT

public:
	QDarkPlastiqueStyle();

	virtual QPalette standardPalette() const;
};

#endif // __QDarkPlastiqueStyle_h__
