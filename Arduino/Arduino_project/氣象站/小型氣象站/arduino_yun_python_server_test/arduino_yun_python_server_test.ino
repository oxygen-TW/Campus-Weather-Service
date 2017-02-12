#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

YunServer server;

void process(YunClient client) {
  String command = client.readStringUntil('\r');
  if (command == "Temp") {
    digitalWrite(13, HIGH);
  }
  else if (command == "Humi") {
    digitalWrite(13, LOW);
  }
}

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();
  digitalWrite(13, LOW);
}
void loop() {
  YunClient client = server.accept();
  if (client) {
    process(client);
    client.stop();
  }
  delay(500);
}
