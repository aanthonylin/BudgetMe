#ifndef PRIVACYSETTINGSMODEL_H
#define PRIVACYSETTINGSMODEL_H

class PrivacySettingsModel
{
public:
	virtual ~PrivacySettingsModel(){}
	virtual int getPrivacyOption() = 0;
	virtual void setPrivacyOption(int) = 0;
};
#endif // PRIVACYSETTINGSMODEL_H
