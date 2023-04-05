#include <bits/stdc++.h>

using namespace std;

class Device {
public:
    Device(string name) {
        this->name = name;
    }

    void connect(Device* device) {
        connectedDevices.push_back(device);
        device->connectedDevices.push_back(this);
    }

    virtual void send(string data) {
        for (Device* device : connectedDevices) {
            device->receive(data);
        }
    }

    virtual void receive(string data) {
        cout << name << " received data: " << data << endl;
    }

protected:
    string name;
    vector<Device*> connectedDevices;
};

class EndDevice : public Device {
public:
    EndDevice(string name) : Device(name) {}

    void connectTo(Device* device) {
        connect(device);
    }

    void send(string data) override {
        for (Device* device : connectedDevices) {
            if (device != this) {
                device->receive(data);
            }
        }
    }
};

class Hub : public Device {
public:
    Hub(string name) : Device(name) {}

    void sendToAll(string data) {
        for (Device* device : connectedDevices) {
            if (device != this) {
                device->receive(data);
            }
        }
    }
};

int main() {
    // Test Case 1: Two end devices with a dedicated connection
    cout << "----- Test Case 1: Two end devices with a dedicated connection -----" << endl;

    EndDevice device1("Device 1");
    EndDevice device2("Device 2");

    device1.connectTo(&device2);

    device1.send("Hello from Device 1");
    device2.send("Hello from Device 2");

    cout << endl;

    // Test Case 2: A star topology with five end devices connected to a hub
    cout << "----- Test Case 2: A star topology with five end devices connected to a hub -----" << endl;

    Hub hub("Hub");
    EndDevice device3("Device 3");
    EndDevice device4("Device 4");
    EndDevice device5("Device 5");
    EndDevice device6("Device 6");
    EndDevice device7("Device 7");

    device3.connectTo(&hub);
    device4.connectTo(&hub);
    device5.connectTo(&hub);
    device6.connectTo(&hub);
    device7.connectTo(&hub);

    device3.send("Hello from Device 3");
    device4.send("Hello from Device 4");
    device5.send("Hello from Device 5");
    device6.send("Hello from Device 6");
    device7.send("Hello from Device 7");

    device4.send("Hello from Device 4 to Device 3");
    device3.send("Hello from Device 3 to Device 5");
    device5.send("Hello from Device 5 to Device 6");
    device6.send("Hello from Device 6 to Device 7");
    device7.send("Hello from Device 7 to Device 4");

    return 0;
}
