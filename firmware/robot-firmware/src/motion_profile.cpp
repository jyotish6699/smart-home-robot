#include "motion_profile.h"

#include "logger.h"

static MotionProfileType currentProfile =
    PROFILE_NORMAL;

static MotionProfile currentSettings =
{
    180,

    180,

    15,

    100
};

void setupMotionProfile()
{
    logInfo(
        "[PROFILE] Motion Profile Ready"
    );
}

void setMotionProfile(
    MotionProfileType profile
)
{
    currentProfile = profile;

    switch(profile)
    {
        case PROFILE_PRECISION:

            currentSettings.maxSpeed = 80;

            currentSettings.defaultSpeed = 80;

            currentSettings.acceleration = 5;

            currentSettings.turnSensitivity = 70;

            break;

        case PROFILE_NORMAL:

            currentSettings.maxSpeed = 180;

            currentSettings.defaultSpeed = 180;

            currentSettings.acceleration = 15;

            currentSettings.turnSensitivity = 100;

            break;

        case PROFILE_SPORT:

            currentSettings.maxSpeed = 255;

            currentSettings.defaultSpeed = 255;

            currentSettings.acceleration = 30;

            currentSettings.turnSensitivity = 130;

            break;
    }

    String profileName;

    switch(profile)
    {
        case PROFILE_PRECISION:

            profileName = "Precision";

            break;

        case PROFILE_NORMAL:

            profileName = "Normal";

            break;

        case PROFILE_SPORT:

            profileName = "Sport";

            break;
    }

    logInfo(
        "[PROFILE] " +
        profileName
    );
}

MotionProfile getMotionProfile()
{
    return currentSettings;
}

MotionProfileType getMotionProfileType()
{
    return currentProfile;
}