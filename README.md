# ESP32 WiFi and BLE Scanner

This project encompasses a straightforward scanner utilizing an ESP32 to scan for nearby WiFi and Bluetooth devices. The results are hosted and accessible through a web server running on the ESP32.

## Getting Started

1. **Connecting to the ESP32 Web Server:**
    - By default, the ESP32 creates its own WiFi network. Connect to this network and navigate to `192.168.4.1` in your web browser to view the scanning results.

2. **Connecting ESP32 to Your WiFi:**
    - If you prefer to connect the ESP32 to your own WiFi network, simply update the `SSID` and `PASSWORD` variables in the code with your network credentials.
    - Once connected, the ESP32 will display its assigned IP address on the serial monitor. Use this IP address to access the scanning results from your web browser.

## Features

- Detects and displays nearby WiFi and Bluetooth devices.
- Hosts a web server on the ESP32 to present the scanning results in a user-friendly format.
- Allows the ESP32 to connect to a local WiFi network for a more integrated experience.

## Usage

1. Load the provided script onto your ESP32.
2. Power on the ESP32.
3. Follow the steps under **Getting Started** to view the scanning results.

## Support

For any issues or enhancements, feel free to open an issue on the GitHub repository.

## Contributing

We welcome contributions! If you have any improvements or features you'd like to add, please feel free to fork the repository and submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
