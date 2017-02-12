#include "modules.h"

#define WIFI_INTERFACENAME "wlp3s0"
#define VOLUME_SINK_ID "Sink #0"

JSONObject myDate(){
    time_t time_now;
    time_now  = time(&time_now);
    struct tm *ts = gmtime(&time_now);

    string out = "";
    
    out += to_string(ts->tm_hour + 1) + ":";
    if(to_string(ts->tm_min).size() < 2){
        out = out + "0" + to_string(ts->tm_min) + "  ";
    }else{
        out += to_string(ts->tm_min) + "  ";
    }

    out += to_string(ts->tm_mday) + ".";
    out += to_string(ts->tm_mon+1) + ".";
    out += to_string(ts->tm_year + 1900);  //so sind die jahre definiert

    JSONObject date;
    date.add("name","date");
    date.add("full_text",out);
    date.add("color","#ffffff");
    return date;
}

JSONObject myVolume(){
    //from util.h
    string volumetext = getCommandResult("pactl list sinks");

    stringstream ss(volumetext);
    string line;

    string sink = "";
    string volume = "";

    //find the line containing my wifi interface and the Quality
    while(getline(ss,line,'\n')){
        if(line.find(VOLUME_SINK_ID) != string::npos){
            sink = line;
        }
        if(sink.size() > 0){
            if(line.find("Volume") != string::npos){
                volume = line;
                break;
            }
        }
    }

    volume = volume.substr(volume.find("%") - 3, 3);
    volume = to_string(stoi(volume)); //strip off any spaces
    JSONObject vol;

    string pre = "Vol: ";
    vol.add("name","volume");
    vol.add("full_text",pre + volume + "%");

    return vol;
}

JSONObject myWifi(){
    //from util.h
    string wifitext = getCommandResult("iwconfig");

    stringstream ss(wifitext);
    string line;

    string ssidLine = "";
    string strengthLine = "";

    //find the line containing my wifi interface and the Quality
    while(getline(ss,line,'\n')){
        if(line.find(WIFI_INTERFACENAME) != string::npos){
            ssidLine = line;
        }
        if(line.find("Link Quality") != string::npos){
            //only take the Quality if the ssid is found. break after this, because no info is needed anymore
            if(ssidLine.size() > 0){
                strengthLine = line;
                break;
            }
        }
    }

    JSONObject wifi;

    //if there were values found put them into json. else show red WIFI
    if (ssidLine.size() > 0 && strengthLine.size() > 0){
        //extract ssid from the line
        size_t pos = ssidLine.rfind("ESSID") + 7;
        string essid = ssidLine.substr(pos, ssidLine.size() - pos - 3);

        //extract the Quality from the line
        pos = strengthLine.find("=") + 1;
        strengthLine = strengthLine.substr(pos, strengthLine.size() - pos);

        pos = strengthLine.find(" ");
        strengthLine = strengthLine.substr(0, pos);

        pos = strengthLine.find("/");
        float val = stof(strengthLine.substr(0, pos));
        float max = stof(strengthLine.substr(pos + 1, strengthLine.size() - pos - 1));

        //fill the JSONObject with the data
        wifi.add("name","wifi");
        wifi.add("markup","pango");
        wifi.add("full_text","<b>" + essid + "</b>");

        wifi.add("color","#00ff00");
        if(val / max < 0.75){
            wifi.add("color","#ffff00");
        }
        if(val / max < 0.25){
            wifi.add("color","#ff0000");
        }
    }else{
        wifi.add("name","wifi");
        wifi.add("markup","pango");
        wifi.add("full_text","<b>WIFI</b>");
        wifi.add("color","#ff0000");
    }
    
    return wifi;
}

JSONObject myBat(){
    string label = "BAT ";
    string status = "=";

    JSONObject bat;
    bat.add("name","bat");
    bat.add("markup","pango");
    bat.add("color","#00ff00");
    
    //those bars are in the array ▁▂▃▄▅▆▇▉
    string blocks [] = {"\u2581","\u2582","\u2583","\u2584","\u2585","\u2586","\u2587","\u2588"};

    string battext = getCommandResult("acpi");
    size_t pos = battext.find("%");

    //100% are handled differently anyways so offset 2 is okay
    int level = stof(battext.substr(pos - 2, 2));
    int ind = (int)((8*level)/100);


    if(battext.find("Full") != string::npos){
        bat.add("full_text","<b>" + label + blocks[7] + status + "</b>");
    }else{
        if(battext.find("Charging") != string::npos){
            status = "\u2b06";
        }
        if(battext.find("Discharging") != string::npos){
            status = "\u2b07";
        }

        bat.add("full_text","<b>" + label + blocks[ind] + status + "</b>");

        if(level < 75){
            bat.add("color","#ffff00");
        }
        if(level < 25){
            bat.add("color","#ff0000");
        }
    }

    return bat;
}