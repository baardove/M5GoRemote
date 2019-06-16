# M5GoRemote

Uses a cheap M5StickC as a GoPro Hero Wifi Remote

- Will start and stop video recording via wifi
- Support up to 10 GoPros
- Show recording status of each camera on the display
- Will rescan cameras to check their status
- Uses one to one connection, not the GoPro Remotes reverse connection. So works a bit slower.
- Shows signal strength
- Easy to configure

CONTRIBUTIONS

The initial code is based on the open source version 1337Remote by Eurodesign.de
http://euerdesign.de/2016/09/06/goproremote-goes-opensource-and-got-renamed/

And great help from the WifiHack documentation by KonradIT
https://github.com/KonradIT/goprowifihack


PREREQUESITES

HARDWARE

M5 STICK C
- This is an out of the box solution that works good for this project. No hardware hackign needed. Cheap, approx 10usd+5usd 
  shipping makes it the cheapest GoPro Remote you can get in nice package.
- Uses M5 Stick C with ESP32 processor, buttons, display and battery.
- https://www.aliexpress.com/item/New-Arrival-2019-M5StickC-ESP32-PICO-Mini-IoT-Development-Board-Finger-Computer-with-Color-LCD/32985247364.html?spm=a219c.10010108.1000001.12.61e932260T2MfV


GOPRO HERO 4+

- Tested with GoPro Hero 4. Should work with newer models as well, but not tested.
- Might support Hero 3+ in future.


CONFIGURATION

To avoid a lot of configuration and usability on the go, makes some assumptions of your setup.
This can be changed to suite your needs.

// ASSUMES ALL GOPROS TO BE CONTROLLED HAS SAME SSID PREFIX
// T.EX. GOPRO_CAM1, GOPRO_CAM2, etc.
// AND THAT THEY HAVE SAME PASSWORD.  

String wifiPrefix="GOPRO_";
String wifiPassword="12341234";

That is it, ready to rock n roll!


STARTING

When the M5 is booting it will scan the network for devices and list all devices with prefix and show them with signal strength. The strength is a bit random and doesnt really say much about the reality. Each camera will be queried for recording status.

The camera list will show names without Prefix

If one or more camera is already recording the global recording status will be set to recording.

The A-button (large one next to display) will activate the trigger and tell each camera to record.

If one or more camera is already recording it will stop recording. Only cameras in wrong mode will be contacted.

The display will show a RED Icon with "R" to show the camera to indicate it is in recording modus. 

That is more or less what it does right now...


IDEAS FOR FURTHER DEVELOPMENT

- Battery status for each camera 
- Dynamic display if less number of cameras (bigger font for readability), rotation based on accelerometer
- Sorting of list to keep cameras in same order / currently listed in order as reported from wifi scan
- Support for Hero 3+ (uses binary codes)
- Support photomodes
- Support Wake up and Sleep of GoPro
- Support M5 dim display and sleep to save M5 battery
- Support other camera platforms and audio recorders. One button to start / stop it all...










