#include <enet/enet.h>
#include <string>
#include <iostream>
#include <thread>
#include <atomic>
#include <time.h>

using namespace std;

ENetHost* NetHost = nullptr;
ENetPeer* Peer = nullptr;
bool IsServer = false;
thread* PacketThread = nullptr;

bool running;
atomic<bool> canGuess;
atomic<int> clientGuess;
int myClientID;

int serverRandValue;
int currentClientId = 1;

constexpr int MAX_RAND_VAL = 20;

enum PacketHeaderTypes
{
    PHT_Invalid = 0,
    PHT_IsDead,
    PHT_Position,
    PHT_Count,
    PHT_ServerAssignID,
    PHT_ClientGuess,
    PHT_ServerGuessResponse
};

struct GamePacket
{
    GamePacket() {}
    PacketHeaderTypes Type = PHT_Invalid;
};

struct IsDeadPacket : public GamePacket
{
    IsDeadPacket()
    {
        Type = PHT_IsDead;
    }

    int playerId = 0;
    bool IsDead = false;
};

struct PositionPacket : public GamePacket
{
    PositionPacket()
    {
        Type = PHT_Position;
    }

    int playerId = 0;
    int x = 0;
    int y = 0;
};

struct ServerAssignIDPacket : public GamePacket
{
    ServerAssignIDPacket()
    {
        Type = PHT_ServerAssignID;
    }

    int playerId = 0;
};

struct ClientGuessPacket : public GamePacket
{
    ClientGuessPacket()
    {
        Type = PHT_ClientGuess;
    }

    int playerId = 0;
    int guess = -1;
};

struct ServerGuessResponsePacket : public GamePacket
{
    ServerGuessResponsePacket()
    {
        Type = PHT_ServerGuessResponse;
    }

    int playerId = 0;
    int nextPlayerId = 0;
    bool correct = false;
    int guess = -1;
    bool tooHigh = false;
};

//can pass in a peer connection if wanting to limit
bool CreateServer()
{
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = 1234;
    NetHost = enet_host_create(&address /* the address to bind the server host to */,
        32      /* allow up to 32 clients and/or outgoing connections */,
        2      /* allow up to 2 channels to be used, 0 and 1 */,
        0      /* assume any amount of incoming bandwidth */,
        0      /* assume any amount of outgoing bandwidth */);

    return NetHost != nullptr;
}

bool CreateClient()
{
    NetHost = enet_host_create(NULL /* create a client host */,
        1 /* only allow 1 outgoing connection */,
        2 /* allow up 2 channels to be used, 0 and 1 */,
        0 /* assume any amount of incoming bandwidth */,
        0 /* assume any amount of outgoing bandwidth */);

    return NetHost != nullptr;
}

bool AttemptConnectToServer()
{
    ENetAddress address;
    /* Connect to some.server.net:1234. */
    enet_address_set_host(&address, "127.0.0.1");
    address.port = 1234;
    /* Initiate the connection, allocating the two channels 0 and 1. */
    Peer = enet_host_connect(NetHost, &address, 2, 0);
    return Peer != nullptr;
}

void ListenForUserInput()
{
    while (running)
    {
        if (canGuess)
        {
            int guess;
            cin >> guess;
            clientGuess = guess;
            if (guess < 0)
            {
                running = false;
            }
            canGuess = false;
        }
    }
}

void SetServerRandVal()
{
    serverRandValue = rand() % MAX_RAND_VAL + 1;
}

void BroadcastIsDeadPacket()
{
    IsDeadPacket* DeadPacket = new IsDeadPacket();
    DeadPacket->IsDead = true;
    ENetPacket* packet = enet_packet_create(DeadPacket,
        sizeof(IsDeadPacket),
        ENET_PACKET_FLAG_RELIABLE);

    /* One could also broadcast the packet by         */
    enet_host_broadcast(NetHost, 0, packet);
    //enet_peer_send(event.peer, 0, packet);

    /* One could just use enet_host_service() instead. */
    //enet_host_service();
    enet_host_flush(NetHost);
    delete DeadPacket;
}

void RecieveIDFromServer(ServerAssignIDPacket* &packet)
{
    myClientID = packet->playerId;
    cout << "You are player " << myClientID << endl;
}

