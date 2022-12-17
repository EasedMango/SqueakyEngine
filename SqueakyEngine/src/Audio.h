#pragma once
#include <vector>
#include <map>
#include <string>
#include <glm/vec3.hpp>
namespace FMOD
{
	class System;
	class Sound;
	class Channel;
}


class Audio
{
private:
	const int   INTERFACE_UPDATETIME = 50;      // 50ms update for interface
	const float DISTANCEFACTOR = 1.0f;          // Units per meter.  I.e feet would = 3.28.  centimeters would = 100.
	FMOD::System* system;
	FMOD::Channel* channel1, * channel2, * channel3;

	class Transform* listener;


	typedef  std::map< std::string, FMOD::Sound*> Sounds;

	typedef  std::map< int, FMOD::Channel*> Channels;

	Sounds sounds;
	Channels channels;

public:
	Audio();
	void Update() const;
	FMOD::Sound* GetCreate(const std::string& filename);
	void PlayAudio(const std::string& filename,const glm::vec3& pos,const float& volume =1 );

	void LoopSound(const std::string& filename);
	void SetListener(class Transform* listener_);
};

