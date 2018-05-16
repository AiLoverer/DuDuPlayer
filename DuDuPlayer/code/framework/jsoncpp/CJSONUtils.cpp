#include "../dudu.h"
#include "CJSONUtils.h"
#include <stdio.h>
#include <string>
namespace QTDUDU
{
	#define CJSONUTILS_BUFFER_RATIO (4)

	char* CJSONUtils::QStringToCharPointer(const QString& str)
	{
        QByteArray br = str.toUtf8();
        char* data = new char[br.size()+1];
        strcpy(data,br.data());
		data[br.size()] = 0;

        return data;
	}

	void CJSONUtils::encode( const Json::Value& jsonValue, QString& strOut )
	{
		Json::FastWriter jsonWriter;
		std::string strJson = jsonWriter.write( jsonValue );
		strOut = QString::fromUtf8(strJson.c_str());
	}

	BOOLEAN CJSONUtils::decode( const QString& strJson, Json::Value& jsonOut )
	{
		Json::Reader jsonReader(Json::Features::strictMode());

		char* pcBuffer = QStringToCharPointer(strJson);
		BOOLEAN bRet = jsonReader.parse( pcBuffer, jsonOut );
        delete[] pcBuffer;
		return bRet;
	}

	QString CJSONUtils::getStrValue( const char* pcKey, const Json::Value& jsonValue )
	{
		Json::Value jsonRet;
		if (!CJSONUtils::hasProperty(pcKey, jsonValue))
		{
			return STRING_NULL;
		}
		jsonRet = jsonValue[pcKey];
		return toString(jsonRet);
	}

	void CJSONUtils::getStrAryValue( const char* pcKey, const Json::Value& json, QVector<QString>& aryOutStrs )
	{
		if (!CJSONUtils::hasProperty(pcKey, json))
		{
			return ;
		}
		
		if (json[pcKey].isArray())
		{
			INT iSize = json[pcKey].size();

			for ( INT iIndex = 0; iIndex < iSize; ++iIndex )
			{
				QString *strValue = new QString(toString(json[pcKey][iIndex]));
				aryOutStrs.push_back(*strValue);
			}
		}
	}

	BOOLEAN CJSONUtils::getBoolValue( const char* pcKey, const Json::Value& jsonValue )
	{
		if (!CJSONUtils::hasProperty(pcKey, jsonValue))
		{
			return FALSE;
		}
		if (jsonValue[pcKey].isConvertibleTo(Json::booleanValue))
		{
			return jsonValue[pcKey].asBool();
		}
		else
		{
			return FALSE;
		}
	}

	INT CJSONUtils::getIntValue( const char* pcKey, const Json::Value& jsonValue )
	{
		if (!CJSONUtils::hasProperty(pcKey, jsonValue))
		{
			return 0;
		}
		if (jsonValue[pcKey].isConvertibleTo(Json::intValue))
		{
			return jsonValue[pcKey].asInt();
		}
		else
		{
			return 0;
		}
	}

	UINT CJSONUtils::getUIntValue( const char* pcKey, const Json::Value& jsonValue )
	{
		if (!CJSONUtils::hasProperty(pcKey, jsonValue))
		{
			return 0;
		}
		if (jsonValue[pcKey].isConvertibleTo(Json::uintValue))
		{
			return jsonValue[pcKey].asUInt();
		}
		else
		{
			return 0;
		}
	}

	DOUBLE CJSONUtils::getDoubleValue( const char* pcKey, const Json::Value& jsonValue )
	{
		if (!CJSONUtils::hasProperty(pcKey, jsonValue))
		{
			return 0.0;
		}
		if (jsonValue[pcKey].isConvertibleTo(Json::realValue))
		{
			return jsonValue[pcKey].asDouble();
		}
		else
		{
			return 0.0;
		}
	}

	Json::Value CJSONUtils::getJsonValue( const char* pcKey, const Json::Value& jsonValue )
	{
		if (jsonValue[pcKey].isConvertibleTo(Json::objectValue))
		{
			return jsonValue[pcKey];
		}
		else
		{
			return Json::Value::null;
		}
	}

