#pragma once

#include <SDL_mixer.h>
#include "Common.hpp"
#include "Singleton.hpp"
#include "ResourceManager.hpp"

class AudioManager: public Singleton<AudioManager>{
public:
    void PlaySound(const string& filePath, int volume);
private:
    static const int MAX_PENDING = 16;
};