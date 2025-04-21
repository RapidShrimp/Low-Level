#pragma once
#include <map>
#include <string>
#include "Engine/Core/Object.h"
#include "SFML/Audio.hpp"


class AudioManger : public Object{

private:
	AudioManger(); //Prevent Direct Instantiate
	AudioManger(const AudioManger&) = delete; //Prevent Copy Constructor
	AudioManger& operator=(const AudioManger&) = delete; //Prevent Copy Assign
	static AudioManger* m_AudioManger;
	~AudioManger() {};
	
	//Load All Audio Files under a filepath
	void LoadSounds(std::string Filepath);
	void AudioCleanup();

public:
	static inline AudioManger* GetAudioInstance() /*Create / Get;*/
	{
		if (m_AudioManger == nullptr) { m_AudioManger = new AudioManger(); }
		return m_AudioManger;
	};

	static void PlaySound(std::string SoundName, unsigned int Priority = 0);
	static void PlayMusic(std::string MusicName, bool IsLooping);
	static void StopAllSounds();
	static void StopMusic();
protected:
	void Instance_PlaySound(std::string SoundName);
	void Instance_PlayMusic(std::string MusicName, bool Looping);
	std::map < std::string, sf::SoundBuffer > m_Sounds;
	std::vector<sf::Sound> m_ActiveSounds;
	sf::Music m_CurrentTrack;
};