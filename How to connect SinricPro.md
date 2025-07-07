With Sinric Pro, you can easily connect the Google Home and Amazon Alexa App with ESP8266, NodeMCU or ESP32 microcontroller to control any appliance with Google Assistant and Alexa.

**Step-1 Sinric Pro account Setup**

**1.Create the Sinric Pro Account ,**
First visit **sinric.pro/register** , Then enter all the required details and click on Register.

**2.After the creating the account,** please visit **sinric.pro/login**
Then enter the email id and password, and click on login.

**3.Create a Room in Sinric Pro**

Before adding the devices, first you have to create room in the Sinric Pro.

Steps for creating rooms in Sinric Pro:

Goto Rooms in the left side menu>>
Click on Add Room button>>
Enter the Room Name and Description>>
Click on Save.

**4.Add Devices in Sinric Pro**

Go to Devices from the left side menu >> First select the Devices from left side menu, then click on Add Device button.

Enter the Device details:

Enter the Device Name and Description >>
Then select the Device Type as per the requirement. Here I have selected device type as Switch >>
Then select the Room for the device >>
After that click on Next.

Setup Push Notification to the Mobile , 
If you want any push notifications related to this device, then you can turn on the notifications.
This field is optional.
Click on Next.

**Now Click on Save. the device will be created.**


** How to get the 
Sinric API KEY & API SECRET**

Before uploading any example sketch to ESP8266 or ESP32, you have to enter the Sinric API KEY and API SECRET

To get the API KEY and API SECRET, you have to go to Credentials from left side menu.

#define WIFI_SSID         "YOUR-WIFI-NAME"    

#define WIFI_PASS         "YOUR-WIFI-PASSWORD"

#define APP_KEY           "YOUR-APP-KEY"

#define APP_SECRET        "YOUR-APP-SECRET"

After that, enter the APP KEY and APP SECRET with Wi-Fi name and Wi-Fi password in the code.

Also enter the device id in the code. You will find the Device ID from Devices menu.

When you create a device in Sinric Pro, a unique ID assigned to that device.


**Step-2 Connecting Sinric Pro with Alexa App** 

Before connecting the Alexa, you have to add devices in the Sinric Pro.

**1.Steps to add Sinric Pro with Alexa App:**

In the Alexa App tap on More, then select Skills & Games >>
Search for Sinric Pro, then tap on Sinric Pro >>
Tap on ENABLE TO USE >>
Enter the email id and password used for the Sinric account, Then tap on Sign in.

**2.Add Devices in Amazon Alexa App**
After connecting the Sinric Pro account, follow the following steps to add devices.

Tap on CLOSE >>
Tap on DISCOVER DEVICES >>
Now, Alexa will look for new devices. This may take some time >>
After that, go to Devices, then select Plug. You will find all the connected devices.

Now, if the ESP32 or ESP8266 is connected to the Wi-Fi, then you can control the appliances from Alexa App.

COmmand **"Alexa, Turn ON light”** to control the appliances with voice commands.
