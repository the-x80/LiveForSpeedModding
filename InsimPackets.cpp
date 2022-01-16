#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <memory>

#include "InsimPackets.h"
#include "Insim.h"

LiveForSpeed::Packets::InSim::PacketHeader::PacketHeader()
{
	//Developer note.
	//This could be an optional feature.
	//Could be disabled for a tiny speed increase.
	memset(this, 0, sizeof(PacketHeader));
}

LiveForSpeed::Packets::InSim::PacketHeader::PacketHeader(PacketHeader& other) :
	Size(other.Size),
	Type(other.Type),
	ReqI(other.ReqI),
	Zero(other.Zero)
{
}

LiveForSpeed::Packets::InSim::PacketHeader::PacketHeader(PacketHeader&& other) noexcept
{
}

LiveForSpeed::Packets::InSim::PacketHeader::PacketHeader(unsigned char size, unsigned char type, unsigned char reqi, unsigned char zero) :
	Size(size),
	Type(type),
	ReqI(reqi),
	Zero(zero)
{
}

LiveForSpeed::Packets::InSim::PacketHeader::~PacketHeader()
{
}

LiveForSpeed::Packets::InSim::Packet::Packet() :
	header()
{
}

LiveForSpeed::Packets::InSim::Packet::Packet(unsigned char size, PacketTypeIdentifier type, unsigned char reqi, unsigned char zero):
	header(size, (unsigned char)type, reqi, zero)
{
}

LiveForSpeed::Packets::InSim::Packet::Packet(unsigned char version, unsigned char size, PacketTypeIdentifier type, unsigned char reqi, unsigned char zero) :
	header(version >= 9 ? size/4 : size, (unsigned char)type, reqi, zero)
{
}

LiveForSpeed::Packets::InSim::Packet::Packet(unsigned char version, size_t size, PacketTypeIdentifier type, unsigned char reqi, unsigned char zero) :
	header(version >= 9 ? (unsigned char)(size / 4) : (unsigned char)size, (unsigned char)type, reqi, zero)
{
}

LiveForSpeed::Packets::InSim::Packet::Packet(Packet& other) :
	header(other.header)
{
}

LiveForSpeed::Packets::InSim::Packet::Packet(Packet&& other) noexcept
{
}

LiveForSpeed::Packets::InSim::Packet::~Packet()
{
}

LiveForSpeed::Packets::InSim::InitializationPacket::InitializationPacket() :
	Packet(sizeof(InitializationPacket), PacketTypeIdentifier::Initialization, 0, 0),
	UDPPort(0),
	Flags(InitializationFlags::Reserved0),
	InSimVer(InsimClient::HighestSupportedVersion),
	Prefix('!'),
	Interval(0),
	Admin("\0"),
	IName("\0")
{
}

LiveForSpeed::Packets::InSim::InitializationPacket::InitializationPacket(short udp_port, InitializationFlags flags, int version, char prefix, short interval, const char* admin, const char* iname):
	Packet(sizeof(InitializationPacket), PacketTypeIdentifier::Initialization, 0, 0),
	UDPPort(udp_port),
	Flags(flags),
	InSimVer(version),
	Prefix(prefix),
	Interval(interval),
	Admin("\0"),
	IName("\0")
{
	memcpy(this->Admin, admin, sizeof(char)*16);
	memcpy(this->IName, iname, sizeof(char) * 16);
}

LiveForSpeed::Packets::InSim::InitializationPacket::InitializationPacket(InitializationPacket& other):
	Packet(sizeof(InitializationPacket), PacketTypeIdentifier::Initialization, 0, 0),
	UDPPort(other.UDPPort),
	Flags(other.Flags),
	InSimVer(other.InSimVer),
	Prefix(other.Prefix),
	Interval(other.Interval),
	Admin("\0"),
	IName("\0")
{
	memcpy(this->Admin, other.Admin, sizeof(char) * 16);
	memcpy(this->IName, other.IName, sizeof(char) * 16);
}

LiveForSpeed::Packets::InSim::InitializationPacket::InitializationPacket(InitializationPacket&& other)
{
}

LiveForSpeed::Packets::InSim::InitializationPacket::~InitializationPacket()
{
}

size_t LiveForSpeed::Packets::InSim::InitializationPacket::Size()
{
	return sizeof(InitializationPacket);
}

LiveForSpeed::Packets::InSim::VersionPacket::VersionPacket() :
	Packet(InsimClient::HighestSupportedVersion, sizeof(VersionPacket), PacketTypeIdentifier::Version, 0, 0),
	LFSVersion{ 0 },
	LFSProduct{ 0 },
	InSimVersion(InsimClient::HighestSupportedVersion),
	Spare0(0)
{
}

