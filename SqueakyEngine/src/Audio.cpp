#include "Audio.h"
#include "Audio.h"

#include <cstddef>
#include <cstdio>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include "Components/Transform.h"

bool ErrorCheck(const FMOD_RESULT& result)
{
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
		return false;
	}
	return true;
}



Audio::Audio() : system(nullptr), channel1(nullptr), channel2(nullptr), channel3(nullptr), listener(nullptr)
{

	FMOD::Sound* s = nullptr;
	std::string name;

	FMOD_RESULT result = FMOD::System_Create(&system);      // Create the main system object.

	ErrorCheck(result);

	result = system->init(512, FMOD_INIT_NORMAL, nullptr);    // Initialize FMOD.
	ErrorCheck(result);

	result = system->set3DSettings(1.0, DISTANCEFACTOR, 1.0f);
	ErrorCheck(result);




}

void Audio::Update() const
{
	const FMOD_VECTOR pos = { 0,0,0};
	const FMOD_VECTOR vel = { 0,0,0 };
	const FMOD_VECTOR up = { 0,1,0 };
	const FMOD_VECTOR forward = { 0,0,1 };

	FMOD_RESULT result = system->set3DListenerAttributes(0, &pos, &vel,&forward, &up);
	ErrorCheck(result);
	result = system->update();
	ErrorCheck(result);
}
FMOD::Sound* Audio::GetCreate(const std::string& filename)
{

	for (const auto& [key, val] : sounds)
	{
		if (key == filename)

			return val;
	}

	const std::string filepath = "src/Audio/" + filename;
	FMOD::Sound* sound = nullptr;
	FMOD_RESULT result = system->createSound(filepath.c_str(), FMOD_3D, 0, &sound);
	ErrorCheck(result);
	result = sound->set3DMinMaxDistance(0.5f * DISTANCEFACTOR, 5000.0f * DISTANCEFACTOR);
	ErrorCheck(result);
	sounds.insert(std::pair(filepath, sound));
	return sound;
}



void Audio::PlayAudio(const std::string& filename, const glm::vec3& pos, const float& volume)
{
	const FMOD_VECTOR fPos(pos.x * DISTANCEFACTOR, pos.y * DISTANCEFACTOR, pos.z * DISTANCEFACTOR);
	const FMOD_VECTOR fVel(0, 0, 0);
	FMOD_RESULT result = system->playSound(GetCreate(filename), 0, true, &channel1);
	ErrorCheck(result);
	result = channel1->set3DAttributes(&fPos, &fVel);
	ErrorCheck(result);
	result = channel1->setPaused(false);
	ErrorCheck(result);



}

void Audio::LoopSound(const std::string& filename)
{
}

void Audio::SetListener(Transform* listener_)
{
	this->listener = listener_;
}


