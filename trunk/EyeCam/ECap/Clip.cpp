#include "stdafx.h"
#include "Clip.h"

using namespace std;
using namespace xercesc;

const char* Clip::XML_DOC_TYPE = "Range";

const char* Clip::XML_META_VERISON = "Version";
const char* Clip::XML_META_COPYRIGHT = "Copyright";
const char* Clip::XML_META_AUTHOR = "Author";
const char* Clip::XML_META_CREATE_TIME = "CreateTime";

const char* Clip::CONST_VERSION = "1.0.0";
const char* Clip::CONST_COPYRIGHT = "EyeCam";

const char* Clip::XML_TAG_CLIP = "Clip";
const char* Clip::XML_TAG_IMAGE = "Image";
const char* Clip::XML_TAG_NAME = "Name";
const char* Clip::XML_TAG_ROW = "Row";
const char* Clip::XML_TAG_COLUMN = "Column";

Clip::Clip()
{
	m_currentRow = m_currentColumn = 0;
	m_baseName = _T("RGB");
	m_basePath = _T("_capture/");
	m_fileExt = _T("jpg");
	m_manifect = _T("manifect.xml");
}

Clip::~Clip(void)
{
}

CString Clip::GetCurrentImageName()
{
	CString str;
	str.Format("%s_%04d_%04d.%s", m_baseName, m_currentRow, m_currentColumn, m_fileExt);
	return str;
}

CString Clip::GetCurrentImagePath()
{
	CString str;
	str.Format("%s%s", m_basePath, GetCurrentImageName());
	return str;
}

CString Clip::GetManifectName()
{
	return m_manifect;
}


CString Clip::GetManifectPath()
{
	CString str;
	str.Format("%s%s", m_basePath, GetManifectName());
	return str;
}

void Clip::NextRow()
{
	m_currentRow++;
}

void Clip::NextColumn()
{
	m_currentColumn++;
}

void Clip::Clear()
{
	m_currentRow = m_currentColumn = 0;
}


#if !defined(MAX_XMLCH_LENGTH)
  #define MAX_XMLCH_LENGTH 2560
#endif

static XMLCh* transcode(const char* toTranscode, XMLCh* dst)
{
	XMLString::transcode(toTranscode, dst, MAX_XMLCH_LENGTH);
	return dst;
}

bool Clip::WriteManifest()
{
	namespace X = xercesc;

	XMLCh buf[MAX_XMLCH_LENGTH + 1];
	DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation(
						transcode(Clip::XML_DOC_TYPE, buf));
	X::DOMDocument* doc = impl->createDocument(NULL, buf, NULL);
	DOMElement* root = doc->getDocumentElement();

	DOMElement* version = doc->createElement(transcode(Clip::XML_META_VERISON, buf));
	version->setTextContent(transcode(Clip::CONST_VERSION, buf));
	root->appendChild(version);

	DOMElement* copyright = doc->createElement(transcode(Clip::XML_META_COPYRIGHT, buf));
	copyright->setTextContent(transcode(Clip::CONST_COPYRIGHT, buf));
	root->appendChild(copyright);

	DOMElement* author = doc->createElement(transcode(Clip::XML_META_AUTHOR, buf));
	CString computerName = SystemHelper::GetPCName();
	string computerNameStr = CStringConverter::CString2String(computerName);
	author->setTextContent(transcode(computerNameStr.c_str(), buf));
	root->appendChild(author);

	DOMElement* createTime = doc->createElement(transcode(Clip::XML_META_CREATE_TIME, buf));
	CTime time = CTime::GetCurrentTime();
	CString timeCStr = TimeStringConverter::Time2CString(time);
	string timeStr = CStringConverter::CString2String(timeCStr);
	createTime->setTextContent(transcode(timeStr.c_str(), buf));
	root->appendChild(createTime);


	DOMElement* clipItem = doc->createElement(transcode(Clip::XML_TAG_CLIP, buf));
	root->appendChild(clipItem);

	for (int i = 0; i < 10; i++) {
		DOMElement* element = doc->createElement(transcode(Clip::XML_TAG_IMAGE, buf));
		clipItem->appendChild(element);

		// image name:
		{
			DOMElement* name = doc->createElement(transcode(Clip::XML_TAG_NAME, buf));
			element->appendChild(name);

			string str = StringFormatter::Format("Image_%04d", i);
			name->setTextContent(transcode(str.c_str(), buf));
		}
		
		// row index:
		{
			DOMElement* row = doc->createElement(transcode(Clip::XML_TAG_ROW, buf));
			element->appendChild(row);
			
			string str = StringFormatter::Format("%04d", i);
			row->setTextContent(transcode(str.c_str(), buf));
		}
		
		// column index:
		{
			DOMElement* column = doc->createElement(transcode(Clip::XML_TAG_COLUMN, buf));
			element->appendChild(column);

			string str = StringFormatter::Format("%04d", i);
			column->setTextContent(transcode(str.c_str(), buf));
		}
	}

	// serialize:
	DOMLSSerializer* serializer = impl->createLSSerializer();
	serializer->getDomConfig()->setParameter(transcode("format-pretty-print", buf), true);

	CString file = GetManifectPath();
	string strFile = CStringConverter::CString2String(file);
	XMLFormatTarget* formatTarget = new LocalFileFormatTarget(transcode(strFile.c_str(), buf));
	DOMLSOutput* output = impl->createLSOutput();

	output->setByteStream(formatTarget);

	try {
		// do the serialization through DOMLSSerializer::write();
		serializer->write(doc, output);
	}
	catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Exception message is: \n"
			<< message << "\n";
		XMLString::release(&message);
		return false;
	}
	catch (const DOMException& toCatch) {
		char* message = XMLString::transcode(toCatch.msg);
		cout << "Exception message is: \n"
			<< message << "\n";
		XMLString::release(&message);
		return false;
	}
	catch (...) {
		cout << "Unexpected Exception \n" ;
		return false;
	}


	// done with the document, must call release() to release the entire document resources
	doc->release();
	serializer->release();
	output->release();
	SafeDelete(formatTarget);
	
	return true;
}

