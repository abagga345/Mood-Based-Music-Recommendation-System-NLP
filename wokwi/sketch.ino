// #include <WiFi.h>
// #include <HTTPClient.h>
// #include <LiquidCrystal.h>

// // LCD Pins (RS, E, D4, D5, D6, D7)
// LiquidCrystal lcd(2, 0, 4, 16, 17, 5);

// // Wi-Fi credentials
// const char* ssid = "Wokwi-GUEST";
// const char* password = "";
// // API details

// // API endpoint
// const char* apiEndpoint = "https://reqres.in/api/users";

// void setup() {
//   // Initialize LCD
//   lcd.begin(16, 2);
//   lcd.print("Connecting...");

//   // Initialize serial communication
//   Serial.begin(9600);

//   // Connect to Wi-Fi
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     lcd.setCursor(0, 1);
//     lcd.print(".");
//   }

//   lcd.clear();
//   lcd.print("WiFi connected!");
//   delay(1000);
//   lcd.clear();
// }

// void loop() {
//   lcd.setCursor(0, 0);
//   lcd.print("Enter text:");
//   while (!Serial.available()) {
//     // Wait for user input from Serial Monitor
//   }

//   String userInput = Serial.readString(); // Read user input
//   lcd.clear();
//   lcd.setCursor(0, 0);
//   lcd.print("Sending...");

//   // Send data to API
//   String response = sendToAPI(userInput);

//   // Display the response
//   lcd.clear();
//   lcd.setCursor(0, 0);
//   lcd.print("Response:");
//   lcd.setCursor(0, 1);
//   lcd.print(response);

//   delay(50000); // Wait 5 seconds before allowing another input
//   lcd.clear();
// }

// // Function to send data to API
// String sendToAPI(String text) {
//   if (WiFi.status() == WL_CONNECTED) {
//     HTTPClient http;
//     http.begin(apiEndpoint);
//     http.addHeader("Content-Type", "application/json");

//     // Prepare the JSON payload
//     // String payload = "{\"text\":\"" + text + "\"}";
//     String payload = "{\"name\":\""+text+"\",\"job\":\"leader\"}";

//     int httpResponseCode = http.POST(payload);

//     String response = "";
//     if (httpResponseCode > 0) {
//       response = http.getString(); // Get the response
//     } else {
//       response = "Error: " + String(httpResponseCode);
//     }

//     http.end(); // Close the connection
//     return response;
//   } else {
//     return "WiFi Error!";
//   }
// }
#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <ArduinoJson.h>  // Include the ArduinoJson library

// LCD Pins (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(2, 0, 4, 16, 17, 5);

// Wi-Fi credentials
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// API endpoint
const char* apiEndpoint = "https://aihtproject.onrender.com/predict";

void setup() {
  // Initialize LCD
  lcd.begin(20, 4);
  lcd.print("Connecting...");

  // Initialize serial communication
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print(".");
  }

  lcd.clear();
  lcd.print("WiFi connected!");
  delay(1000);
  lcd.clear();
}
// Function to scroll text on the LCD
void scrollText(String text) {
  int textLength = text.length();
  for (int i = 0; i < textLength - 16 + 1; i++) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(text.substring(i, i + 16)); // Display a substring of 16 characters
    delay(300); // Adjust the delay as per your preference for scrolling speed
  }
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Enter text:");
  while (!Serial.available()) {
    // Wait for user input from Serial Monitor
  }

  String userInput = Serial.readString(); // Read user input
  userInput.trim();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Processing...");

  // Send data to API
  String response = sendToAPI(userInput);

  // Split response into lines
  String lines[6];  // Assuming max 6 lines
  int lineIndex = 0;
  int start = 0;
  while (lineIndex < 6) {
    int newLinePos = response.indexOf('\n', start);
    if (newLinePos == -1) {
      lines[lineIndex] = response.substring(start);
      break;
    } else {
      lines[lineIndex] = response.substring(start, newLinePos);
      start = newLinePos + 1;
      lineIndex++;
    }
  }

  // Display first 4 lines
  for (int i = 0; i < 6; i++) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(lines[i]);
    delay(3000); // 300 seconds = 5 minutes
  }

  lcd.clear();
}



// Function to send data to API
String sendToAPI(String text) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(apiEndpoint);
    http.addHeader("Content-Type", "application/json");
    Serial.println(text);
    // Prepare the JSON payload
    String payload = "{\"text\":\"" + text + "\"}";// Update the payload to include user input
    Serial.println(payload);
    int httpResponseCode = http.POST(payload);

    String response = "";
    if (httpResponseCode > 0) {
      response = http.getString(); // Get the response as a string

      // Debug: Print the raw response in the serial monitor
      Serial.println("Raw Response:");
      Serial.println(response);

      // Increase the buffer size for ArduinoJson
      StaticJsonDocument<512> doc;  // Increased buffer size

      DeserializationError error = deserializeJson(doc, response);

      if (error) {
        Serial.println("JSON parse error: " + String(error.f_str()));
        return "JSON parse error";  // Return an error message
      }

      // Extract data from the response
      String sentiment = doc["sentiment"];
      String confidence = doc["confidence"][0].as<String>() + ", " +
                          doc["confidence"][1].as<String>() + ", " +
                          doc["confidence"][2].as<String>();
      JsonArray recommendations = doc["recommendations"].as<JsonArray>();
        String recommendationList = "";
        for (int i = 0; i < recommendations.size(); i++) {
          recommendationList += recommendations[i].as<String>() + "\n";
          // if (recommendationList.length() > 40) {
          //   break; // Limit recommendations to fit LCD display
          // }
        }

        // Format the display string
        String displayResponse = "Sentiment: " + sentiment + "\n" + recommendationList;
        return displayResponse;
    } else {
      response = "Error: " + String(httpResponseCode);
    }

    http.end(); // Close the connection
    return response;
  } else {
    return "WiFi Error!";
  }
}

