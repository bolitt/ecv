#ifndef Converter_h__
#define Converter_h__


class TimeStringConverter
{
public:
	static CString Time2CString(CTime& time)
	{
		CString str = time.Format("%Y-%m-%d %H:%M:%S");
		return str;
	}
	static CTime CString2Time(CString& str)
	{
		COleDateTime   tm;   
		tm.ParseDateTime(str);   
		SYSTEMTIME   st;   
		tm.GetAsSystemTime(st);   
		CTime ct(st);
		return ct;
	}
};

class CStringConverter
{
public:
	static std::string CString2String(CString& cstr)
	{
		std::string str = cstr.GetBuffer(0);
		cstr.ReleaseBuffer();
		return str;
	}

	static CString String2CString(std::string& str)
	{
		CString cstr;
		cstr.Format("%s", str);
		return cstr;
	}
};

template<class tstring, size_t nBufferSize=2560> 
class _TStringFormatter 
{
public:
	static tstring Format(const TCHAR*   szFormat, ...) 
	{ 
		TCHAR szBuffer[nBufferSize+1] = _T(""); 
		va_list argList;
		va_start(argList, szFormat); 
		_vsnprintf(szBuffer, nBufferSize, szFormat, argList); 
		va_end(argList);
		return szBuffer; 
	} 
	/*
	static tstring Get(long nValue) 
	{ 
		TCHAR szBuffer[nBufferSize+1] = _T(""); 
		_sntprintf(szBuffer, nBufferSize, "%ld ", nValue); 
		return szBuffer; 
	} */
};

typedef _TStringFormatter<std::string> StringFormatter;
typedef _TStringFormatter<std::wstring> WStringFormatter;

template<int nBufferSize = 2560>
class _SystemHelper
{
public:
	static CString GetPCName()
	{
		TCHAR cpt[nBufferSize + 1];
		ZeroMemory(cpt, nBufferSize + 1);
		DWORD dwRet = nBufferSize;
		BOOL ret = GetComputerName(cpt, &dwRet);
		return ret ? CString(cpt) : CString();
	}
};

typedef _SystemHelper<> SystemHelper;

#endif // Converter_h__