bool Clip::ReadManifest()
{
	namespace X = xercesc;
	XMLCh buf[MAX_XMLCH_LENGTH + 1];

	XercesDOMParser* parser = new XercesDOMParser();
	parser->setValidationScheme(XercesDOMParser::Val_Always);
	parser->setDoNamespaces(true);

	CString file = GetManifectPath();
	string strFile = CStringConverter::CString2String(file);
	
	X::DOMDocument* doc = NULL;
	try {
		parser->parse(strFile.c_str());
		doc = parser->getDocument();

		DOMElement* root = doc->getDocumentElement();
		ASSERT(XMLString::compareString(root->getNodeName(), transcode(Clip::XML_DOC_TYPE, buf)) == 0);
		
		DOMElement* clip = (DOMElement*)root->getElementsByTagName(transcode(Clip::XML_TAG_CLIP, buf))->item(0);

		DOMNodeList* images = clip->getElementsByTagName(transcode(Clip::XML_TAG_IMAGE, buf));
		for (XMLSize_t i = 0; i < images->getLength(); i++) {
			DOMElement* image = (DOMElement*)images->item(i);

			DOMElement* name = (DOMElement*)image->getElementsByTagName(transcode(Clip::XML_TAG_NAME, buf))->item(0);
			const XMLCh* cName = name->getTextContent();

			DOMElement* row = (DOMElement*)image->getElementsByTagName(transcode(Clip::XML_TAG_ROW, buf))->item(0);
			const XMLCh* cRow = row->getTextContent();

			DOMElement* column = (DOMElement*)image->getElementsByTagName(transcode(Clip::XML_TAG_COLUMN, buf))->item(0);			
			const XMLCh* cColumn = column->getTextContent();
		}
		
	} catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Exception message is: \n"
			<< message << "\n";
		XMLString::release(&message);
		return false;
	} catch (const DOMException& toCatch) {
		char* message = XMLString::transcode(toCatch.msg);
		cout << "Exception message is: \n"
			<< message << "\n";
		XMLString::release(&message);
		return false;
	} catch (...) {
		cout << "Unexpected Exception \n" ;
		return false;
	}
	
	doc->release();	
	SafeDelete(parser);
	return true;
}

#if defined(MAX_XMLCH_LENGTH)
  #undef MAX_XMLCH_LENGTH
#endif
