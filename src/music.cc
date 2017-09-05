#include <music.hpp>

const MPlayer::MPMusic_idx MPlayer::MPMusic_idx_INVALID = 0;

MPlayer&
MPlayer::GetMPlayer()
{
    static MPlayer mPlayer_Instance;
    return mPlayer_Instance;
}

MPlayer::MPlayer()
{

}

MPlayer::~MPlayer()
{

}

// Load music file, return its reference id.
MPlayer::MPMusic_idx
MPlayer::LoadMusic(std::string filename)
{
    //static MPMusic_idx LAST_IDX = 1;

    return MPMusic_idx_INVALID;
}

// Unload music and delete its index.
bool
MPlayer::DisposeMusic(const MPMusic_idx & i)
{
    return false;
}

void
MPlayer::PlayMusic(const MPMusic_idx & i)
{

}

void
MPlayer::StopMusic(const MPMusic_idx & i)
{

}

void
MPlayer::PauseMusic(const MPMusic_idx & i)
{

}
