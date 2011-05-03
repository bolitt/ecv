#ifndef Clip_h__
#define Clip_h__

#pragma once

class ClipImage
{
public:
	CString m_name;
	CString m_row;
	CString m_column;
};

class Clip
{
public:
	Clip();
	virtual ~Clip();

protected:
	CString m_baseName;
	CString m_basePath;
	CString m_fileExt;
	CString m_manifect;
	
public:
	int m_currentRow;
	int m_currentColumn;
	CString m_width;
	CString m_height;

public:
	CString GetCurrentImageName();
	CString GetCurrentImagePath();
	CString GetManifectPath();
	CString GetManifectName();
	void NextRow();
	void NextColumn();
	void Clear();

	bool WriteManifest();
	bool ReadManifest();

public:
	const static char* XML_DOC_TYPE;
	
	const static char* XML_META_VERISON;
	const static char* XML_META_COPYRIGHT;
	const static char* XML_META_AUTHOR;
	const static char* XML_META_CREATE_TIME;
	
	const static char* CONST_VERSION;
	const static char* CONST_COPYRIGHT;

	const static char* XML_TAG_CLIP;
	const static char* XML_TAG_IMAGE;
	const static char* XML_TAG_NAME;
	const static char* XML_TAG_ROW;
	const static char* XML_TAG_COLUMN;
};

#endif // Clip_h__
