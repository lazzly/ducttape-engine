#ifndef DUCTTAPE_ENGINE_NETWORK_NETWORKMANAGER
#define DUCTTAPE_ENGINE_NETWORK_NETWORKMANAGER

#include <boost/ptr_container/ptr_deque.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include <SFML/Network.hpp>

#include "ConnectionsManager.hpp"
#include "event/EventListener.hpp"
#include "event/HandshakeEvent.hpp"
#include "event/GoodbyeEvent.hpp"
#include "event/NetworkEvent.hpp"
#include "utils/Utils.hpp"

namespace dt {

/**
  * Manager for serializing events and sending them over network.
  * @see ConnectionsManager - Holds all connections of this manager.
  */
class NetworkManager : public EventListener {
public:
    /**
      * Default constructor.
      */
    NetworkManager();

    /**
      * Destructor.
      */
    ~NetworkManager();

    /**
      * Initialization method. Registers this manager as EventListener.
      */
    void Initialize();

    /**
      * Deinitialization method. Unregisters this manager as EventListener.
      */
    void Deinitialize();

    /**
      * Binds the Socket used for the complete networking to the port given.
      * @param port The port to bind the socket to, or 0 to automatically select a free port.
      * @returns True if the binding was successful. Otherwise false.
      */
    bool BindSocket(uint16_t port = 0);

    /**
      * Connects to a remote device. This method sends a HandshakeEvent to that target.
      * @param target The remote device to connect to.
      */
    void Connect(Connection target);

    /**
      * Disconnects from a remote device. This method sends a GoodbyeEvent to that target.
      * @param target The remote device to disconnect from.
      */
    void Disconnect(Connection target);

    /**
      * Disconnects from all remote devices.
      * @see NetworkManager::Disconnect(Connection target)
      */
    void DisconnectAll();

    /**
      * Sends all pending Events from the queue.
      * @see NetworkManager::QueueEvent(NetworkEvent* event);
      */
    void SendQueuedEvents();

    /**
      * Queues an Event to be sent later.
      * @see NetworkManager::SendQueuedEvents();
      * @param event The NetworkEvent to be sent.
      */
    void QueueEvent(NetworkEvent* event);

    /**
      * Receives and handles all events pending at the socket.
      */
    void HandleIncomingEvents();

    /**
      * Event callback. Checks if the Event is to be send over Network and if so queues it.
      * @see Event::IsNetworkEvent()
      * @see EventListener
      * @see NetworkManager::QueueEvent(NetworkEvent* event);
      * @param e The incoming Event.
      */
    void HandleEvent(Event* e);

    /**
      * Registers a NetworkEvent as prototype for incoming packets.
      * @see Factory Pattern
      * @see NetworkEvent::Clone();
      * @param event A new instance of a NetworkEvent to be used for factory.
      */
    void RegisterNetworkEventPrototype(NetworkEvent* event);

    /**
      * Creates a new instance of the prototype with the type ID given.
      * @see Factory Pattern
      * @see NetworkEvent::Clone();
      * @see Event::GetTypeID();
      * @param type_id The ID of the type of NetworkEvent to create an instance of.
      * @returns A new instance of the prototype with the type ID given.
      */
    NetworkEvent* CreatePrototypeInstance(uint32_t type_id);

    /**
      * Creates a new instance of the prototype with the type name given.
      * @see Factory Pattern
      * @see NetworkEvent::Clone();
      * @see Event::GetType();
      * @param type The name of the type of NetworkEvent to create an instance of.
      * @returns A new instance of the prototype with the type name given.
      */
    NetworkEvent* CreatePrototypeInstance(const std::string& type);

    /**
      * Returns a pointer to the ConnectionsManager.
      * @returns A pointer to the ConnectionsManager.
      */
    ConnectionsManager* GetConnectionsManager();

private:
    /**
      * Sends an Event to it's recipients.
      * @param event The event to send.
      */
    void _SendEvent(NetworkEvent* event);

    ConnectionsManager mConnectionsManager;                     //!< The ConnectionsManager that manages all remote devices.
    boost::ptr_deque<NetworkEvent> mQueue;                      //!< The queue of Events to be send. @see NetworkManager::QueueEvent(NetworkEvent* event);
    boost::ptr_vector<NetworkEvent> mNetworkEventPrototypes;    //!< The list of prototypes known to mankind :P
    sf::UdpSocket mSocket;                                      //!< The socket used for data transmissions over network.
};

}

#endif
