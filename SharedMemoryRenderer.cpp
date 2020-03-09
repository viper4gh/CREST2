#include "SharedMemoryRenderer.h"
#include "Utils.h"

SharedMemoryRenderer::SharedMemoryRenderer(){};

void renderBuildInfo(std::stringstream& ss, const SharedMemory* sharedData)	{
	ss << "  \"buildinfo\":{\r\n";
	ss << "    \"mVersion\":" << sharedData->mVersion << ",\r\n";
	ss << "    \"mBuildVersionNumber\":" << sharedData->mBuildVersionNumber << "\r\n  }";
}

void renderGameStates(std::stringstream& ss, const SharedMemory* sharedData)	{
	ss << "  \"gameStates\":{\r\n";
	ss << "    \"mGameState\":" << sharedData->mGameState << ",\r\n";
	ss << "    \"mSessionState\":" << sharedData->mSessionState << ",\r\n";
	ss << "    \"mRaceState\":" << sharedData->mRaceState << "\r\n  }";
}

void renderParticipant(std::stringstream& ss, const ParticipantInfo participantInfo)	{
	ss << "      {\r\n        \"mIsActive\":" << (participantInfo.mIsActive ? "true" : "false") << ",\r\n";
	ss << "        \"mName\":\"" << participantInfo.mName << "\",\r\n";
	ss << "        \"mWorldPosition\":[" << participantInfo.mWorldPosition[0] << "," << participantInfo.mWorldPosition[1] << "," << participantInfo.mWorldPosition[2] << "],\r\n";
	ss << "        \"mCurrentLapDistance\":" << participantInfo.mCurrentLapDistance << ",\r\n";
	ss << "        \"mRacePosition\":" << participantInfo.mRacePosition << ",\r\n";
	ss << "        \"mLapsCompleted\":" << participantInfo.mLapsCompleted << ",\r\n";
	ss << "        \"mCurrentLap\":" << participantInfo.mCurrentLap << ",\r\n";
	ss << "        \"mCurrentSector\":" << participantInfo.mCurrentSector << ",\r\n";
}

void renderParticipants(std::stringstream& ss, const SharedMemory* sharedData)	{
	ss << "  \"participants\":{\r\n";
	ss << "    \"mViewedParticipantIndex\":" << sharedData->mViewedParticipantIndex << ",\r\n";
	ss << "    \"mNumParticipants\":" << sharedData->mNumParticipants;

	if (sharedData->mNumParticipants > -1)	{
		ss << ",\r\n";
		ss << "    \"mParticipantInfo\":[\r\n";

		for (int i = 0; i < sharedData->mNumParticipants; i++)	{
			renderParticipant(ss, sharedData->mParticipantInfo[i]);
			// pcars2 additional participant data:
			ss << "        \"mRaceStates\":" << sharedData->mRaceStates[i] << ",\r\n";
			ss << "        \"mPitModes\":" << sharedData->mPitModes[i] << ",\r\n";
			ss << "        \"mFastestLapTimes\":" << sharedData->mFastestLapTimes[i] << ",\r\n";
			ss << "        \"mLastLapTimes\":" << sharedData->mLastLapTimes[i] << ",\r\n";
			ss << "        \"mFastestSector1Times\":" << sharedData->mFastestSector1Times[i] << ",\r\n";
			ss << "        \"mFastestSector2Times\":" << sharedData->mFastestSector2Times[i] << ",\r\n";
			ss << "        \"mFastestSector3Times\":" << sharedData->mFastestSector3Times[i] << ",\r\n";
			ss << "        \"mCurrentSector1Times\":" << sharedData->mCurrentSector1Times[i] << ",\r\n";
			ss << "        \"mCurrentSector2Times\":" << sharedData->mCurrentSector2Times[i] << ",\r\n";
			ss << "        \"mCurrentSector3Times\":" << sharedData->mCurrentSector3Times[i] << ",\r\n";
			ss << "        \"mLapsInvalidated\":" << sharedData->mLapsInvalidated[i] << ",\r\n";
			ss << "        \"mOrientations\":[" << sharedData->mOrientations[i][0] << "," << sharedData->mOrientations[i][1] << "," << sharedData->mOrientations[i][2] << "],\r\n";
			ss << "        \"mSpeeds\":" << sharedData->mSpeeds[i] << ",\r\n";
			ss << "        \"mCarNames\":\"" << sharedData->mCarNames[i] << "\",\r\n";
			ss << "        \"mCarClassNames\":\"" << sharedData->mCarClassNames[i] << "\",\r\n";
			ss << "        \"mPitSchedules\":" << sharedData->mPitSchedules[i] << ",\r\n";
			ss << "        \"mHighestFlagColours\":" << sharedData->mHighestFlagColours[i] << ",\r\n";
			ss << "        \"mHighestFlagReasons\":" << sharedData->mPitModes[i] << ",\r\n";
			ss << "        \"mNationalities\":" << sharedData->mPitModes[i] << "\r\n      }";
			// End pcars2 participant data
			
			if (i < (sharedData->mNumParticipants - 1))	{
				ss << ",\r\n";
			}
		}
		ss << "\r\n    ]";
	}
	ss << "\r\n  }";
}

