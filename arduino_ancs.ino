#include <SoftwareSerial.h>
#include<string.h>
#include <stdlib.h>
#include<stddef.h>
#include <stdio.h>

char buf[256];
int offset = 0;
enum MsgState{
 MSG_UNKNOWN,
MSG_RECEIVE,
MSG_END
};

SoftwareSerial mySerial(10,11); // RX, TX

 MsgState status = MSG_END;

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
// set the data rate for the SoftwareSerial port
  mySerial.begin(57600);
  
  // sending reset command to ancs module
delay(500);
 mySerial.write("RST\n");
 delay(500);
 mySerial.write("RST\n");
  delay(500);
 mySerial.write("RST\n");

}

 

void loop() // run over and over
{
     
   
  
  while (mySerial.available()){
    
    char c = mySerial.read();
    
if (c == '\n'){

       if (strstr(buf,"=e=")){
        status = MSG_END;
      }
     
      
      if (status == MSG_RECEIVE){

		// doing decode here 
		int cursor = 0;
		int appid_idx = 5;
		int appid_len =   buf[appid_idx+1];
		cursor = appid_idx+appid_len+3; // additional 2, skip 2 bytes appid_len 0x0000
		int title_idx = cursor;
		int title_len  =  buf[title_idx+1];
		cursor = title_idx + title_len+3;
		int subtitle_idx = cursor;
		int subtitle_len = buf[subtitle_idx+1];
		cursor = subtitle_idx + subtitle_len +3;
		int message_idx = cursor;
		int message_len = buf[message_idx+1];
		cursor = message_idx + message_len +3;
		int timestamp_idx = cursor;
		int timestamp_len = buf[timestamp_idx+1];
		cursor = timestamp_idx + timestamp_len +3;

/* ======= parse by application name ======= */
		char appid[appid_len];
		Serial.write("appid:");
		for (int k=0;k<appid_len;k++){
			appid[k] =  buf[appid_idx+3+k];
                 Serial.write(appid[k]);
		}
		Serial.write("\n");
		
		if ( strstr(appid,"com.facebook.Messenger")){
		// for message from facebook messenger 	
	
		}else if ( strstr(appid,"com.apple.MobileSMS")){
	// for message from imessage
		}

/* ============ Unread Message ============= */
                Serial.write("UnRead:");
                Serial.print(buf[0],DEC);
                Serial.write("\n");

/* ============ Title ===================== */                 
                  Serial.write("Title:");
		char title[title_len];
		for (int k=0;k<title_len;k++){
			title[k] =  buf[title_idx+3+k];
                Serial.write(title[k]);
		}
		 Serial.write("\n");
		
                 
 /* ============= Subtitle =============== */                
		char subtitle[subtitle_len];
                Serial.write("subtitle:");
		for (int k =0;k<subtitle_len;k++){
			subtitle[k] = buf[subtitle_idx+3+k];
                Serial.write(subtitle[k]);
		}
		Serial.write("\n");

 /* ============= Message content =========== */
                 Serial.write("message:{");
		char message[message_len];
		for ( int k=0;k<message_len;k++){
			message[k] =  buf[message_idx+3+k];
                Serial.write(message[k]);
		}
		Serial.write("}\n");


/* ============== Timestamp ============== */		
                 Serial.write("timestamp:");
		char timestamp[timestamp_len];
		for (int k=0;k<timestamp_len;k++){
			timestamp[k] = buf[timestamp_idx+3+k];
                Serial.write(timestamp[k]);
		}
	
		Serial.write("\n");

	}
  
        if (strstr(buf,"=s=")){
        status = MSG_RECEIVE;

      }
      
/* ================ Status Handling ================ */      
      if (strstr(buf,"Apple ANCS Start init.")){
      Serial.write("Module Starting\n");
      }
      
       if (strstr(buf,"Bonding Success")){
      Serial.write("Mobile Paired\n");
      }
      
       if (strstr(buf,"Pairing Fail")){
          // if you see this message , remove the pairing on iphone 
       Serial.write("Pairing Fail\n");
      }
      
       if (strstr(buf,"Connecting")){
       Serial.write("Connecting\n");
      }
      
       if (strstr(buf,"Set Message Notifer")){
       Serial.write("Registering Service(1/2)\n");
      }
      
        if (strstr(buf,"Set Message Notifer")){
       Serial.write("Registering Service(2/2)\n");
       Serial.write("Init Process Success\n");
      }
       if (strstr(buf,"Message Notifer fail")){
         // if you see this message , remove the pairing on iphone 
       Serial.write("Registering Service Fail\n");
      }
      if (strstr(buf,"Detail Parser Fail")){
         // if you see this message , remove the pairing on iphone 
      Serial.write("Registering Service Fail\n");
      }
  
      offset = 0;
     memset(buf, 0,256);
  
    }else{
    
    buf[offset] = c;
    offset +=1;
    }

  }
  
  
  while (Serial.available()){

    
     int inByte = Serial.read();
    mySerial.write(inByte); 
}
}




