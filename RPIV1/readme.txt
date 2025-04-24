1. Make sure all libraries are downloaded.
- Some of the commands that helped me, is here:
sudo apt install qtbase5-dev
sudo apt install qtbase5-dev qt5-qmake libqt5widgets5 libqt5gui5 libqt5core5a

2. Make sure the MAC adress is correct. This line needs to be changed.
string targetBluetoothAddress = "00:1A:7D:DA:71:13"; // REPLACE WITH MAC ADRESS OF PSOC

3. Make sure the BL module on the PSOC is connected to the RPI
- Run: sudo apt-get install bluemanbluez Bluetooth
- Run: bluetoothctl
- Run: power on
- RUn: agent on
- Run: pair <mac address>
- Run: trust <mac address>

4. You need to create a moc file of the GUI, is done like this:
moc GUIThread.h -o moc_GUIThread.cpp

4. Compile the code.
g++ -fPIC main.cpp VarHandler.cpp GUIThread.cpp BluetoothThread.cpp moc_GUIThread.cpp -o my_app     `pkg-config --cflags --libs Qt5Widgets` -lbluetooth

5. run the code
./my_app
