//
// Created by keyner on 9/14/21.
//

#ifndef SERVERBREAKOUT_JSONMANAGEMENT_H
#define SERVERBREAKOUT_JSONMANAGEMENT_H

#include <iostream>
#include "../../lib/rapidjson/stringbuffer.h"
#include "../../lib/rapidjson/stringbuffer.h"
#include "../../lib/rapidjson/writer.h"
#include "../../lib/rapidjson/document.h"
#include "TypeMessage.h"

using namespace rapidjson;
using namespace std;

class JSON_Management {
public:

    /**
     * @brief Method that gets the key searched from the JSON.
     * @param key the string that gets searched
     * @param jsonString  the JSON where the search is done
     * @return the string key from the JSON.
     */
    static string GetJSONString(string key, const string &jsonString) {
        rapidjson::Document document;
        document.Parse<kParseDefaultFlags>(jsonString.c_str());
        const char *searchedString;
        if (document.HasMember(key.c_str())) {
            if (document[key.c_str()].IsString()) {
                searchedString = document[key.c_str()].GetString();
                return searchedString;
            }
        } else {
            cout << "ERROR : KEY NOT FOUND" << endl;
            return " ";

        }
    }

    static string GetJSONStringArray(string key, const string &jsonString) {
        rapidjson::Document document;
        document.Parse<kParseDefaultFlags>(jsonString.c_str());
        const char *searchedString;
        if (document.HasMember(key.c_str())) {
            if (document[key.c_str()].IsString()) {
                searchedString = document[key.c_str()].GetString();
                return searchedString;
            }
        } else {
            cout << "ERROR : KEY NOT FOUND" << endl;
            return " ";

        }
    }

    /**
   * @brief Method that serializes a TypeMessage.h method to a JSON string
   * @param typemessageObject is the TypeMessage.h object that contains all the information
   * @return the serialized object into a JSON string
   */
    static string TypeMessageToJSON(TypeMessage *message) {
        Document json_document;
        StringBuffer buffer;

        Document::AllocatorType &allocator = json_document.GetAllocator();

        Writer<rapidjson::StringBuffer> writer(buffer);

        writer.StartObject();

        writer.Key("Matrix");
        writer.String(message->getMatrix().c_str());

        writer.EndObject();

        return buffer.GetString();
    }

};


#endif //SERVERBREAKOUT_JSONMANAGEMENT_H
