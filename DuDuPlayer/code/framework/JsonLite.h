#ifndef _JSON_ENCODER_
#define _JSON_ENCODER_
#pragma onece
#include "./jsoncpp/CJSONUtils.h"

namespace QTDUDU {
	
	class JsonLite;
    class CJSONUtils;

	template<class T>
	class JsonArray {
	public:
		explicit JsonArray(const QVector<T>& arr)
			: mJson(Json::arrayValue) {
			for (int i = 0; i < arr.size(); ++i) {
				JsonLite obj = toJson(&arr[i]);
				mJson.append((Json::Value)obj);
			}
		}

		const QString& toString() {
            QTDUDU::CJSONUtils::encode(mJson, mJsonStr);
			return mJsonStr;
		}

		operator Json::Value() {
			return mJson;
		}

		const Json::Value& getJson() const{
			return mJson;
		}

	private:
		Json::Value mJson;
		QString mJsonStr;
	};

	class JsonLite {
	public:
		JsonLite () : mJson(Json::objectValue){

		}

		JsonLite(const Json::Value& value)
		: mJson(value)
		, mCanDecode(true) {

		}

		JsonLite(const QString& data) 
			: mJson(Json::objectValue)
			, mCanDecode(false) {
			mCanDecode = CJSONUtils::decode(data, mJson);
		}

		void add(const char* key, int val) {
			mJson[key] = val;
		}

		void add(const char* key, const char* val) {
			mJson[key] = val;
		}

		void add(const char* key, const QString& val) {
			CJSONUtils::setStrValue(mJson, key, val);
		}

		void add(const char* key, QVector<QString> &val) {
			CJSONUtils::setStrAryValue(mJson, key, val);
		}

		template<class T>
		void add(const char* key, const QVector<T>& val);

		void add(const char* key, QVector<int>& val) {
			CJSONUtils::setIntAryValue(mJson, key, val);
		}

		void add(const char* key, unsigned int val) {
			CJSONUtils::setUIntValue(mJson, key, val);
		}

		void add(const char* key, QVector<unsigned int>& val) {
			CJSONUtils::setUintAryValue(mJson, key, val);
		}

		void add(const char* key, bool val) {
			CJSONUtils::setBoolValue(mJson, key, val);
		}

		void add(const char* key, double val) {
			CJSONUtils::setDoubleValue(mJson, key, val);
		}

		void add(const char* key, Json::Value& val) {
			CJSONUtils::setJsonValue(mJson, key, val);
		}

		void add(const char* key, QVector<Json::Value>& val) {
			CJSONUtils::setJsonAryValue(mJson, key, val);
		}

		template<class T> void add(const char* key, const JsonArray<T> val) {
			//Json::Value& json = (Json::Value)val;
			mJson[key] = val.getJson();
		}

		const QString& toString() {
			CJSONUtils::encode(mJson, mJsonStr);
			return mJsonStr;
		}

		///
		bool isValid() const {
			return (mCanDecode && !mJson.isNull());
		}

		bool hasProperty(const char* key) const {
			return mJson.isMember(key);
		}

		QString getStrValue(const char* key) const {
			Json::Value jsonRet;
			if (!hasProperty(key))
			{
				return STRING_NULL;
			}
			jsonRet = mJson[key];
			return CJSONUtils::toString(jsonRet);
		}

		void getStrArrayValue(const char* key, QVector<QString>& val) const {
			if (!hasProperty(key)) {
				return;
			}

			if (mJson[key].isArray()) {
				INT iSize = mJson[key].size();
				for (INT iIndex = 0; iIndex < iSize; ++iIndex) {
					val.push_back(CJSONUtils::toString(mJson[key][iIndex]));
				}
			}
		}

		bool getBoolValue(const char* key) const {
			if (!hasProperty(key)) return false;
			if (mJson[key].isConvertibleTo(Json::booleanValue))
				return mJson[key].asBool();
			else
				return false;
		}

		int getIntValue(const char* key) const {
			int val = 0;
			if (hasProperty(key) && mJson[key].isConvertibleTo(Json::intValue)) {
				val = mJson[key].asInt();
			}
			return val;
		}

		unsigned int getUIntValue(const char* key) const {
			unsigned int val = 0;
			if (hasProperty(key) && mJson[key].isConvertibleTo(Json::uintValue)) {
				val = mJson[key].asUInt();
			}
			return val;
		}

		double getDoubleValue(const char* key) const {
			double val = 0.0;
			if (hasProperty(key) && mJson[key].isConvertibleTo(Json::realValue)) {
				val = mJson[key].asDouble();
			}
			return val;
		}

		Json::Value getJsonValue(const char* key) const {
			if (hasProperty(key) && mJson[key].isConvertibleTo(Json::objectValue))
				return mJson[key];
			else
				return Json::Value::null;
		}

		void getJsonArrayValue(const char* key, QVector<JsonLite>& val) const {
			if (hasProperty(key) && mJson[key].isArray()) {
				int size = mJson[key].size();
				for (int i = 0; i < size; ++i) {
					if (mJson[key][i].isConvertibleTo(Json::objectValue))
						val.push_back(JsonLite(mJson[key][i]));
				}
			}
		}

		///
		operator Json::Value() {
			return mJson;
		}

	private:
		Json::Value mJson;
		bool mCanDecode;
		QString mJsonStr;
	};


	typedef JsonLite JsonObject;

	template<class T> JsonObject toJson(const T* t);
	/*class CData_ProfileSearchListItem;
	class CData_ServiceSearchListItem;
	class CData_PairedDeviceListItem;
	template<> QString toJson<CData_ProfileSearchListItem>(const CData_ProfileSearchListItem* t);
	template<> QString toJson<CData_ServiceSearchListItem>(const CData_ServiceSearchListItem* t);
	template<> QString toJson<CData_PairedDeviceListItem>(const CData_PairedDeviceListItem* t);*/

}
#endif