	void CJSONUtils::getJsonAryValue( const char* pcKey, const Json::Value& json, QVector<Json::Value>& aryOutJsons )
	{
		if (!CJSONUtils::hasProperty(pcKey, json))
		{
			return ;
		}

		if (json[pcKey].isArray())
		{
			INT iSize = json[pcKey].size();

			for ( INT iIndex = 0; iIndex < iSize; ++iIndex )
			{
				if (json[pcKey][iIndex].isConvertibleTo(Json::objectValue))
				{
					aryOutJsons.push_back( json[pcKey][iIndex] );
				}
				else
				{
					aryOutJsons.push_back( Json::Value::null );
				}
			}
		}
	}

	QString CJSONUtils::getStrValue( const QString& strKey, const Json::Value& json )
	{
		char* pcKey = QStringToCharPointer(strKey);
		return getStrValue( pcKey, json );

		delete[] pcKey;
	}

	void CJSONUtils::getStrAryValue( const QString& strKey, const Json::Value& json, QVector<QString>& aryOutStrs )
	{
		char* pcKey = QStringToCharPointer(strKey);
		getStrAryValue( pcKey, json, aryOutStrs );

		delete[] pcKey;
	}

	BOOLEAN CJSONUtils::getBoolValue( const QString& strKey, const Json::Value& json )
	{
		char* pcKey = QStringToCharPointer(strKey);
		BOOLEAN ret =  getBoolValue( pcKey, json );
		delete[] pcKey;
		return ret;
	}

	INT CJSONUtils::getIntValue ( const QString& strKey, const Json::Value& json )
	{
		char* pcKey = QStringToCharPointer(strKey);
		INT ret =  getIntValue( pcKey, json );
		delete[] pcKey;
		return ret;
	}

	UINT CJSONUtils::getUIntValue( const QString& strKey, const Json::Value& json )
	{
		char* pcKey = QStringToCharPointer(strKey);
		UINT ret =  getUIntValue( pcKey, json );
		delete[] pcKey;
		return ret;
	}

	DOUBLE CJSONUtils::getDoubleValue( const QString& strKey, const Json::Value& json )
	{
		char* pcKey = QStringToCharPointer(strKey);
		DOUBLE dRet = getDoubleValue( pcKey, json );
		delete[] pcKey;
		return dRet;
	}

	Json::Value CJSONUtils::getJsonValue( const QString& strKey, const Json::Value& json )
	{
		char* pcKey = QStringToCharPointer(strKey);
		Json::Value dRet = getJsonValue( pcKey, json );
		delete[] pcKey;
		return dRet;
	}

	void CJSONUtils::getJsonAryValue( const QString& strKey, const Json::Value& json, QVector<Json::Value>& aryOutJsons )
	{
		char* pcKey = QStringToCharPointer(strKey);
		getJsonAryValue( pcKey, json, aryOutJsons );
		delete[] pcKey;
	}

	void CJSONUtils::setStrValue(Json::Value &json, const char *pcKey, const QString &strValue)
	{
		char* pcData = QStringToCharPointer(strValue);
		json[pcKey] = pcData;

		delete[] pcData;
	}

	void CJSONUtils::setBoolValue(Json::Value &json, const char *pcKey, BOOLEAN bValue)
	{
		json[pcKey] = bValue;
	}

	void CJSONUtils::setIntValue(Json::Value &json, const char *pcKey, INT iValue)
	{
		json[pcKey] = iValue;
	}

	void CJSONUtils::setIntAryValue(Json::Value &json, const char *pcKey, QVector<INT> &aryInt)
	{
		Json::Value jsonAry(Json::arrayValue);
		for (INT i = 0; i < aryInt.size(); ++i)
		{
			jsonAry.append(aryInt[i]);
		}
		json[pcKey] = jsonAry;
	}

	void CJSONUtils::setUIntValue(Json::Value &json, const char *pcKey, UINT uiValue)
	{
		json[pcKey] = uiValue;
	}

	void CJSONUtils::setDoubleValue(Json::Value &json, const char *pcKey, DOUBLE dValue)
	{
		json[pcKey] = dValue;
	}

	void CJSONUtils::setStrAryValue(Json::Value &json, const char *pcKey, QVector<QString> &aryStr)
	{
		INT uiBufferLen = 0;
		for (INT i = 0; i < aryStr.size(); ++i)
		{
			INT uiStrLen = aryStr[i].length();
			if (uiBufferLen < uiStrLen)
			{
				uiBufferLen = uiStrLen;
			}
		}
		char* pcData;
		Json::Value jsonAry(Json::arrayValue);
		for (INT i = 0; i < aryStr.size(); ++i)
		{
			pcData = QStringToCharPointer(aryStr[i]);
			jsonAry.append(pcData);
		}
		json[pcKey] = jsonAry;

		delete[] pcData;
	}

