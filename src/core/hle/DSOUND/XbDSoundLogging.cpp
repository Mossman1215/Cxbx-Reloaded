// ******************************************************************
// *
// *    .,-:::::    .,::      .::::::::.    .,::      .:
// *  ,;;;'````'    `;;;,  .,;;  ;;;'';;'   `;;;,  .,;;
// *  [[[             '[[,,[['   [[[__[[\.    '[[,,[['
// *  $$$              Y$$$P     $$""""Y$$     Y$$$P
// *  `88bo,__,o,    oP"``"Yo,  _88o,,od8P   oP"``"Yo,
// *    "YUMMMMMP",m"       "Mm,""YUMMMP" ,m"       "Mm,
// *
// *   src->core->HLE->DSound->XbDSoundLogging.cpp
// *
// *  This file is part of the Cxbx project.
// *
// *  Cxbx and Cxbe are free software; you can redistribute them
// *  and/or modify them under the terms of the GNU General Public
// *  License as published by the Free Software Foundation; either
// *  version 2 of the license, or (at your option) any later version.
// *
// *  This program is distributed in the hope that it will be useful,
// *  but WITHOUT ANY WARRANTY; without even the implied warranty of
// *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// *  GNU General Public License for more details.
// *
// *  You should have recieved a copy of the GNU General Public License
// *  along with this program; see the file COPYING.
// *  If not, write to the Free Software Foundation, Inc.,
// *  59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
// *
// *  (c) 2019 RadWolfie
// *
// *  All rights reserved
// *
// ******************************************************************

#include <dsound.h> // Temporary placeholder until XbDSoundTypes.h is cross-platform + filled in the blanks
#include "Logging.h"
#include "XbDSoundLogging.hpp"
// For XTL::DSBUFFERDESC and XTL::DSSTREAMDESC temporary usage
extern LOGRENDER_HEADER(WAVEFORMATEX)
extern LOGRENDER_HEADER(D3DVECTOR)