void renderUnfilteredInput(std::stringstream& ss, const SharedMemory* sharedData)	{
	ss << "  \"unfilteredInput\":{\r\n";
	ss << "    \"mUnfilteredThrottle\":" << sharedData->mUnfilteredThrottle << ",\r\n";
	ss << "    \"mUnfilteredBrake\":" << sharedData->mUnfilteredBrake << ",\r\n";
	ss << "    \"mUnfilteredSteering\":" << sharedData->mUnfilteredSteering << ",\r\n";
	ss << "    \"mUnfilteredClutch\":" << sharedData->mUnfilteredClutch << "\r\n  }";
}

void renderVehicleInformation(std::stringstream& ss, const SharedMemory* sharedData)	{
	ss << "  \"vehicleInformation\":{\r\n";
	ss << "    \"mCarName\":\"" << sharedData->mCarName << "\",\r\n";
	ss << "    \"mCarClassName\":\"" << sharedData->mCarClassName << "\"\r\n  }";
}

void renderEventInformation(std::stringstream& ss, const SharedMemory* sharedData)	{
	ss << "  \"eventInformation\":{\r\n";
	ss << "    \"mLapsInEvent\":" << sharedData->mLapsInEvent << ",\r\n";
	ss << "    \"mTrackLocation\":\"" << sharedData->mTrackLocation << "\",\r\n";
	ss << "    \"mTrackVariation\":\"" << sharedData->mTrackVariation << "\",\r\n";
	ss << "    \"mTrackLength\":" << sharedData->mTrackLength << ",\r\n";
	//pcars2 additional data
	ss << "    \"mTranslatedTrackLocation\":\"" << sharedData->mTranslatedTrackLocation << "\",\r\n";
	ss << "    \"mTranslatedTrackVariation\":\"" << sharedData->mTranslatedTrackVariation << "\"\r\n  }";
}

void renderTimings(std::stringstream& ss, const SharedMemory* sharedData)	{
	ss << "  \"timings\":{\r\n";
	ss << "    \"mLapInvalidated\":" << (sharedData->mLapInvalidated ? "true" : "false") << ",\r\n";
	ss << "    \"mBestLapTime\":" << sharedData->mBestLapTime << ",\r\n";
	ss << "    \"mLastLapTime\":" << sharedData->mLastLapTime << ",\r\n";
	ss << "    \"mCurrentTime\":" << sharedData->mCurrentTime << ",\r\n";
	ss << "    \"mSplitTimeAhead\":" << sharedData->mSplitTimeAhead << ",\r\n";
	ss << "    \"mSplitTimeBehind\":" << sharedData->mSplitTimeBehind << ",\r\n";
	ss << "    \"mSplitTime\":" << sharedData->mSplitTime << ",\r\n";
	ss << "    \"mEventTimeRemaining\":" << sharedData->mEventTimeRemaining << ",\r\n";
	ss << "    \"mPersonalFastestLapTime\":" << sharedData->mPersonalFastestLapTime << ",\r\n";
	ss << "    \"mWorldFastestLapTime\":" << sharedData->mWorldFastestLapTime << ",\r\n";
	ss << "    \"mCurrentSector1Time\":" << sharedData->mCurrentSector1Time << ",\r\n";
	ss << "    \"mCurrentSector2Time\":" << sharedData->mCurrentSector2Time << ",\r\n";
	ss << "    \"mCurrentSector3Time\":" << sharedData->mCurrentSector3Time << ",\r\n";
	ss << "    \"mFastestSector1Time\":" << sharedData->mFastestSector1Time << ",\r\n";
	ss << "    \"mFastestSector2Time\":" << sharedData->mFastestSector2Time << ",\r\n";
	ss << "    \"mFastestSector3Time\":" << sharedData->mFastestSector3Time << ",\r\n";
	ss << "    \"mPersonalFastestSector1Time\":" << sharedData->mPersonalFastestSector1Time << ",\r\n";
	ss << "    \"mPersonalFastestSector2Time\":" << sharedData->mPersonalFastestSector2Time << ",\r\n";
	ss << "    \"mPersonalFastestSector3Time\":" << sharedData->mPersonalFastestSector3Time << ",\r\n";
	ss << "    \"mWorldFastestSector1Time\":" << sharedData->mWorldFastestSector1Time << ",\r\n";
	ss << "    \"mWorldFastestSector2Time\":" << sharedData->mWorldFastestSector2Time << ",\r\n";
	ss << "    \"mWorldFastestSector3Time\":" << sharedData->mWorldFastestSector3Time << "\r\n  }";
}

