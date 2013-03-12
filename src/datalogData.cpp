/*
 * datalogData.cpp
 *
 *  Created on: Jun 10, 2009
 *      Author: brent
 */
#include "datalogData.h"
#include "wx/arrstr.h"
#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!

WX_DEFINE_OBJARRAY(DatalogStoreRows);
WX_DEFINE_OBJARRAY(DatalogChannels);
WX_DEFINE_OBJARRAY(DatalogChannelTypes);
WX_DEFINE_OBJARRAY(ViewChannels);
WX_DEFINE_OBJARRAY(DatalogSnapshots);

DatalogChannelType::DatalogChannelType(wxString newName, wxString newUnitsLabel, int newSmoothingLevel, double newMinValue, double newMaxValue, size_t precision) :
	name(newName), unitsLabel(newUnitsLabel), smoothingLevel(newSmoothingLevel), minValue(newMinValue), maxValue(newMaxValue), precision(precision)
{ }

DatalogChannel::DatalogChannel(wxString newName, int newTypeId, wxString newDescription, bool en) :
	name(newName), typeId(newTypeId), sampleRate(0), description(newDescription), enabled(en)
{ }

DatalogChannel::DatalogChannel() :
	name(""), typeId(UNDEFINED_TYPE), sampleRate(0), description(""), enabled(true)
{ }

int DatalogChannelUtil::FindChannelIdByName(DatalogChannels &channels, wxString &name){

	size_t count = channels.Count();

	for (size_t i = 0; i < count; i++){
		if (name == channels[i].name) return i;
	}
	return -1;
}

int DatalogChannelUtil::FindChannelTypeIdByName(DatalogChannelTypes &channelTypes, wxString &name){
	size_t count = channelTypes.Count();

	for (size_t i = 0; i < count; i++){
		if (name == channelTypes[i].name) return i;
	}
	return -1;
}
