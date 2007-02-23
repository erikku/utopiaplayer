#include "ipodplugin.h"
#include "ipod.h"

#include <QtGui/QAction>

Q_EXPORT_PLUGIN2(ipodplugin, iPodPlugin)

iPodPlugin::iPodPlugin(QObject *parent, const QStringList& args) : DeviceInterface(parent, args)
{
	//mDevices << new iPod("/home/eric/ipod/image", this);
	mDevices << new iPod("/media/utopia/Music", this);
	emit deviceAdded( mDevices.at(0) );
};

iPodPlugin::~iPodPlugin()
{
};

QList<QTreeWidgetItem*> iPodPlugin::deviceItems() const
{
	QList<QTreeWidgetItem*> list;

	for(int i = 0; i < mDevices.count(); i++)
	{
		list << mDevices.at(i)->baseItem();
	}

	return list;
};

QList<QAction*> iPodPlugin::contextMenu(QTreeWidgetItem *device, QTreeWidgetItem *item) const
{
	QList<QAction*> list;

	Device *dev = 0;
	for(int i = 0; i < mDevices.count(); i++)
	{
		if(mDevices.at(i)->baseItem() == device)
		{
			dev = mDevices.at(i);
		}
	}

	if(dev)
		list << dev->contextMenu(item);

	return list;
};

QString iPodPlugin::pluginName() const
{
	return tr("iPod");
};

QList<Device*> iPodPlugin::devices() const
{
	QList<Device*> devices;

	foreach(Device *device, mDevices)
	{
		devices << device;
	}

	return devices;
};

void iPodPlugin::refreshDeviceList()
{
};
