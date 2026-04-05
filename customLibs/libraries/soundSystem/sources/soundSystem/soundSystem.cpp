#include "soundSystem/soundSystem.h"
#include "logging/logsStruct.h"
#include "soundsPathsConsts.h"
#include <cassert>

SoundSystem::SoundSystem(AppLogFiles& logs, const std::vector< fs::path >& pathsList, unsigned expectedSoundsNumber, int expectedGroupTagsNumber):
	soundsVolume{ logs, pathsList[sounds::PATH_SND_VOLUME] },
	soundsListLoader{ logs, pathsList[sounds::PATH_SND_WAVEFORM_LIST], pathsList[sounds::PATH_SND_WAVEFORM_DIRECTORY] },
	soundPlayer{ soundsListLoader.getLoadedData(), expectedSoundsNumber, expectedGroupTagsNumber, soundsVolume.isSoundActive(), soundsVolume.getLoadedSoundVolume() },
	soundChannels{ logs, pathsList[sounds::PATH_SND_CHANNEL_CONFIG] }
{
	assert( pathsList.size() == sounds::PATH_SND_MAX );
	
	logNumberLoadedSoundError(logs, expectedSoundsNumber);
}

bool SoundSystem::wasLoadingPerfect() const
{
	return soundsVolume.wasLoadingPerfect() 
		&& soundsListLoader.wasLoadingPerfect() 
		&& soundPlayer.wasLoadingPerfect() 
		&& soundChannels.wasLoadingPerfect();
}

void SoundSystem::logNumberLoadedSoundError(AppLogFiles& logs, unsigned expectedSoundsNumber) const
{
	if( soundPlayer.size() != static_cast<std::size_t>(expectedSoundsNumber) )
	{
		logs.error << "Error: wrong loaded sounds chunks (" << soundPlayer.size() << ") versus expected sounds chunk number (" << expectedSoundsNumber << ").\n";
	}
}