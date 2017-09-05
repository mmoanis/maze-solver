#pragma once

#include <SFML/Audio.hpp>
#include <map>

class MPlayer;

class MPlayer
{
public:
    using MPMusic_idx = unsigned short;
    static const MPMusic_idx MPMusic_idx_INVALID;

    static MPlayer & GetMPlayer();

    MPlayer(const MPlayer&) = delete;
    MPlayer& operator=(const MPlayer&) = delete;
    virtual ~MPlayer();

    // Load music file, return its reference id.
    MPMusic_idx LoadMusic(std::string filename);

    // Unload music and delete its index.
    bool DisposeMusic(const MPMusic_idx & i);

    void PlayMusic(const MPMusic_idx & i);
    void StopMusic(const MPMusic_idx & i);
    void PauseMusic(const MPMusic_idx & i);

protected:
    MPlayer();

    using AlbumImpl = std::map<MPMusic_idx, sf::SoundBuffer*>;

    AlbumImpl m_musicAlbum;
    sf::Sound m_soundPlayer;
};
