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

/**
 * This is a demo program showing how to use Mecanum control with the
 * MecanumDrive class.
 */
class Robot : public frc::TimedRobot {
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
  frc::Joystick joyone = new Joystick (1);
  frc::Joystick joytwo = new Joystick(2);
    
 // Joystick *stick = new j_left(1); // Creates a Joystick object connected to USB on port 1 of the driverstation
 // Joystick *stick = new j_right(2); // Creates a Joystick object connected to USB on port 2 of the driverstation
  }

  void AutonomousInit() override {
  }

  void AutonomousPeriodic() override {
  }


  void TeleopPeriodic() override {
    /* Use the joystick X axis for lateral movement, Y axis for forward
     * movement, and Z axis for rotation.
     */
    m_robotDrive.DriveCartesian(joyone.GetX(), joytwo.GetY(), joytwo.GetX());
  }

 private:
  frc::MecanumDrive m_robotDrive{m_frontLeft, m_backLeft, m_frontRight, m_backRight};

  frc::Spark m_frontLeft{0};
  frc::Spark m_backLeft{1};
  frc::Spark m_frontRight{2};
  frc::Spark m_backRight{3};

};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
