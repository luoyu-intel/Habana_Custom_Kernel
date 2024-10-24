#include <stdio.h>
#include <synapse_api.h>
#include <iostream>

using namespace std;
bool acquire_device()
{
    synStatus status;
    uint32_t dev_counter;

    status = synDeviceGetCount(&dev_counter);
    if (status != synSuccess)
    {
        cout << "Failed to synDeviceGetCount" << endl;
        return false;
    }
    if (dev_counter == 0)
    {
        return false;
    }
    printf("Device Number :%d\n", dev_counter);
    uint32_t deviceID[dev_counter];

    for (uint32_t i = 0; i < dev_counter; i++)
    {
        status = synDeviceAcquire(&deviceID[i], nullptr);
        printf("Deivce %d %d\n", i, deviceID[i]);
        if (status != synSuccess)
        {
            cout << "Failed to Acquire device: " << int(i) << endl;
            return false;
        }
    }

    for (uint32_t i = 0; i < dev_counter; i++)
    {
        status = synDeviceRelease(deviceID[i]);
        if (status != synSuccess)
        {
            cout << "Failed to release device: " << int(i) << endl;
            return false;
        }
    }
    return true;
}

int main()
{
    printf("Hello SYNAPSE!\n");
    auto status = synInitialize();
    std::cout << "synInitialize: " << status << "\n";
    if (status != synSuccess)
    {
        printf("Failed at %d\n", __LINE__);
        return -1;
    }
    if (!acquire_device())
    {
        printf("No Gaudi Devices\n");
        return -1;
    }
    synGraphHandle agraph;
    status = synGraphCreate(&agraph, synDeviceType::synDeviceGaudi2);
    std::cout << "create synapse graph: " << status << "\n";
    if (status != synSuccess)
    {
        printf("Failed at %d\n", __LINE__);
        return -1;
    }
    synStreamHandle stream;
    status = synStreamCreateGeneric(&stream, 0, 0);
    if (status != synSuccess)
    {
        printf("Failed at %d\n", __LINE__);
        return -1;
    }
    return 0;
}