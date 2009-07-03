/*
 * datalogStore.h
 *
 *  Created on: May 19, 2009
 *      Author: brent
 */

#ifndef DATALOGSTORE_H_
#define DATALOGSTORE_H_

#include "wx/wxprec.h"
#include "sqlite3.h"
#include "exceptions.h"
#include "wx/ffile.h"
#include "logging.h"
#include "wx/dynarray.h"
#include "datalogData.h"


class DatastoreException : public RuntimeException{
public:
	DatastoreException(wxString msg, int errorCode):RuntimeException(msg),m_errorCode(errorCode) {
		VERBOSE(FMT("DatastoreException thrown- code %d; message: %s",GetErrorCode(),GetMessage().ToAscii()));
	}
	int GetErrorCode(){return m_errorCode;}

private:
	int m_errorCode;
};


class DatalogStore {

public:

	static const int TIMEPOINT_REST = -1;

	DatalogStore();
	~DatalogStore();
	void Open(wxString filePath);
	void Close();
	void CreateNew(wxString filePath);
	wxString GetFileName();
	bool IsOpen();
	void ImportDatalog(const wxString &filePath, const wxString &name, const wxString &notes);

	void ReadDatalogInfo(int datalogId, int &timeOffset, wxString &name, wxString &notes);
	void ReadChannels(DatalogChannels &channels);
	void ReadChannelTypes(DatalogChannelTypes &channelTypes);
	void ReadDatalog(DatalogStoreRows &data, int datalogId, wxArrayString &names, int fromTimePoint, int toTimepoint = TIMEPOINT_REST);
	void ReadDatalogIds(wxArrayInt &data);

	void GetChannelNames(wxArrayString &channelNames);
	void GetChannelTypes(DatalogChannelTypes &channelTypes);
	void GetChannels(DatalogChannels &channels);
	void ClearChannelTypes();
	void ClearChannels();
	void ImportChannels(DatalogChannels &channels);
	void ImportChannelTypes(DatalogChannelTypes &channelTypes);
	void GetDatalogHeaders(wxArrayString &headers, wxFFile &file);

private:

	void SetFilename(wxString name);
	void CreateTables();
	size_t ReadLine(wxString &buffer, wxFFile &file);
	size_t ExtractValues(wxArrayString &valueList, wxString &line);

	void InsertDatalogRow(sqlite3_stmt *query, int id, int timePoint, wxArrayString &values);
	void AddMissingChannels(wxArrayString &channelNames);
	bool ChannelExists(wxArrayString &existingChannels, wxString &channelName);
	void AddDatalogChannel(wxString &channelName, int typeId);
	sqlite3_stmt * CreateDatalogInsertPreparedStatement(wxArrayString &headers);
	int GetTopDatalogId();
	int GetTopTimePoint();

	bool m_isOpen;
	sqlite3 *m_db;
	wxString m_datastoreName;


};

#endif /* DATALOGSTORE_H_ */