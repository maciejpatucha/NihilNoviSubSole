#include "task_executors.h"
#include "common_headers.h"

#include <pthread.h>

static pthread_t networkThread;
static pthread_t devicesThread;
static pthread_t ipcThread;

static int networkThreadResult;
static int devicesThreadResult;
static int ipcThreadResult;

static typedef enum {
    NETWORK_THREAD,
    DEVICES_THREAD,
    IPC_THREAD
} threadType;

static int CreateThread(threadType type);

int StartNetworkDiscoveryService()
{
    WriteToLog(INFORMATION, "Trying to create networkThread.");
    if (CreateThread(NETWORK_THREAD) == -1)
    {
        WriteToLog(ERROR, "Failed to create networkThread.");
        return -1;
    }
    else
    {
        WriteToLog(INFORMATION, "networkThread created successfully.");
        return 0;
    }

    return 0;
}

int StartDeviceDiscoveryService()
{
    WriteToLog(INFORMATION, "Trying to create devicesThread.");
    if (CreateThread(DEVICES_THREAD) == -1)
    {
        WriteToLog(ERROR, "Failed to create devicesThread.");
        return -1;
    }
    else
    {
        WriteToLog(INFORMATION, "devicesThread created successfully.");
        return 0;
    }

    return 0;
}

int StartIPCService()
{
    WriteToLog(INFORMATION, "Trying to create ipcThread.");
    if (CreateThread(IPC_THREAD) == -1)
    {
        WriteToLog(ERROR, "Failed to create ipcThread.");
        return -1;
    }
    else
    {
        WriteToLog(INFORMATION, "ipcThread created successfully.");
        return 0;
    }

    return 0;
}

int StopNetworkDiscoveryService()
{

}

int StopDeviceDiscoveryService()
{

}

int StopIPCService()
{

}

static int CreateThread(threadType type)
{
    int retval = 0;
    switch(type)
    {
    case NETWORK_THREAD:
        retval = pthread_create(networkThread, NULL, ListenToClients, NULL);
        break;
    case DEVICES_THREAD:
        retval = pthread_create(devicesThread, NULL, LookForDevices, NULL);
        break;
    case IPC_THREAD:
        retval = pthread_create(&ipcThread, NULL, TalkToMe, NULL);
        break;
    }

    if (retval == -1)
    {
        switch(errno)
        {
        case EAGAIN:
            WriteToLog(ERROR, "Failed to create thread: %s", strerror(errno));
            return -1;
        case EINVAL:
            WriteToLog(ERROR, "Failed to create thread: %s", strerror(errno));
            return -1;
        }
    }
}
