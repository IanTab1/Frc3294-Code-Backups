/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include <thread>

#include <cameraserver/CameraServer.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <wpi/raw_ostream.h>
#include <frc/Joystick.h>
#include <frc/Spark.h>
#include <frc/TimedRobot.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/SpeedControllerGroup.h>
#include <AHRS.h>
#include <WPILib.h>

class Robot : public frc::TimedRobot {
#if defined(__linux__)
	AHRS *ahrs;
 public:
	//defining motors
	/*
    0/| |\2
    1\| |/3
    */
    frc::Spark m_frontLeft{0};
    frc::Spark m_backLeft{1};
    frc::Spark m_frontRight{2};
    frc::Spark m_backRight{3};
    //initiating joystick at m_stick
    frc::Joystick m_stick{0};

		ahrs = new AHRS(SPI.Port.kMXP);

		//initiating robot drive at m_drive
    frc::MecanumDrive m_drive{m_frontLeft, m_backLeft, m_frontRight, m_backRight};
	void TeleopPeriodic() {
    // Drive with Mecanum
		/*
		m_drive.SetSafetyEnabled(false);
    while (IsOperatorControl() && IsEnabled()) {
		bool reset_yaw_button_pressed = m_stick.GetRawButton(1);
    	if ( reset_yaw_button_pressed ) {
        ahrs->ZeroYaw();
		}
    	m_drive.DriveCartesian(m_stick.GetX(), m_stick.GetY(), m_stick.GetZ(), ahrs->GetAngle());
    }
    Wait(0.005); // wait 5ms to avoid hogging CPU cycles
		*/
	}
static void VisionThread() {
    // Get the USB camera from CameraServer
    cs::UsbCamera camera = frc::CameraServer::GetInstance()->StartAutomaticCapture();
    // Set the resolution
    camera.SetResolution(640, 480);
    // Get a CvSink. This will capture Mats from the Camera
    cs::CvSink cvSink = frc::CameraServer::GetInstance()->GetVideo();
    // Setup a CvSource. This will send images back to the Dashboard
    cs::CvSource outputStream = frc::CameraServer::GetInstance()->PutVideo("Rectangle", 640, 480);
    // Mats are very memory expensive. Lets reuse this Mat.
    cv::Mat mat;
    while (true) {
    	// Tell the CvSink to grab a frame from the camera and
    	// put it
    	// in the source mat.  If there is an error notify the
    	// output.
    	if (cvSink.GrabFrame(mat) == 0) {
			// Send the output the error.
    		outputStream.NotifyError(cvSink.GetError());
    		// skip the rest of the current iteration
    		continue;
    	}
    	// Put a rectangle on the image
    	rectangle(mat, cv::Point(100, 100), cv::Point(400, 400), cv::Scalar(255, 255, 255), 5);
    	// Give the output stream a new image to display
    	outputStream.PutFrame(mat);
    }
}
#endif

  void RobotInit() override {
	// We need to run our vision program in a separate thread. If not, our robot
	// program will not run.
#if defined(__linux__)
    std::thread visionThread(VisionThread);
    visionThread.detach();
#else
	wpi::errs() << "Vision only available on Linux.\n";
	wpi::errs().flush();
#endif
	}
};
#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