void renderFlags(std::stringstream& ss, const SharedMemory* sharedData)	{
	ss << "  \"flags\":{\r\n";
	ss << "    \"mHighestFlagColour\":" << sharedData->mHighestFlagColour << ",\r\n";
	ss << "    \"mHighestFlagReason\":" << sharedData->mHighestFlagReason << "\r\n  }";
}

void renderPitInfo(std::stringstream& ss, const SharedMemory* sharedData)	{
	ss << "  \"pitInfo\":{\r\n";
	ss << "    \"mPitMode\":" << sharedData->mPitMode << ",\r\n";
	ss << "    \"mPitSchedule\":" << sharedData->mPitSchedule << ",\r\n";
	//pcars2 additional data
	ss << "    \"mEnforcedPitStopLap\":" << sharedData->mEnforcedPitStopLap << "\r\n  }";
}

void renderCarState(std::stringstream& ss, const SharedMemory* sharedData)	{
	ss << "  \"carState\":{\r\n";
	ss << "    \"mCarFlags\":" << sharedData->mCarFlags << ",\r\n";
	ss << "    \"mOilTempCelsius\":" << sharedData->mOilTempCelsius << ",\r\n";
	ss << "    \"mWaterTempCelsius\":" << sharedData->mWaterTempCelsius << ",\r\n";
	ss << "    \"mWaterPressureKPa\":" << sharedData->mWaterPressureKPa << ",\r\n";
	ss << "    \"mFuelPressureKPa\":" << sharedData->mFuelPressureKPa << ",\r\n";
	ss << "    \"mFuelLevel\":" << sharedData->mFuelLevel << ",\r\n";
	ss << "    \"mFuelCapacity\":" << sharedData->mFuelCapacity << ",\r\n";
	ss << "    \"mSpeed\":" << sharedData->mSpeed << ",\r\n";
	ss << "    \"mRpm\":" << sharedData->mRpm << ",\r\n";
	ss << "    \"mMaxRPM\":" << sharedData->mMaxRPM << ",\r\n";
	ss << "    \"mBrake\":" << sharedData->mBrake << ",\r\n";
	ss << "    \"mThrottle\":" << sharedData->mThrottle << ",\r\n";
	ss << "    \"mClutch\":" << sharedData->mClutch << ",\r\n";
	ss << "    \"mSteering\":" << sharedData->mSteering << ",\r\n";
	ss << "    \"mGear\":" << sharedData->mGear << ",\r\n";
	ss << "    \"mNumGears\":" << sharedData->mNumGears << ",\r\n";
	ss << "    \"mOdometerKM\":" << sharedData->mOdometerKM << ",\r\n";
	ss << "    \"mAntiLockActive\":" << (sharedData->mAntiLockActive ? "true" : "false") << ",\r\n";
	ss << "    \"mLastOpponentCollisionIndex\":" << sharedData->mLastOpponentCollisionIndex << ",\r\n";
	ss << "    \"mLastOpponentCollisionMagnitude\":" << sharedData->mLastOpponentCollisionMagnitude << ",\r\n";
	ss << "    \"mBoostActive\":" << (sharedData->mBoostActive ? "true" : "false") << ",\r\n";
	ss << "    \"mBoostAmount\":" << sharedData->mBoostAmount << ",\r\n";
	//pcars2 additional data
	ss << "    \"mEngineSpeed\":" << sharedData->mEngineSpeed << ",\r\n";
	ss << "    \"mEngineTorque\":" << sharedData->mEngineTorque << ",\r\n";
	ss << "    \"mWings\":[" << sharedData->mWings[0] << "," << sharedData->mWings[1] << "],\r\n";
	ss << "    \"mHandBrake\":" << sharedData->mHandBrake << ",\r\n";
	ss << "    \"mBrakeBias\":" << sharedData->mBrakeBias << ",\r\n";
	ss << "    \"mTurboBoostPressure\":" << sharedData->mTurboBoostPressure << "\r\n  }";

}

