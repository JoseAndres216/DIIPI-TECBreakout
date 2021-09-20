//
// Created by keyner on 9/14/21.
//

#ifndef CLIENTBREAKOUT_JSONMANAGEMENT_H
#define CLIENTBREAKOUT_JSONMANAGEMENT_H

#include <iostream>
#include "../../lib/rapidjson/stringbuffer.h"
#include "../../lib/rapidjson/stringbuffer.h"
#include "../../lib/rapidjson/writer.h"
#include "../../lib/rapidjson/document.h"
#include "TypeMessage.h"

using namespace rapidjson;
using namespace std;

class JSON_Management{

public:

    /**
     * @brief Method that gets the key searched from the JSON.
     * @param key the string that gets searched
     * @param jsonString  the JSON where the search is done
     * @return the string key from the JSON.
     */
    static string GetJSONString(string key, const string& jsonString) {
        rapidjson::Document document;
        document.Parse<kParseDefaultFlags>(jsonString.c_str());
        const char* searchedString;
        if (document.HasMember(key.c_str())) {
            if (document[key.c_str()].IsString()) {
                searchedString = document[key.c_str()].GetString();
                return searchedString;
            }
        }
        else {
            cout << "ERROR : KEY NOT FOUND" << endl;
            return " ";

        }
    }

    /**
   * @brief Method that serializes a TypeMessage.h method to a JSON string
   * @param typemessageObject is the TypeMessage.h object that contains all the information
   * @return the serialized object into a JSON string
   */
    static string TypeMessageToJSON(TypeMessage* message){
        Document json_document;
        StringBuffer buffer;

        Document::AllocatorType& allocator = json_document.GetAllocator();

        Writer<rapidjson::StringBuffer> writer(buffer);

        writer.StartObject();

        writer.Key("App");
        writer.String(message->getAppName().c_str());

        writer.Key("Keyword");
        writer.String(message->getKeyWord().c_str());

        writer.Key("Path");
        writer.String(message->getPath().c_str());

        writer.Key("First_Time");
        writer.String(message->getFirstTime().c_str());

        writer.Key("Client_Type");
        writer.String(message->getClientType().c_str());

        writer.Key("Specific_Type");
        writer.String(message->getSpecificType().c_str());

        writer.Key("Filename");
        writer.String(message->getFileName().c_str());

        writer.Key("Request");
        writer.String(message->getRequest().c_str());

        writer.EndObject();
        cout << buffer.GetString() << endl;

        return buffer.GetString();
    }
};

#endif //CLIENTBREAKOUT_JSONMANAGEMENT_H