namespace XTL {

// DSound class usage
ENUM2STR_START(DSMIXBIN_SPEAKER)
	ENUM2STR_CASE(XDSMIXBIN_FRONT_LEFT)
	ENUM2STR_CASE(XDSMIXBIN_FRONT_RIGHT)
	ENUM2STR_CASE(XDSMIXBIN_FRONT_CENTER)
	ENUM2STR_CASE(XDSMIXBIN_LOW_FREQUENCY)
	ENUM2STR_CASE(XDSMIXBIN_BACK_LEFT)
	ENUM2STR_CASE(XDSMIXBIN_BACK_RIGHT)
	//ENUM2STR_CASE(XDSMIXBIN_SPEAKERS_MAX) // NOTE: Only used as a counter.
ENUM2STR_END_and_LOGRENDER(DSMIXBIN_SPEAKER)

FLAGS2STR_START(DSSPEAKER_FLAG)
	FLAG2STR(X_DSSPEAKER_STEREO)
	FLAG2STR(X_DSSPEAKER_MONO)
	FLAG2STR(X_DSSPEAKER_SURROUND)
	FLAG2STR(X_DSSPEAKER_ENABLE_AC3)
	FLAG2STR(X_DSSPEAKER_ENABLE_DTS)
FLAGS2STR_END_and_LOGRENDER(DSSPEAKER_FLAG)

// DSound generic flag/enum
ENUM2STR_START(DSFILTER_MODE)
	ENUM2STR_CASE(DSFILTER_MODE_BYPASS)
	ENUM2STR_CASE(DSFILTER_MODE_DLS2)
	ENUM2STR_CASE(DSFILTER_MODE_PARAMEQ)
	ENUM2STR_CASE(DSFILTER_MODE_MULTI)
ENUM2STR_END_and_LOGRENDER(DSFILTER_MODE)

// DSound Buffer flag/enum
FLAGS2STR_START(DSBCAPS_FLAG)
	FLAG2STR(XTL_DSBCAPS_CTRL3D)
	FLAG2STR(XTL_DSBCAPS_CTRLFREQUENCY)
	FLAG2STR(XTL_DSBCAPS_CTRLVOLUME)
	FLAG2STR(XTL_DSBCAPS_CTRLPOSITIONNOTIFY)
	FLAG2STR(XTL_DSBCAPS_MIXIN)
	FLAG2STR(XTL_DSBCAPS_MUTE3DATMAXDISTANCE)
	FLAG2STR(XTL_DSBCAPS_LOCDEFER)
	FLAG2STR(XTL_DSBCAPS_FXIN)
	FLAG2STR(XTL_DSBCAPS_FXIN2)
FLAGS2STR_END_and_LOGRENDER(DSBCAPS_FLAG)

FLAGS2STR_START(DSBPAUSE_FLAG)
	FLAG2STR(X_DSBPAUSE_RESUME)
	FLAG2STR(X_DSBPAUSE_PAUSE)
	FLAG2STR(X_DSBPAUSE_SYNCHPLAYBACK)
FLAGS2STR_END_and_LOGRENDER(DSBPAUSE_FLAG)

FLAGS2STR_START(DSBPLAY_FLAG)
	FLAG2STR(X_DSBPLAY_LOOPING)
	FLAG2STR(X_DSBPLAY_FROMSTART)
	FLAG2STR(X_DSBPLAY_SYNCHPLAYBACK)
FLAGS2STR_END_and_LOGRENDER(DSBPLAY_FLAG)

FLAGS2STR_START(DSBSTATUS_FLAG)
	FLAG2STR(X_DSBSTATUS_PLAYING)
	FLAG2STR(X_DSBSTATUS_PAUSED)
	FLAG2STR(X_DSBSTATUS_LOOPING)
FLAGS2STR_END_and_LOGRENDER(DSBSTATUS_FLAG)

FLAGS2STR_START(DSBSTOPEX_FLAG)
	FLAG2STR(X_DSBSTOPEX_IMMEDIATE)
	FLAG2STR(X_DSBSTOPEX_ENVELOPE)
	FLAG2STR(X_DSBSTOPEX_RELEASEWAVEFORM)
	//FLAG2STR(X_DSBSTOPEX_ALL) // NOTE: Only a combine of envelope and releasewaveform flags together.
FLAGS2STR_END_and_LOGRENDER(DSBSTOPEX_FLAG)

// DSound Stream flag/enum
FLAGS2STR_START(DSSCAPS_FLAG)
	FLAG2STR(XTL_DSSCAPS_CTRL3D)
	FLAG2STR(XTL_DSSCAPS_CTRLFREQUENCY)
	FLAG2STR(XTL_DSSCAPS_CTRLVOLUME)
	FLAG2STR(XTL_DSSCAPS_MUTE3DATMAXDISTANCE)
	FLAG2STR(XTL_DSSCAPS_LOCDEFER)
	FLAG2STR(XTL_DSSCAPS_NOMERGE)
	FLAG2STR(XTL_DSSCAPS_ACCURATENOTIFY)
FLAGS2STR_END_and_LOGRENDER(DSSCAPS_FLAG)

FLAGS2STR_START(DSSFLUSHEX_FLAG)
	FLAG2STR(X_DSSFLUSHEX_IMMEDIATE)
	FLAG2STR(X_DSSFLUSHEX_ASYNC)
	FLAG2STR(X_DSSFLUSHEX_ENVELOPE)
	FLAG2STR(X_DSSFLUSHEX_ENVELOPE2)
FLAGS2STR_END_and_LOGRENDER(DSSFLUSHEX_FLAG)

FLAGS2STR_START(DSSPAUSE_FLAG)
	FLAG2STR(X_DSSPAUSE_RESUME)
	FLAG2STR(X_DSSPAUSE_PAUSE)
	FLAG2STR(X_DSSPAUSE_SYNCHPLAYBACK)
	FLAG2STR(X_DSSPAUSE_PAUSENOACTIVATE)
FLAGS2STR_END_and_LOGRENDER(DSSPAUSE_FLAG)

FLAGS2STR_START(DSSSTATUS_FLAG)
	FLAG2STR(X_DSSSTATUS_READY)
	FLAG2STR(X_DSSSTATUS_PLAYING)
	FLAG2STR(X_DSSSTATUS_PAUSED)
	FLAG2STR(X_DSSSTATUS_STARVED)
	FLAG2STR(X_DSSSTATUS_ENVELOPECOMPLETE)
FLAGS2STR_END_and_LOGRENDER(DSSSTATUS_FLAG)

// DSound XMedia flag/enum
ENUM2STR_START(XMP_STATUS)
	ENUM2STR_CASE(XMP_STATUS_SUCCESS)
	ENUM2STR_CASE(XMP_STATUS_PENDING)
	ENUM2STR_CASE(XMP_STATUS_FLUSHED)
	ENUM2STR_CASE(XMP_STATUS_FAILURE)
	ENUM2STR_CASE(XMP_STATUS_RELEASE_CXBXR) // NOTE: Custom status for Cxbx-Reloaded.
ENUM2STR_END_and_LOGRENDER(XMP_STATUS)

FLAGS2STR_START(XMO_STREAMF)
	FLAG2STR(XMO_STREAMF_FIXED_SAMPLE_SIZE)
	FLAG2STR(XMO_STREAMF_FIXED_PACKET_ALIGNMENT)
	FLAG2STR(XMO_STREAMF_INPUT_ASYNC)
	FLAG2STR(XMO_STREAMF_OUTPUT_ASYNC)
	FLAG2STR(XMO_STREAMF_IN_PLACE)
	FLAG2STR(XMO_STREAMF_MASK)
FLAGS2STR_END_and_LOGRENDER(XMO_STREAMF)

// DSound class usage
LOGRENDER(X_DSCAPS)
{
	return os
		LOGRENDER_MEMBER(dwFree2DBuffers)
		LOGRENDER_MEMBER(dwFree3DBuffers)
		LOGRENDER_MEMBER(dwFreeBufferSGEs)
		LOGRENDER_MEMBER(dwMemoryAllocated)
		;
}

LOGRENDER(X_DSI3DL2LISTENER)
{
	return os
		LOGRENDER_MEMBER(lRoom)
		LOGRENDER_MEMBER(lRoomHF)
		LOGRENDER_MEMBER(flRoomRolloffFactor)
		LOGRENDER_MEMBER(flDecayTime)
		LOGRENDER_MEMBER(flDecayHFRatio)
		LOGRENDER_MEMBER(lReflections)
		LOGRENDER_MEMBER(flReflectionsDelay)
		LOGRENDER_MEMBER(lReverb)
		LOGRENDER_MEMBER(flReverbDelay)
		LOGRENDER_MEMBER(flDiffusion)
		LOGRENDER_MEMBER(flDensity)
		LOGRENDER_MEMBER(flHFReference)
		;
}

LOGRENDER(X_DSMIXBINS)
{
	return os
		LOGRENDER_MEMBER(dwCount)
		// TODO: Need to make a loop somehow for complete output base on dwCount variable.
		LOGRENDER_MEMBER_TYPE(X_LPDSMIXBINSVOLUMEPAIR, lpMixBinVolumePairs)
		;
}

LOGRENDER(X_DSMIXBINSVOLUMEPAIR)
{
	return os
		LOGRENDER_MEMBER(dwMixBin)
		LOGRENDER_MEMBER(lVolume)
		;
}

LOGRENDER(X_DSOUTPUTLEVELS)
{
	return os
		LOGRENDER_MEMBER(dwAnalogLeftTotalPeak)
		LOGRENDER_MEMBER(dwAnalogRightTotalPeak)
		LOGRENDER_MEMBER(dwAnalogLeftTotalRMS)
		LOGRENDER_MEMBER(dwAnalogRightTotalRMS)
		LOGRENDER_MEMBER(dwDigitalFrontLeftPeak)
		LOGRENDER_MEMBER(dwDigitalFrontCenterPeak)
		LOGRENDER_MEMBER(dwDigitalFrontRightPeak)
		LOGRENDER_MEMBER(dwDigitalBackLeftPeak)
		LOGRENDER_MEMBER(dwDigitalBackRightPeak)
		LOGRENDER_MEMBER(dwDigitalLowFrequencyPeak)
		LOGRENDER_MEMBER(dwDigitalFrontLeftRMS)
		LOGRENDER_MEMBER(dwDigitalFrontCenterRMS)
		LOGRENDER_MEMBER(dwDigitalFrontRightRMS)
		LOGRENDER_MEMBER(dwDigitalBackLeftRMS)
		LOGRENDER_MEMBER(dwDigitalBackRightRMS)
		LOGRENDER_MEMBER(dwDigitalLowFrequencyRMS)
		;
}

// DSound generic class usage
LOGRENDER(X_DS3DBUFFER)
{
	return os
		LOGRENDER_MEMBER(dwSize)
		LOGRENDER_MEMBER_TYPE(D3DVECTOR, vPosition)
		LOGRENDER_MEMBER_TYPE(D3DVECTOR, vVelocity)
		LOGRENDER_MEMBER(dwInsideConeAngle)
		LOGRENDER_MEMBER(dwOutsideConeAngle)
		LOGRENDER_MEMBER_TYPE(D3DVECTOR, vConeOrientation)
		LOGRENDER_MEMBER(lConeOutsideVolume)
		LOGRENDER_MEMBER(flMinDistance)
		LOGRENDER_MEMBER(flMaxDistance)
		LOGRENDER_MEMBER(dwMode)
		LOGRENDER_MEMBER(flDistanceFactor)
		LOGRENDER_MEMBER(flRolloffFactor)
		LOGRENDER_MEMBER(flDopplerFactor)
		;
}

LOGRENDER(X_DSENVOLOPEDESC)
{
	return os
		LOGRENDER_MEMBER(dwEnvelopGenerator)
		LOGRENDER_MEMBER(dwMode)
		LOGRENDER_MEMBER(dwDelay)
		LOGRENDER_MEMBER(dwAttack)
		LOGRENDER_MEMBER(dwHold)
		LOGRENDER_MEMBER(dwDecay)
		LOGRENDER_MEMBER(dwRelease)
		LOGRENDER_MEMBER(dwSustain)
		LOGRENDER_MEMBER(lPitchScale)
		LOGRENDER_MEMBER(lFilterCutOff)
		;
}

LOGRENDER(X_DSFILTERDESC)
{
	return os
		LOGRENDER_MEMBER_TYPE(DSFILTER_MODE, dwMode)
		LOGRENDER_MEMBER(dwQCoefficient)
		LOGRENDER_MEMBER(adwCoefficients)
		;
}

LOGRENDER(X_DSI3DL2BUFFER)
{
	return os
		LOGRENDER_MEMBER(lDirect)
		LOGRENDER_MEMBER(lDirectHF)
		LOGRENDER_MEMBER(lRoom)
		LOGRENDER_MEMBER(lRoomHF)
		LOGRENDER_MEMBER(flRoomRolloffFactor)
		LOGRENDER_MEMBER_TYPE(X_DSI3DL2OBSTRUCTION, Obstruction)
		LOGRENDER_MEMBER_TYPE(X_DSI3DL2OCCLUSION, Occlusion)
		;
}

LOGRENDER(X_DSI3DL2OBSTRUCTION)
{
	return os
		LOGRENDER_MEMBER(lHFLevel)
		LOGRENDER_MEMBER(flLFRatio)
		;
}

LOGRENDER(X_DSI3DL2OCCLUSION)
{
	return os
		LOGRENDER_MEMBER(lHFLevel)
		LOGRENDER_MEMBER(flLFRatio)
		;
}

LOGRENDER(DSLFODESC)
{
	return os
		LOGRENDER_MEMBER(dwLFO)
		LOGRENDER_MEMBER(dwDelay)
		LOGRENDER_MEMBER(dwDelta)
		LOGRENDER_MEMBER(lPitchModulation)
		LOGRENDER_MEMBER(lFilterCutOffRange)
		LOGRENDER_MEMBER(lAmplitudeModulation)
		;
}

LOGRENDER(XBOXADPCMWAVEFORMAT)
{
	return os
		LOGRENDER_MEMBER_TYPE(WAVEFORMATEX, wfx)
		LOGRENDER_MEMBER(wSamplesPerBlock)
		;
}

// DSound Buffer class usage
LOGRENDER(X_DSBUFFERDESC)
{
	return os
		LOGRENDER_MEMBER(dwSize)
		LOGRENDER_MEMBER_TYPE(DSBCAPS_FLAG, dwFlags)
		LOGRENDER_MEMBER(dwBufferBytes)
		LOGRENDER_MEMBER_TYPE(LPWAVEFORMATEX, lpwfxFormat)
		LOGRENDER_MEMBER(lpMixBins)
		LOGRENDER_MEMBER(dwInputMixBin)
		;
}

// DSound Stream class usage
LOGRENDER(X_DSSTREAMDESC)
{
	return os
		LOGRENDER_MEMBER_TYPE(DSSCAPS_FLAG, dwFlags)
		LOGRENDER_MEMBER(dwMaxAttachedPackets)
		LOGRENDER_MEMBER_TYPE(LPWAVEFORMATEX, lpwfxFormat)
		LOGRENDER_MEMBER_TYPE(void*, lpfnCallback)
		LOGRENDER_MEMBER(lpvContext)
		LOGRENDER_MEMBER(lpMixBins)
		;
}

// DSound XMedia class usage
LOGRENDER(XMEDIAINFO)
{
	return os
		LOGRENDER_MEMBER(dwFlags)
		LOGRENDER_MEMBER(dwInputSize)
		LOGRENDER_MEMBER(dwOutputSize)
		LOGRENDER_MEMBER(dwMaxLookahead)
		;
}

LOGRENDER(XMEDIAPACKET)
{
	return os
		LOGRENDER_MEMBER(pvBuffer)
		LOGRENDER_MEMBER(dwMaxSize)
		LOGRENDER_MEMBER(pdwCompletedSize)
		LOGRENDER_MEMBER_TYPE(XMO_STREAMF*, pdwStatus)
		// NOTE: hCompletionEvent and pContext are a union.
		//LOGRENDER_MEMBER(hCompletionEvent)
		//LOGRENDER_MEMBER(pContext)
		LOGRENDER_MEMBER(prtTimestamp)
		;
}

}
