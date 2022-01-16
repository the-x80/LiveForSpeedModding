#pragma once
#ifndef LIVE_FOR_SPEED_INSIM_PACKETS_H
#define LIVE_FOR_SPEED_INSIM_PACKETS_H

/*
Developement notes:
	1.) 15.1.2022
		Currently the way its designed a change in structure would require compleete refactoring.
		Maybe there should be a system where the structure of the packets is programmatically determined and sized

*/

namespace LiveForSpeed {
	namespace Packets {
		namespace InSim {
			enum class PacketTypeIdentifier : unsigned char {
				None,
				Initialization,
				Version,
				Tiny,
				Small,
				State,
				StateFlags = 7,
				MessageOut = 11,
				ScreenMode = 15
			};

			struct PacketHeader {
				unsigned char Size;
				unsigned char Type;
				unsigned char ReqI;
				unsigned char Zero;

				PacketHeader();
				PacketHeader(PacketHeader& other);
				PacketHeader(PacketHeader&& other) noexcept;
				PacketHeader(unsigned char size, unsigned char type, unsigned char reqi = 0, unsigned char zero = 0);
				~PacketHeader();
			};
			struct Packet {
				PacketHeader header;

				Packet();
				Packet(unsigned char size, PacketTypeIdentifier type, unsigned char reqi = 0, unsigned char zero = 0);
				Packet(unsigned char version, unsigned char size, PacketTypeIdentifier type, unsigned char reqi = 0, unsigned char zero = 0);
				Packet(unsigned char version, size_t size, PacketTypeIdentifier type, unsigned char reqi = 0, unsigned char zero = 0);
				Packet(Packet& other);
				Packet(Packet&& other) noexcept;
				~Packet();

				virtual size_t Size() = 0;
				int CopyToBuffer(char* buffer, size_t bufferSize);
			};

			enum class InitializationFlags : short {
				None = 0,
				Reserved0 = 1,
				Reserved1 = 2,
				Local = 4,
				MessageColors = 8,
				NodeLapPacket = 16,
				MultiCarInfo = 32,
				CON = 64,//Edit this
				OBH = 128,//Edit this
				HotLapValidation = 256,
				AutocrossLoad = 512,
				AutocrossEdit = 1024,
				ProcessJoinRequests = 2048
			};

			/// <summary>
			/// Packet used to initialize the connection between the InSimClient and InSimHost
			/// This is the first packet that is sent after establishing a connection.
			/// </summary>
			struct InitializationPacket : public Packet {
				short UDPPort;
				InitializationFlags Flags;

				unsigned char InSimVer;
				char Prefix;

				short Interval;

				char Admin[16];
				char IName[16];

				InitializationPacket();
				InitializationPacket(short udp_port, InitializationFlags flags, int version, char prefix, short interval, const char* admin, const char* iname);
				InitializationPacket(InitializationPacket& other);
				InitializationPacket(InitializationPacket&& other);
				~InitializationPacket();

				size_t Size() override;
			};

			struct VersionPacket : public Packet {
				char LFSVersion[8];
				char LFSProduct[6];

				unsigned char InSimVersion;
				unsigned char Spare0;

				VersionPacket();
				explicit VersionPacket(unsigned char version);
				VersionPacket(VersionPacket& other);
				VersionPacket(VersionPacket&& other) noexcept;
				~VersionPacket();

				size_t Size() override;
			};

			struct TinyPacket : public Packet {
				TinyPacket();
				explicit TinyPacket(unsigned int version);
				explicit TinyPacket(unsigned int version, unsigned char SubT);
				TinyPacket(TinyPacket& other);
				TinyPacket(TinyPacket&& other) noexcept;
				~TinyPacket();

				size_t Size() override;
			};
			struct SmallPacket : public Packet {
				unsigned int UVal;

				SmallPacket();
				explicit SmallPacket(unsigned int version);
				explicit SmallPacket(unsigned int version, unsigned int uval);
				SmallPacket(SmallPacket& other);
				SmallPacket(SmallPacket&& other);
				~SmallPacket();

				size_t Size() override;
			};
			struct TargetToConnectionPacket : public Packet {
				unsigned char UCID;
				unsigned char B1;
				unsigned char B2;
				unsigned char B3;
			};

			enum class StateFlags : unsigned short {
				None = 0,
				InGame = 1,
				Replay = 2,
				Paused = 4,
				ShiftU = 8,
				Dialog = 16,
				ShiftUFollow = 32,
				ShiftUNoOptions = 64,
				Show2D = 128,
				Entry = 256,
				Multiplayer = 512,
				MultiplayerSpeedup = 1024,
				Windowed = 2048,
				SoundMute = 4096,
				ViewOverride = 8192,
				ButtonsVisible = 16384,
				TextEntry = 32768
			};
			enum class ViewIdentifier : unsigned char {
				Follow,
				Heli,
				TV,
				Driver,
				Custom
			};
			struct StatePacket : public Packet {
				float ReplaySpeed;

				StateFlags Flags;
				ViewIdentifier InGameCam;
				unsigned char ViewedPLID;

				unsigned char NumberOfPlayers;
				unsigned char NumberOfConnections;

				unsigned char NumberOfFinishers;
				unsigned char RaceProgressState;

				unsigned char QualiMinutes;
				unsigned char RaceLaps;

				unsigned char Spare0;
				unsigned char ServerState;

				char TrackShortName[6];
				unsigned char Weather;
				unsigned char Wind;


				StatePacket();
				explicit StatePacket(unsigned int version);
				StatePacket(StatePacket& other);
				StatePacket(StatePacket&& other) noexcept;
				~StatePacket();
			};
			struct StateFlagsPacket : public Packet {
				StateFlags Flag;
				unsigned char State;
				unsigned char Spare0;

				StateFlagsPacket();
				explicit StateFlagsPacket(unsigned int version);
				StateFlagsPacket(StateFlagsPacket& other);
				StateFlagsPacket(StateFlagsPacket&& other) noexcept;
				~StateFlagsPacket();
			};

			struct ScreenModePacket : public Packet {
				int Bit16;
				int RefreshRate;
				int Width;
				int Height;

				ScreenModePacket();
				explicit ScreenModePacket(unsigned int version);
				ScreenModePacket(ScreenModePacket& other);
				ScreenModePacket(ScreenModePacket&& other) noexcept;
				~ScreenModePacket();
			};

			enum class MessageUserTypes : unsigned char {
				System,
				User,
				Prefix,
				O
			};
			struct MessageOutPacket : public Packet {
				unsigned char UCID;
				unsigned char PLID;
				MessageUserTypes UserType;
				unsigned char TextStart;

			private:
				char Message[128];
			public:


				MessageOutPacket();
				explicit MessageOutPacket(unsigned int version);
				MessageOutPacket(unsigned int version, char* message);
				MessageOutPacket(unsigned int version, const char* message);
				MessageOutPacket(MessageOutPacket& other);
				MessageOutPacket(MessageOutPacket&& other) noexcept;
				~MessageOutPacket();


				int SetMessage(char* message);
				int SetMessage(const char* message);
			};
		}
	}
}

#endif