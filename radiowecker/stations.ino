
//default stationlist
#define DEFAULTSTATIONS 24


//Definition of a set of tested default stations
Station defstations[DEFAULTSTATIONS] PROGMEM = {
{"http://streams.radiobob.de/rockoldies/mp3-192/mediaplayer","BOB Rock Oldies",1},
{"http://streams.radiobob.de/bob-kuschelrock/mp3-192/mediaplayer","BOB Kuschelrock",1},
{"http://streams.radiobob.de/southernrock/mp3-192/mediaplayer","BOB Southern Rock",1},
{"http://streams.radiobob.de/blues/mp3-192","BOB Blues",1},
{"http://stream.srg-ssr.ch/m/drs1/mp3_128","DRS1",1},
{"http://stream.srg-ssr.ch/m/rsp/mp3_128","Swiss Pop",1}};

//fill the station list from preferences. If an entry not exists the default list will be used
void setup_senderList() {
  char nkey[4];
  char ukey[4];
  char fkey[4];
  for (uint8_t i = 0; i<STATIONS; i++) {
    sprintf(nkey,"n%i",i);
    sprintf(ukey,"u%i",i);
    sprintf(fkey,"f%i",i);
    if (i<DEFAULTSTATIONS) {
      strlcpy(stationlist[i].name,sender.getString(nkey,defstations[i].name).c_str(),32);
      strlcpy(stationlist[i].url,sender.getString(ukey,defstations[i].url).c_str(),150);
      stationlist[i].enabled = sender.getUChar(fkey,defstations[i].enabled);
    } else {
      strlcpy(stationlist[i].name,sender.getString(nkey,nkey).c_str(),32);
      strlcpy(stationlist[i].url,sender.getString(ukey,"").c_str(),150);
      stationlist[i].enabled = sender.getUChar(fkey,0);
    }
  }
}

//fill the station list from default list and save it into preferences
void restore() {
  char nkey[4];
  char ukey[4];
  char fkey[4];
  for (uint8_t i = 0; i<STATIONS; i++) {
    sender.clear();
    sprintf(nkey,"n%i",i);
    sprintf(ukey,"u%i",i);
    sprintf(fkey,"f%i",i);
    if (i<DEFAULTSTATIONS) {
      strlcpy(stationlist[i].name,defstations[i].name,32);
      sender.putString(nkey,defstations[i].name);
      strlcpy(stationlist[i].url,defstations[i].url,150);
      sender.putString(ukey,defstations[i].url);
      stationlist[i].enabled = defstations[i].enabled;
      sender.putUChar(fkey,defstations[i].enabled);
    } else {
      strlcpy(stationlist[i].name,nkey,32);
      sender.putString(nkey,nkey);
      strlcpy(stationlist[i].url,"",150);
      sender.putString(ukey,"");
      stationlist[i].enabled = 0;
      sender.putUChar(fkey,0);
    }
  }
}

//save stationlist into preferences
void saveList() {
  char nkey[4];
  char ukey[4];
  char fkey[4];
  for (uint8_t i = 0; i<STATIONS; i++) {
    sprintf(nkey,"n%i",i);
    sprintf(ukey,"u%i",i);
    sprintf(fkey,"f%i",i);
    sender.putString(nkey,stationlist[i].name);
    sender.putString(ukey,stationlist[i].url);
    sender.putUChar(fkey,stationlist[i].enabled);
  }
}

//move a station inside the station list from old position to newposition
void reorder(uint8_t oldpos, uint8_t newpos) {
  Station temp;
  if ((oldpos < STATIONS) && (newpos  < STATIONS)) {
    if (oldpos > newpos) {
      memcpy(&temp,&stationlist[oldpos],sizeof(Station));
      for (uint8_t i = oldpos; i>newpos; i--) {
        memcpy(&stationlist[i],&stationlist[i-1],sizeof(Station));
      }
      memcpy(&stationlist[newpos],&temp,sizeof(Station));
    } else {
      memcpy(&temp,&stationlist[oldpos],sizeof(Station));
      for (uint8_t i = oldpos; i<newpos; i++) {
        memcpy(&stationlist[i],&stationlist[i+1],sizeof(Station));
      }
      memcpy(&stationlist[newpos],&temp,sizeof(Station));
    }
  }
}