void SendClientGuessPacket()
{
    ClientGuessPacket* guessPacket = new ClientGuessPacket();
    guessPacket->guess = clientGuess;
    guessPacket->playerId = myClientID;
    ENetPacket* packet = enet_packet_create(guessPacket,
        sizeof(ClientGuessPacket),
        ENET_PACKET_FLAG_RELIABLE);

    /* One could also broadcast the packet by         */
    enet_host_broadcast(NetHost, 0, packet);
    //enet_peer_send(event.peer, 0, packet);

    /* One could just use enet_host_service() instead. */
    //enet_host_service();
    enet_host_flush(NetHost);
    delete guessPacket;
}

void HandleServerGuessResponse(ServerGuessResponsePacket*& packet)
{
    if (packet->playerId == -1)
    {
        // Initial game

    }
    else
    {
        cout << "Guess from player " << packet->playerId << endl;
        string wasCorrect = "right!";
        bool correct = packet->correct;
        string nextOut = "";
        if (!correct)
        {
            nextOut = "It was ";
            wasCorrect = "wrong!";
            string notString = "not ";
            if (packet->tooHigh)
            {
                notString = "";
            }
            nextOut += notString + "too high.";
        }
        else
        {
            nextOut = "A new game has started.";
        }
        cout << "Guess: " << packet->guess << " was " << wasCorrect << endl;
        cout << nextOut << endl;

    }
    
    cout << "It is now player " << packet->nextPlayerId << "'s turn!" << endl;
    if (packet->nextPlayerId == myClientID)
    {
        canGuess = true;
    }
}


void InitializeClientWithID(const ENetEvent& event)
{
    ServerAssignIDPacket* idPacket = new ServerAssignIDPacket();
    idPacket->playerId = currentClientId;
    ENetPacket* packet = enet_packet_create(idPacket,
        sizeof(ServerAssignIDPacket),
        ENET_PACKET_FLAG_RELIABLE);

    /* One could also broadcast the packet by         */
    //enet_host_broadcast(NetHost, 0, packet);
    enet_peer_send(event.peer, 0, packet);

    /* One could just use enet_host_service() instead. */
    //enet_host_service();
    enet_host_flush(NetHost);
    delete idPacket;
}

void BroadcastGuessResponse(int player, bool correct, int guess, bool tooHigh)
{
    ServerGuessResponsePacket* respPacket = new ServerGuessResponsePacket();
    respPacket->playerId = player;
    int nextPlayer;
    if (player == -1)
    {
        nextPlayer = 1;
    }
    else
    {
        // should do this with mod but....
        nextPlayer = player + 1;
        if (nextPlayer >= currentClientId)
        {
            nextPlayer = 1;
        }
    }
    
    respPacket->nextPlayerId = nextPlayer;
    respPacket->correct = correct;
    respPacket->guess = guess;
    respPacket->tooHigh = tooHigh;

    ENetPacket* packet = enet_packet_create(respPacket,
        sizeof(ServerGuessResponsePacket),
        ENET_PACKET_FLAG_RELIABLE);

    /* One could also broadcast the packet by         */
    enet_host_broadcast(NetHost, 0, packet);
    //enet_peer_send(event.peer, 0, packet);

    /* One could just use enet_host_service() instead. */
    //enet_host_service();
    enet_host_flush(NetHost);
    delete respPacket;
}