	void CJSONUtils::setUintAryValue(Json::Value &json, const char *pcKey, QVector<UINT> &aryUint)
	{
		Json::Value jsonAry(Json::arrayValue);
		for (INT i = 0; i < aryUint.size(); ++i)
		{
			jsonAry.append(aryUint[i]);
		}
		json[pcKey] = jsonAry;
	}

	void CJSONUtils::setJsonValue(Json::Value &json, const char *pcKey, Json::Value &jsonValue)
	{
		json[pcKey] = jsonValue;
	}

	void CJSONUtils::setJsonAryValue(Json::Value &json, const char *pcKey, QVector<Json::Value> &aryJson)
	{
		Json::Value jsonAry(Json::arrayValue);
		for (INT i = 0; i < aryJson.size(); ++i)
		{
			jsonAry.append(aryJson[i]);
		}
		json[pcKey] = jsonAry;
	}

	void CJSONUtils::setStrValue(Json::Value &json, const QString &strKey, const QString &strValue)
	{
		char* pcKey = QStringToCharPointer(strKey);
		setStrValue(json, pcKey, strValue);

		delete[] pcKey;
	}

	void CJSONUtils::setBoolValue(Json::Value &json, const QString &strKey, BOOLEAN bValue)
	{
		char* pcKey = QStringToCharPointer(strKey);
		setBoolValue(json, pcKey, bValue);

		delete[] pcKey;
	}

	void CJSONUtils::setIntValue(Json::Value &json, const QString &strKey, INT iValue)
	{
		char* pcKey = QStringToCharPointer(strKey);
		setIntValue(json, pcKey, iValue);

		delete[] pcKey;
	}

	void CJSONUtils::setIntAryValue(Json::Value &json, const QString &strKey, QVector<INT> &aryInt)
	{
		char* pcKey = QStringToCharPointer(strKey);
		setIntAryValue(json, pcKey, aryInt);

		delete[] pcKey;
	}

	void CJSONUtils::setUIntValue(Json::Value &json, const QString &strKey, UINT uiValue)
	{
		char* pcKey = QStringToCharPointer(strKey);
		setUIntValue(json, pcKey, uiValue);

		delete[] pcKey;
	}
	
	void CJSONUtils::setDoubleValue(Json::Value &json, const QString &strKey, DOUBLE dValue)
	{
		char* pcKey = QStringToCharPointer(strKey);
		setDoubleValue(json, pcKey, dValue);

		delete[] pcKey;
	}

	void CJSONUtils::setStrAryValue	(Json::Value &json, const QString &strKey, QVector<QString> &aryStr)
	{
		char* pcKey = QStringToCharPointer(strKey);
		setStrAryValue(json, pcKey, aryStr);

		delete[] pcKey;
	}

	void CJSONUtils::setUintAryValue(Json::Value &json, const QString &strKey, QVector<UINT> &aryUint)
	{
		char* pcKey = QStringToCharPointer(strKey);
		setUintAryValue(json, pcKey, aryUint);

		delete[] pcKey;
	}

	void CJSONUtils::setJsonValue(Json::Value &json, const QString &strKey, Json::Value &jsonValue)
	{
		char* pcKey = QStringToCharPointer(strKey);
		setJsonValue(json, pcKey, jsonValue);

		delete[] pcKey;
	}

	void CJSONUtils::setJsonAryValue(Json::Value &json, const QString &strKey, QVector<Json::Value> &aryJson)
	{
		char* pcKey = QStringToCharPointer(strKey);
		setJsonAryValue(json, pcKey, aryJson);

		delete[] pcKey;
	}

	BOOLEAN	CJSONUtils::hasProperty(const char *pcKey, const Json::Value &json)
	{
		return json.isMember(pcKey);
	}

	BOOLEAN CJSONUtils::hasProperty( const QString& strKey, const Json::Value& json )
	{
		char* pcKey = QStringToCharPointer(strKey);
		BOOLEAN bRet = hasProperty( pcKey, json );
		delete[] pcKey;
		return bRet;
	}

	QString CJSONUtils::toString(const Json::Value &json)
	{
		if (json.isConvertibleTo(Json::stringValue))
		{
			std::string strJson = json.asString();
			QString strRet = QString::fromUtf8(strJson.c_str());
			return strRet;
		}
		else
		{
			return "";
		}
	}
}
