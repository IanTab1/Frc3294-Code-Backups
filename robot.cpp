/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/Joystick.h>
#include <frc/Spark.h>
#include <frc/TimedRobot.h>
#include <frc/drive/MecanumDrive.h>

  static constexpr int lJoystickChannel = 0;
  static constexpr int rJoystickChannel = 1;

class Robot : public frc::TimedRobot {
    frc::Joystick l_stick{lJoystickChannel};
  frc::Joystick r_stick{rJoystickChannel};
 public:

void RobotInit() override {
   // Invert the left side motors. You may need to change or remove this to
   // match your robot.

    m_frontLeft.SetInverted(true);
    m_backLeft.SetInverted(true);

    m_frontLeft.Set(0.5);
    m_backLeft.Set(0.5);
    m_frontRight.Set(0.5);
    m_backRight.Set(0.5);
  

 
  }

  void AutonomousInit() override {
  }

  void AutonomousPeriodic() override {
  }


  void TeleopPeriodic() override {

m_robotDrive.DriveCartesian(l_stick.GetX(), r_stick.GetY(), r_stick.GetX());
  }

 private:
  frc::Spark m_frontLeft{0};
  frc::Spark m_backLeft{1};
  frc::Spark m_frontRight{2};
  frc::Spark m_backRight{3};
  
  frc::MecanumDrive m_robotDrive{m_frontLeft, m_backLeft, m_frontRight, m_backRight};



};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
