#pragma once

#include "./json/json.h"
#include "./json/config.h"
#include "./json/assertions.h"
#include "./json/autolink.h"
#include "./json/features.h"
#include "./json/forwards.h"
#include "./json/reader.h"
#include "./json/value.h"
#include "./json/version.h"
#include "./json/writer.h"
#include <QtCore/qstring.h>
#include <QtCore/qvector.h>
#include "../dudu.h"

namespace QTDUDU
{
	class JSON_API CJSONUtils
	{
	public:
		static void		encode	(const Json::Value &json, QString &strJson);
		static BOOLEAN	decode	(const QString &strJson, Json::Value &json);

		static QString		getStrValue		(const char *pcKey, const Json::Value &json);
		static void			getStrAryValue	(const char *pcKey, const Json::Value &json, QVector<QString>& aryOutStrs);
		static BOOLEAN		getBoolValue	(const char *pcKey, const Json::Value &json);
		static INT			getIntValue		(const char *pcKey, const Json::Value &json);
		static UINT			getUIntValue	(const char *pcKey, const Json::Value &json);
		static DOUBLE		getDoubleValue	(const char *pcKey, const Json::Value &json);
		static Json::Value	getJsonValue	(const char *pcKey, const Json::Value &json);
		static void			getJsonAryValue	(const char *pcKey, const Json::Value &json, QVector<Json::Value>& aryOutJsons);

		static QString		getStrValue		(const QString &strKey, const Json::Value &json);
		static void			getStrAryValue	(const QString &strKey, const Json::Value &json, QVector<QString>& aryOutStrs);
		static BOOLEAN		getBoolValue	(const QString &strKey, const Json::Value &json);
		static INT			getIntValue		(const QString &strKey, const Json::Value &json);
		static UINT			getUIntValue	(const QString &strKey, const Json::Value &json);
		static DOUBLE		getDoubleValue	(const QString &strKey, const Json::Value &json);
		static Json::Value	getJsonValue	(const QString &strKey, const Json::Value &json);
		static void			getJsonAryValue	(const QString &strKey, const Json::Value &json, QVector<Json::Value>& aryOutJsons);

		static void		setStrValue		(Json::Value &json, const char *pcKey, const QString &strValue);
		static void		setBoolValue	(Json::Value &json, const char *pcKey, BOOLEAN bValue);
		static void		setIntValue		(Json::Value &json, const char *pcKey, INT iValue);
		static void		setIntAryValue	(Json::Value &json, const char *pcKey, QVector<INT> &aryInt);
		static void		setUIntValue	(Json::Value &json, const char *pcKey, UINT uiValue);
		static void		setUintAryValue	(Json::Value &json, const char *pcKey, QVector<UINT> &aryUint);
		static void		setDoubleValue	(Json::Value &json, const char *pcKey, DOUBLE dValue);
		static void		setStrAryValue	(Json::Value &json, const char *pcKey, QVector<QString> &aryStr);
		static void		setJsonValue	(Json::Value &json, const char *pcKey, Json::Value &jsonValue);
		static void		setJsonAryValue	(Json::Value &json, const char *pcKey, QVector<Json::Value> &aryJson);

		static void		setStrValue		(Json::Value &json, const QString &strKey, const QString &strValue);
		static void		setBoolValue	(Json::Value &json, const QString &strKey, BOOLEAN bValue);
		static void		setIntValue		(Json::Value &json, const QString &strKey, INT iValue);
		static void		setIntAryValue	(Json::Value &json, const QString &strKey, QVector<INT> &aryInt);
		static void		setUIntValue	(Json::Value &json, const QString &strKey, UINT uiValue);
		static void		setUintAryValue	(Json::Value &json, const QString &strKey, QVector<UINT> &aryUint);
		static void		setDoubleValue	(Json::Value &json, const QString &strKey, DOUBLE dValue);
		static void		setStrAryValue	(Json::Value &json, const QString &strKey, QVector<QString> &aryStr);
		static void		setJsonValue	(Json::Value &json, const QString &strKey, Json::Value &jsonValue);
		static void		setJsonAryValue	(Json::Value &json, const QString &strKey, QVector<Json::Value> &aryJson);

		static BOOLEAN	hasProperty		(const char *pcKey, const Json::Value &json);
		static BOOLEAN	hasProperty		(const QString &strKey, const Json::Value &json);

		static QString	toString		(const Json::Value &json);
		static char* QStringToCharPointer(const QString& str);
	};
}