void HandleReceivePacket(const ENetEvent& event)
{
    GamePacket* RecGamePacket = (GamePacket*)(event.packet->data);
    if (RecGamePacket)
    {
        cout << "Received Game Packet " << endl;

        if (RecGamePacket->Type == PHT_IsDead)
        {
            cout << "u dead?" << endl;
            IsDeadPacket* DeadGamePacket = (IsDeadPacket*)(event.packet->data);
            if (DeadGamePacket)
            {
                string response = (DeadGamePacket->IsDead ? "yeah" : "no");
                cout << response << endl;
            }
        }
        if (IsServer)
        {
            if (RecGamePacket->Type == PHT_ClientGuess)
            {
                cout << "guess recieved" << endl;
                ClientGuessPacket* guessPacket = (ClientGuessPacket*)(event.packet->data);
                if (guessPacket)
                {
                    bool wasCorrect = guessPacket->guess == serverRandValue;
                    bool tooHigh = guessPacket->guess > serverRandValue;
                    if (wasCorrect)
                    {
                        SetServerRandVal();
                    }
                    BroadcastGuessResponse(guessPacket->playerId, wasCorrect, guessPacket->guess, tooHigh);
                }
            }
        }
        else
        {
            if (RecGamePacket->Type == PHT_ServerAssignID)
            {
                ServerAssignIDPacket* idPacket = (ServerAssignIDPacket*)(event.packet->data);
                if (idPacket)
                {
                    RecieveIDFromServer(idPacket);
                }
            }
            else if (RecGamePacket->Type == PHT_ServerGuessResponse)
            {
                ServerGuessResponsePacket* respPacket = (ServerGuessResponsePacket*)(event.packet->data);
                if (respPacket)
                {
                    HandleServerGuessResponse(respPacket);
                }
            }

        }
    }
    else
    {
        cout << "Invalid Packet " << endl;
    }

    /* Clean up the packet now that we're done using it. */
    enet_packet_destroy(event.packet);
    {
        enet_host_flush(NetHost);
    }
}

void ServerProcessPackets()
{
    /* initialize random seed: */
    srand(time(NULL));

    SetServerRandVal();

    while (1)
    {
        ENetEvent event;
        while (enet_host_service(NetHost, &event, 1000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                cout << "A new client connected from "
                    << event.peer->address.host
                    << ":" << event.peer->address.port
                    << endl;
                /* Store any relevant client information here. */
                event.peer->data = (void*)("Client information");
                InitializeClientWithID(event);
                currentClientId++;
                if (currentClientId > 2)
                {
                    Sleep(500);
                    BroadcastGuessResponse(-1, false, -1, false);
                }
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                HandleReceivePacket(event);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                cout << (char*)event.peer->data << "disconnected." << endl;
                /* Reset the peer's client information. */
                event.peer->data = NULL;
                //notify remaining player that the game is done due to player leaving
            }
        }
    }
}

void ClientProcessPackets()
{
    canGuess = false;
    thread inputThread(ListenForUserInput);

    while (running)
    {
        ENetEvent event;
        /* Wait up to 1000 milliseconds for an event. */
        while (enet_host_service(NetHost, &event, 1000) > 0)
        {
            switch (event.type)
            {
            case  ENET_EVENT_TYPE_CONNECT:
                cout << "Connection succeeded " << endl;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                HandleReceivePacket(event);
                break;
            }
        }

        if (clientGuess > 0)
        {
            SendClientGuessPacket();
            clientGuess = 0;
        }
    }

    inputThread.join();
}

int main(int argc, char** argv)
{
    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        cout << "An error occurred while initializing ENet." << endl;
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    cout << "1) Create Server " << endl;
    cout << "2) Create Client " << endl;
    int UserInput;
    cin >> UserInput;
    if (UserInput == 1)
    {
        //How many players?

        if (!CreateServer())
        {
            fprintf(stderr,
                "An error occurred while trying to create an ENet server.\n");
            exit(EXIT_FAILURE);
        }

        IsServer = true;
        cout << "waiting for players to join..." << endl;
        PacketThread = new thread(ServerProcessPackets);
    }
    else if (UserInput == 2)
    {
        if (!CreateClient())
        {
            fprintf(stderr,
                "An error occurred while trying to create an ENet client host.\n");
            exit(EXIT_FAILURE);
        }

        ENetEvent event;
        if (!AttemptConnectToServer())
        {
            fprintf(stderr,
                "No available peers for initiating an ENet connection.\n");
            exit(EXIT_FAILURE);
        }

        PacketThread = new thread(ClientProcessPackets);

        //handle possible connection failure
        {
            //enet_peer_reset(Peer);
            //cout << "Connection to 127.0.0.1:1234 failed." << endl;
        }
    }
    else
    {
        cout << "Invalid Input" << endl;
    }

    running = true;

    if (PacketThread)
    {
        PacketThread->join();
    }
    delete PacketThread;
    if (NetHost != nullptr)
    {
        enet_host_destroy(NetHost);
    }

    return EXIT_SUCCESS;
}