void renderMotionDeviceRelated(std::stringstream& ss, const SharedMemory* sharedData)	{
	ss << "  \"motionAndDeviceRelated\":{\r\n";
	ss << "    \"mOrientation\":[" << sharedData->mOrientation[0] << "," << sharedData->mOrientation[1] << "," << sharedData->mOrientation[2] << "],\r\n";
	ss << "    \"mLocalVelocity\":[" << sharedData->mLocalVelocity[0] << "," << sharedData->mLocalVelocity[1] << "," << sharedData->mLocalVelocity[2] << "],\r\n";
	ss << "    \"mWorldVelocity\":[" << sharedData->mWorldVelocity[0] << "," << sharedData->mWorldVelocity[1] << "," << sharedData->mWorldVelocity[2] << "],\r\n";
	ss << "    \"mAngularVelocity\":[" << sharedData->mAngularVelocity[0] << "," << sharedData->mAngularVelocity[1] << "," << sharedData->mAngularVelocity[2] << "],\r\n";
	ss << "    \"mLocalAcceleration\":[" << sharedData->mLocalAcceleration[0] << "," << sharedData->mLocalAcceleration[1] << "," << sharedData->mLocalAcceleration[2] << "],\r\n";
	ss << "    \"mWorldAcceleration\":[" << sharedData->mWorldAcceleration[0] << "," << sharedData->mWorldAcceleration[1] << "," << sharedData->mWorldAcceleration[2] << "],\r\n";
	ss << "    \"mExtentsCentre\":[" << sharedData->mExtentsCentre[0] << "," << sharedData->mExtentsCentre[1] << "," << sharedData->mExtentsCentre[2] << "]\r\n  }";
}

