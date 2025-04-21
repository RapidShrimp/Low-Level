#pragma once
#include "AudioManager.h"
#include "Engine/Core/Libs/GameFunctionLib.h"

AudioManger::AudioManger()
{
	SetName("Audio Manager");
	LoadSounds("Assets/Audio/Sounds");
}

void AudioManger::LoadSounds(std::string Filepath)
{

	//Use auto here becuase potential of wav or mp3
	for(const auto& AudioFile : std::filesystem::directory_iterator(Filepath))
	{
		assert("The filepath for sounds may not contain any file other than '.wav' files, please check your directory", !AudioFile.path().filename().string().find(".wav"));

		sf::SoundBuffer buffer(AudioFile.path().string());
		m_Sounds.insert({ AudioFile.path().filename().string(), buffer });

		
	}
	Debug::Log(this, Confirm, "Loaded All Sounds!");
}

void AudioManger::AudioCleanup()
{
	for (std::vector<sf::Sound>::iterator AudioFile = m_ActiveSounds.begin(); AudioFile != m_ActiveSounds.end();)
	{
		if (AudioFile->getStatus() == sf::Sound::Status::Stopped) {
			m_ActiveSounds.erase(AudioFile);
		}
	}
}

void AudioManger::PlaySound(std::string SoundName, unsigned int Priority)
{
	GetAudioInstance()->Instance_PlaySound(SoundName);
}

void AudioManger::PlayMusic(std::string MusicFilePath, bool IsLooping)
{
	GetAudioInstance()->Instance_PlayMusic(MusicFilePath,IsLooping); 
}

void AudioManger::Instance_PlaySound(std::string SoundName)
{
	m_ActiveSounds.emplace_back(m_Sounds[SoundName]);
	sf::Sound PlaySound(m_Sounds[SoundName]);
	m_ActiveSounds.back().play();
}

void AudioManger::Instance_PlayMusic(std::string MusicName, bool Looping)
{
	m_CurrentTrack.setLooping(Looping);
	if (!m_CurrentTrack.openFromFile("Assets/Audio/Music/" + MusicName)) 
	{
		Debug::Log(this, Error, "No File Found to play Music:" + MusicName);
		return;
	}

	m_CurrentTrack.play();
	Debug::Log(this, Confirm, "Playing Theme: " + MusicName);
}
