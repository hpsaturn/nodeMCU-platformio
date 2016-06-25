/*
   Basic MQTT example 

   - connects to an MQTT server
   - publishes "hello world" to the topic "outTopic"
   - subscribes to the topic "inTopic"
   */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *ssid =	"Atins";		// cannot be longer than 32 characters!
const char *pass =	"DoisLencois2009";		//

// Update these with values suitable for your network.
IPAddress server(192, 168, 1, 111);

WiFiClient wclient;
PubSubClient client(wclient, server);

long test=0;

void callback(const MQTT::Publish& pub) {
    // handle message arrived
    Serial.print("MQTT callback..");
    // Copy the payload to a new message
    MQTT::Publish newpub("outTopic", pub.payload(), pub.payload_len());
    client.publish(newpub);
}


void setup() {
    // Setup console
    Serial.begin(115200);
    delay(10);
    Serial.println();
    Serial.println();

    client.set_callback(callback);
}

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.print("Connecting to ");
        Serial.print(ssid);
        Serial.println("...");
        WiFi.begin(ssid, pass);

        if (WiFi.waitForConnectResult() != WL_CONNECTED)
            return;
        Serial.println("WiFi connected");
    }

    if (WiFi.status() == WL_CONNECTED) {
        if (!client.connected()) {
            Serial.println("connecting to server..");
            if (client.connect("arduinoClient")) {
                client.publish("outTopic","hello world");
	            client.set_callback(callback);
                client.subscribe("inTopic");
                Serial.print("client connected, publish and subscribed!");
            }
        }

        if (client.connected())
            client.loop();

        String output = String(test++);
        client.publish("outTopic",output);
    }
}