void renderWheelsTyres(std::stringstream& ss, const SharedMemory* sharedData)	{
	ss << "  \"wheelsAndTyres\":{\r\n";
	ss << "    \"mTyreFlags\":[" << sharedData->mTyreFlags[0] << "," << sharedData->mTyreFlags[1] << "," << sharedData->mTyreFlags[2] << "," << sharedData->mTyreFlags[3] << "],\r\n";
	ss << "    \"mTerrain\":[" << sharedData->mTerrain[0] << "," << sharedData->mTerrain[1] << "," << sharedData->mTerrain[2] << "," << sharedData->mTerrain[3] << "],\r\n";
	ss << "    \"mTyreY\":[" << sharedData->mTyreY[0] << "," << sharedData->mTyreY[1] << "," << sharedData->mTyreY[2] << "," << sharedData->mTyreY[3] << "],\r\n";
	ss << "    \"mTyreRPS\":[" << sharedData->mTyreRPS[0] << "," << sharedData->mTyreRPS[1] << "," << sharedData->mTyreRPS[2] << "," << sharedData->mTyreRPS[3] << "],\r\n";
	ss << "    \"mTyreSlipSpeed\":[" << sharedData->mTyreSlipSpeed[0] << "," << sharedData->mTyreSlipSpeed[1] << "," << sharedData->mTyreSlipSpeed[2] << "," << sharedData->mTyreSlipSpeed[3] << "],\r\n";
	ss << "    \"mTyreTemp\":[" << sharedData->mTyreTemp[0] << "," << sharedData->mTyreTemp[1] << "," << sharedData->mTyreTemp[2] << "," << sharedData->mTyreTemp[3] << "],\r\n";
	ss << "    \"mTyreGrip\":[" << sharedData->mTyreGrip[0] << "," << sharedData->mTyreGrip[1] << "," << sharedData->mTyreGrip[2] << "," << sharedData->mTyreGrip[3] << "],\r\n";
	ss << "    \"mTyreHeightAboveGround\":[" << sharedData->mTyreHeightAboveGround[0] << "," << sharedData->mTyreHeightAboveGround[1] << "," << sharedData->mTyreHeightAboveGround[2] << "," << sharedData->mTyreHeightAboveGround[3] << "],\r\n";
	ss << "    \"mTyreLateralStiffness\":[" << sharedData->mTyreLateralStiffness[0] << "," << sharedData->mTyreLateralStiffness[1] << "," << sharedData->mTyreLateralStiffness[2] << "," << sharedData->mTyreLateralStiffness[3] << "],\r\n";
	ss << "    \"mTyreWear\":[" << sharedData->mTyreWear[0] << "," << sharedData->mTyreWear[1] << "," << sharedData->mTyreWear[2] << "," << sharedData->mTyreWear[3] << "],\r\n";
	ss << "    \"mBrakeDamage\":[" << sharedData->mBrakeDamage[0] << "," << sharedData->mBrakeDamage[1] << "," << sharedData->mBrakeDamage[2] << "," << sharedData->mBrakeDamage[3] << "],\r\n";
	ss << "    \"mSuspensionDamage\":[" << sharedData->mSuspensionDamage[0] << "," << sharedData->mSuspensionDamage[1] << "," << sharedData->mSuspensionDamage[2] << "," << sharedData->mSuspensionDamage[3] << "],\r\n";
	ss << "    \"mBrakeTempCelsius\":[" << sharedData->mBrakeTempCelsius[0] << "," << sharedData->mBrakeTempCelsius[1] << "," << sharedData->mBrakeTempCelsius[2] << "," << sharedData->mBrakeTempCelsius[3] << "],\r\n";
	ss << "    \"mTyreTreadTemp\":[" << sharedData->mTyreTreadTemp[0] << "," << sharedData->mTyreTreadTemp[1] << "," << sharedData->mTyreTreadTemp[2] << "," << sharedData->mTyreTreadTemp[3] << "],\r\n";
	ss << "    \"mTyreLayerTemp\":[" << sharedData->mTyreLayerTemp[0] << "," << sharedData->mTyreLayerTemp[1] << "," << sharedData->mTyreLayerTemp[2] << "," << sharedData->mTyreLayerTemp[3] << "],\r\n";
	ss << "    \"mTyreCarcassTemp\":[" << sharedData->mTyreCarcassTemp[0] << "," << sharedData->mTyreCarcassTemp[1] << "," << sharedData->mTyreCarcassTemp[2] << "," << sharedData->mTyreCarcassTemp[3] << "],\r\n";
	ss << "    \"mTyreRimTemp\":[" << sharedData->mTyreRimTemp[0] << "," << sharedData->mTyreRimTemp[1] << "," << sharedData->mTyreRimTemp[2] << "," << sharedData->mTyreRimTemp[3] << "],\r\n";
	ss << "    \"mTyreInternalAirTemp\":[" << sharedData->mTyreInternalAirTemp[0] << "," << sharedData->mTyreInternalAirTemp[1] << "," << sharedData->mTyreInternalAirTemp[2] << "," << sharedData->mTyreInternalAirTemp[3] << "],\r\n";
	//pcars2 additional data
	ss << "    \"mWheelLocalPositionY\":[" << sharedData->mWheelLocalPositionY[0] << "," << sharedData->mWheelLocalPositionY[1] << "," << sharedData->mWheelLocalPositionY[2] << "," << sharedData->mWheelLocalPositionY[3] << "],\r\n";
	ss << "    \"mSuspensionTravel\":[" << sharedData->mSuspensionTravel[0] << "," << sharedData->mSuspensionTravel[1] << "," << sharedData->mSuspensionTravel[2] << "," << sharedData->mSuspensionTravel[3] << "],\r\n";
	ss << "    \"mSuspensionVelocity\":[" << sharedData->mSuspensionVelocity[0] << "," << sharedData->mSuspensionVelocity[1] << "," << sharedData->mSuspensionVelocity[2] << "," << sharedData->mSuspensionVelocity[3] << "],\r\n";
	ss << "    \"mAirPressure\":[" << sharedData->mAirPressure[0] << "," << sharedData->mAirPressure[1] << "," << sharedData->mAirPressure[2] << "," << sharedData->mAirPressure[3] << "],\r\n";
	ss << "    \"mTyreCompound\":[\"" << sharedData->mTyreCompound[0] << "\",\"" << sharedData->mTyreCompound[1] << "\",\"" << sharedData->mTyreCompound[2] << "\",\"" << sharedData->mTyreCompound[3] << "\"]\r\n  }";

}

void renderCarDamage(std::stringstream& ss, const SharedMemory* sharedData)	{
	ss << "  \"carDamage\":{\r\n";
	ss << "    \"mCrashState\":" << sharedData->mCrashState << ",\r\n";
	ss << "    \"mAeroDamage\":" << sharedData->mAeroDamage << ",\r\n";
	ss << "    \"mEngineDamage\":" << sharedData->mEngineDamage << "\r\n  }";
}

