#pragma once
#ifndef DRAG_API_H
#include <DragAPI.h>
#pragma comment(lib, "DragAPI.lib")
#endif

#include <string>
#include <math.h>
#include <vector>
#include "InsimPackets.h"

namespace LiveForSpeed {
	class InsimClient;
	class Player;
	class Connection;

	/// <summary>
	/// Base interface for creating InSim behaviours
	/// </summary>
	class IInsimBehaviour {
	public:
		InsimClient* insimClient;

		virtual void RegisterEvents() = 0;
		virtual void UnRegisterEvents() = 0;
	};
	class IPlayerBehaviour {
	public:
		Player* player;
	};
	class IConnectionBehaviour {
	public:
		Connection* connection;
	};

	class RaceInfo {
	public:
		std::vector<Player*> drivers;
	};
	class SplitInfo {
	public:
		DragAPI::DateTime splitTime;
	};
	class LapInfo {
	public:
		std::vector<SplitInfo> splits;
		DragAPI::DateTime lapTime;
	};

	class Player {
	public:
		Connection* connection;
		wchar_t* PName;
		int PLID;
	};
	class PlayerList {
	private:
		std::vector<Player> players;
	public:
	};
	class Connection {
	public:
		std::vector<Player*> players;
		int UCID;
		wchar_t* UName;
	};
	class ConnectionList {
	private:
		std::vector<Connection> connections;
	public:
	};

	class InsimButton {
	public:
		int id;
		bool isShown;
		DragAPI::Rect<int> rect;
		wchar_t* caption;

		InsimButton();
		InsimButton(InsimButton& other);
		InsimButton(InsimButton&& other);
		~InsimButton();
	};
	class InsimButtonList {
	private:
		std::vector<InsimButton> buttons;
		
	public:
		static const int MaxButtonCount = 240;
	};

	class InsimClient {
	public:
		enum class StateFlags {
			None = 0b0,
			Initialized = 0b1,
			Connected = 0b10
		};
	private:
		std::vector<IInsimBehaviour*> behaviours;

		PlayerList playerList;
		ConnectionList connectionList;

		DragAPI::Networking::Socket socketTCP;
		DragAPI::Networking::Socket socketUDP;
	protected:
	public:
		static const int HighestSupportedVersion = 9;



		InsimClient();
		~InsimClient();

		/// <summary>
		/// Initializes the insim client
		/// </summary>
		void Initialize();

		/// <summary>
		/// Connects to the InSim host
		/// </summary>
		void Connect();

		/// <summary>
		/// Softly disconnects from the InSim host
		/// </summary>
		void Disconnect();

		/// <summary>
		/// Cleans up the InSim client
		/// </summary>
		void Cleanup();
	};
}