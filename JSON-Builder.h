#pragma once

#include <string>

using namespace std;

class JSONArray{
    public:
    JSONArray(){
        m_value = "[";
    }

    void add(string a_value);
    string toString();

    void reset(){
        m_value = "[";
    }

    protected:
    string m_value;
};

class JSONObject{
    public:
    JSONObject(){
        m_value = "{";
    }

    void add(string a_name, string a_value);
    string toString();

    void reset(){
        m_value = "{";
    }

    protected:
    string m_value;
};