## Smart signage project
> Dutch: slimme bewegwijering

### Setup
1. Apply the following circuit setup on to a ESP32 (should be roughly the same as this Arduino schematic):
![Arduino schematic circuit](./Arduino_schematic_circuit.jpeg)

2. Set the `ssid` and `pass` values inside the code.

3. Upload the [main.ino](./main.ino) onto the ESP32.

After the Wi-Fi has connected you should see a IP in your output console, remember this IP.

Now you can flip the text on the LCD (by flipping the `isToggled`) by  posting via HTTP to the REST API server.
This can be achieved via e.g.: curl or Postman.

> Curl example: 
`curl -X POST http://<IP>:80/flip`
