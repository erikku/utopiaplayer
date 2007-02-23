#ifndef __iPodNode_h__
#define __iPodNode_h__

#include <QtCore/QObject>

class QFile;

class iPodNode : public QObject
{
	Q_OBJECT

public:
	iPodNode(QObject *parent = 0) : QObject(parent) { };
	virtual ~iPodNode() { };

	virtual quint32 type() const = 0;
	virtual bool read(QFile* file) = 0;
};

#endif // __iPodNode_h__
