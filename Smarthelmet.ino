int gasValue = analogRead(MQ2_PIN); // Check conditions for sending email alerts 
if (irValue == HIGH || temperature > 35.0 || humidity > 50.0 || 
detectMethaneOrSmoke(gasValue)) 
{ 
sendEmailAlert(temperature, humidity, irValue, gasValue); 
delay(60000); // Send email every minute (60000 milliseconds) 
} 
delay(1000); // Check conditions every second 
} 
bool detectMethaneOrSmoke(int gasValue) 
{ 
// Define threshold values for methane and smoke detection 
const int thresholdMethane = 500; 
const int thresholdSmoke = 700; // Check for methane or smoke based on MQ2 gas sensor 
reading 
return (gasValue > thresholdMethane || gasValue > thresholdSmoke); 
}void sendEmailAlert(float temp, float hum, int ir, int gas) 
{ 
Session_Config config; 
config.server.host_name = SMTP_HOST; 
config.server.port = SMTP_PORT; 
config.login.email = AUTHOR_EMAIL; 
config.login.password = AUTHOR_PASSWORD; 
SMTP_Message message; 
message.sender.name = "ESP"; 
message.sender.email = AUTHOR_EMAIL; 
message.subject = "Alert from ESP32"; // Compose alert details for the email body 
String alertDetails = "Alert Details:\n"; if (ir == HIGH) { alertDetails += "Worker fallen down\n"; } 
if (temp > 35.0) { 
alertDetails += "Temperature is above 35°C: " + String(temp) + "°C\n"; } 
if (hum > 50.0) { alertDetails += "Humidity is above 50%: " + String(hum) + "%\n"; } 
if (detectMethaneOrSmoke(gas)) 
{ 
alertDetails += "Dangerous gas (Methane or Smoke) detected!\n"; } 
// Append the default message with GPS location to the alert details
