// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <cmath>

/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

namespace OperatorConstants {

inline constexpr int kDriverControllerPort = 0;

}  // namespace OperatorConstants


namespace drivetrain {
    //example values not set
    const int kLeftDriveVenomPort = 1;
    const int kLeftDriveTalonPort = 2; 

    const int kLeftDriveSparkPort1 = 1;
    const int kLeftDriveSparkPort2 = 2;
    
    //const int kRightDriveVenomPort = 19;
    //const int kRightDriveTalonPort = 18;

    const int kRightDriveSparkPort1 = 19;
    const int kRightDriveSparkPort2 = 18;

    const int wheelDiameter = 6; //inches 

}


namespace arm{
    const int kLeftArmSparkPort = 11;
    const int kRightArmSparkPort = 12;
}

namespace shooter{
    const int kLeftShootSparkPort = 13;
    const int kRightShootSparkPort = 14;
}

namespace intake{
    const int kKicker = 15;
}




