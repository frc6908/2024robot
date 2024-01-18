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

namespace drivetrain {
    const int kLeftDriveTalonPort = 16;
    const int kLeftDriveVenomPort = 19;

    const int kRightDriveVictorPort = 17;
    const int kRightDriveVenomPort = 18; 

    const int kWheelDiameter = 6;
    
    const double kDT = 0.02;
}
