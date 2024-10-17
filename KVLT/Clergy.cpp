#include "Clergy.h"

Clergy::Clergy(){
	_countClergy = 200;
}

int Clergy::GetClergyCount()
{
	return _countClergy;
}

json Clergy::toJson() const
{
	return json{ {"CountClergy", _countClergy}};
}

Clergy Clergy::fromJson(const json& _filename)
{
	return Clergy(_filename["CountClergy"]);
}