LiveForSpeed::Packets::InSim::VersionPacket::VersionPacket(unsigned char version) :
	Packet(version, sizeof(VersionPacket), PacketTypeIdentifier::Version, 0, 0),
	LFSVersion{ 0 },
	LFSProduct{ 0 },
	InSimVersion(version),
	Spare0(0)
{
}

LiveForSpeed::Packets::InSim::VersionPacket::VersionPacket(VersionPacket& other)
{
}

LiveForSpeed::Packets::InSim::VersionPacket::VersionPacket(VersionPacket&& other) noexcept
{
}

LiveForSpeed::Packets::InSim::VersionPacket::~VersionPacket()
{
}

size_t LiveForSpeed::Packets::InSim::VersionPacket::Size()
{
	return sizeof(VersionPacket);
}

LiveForSpeed::Packets::InSim::TinyPacket::TinyPacket() : 
	Packet(InsimClient::HighestSupportedVersion, sizeof(TinyPacket), PacketTypeIdentifier::Tiny, 0, 0)
{
}

LiveForSpeed::Packets::InSim::TinyPacket::TinyPacket(unsigned int version) :
	Packet(version, sizeof(TinyPacket), PacketTypeIdentifier::Tiny, 0, 0)
{
}

LiveForSpeed::Packets::InSim::TinyPacket::TinyPacket(unsigned int version, unsigned char SubT) :
	Packet(version, sizeof(TinyPacket), PacketTypeIdentifier::Tiny, 0, SubT)
{
}

LiveForSpeed::Packets::InSim::TinyPacket::TinyPacket(TinyPacket& other) :
	Packet(other)
{
}

LiveForSpeed::Packets::InSim::TinyPacket::TinyPacket(TinyPacket&& other) noexcept
{
}

LiveForSpeed::Packets::InSim::TinyPacket::~TinyPacket()
{
}

size_t LiveForSpeed::Packets::InSim::TinyPacket::Size()
{
	return sizeof(TinyPacket);
}

LiveForSpeed::Packets::InSim::SmallPacket::SmallPacket()
{
}

LiveForSpeed::Packets::InSim::SmallPacket::SmallPacket(unsigned int version)
{
}

LiveForSpeed::Packets::InSim::SmallPacket::SmallPacket(unsigned int version, unsigned int uval)
{
}

LiveForSpeed::Packets::InSim::SmallPacket::SmallPacket(SmallPacket& other)
{
}

LiveForSpeed::Packets::InSim::SmallPacket::SmallPacket(SmallPacket&& other)
{
}

LiveForSpeed::Packets::InSim::SmallPacket::~SmallPacket()
{
}

size_t LiveForSpeed::Packets::InSim::SmallPacket::Size()
{
	return sizeof(SmallPacket);
}

LiveForSpeed::Packets::InSim::StatePacket::StatePacket() :
	Packet(InsimClient::HighestSupportedVersion, sizeof(StatePacket), PacketTypeIdentifier::State, 0, 0),
	ReplaySpeed(0.0f),
	Flags(StateFlags::None),
	InGameCam((ViewIdentifier)0),
	ViewedPLID(0),
	NumberOfPlayers(0),
	NumberOfConnections(0),
	NumberOfFinishers(0),
	RaceProgressState(0),
	QualiMinutes(0),
	RaceLaps(0),
	Spare0(0),
	ServerState(0),
	TrackShortName{ 0 },
	Weather(0),
	Wind(0)
{
}

LiveForSpeed::Packets::InSim::StatePacket::StatePacket(unsigned int version):
	Packet(version, sizeof(StatePacket), PacketTypeIdentifier::State, 0, 0),
	ReplaySpeed(0.0f),
	Flags(StateFlags::None),
	InGameCam((ViewIdentifier)0),
	ViewedPLID(0),
	NumberOfPlayers(0),
	NumberOfConnections(0),
	NumberOfFinishers(0),
	RaceProgressState(0),
	QualiMinutes(0),
	RaceLaps(0),
	Spare0(0),
	ServerState(0),
	TrackShortName{ 0 },
	Weather(0),
	Wind(0)
{
}

LiveForSpeed::Packets::InSim::StatePacket::StatePacket(StatePacket& other):
	Packet(other),
	ReplaySpeed(other.ReplaySpeed),
	Flags(other.Flags),
	InGameCam(other.InGameCam),
	ViewedPLID(other.ViewedPLID),
	NumberOfPlayers(other.NumberOfPlayers),
	NumberOfConnections(other.NumberOfConnections),
	NumberOfFinishers(other.NumberOfFinishers),
	RaceProgressState(other.RaceProgressState),
	QualiMinutes(other.QualiMinutes),
	RaceLaps(other.RaceLaps),
	Spare0(other.Spare0),
	ServerState(other.ServerState),
	TrackShortName{ 0 },
	Weather(other.Weather),
	Wind(other.Wind)
{
	memcpy(this->TrackShortName, other.TrackShortName, sizeof(char) * 6);
}