void renderWeather(std::stringstream& ss, const SharedMemory* sharedData)	{
	ss << "  \"weather\":{\r\n";
	ss << "    \"mAmbientTemperature\":" << sharedData->mAmbientTemperature << ",\r\n";
	ss << "    \"mTrackTemperature\":" << sharedData->mTrackTemperature << ",\r\n";
	ss << "    \"mRainDensity\":" << sharedData->mRainDensity << ",\r\n";
	ss << "    \"mWindSpeed\":" << sharedData->mWindSpeed << ",\r\n";
	ss << "    \"mWindDirectionX\":" << sharedData->mWindDirectionX << ",\r\n";
	ss << "    \"mWindDirectionY\":" << sharedData->mWindDirectionY << ",\r\n";
	ss << "    \"mCloudBrightness\":" << sharedData->mCloudBrightness << ",\r\n";
	//pcars2 additional data
	ss << "    \"mSnowDensity\":" << sharedData->mSnowDensity << "\r\n  }";
}

// Adds a comma, unless skipped
void addSeparator(std::stringstream& ss, bool skip)	{
	if (!skip)	{
		ss << ",\r\n";
	}
}

// Returns true if the given section should be rendered, based on the presence
// of the sections name parameter in the query string
bool shouldRender(std::string queryString, std::string sectionName)	{
	std::stringstream ss;
	ss << sectionName << "=true";
	return queryString.empty() || Utils::contains(queryString, ss.str());
}

std::string SharedMemoryRenderer::render(const SharedMemory* sharedData, std::string queryString)	{

	std::stringstream ss;

	ss << "{\r\n";
	bool skipSeparator = true;
	if (shouldRender(queryString, "buildInfo"))	{
		renderBuildInfo(ss, sharedData);
		skipSeparator = false;
	}
	if (shouldRender(queryString, "gameStates"))	{
		addSeparator(ss, skipSeparator);
		renderGameStates(ss, sharedData);
		skipSeparator = false;
	}
	if (shouldRender(queryString, "participants"))	{
		addSeparator(ss, skipSeparator);
		renderParticipants(ss, sharedData);
		skipSeparator = false;
	}
	if (shouldRender(queryString, "unfilteredInputs"))	{
		addSeparator(ss, skipSeparator);
		renderUnfilteredInput(ss, sharedData);
		skipSeparator = false;
	}
	if (shouldRender(queryString, "vehicleInformation"))	{
		addSeparator(ss, skipSeparator);
		renderVehicleInformation(ss, sharedData);
		skipSeparator = false;
	}
	if (shouldRender(queryString, "eventInformation"))	{
		addSeparator(ss, skipSeparator);
		renderEventInformation(ss, sharedData);
		skipSeparator = false;
	}
	if (shouldRender(queryString, "timings"))	{
		addSeparator(ss, skipSeparator);
		renderTimings(ss, sharedData);
		skipSeparator = false;
	}
	if (shouldRender(queryString, "flags"))	{
		addSeparator(ss, skipSeparator);
		renderFlags(ss, sharedData);
		skipSeparator = false;
	}
	if (shouldRender(queryString, "pitInfo"))	{
		addSeparator(ss, skipSeparator);
		renderPitInfo(ss, sharedData);
		skipSeparator = false;
	}
	if (shouldRender(queryString, "carState"))	{
		addSeparator(ss, skipSeparator);
		renderCarState(ss, sharedData);
		skipSeparator = false;
	}
	if (shouldRender(queryString, "motionDeviceRelated"))	{
		addSeparator(ss, skipSeparator);
		renderMotionDeviceRelated(ss, sharedData);
		skipSeparator = false;
	}
	if (shouldRender(queryString, "wheelsAndTyres"))	{
		addSeparator(ss, skipSeparator);
		renderWheelsTyres(ss, sharedData);
		skipSeparator = false;
	}
	if (shouldRender(queryString, "carDamage"))	{
		addSeparator(ss, skipSeparator);
		renderCarDamage(ss, sharedData);
		skipSeparator = false;
	}
	if (shouldRender(queryString, "weather"))	{
		addSeparator(ss, skipSeparator);
		renderWeather(ss, sharedData);
		skipSeparator = false;
	}
	ss << "\r\n}";

	return ss.str();
}