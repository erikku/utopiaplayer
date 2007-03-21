#ifndef __ComponentInterface_h__
#define __ComponentInterface_h__

class Component
{
public:
	virtual QIcon icon() const = { return QIcon() };
	virtual QString name() const = 0; // This looks something like: "Controls/Volume Slider"
	virtual QString version() const = 0;
	virtual QStringList authors() const = 0;
	virtual QString copyrightNotice() const = 0;

	virtual QPointer<QWidget*> aboutDialog() { return 0; } const;
	virtual bool hasAboutDialog() { return false; };

	virtual QPointer<QWidget*> configDialog() { return 0; } const;
	virtual bool hasConfigDialog() { return false; };

	virtual int maxInstances() { return 1 };
	virtual int minSubComponents() { return 0; };
	virtual int maxSubComponents() { return 0; };

	// If the component is not created, it should be created and then returned.
	virtual QPointer<QWidget*> widget(int instance = 0) const = 0;

	virtual bool isCompatible() { return (UTOPIAPLAYER_VERSION == utopiaplayer_version()); };
};

class ComponentInterface
{
public:
	virtual QIcon collectionIcon() const = { return QIcon() };
	virtual QString collectionName() const = 0;

	virtual QStringList avaliableComponents() const = 0;
	virtual Component component(const QString& name) const = 0;
};

#endif // __ComponentInterface_h__