LiveForSpeed::Packets::InSim::StatePacket::StatePacket(StatePacket&& other) noexcept
{
}

LiveForSpeed::Packets::InSim::StatePacket::~StatePacket()
{
}

LiveForSpeed::Packets::InSim::StateFlagsPacket::StateFlagsPacket():
	Packet(InsimClient::HighestSupportedVersion, sizeof(StateFlagsPacket), PacketTypeIdentifier::StateFlags, 0, 0),
	Flag(StateFlags::None),
	State(0)
{
}

LiveForSpeed::Packets::InSim::StateFlagsPacket::StateFlagsPacket(unsigned int version):
	Packet(version, sizeof(StateFlagsPacket), PacketTypeIdentifier::StateFlags, 0, 0),
	Flag(StateFlags::None),
	State(0)
{
}

LiveForSpeed::Packets::InSim::StateFlagsPacket::StateFlagsPacket(StateFlagsPacket& other):
	Packet(other),
	Flag(other.Flag),
	State(other.State)
{
}

LiveForSpeed::Packets::InSim::StateFlagsPacket::StateFlagsPacket(StateFlagsPacket&& other) noexcept
{
}

LiveForSpeed::Packets::InSim::StateFlagsPacket::~StateFlagsPacket()
{
}

LiveForSpeed::Packets::InSim::ScreenModePacket::ScreenModePacket() :
	Packet(InsimClient::HighestSupportedVersion, sizeof(ScreenModePacket), PacketTypeIdentifier::ScreenMode, 0, 0),
	Bit16(0),
	RefreshRate(0),
	Width(0),
	Height(0)
{
}

LiveForSpeed::Packets::InSim::ScreenModePacket::ScreenModePacket(unsigned int version):
	Packet(version, sizeof(ScreenModePacket), PacketTypeIdentifier::ScreenMode, 0, 0),
	Bit16(0),
	RefreshRate(0),
	Width(0),
	Height(0)
{
}

LiveForSpeed::Packets::InSim::ScreenModePacket::ScreenModePacket(ScreenModePacket& other):
	Packet(other),
	Bit16(other.Bit16),
	RefreshRate(other.RefreshRate),
	Width(other.Width),
	Height(other.Height)
{
}

LiveForSpeed::Packets::InSim::ScreenModePacket::ScreenModePacket(ScreenModePacket&& other) noexcept
{
}

LiveForSpeed::Packets::InSim::ScreenModePacket::~ScreenModePacket()
{
}

LiveForSpeed::Packets::InSim::MessageOutPacket::MessageOutPacket() :
	Packet(InsimClient::HighestSupportedVersion, sizeof(MessageOutPacket), PacketTypeIdentifier::MessageOut, 0, 0),
	UCID(0),
	PLID(0),
	UserType(MessageUserTypes::System),
	TextStart(0),
	Message{ 0 }
{
}

LiveForSpeed::Packets::InSim::MessageOutPacket::MessageOutPacket(unsigned int version):
	Packet(version, sizeof(MessageOutPacket), PacketTypeIdentifier::MessageOut, 0, 0),
	UCID(0),
	PLID(0),
	UserType(MessageUserTypes::System),
	TextStart(0),
	Message{ 0 }
{
}

LiveForSpeed::Packets::InSim::MessageOutPacket::MessageOutPacket(unsigned int version, char* message):
	Packet(version, sizeof(MessageOutPacket), PacketTypeIdentifier::MessageOut, 0, 0),
	UCID(0),
	PLID(0),
	UserType(MessageUserTypes::System),
	TextStart(0),
	Message{ 0 }
{
	this->SetMessage(message);
}

LiveForSpeed::Packets::InSim::MessageOutPacket::MessageOutPacket(MessageOutPacket& other):
	Packet(other),
	UCID(other.UCID),
	PLID(other.PLID),
	UserType(other.UserType),
	TextStart(other.TextStart),
	Message{ 0 }
{
	this->SetMessage(other.Message);
}

LiveForSpeed::Packets::InSim::MessageOutPacket::MessageOutPacket(MessageOutPacket&& other) noexcept
{
}

LiveForSpeed::Packets::InSim::MessageOutPacket::~MessageOutPacket()
{
}

int LiveForSpeed::Packets::InSim::MessageOutPacket::SetMessage(char* message)
{
	memset(this->Message, 0, sizeof(char) * 128);
	if (strlen(message) + 1 >= 128) {
		return -1;
	}

	strcpy(this->Message, message);
	return strlen(this->Message)+1;
}