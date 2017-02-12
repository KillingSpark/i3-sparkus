#include "JSON-Builder.h"

using namespace std;

void JSONObject::add(string a_name, string a_value){
    if(this->m_value != "{"){
        this->m_value += ",";
    }
    this->m_value += "\"" + a_name + "\": " +  "\"" + a_value + "\"";
}

string JSONObject::toString(){
    return this->m_value + "}";
}

void JSONArray::add(string a_value){
    if(this->m_value != "["){
        this->m_value += ",";
    }
    this->m_value += a_value;
}

string JSONArray::toString(){
    return this->m_value + "]";
}