#ifndef __ImportExportInterface_h__
#define __ImportExportInterface_h__

#include "PluginInterface.h"

class QAction;

class ImportExportInterface : public PluginInterface
{
	Q_OBJECT

public:
	ImportExportInterface(QObject *parent = 0, const QStringList& args = QStringList()) : PluginInterface(parent, args) { };
	virtual ~ImportExportInterface() {};

	virtual QAction* importAction() { return 0; };
	virtual QAction* exportAction() { return 0; };

	virtual QString    pluginName() const = 0;
	virtual PluginType pluginType() { return ImportExportPlugin; };

public slots:
	virtual void doImport() = 0;
	virtual void doExport() = 0;
};

Q_DECLARE_INTERFACE(ImportExportInterface, "com.emotionalcoder.UtopiaPlayer.ImportExportInterface/0.1")

#endif // __ImportExportInterface_h__
