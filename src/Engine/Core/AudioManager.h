#pragma once
#include <vector>
#include <string>
#include "Engine/Core/Object.h"
#include "SFML/Audio.hpp"


class AudioManger : public Object{

private:
	AudioManger() { SetName("Audio Manager"); }; //Prevent Direct Instantiate
	AudioManger(const AudioManger&) = delete; //Prevent Copy Constructor
	AudioManger& operator=(const AudioManger&) = delete; //Prevent Copy Assign
	static AudioManger* m_AudioManger;
	~AudioManger() {};

public:
	static inline AudioManger* GetGameInstance() /*Create / Get;*/
	{
		if (m_AudioManger == nullptr) { m_AudioManger = new AudioManger(); }
		return m_AudioManger;
	};

	static void PlaySound(std::string AudioFilePath, unsigned int Priority = 0);
	static void PlayMusic(std::string MusicFilePath, bool IsLooping);
};