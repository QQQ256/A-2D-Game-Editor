#include "AudioManager.hpp"

void AudioManager::PlaySound(const string &filePath, int volume)
{
    Mix_Chunk* sound = ResourceManager::GetInstance().LoadSound(filePath);
    if (sound != nullptr)
    {
        Mix_VolumeChunk(sound, volume);
        if (Mix_PlayChannel(-1, sound, 0) == -1)
        {
            std::cerr << "Error playing sound: " << Mix_GetError() << std::endl;
        }
        Mix_PlayChannel(-1, sound, 0);
    }
}