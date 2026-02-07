#include "../hardware.hpp"
#include "../helpers.hpp"
#include "auton/autons.hpp"

#include "lemlib/api.hpp"
void skills_auton() {/* CODEGEN EXPORT: LemLib */
scoreHigh();

	chassis.setPose(-49.920000, 15.120000, 85.236000);

	
	chassis.moveToPoint(-36.24, 15.12, 1245);
	chassis.turnToHeading(0, 1000);
	
	chassis.turnToHeading(0, 1000);
	
	chassis.moveToPoint(-45.6, 47, 1312, {}, false);
	pros::delay(200);
	chassis.turnToHeading(260, 1000, {}, false);


	setMatchLoader(true);
	scoreHigh();
	chassis.moveToPoint(-74.32, 45.5, 1000, {.maxSpeed=50}, false); //node 6
	pros::delay(300);
	chassis.moveToPoint(-74.32, 46.5, 1000, {.maxSpeed=20}, false); //node 6

	// pros::delay(2000);
	chassis.moveToPoint(-45.12, 47, 1436, {.forwards = false}); //node 7	
	chassis.waitUntil(14.629714);
	setMatchLoader(false);
	stopScore();


	scoreHigh();
	chassis.waitUntilDone();
	pros::delay(200);
	chassis.turnToHeading(24.034288, 1258);
	chassis.moveToPoint(-37.2, 64.08, 1443); //node 8

	chassis.turnToHeading(91.487868, 465);
	chassis.moveToPoint(42, 70.52, 2000, {.maxSpeed=100}); //node 13

	

	pros::delay(2000);
	chassis.turnToHeading(173, 1116, {.maxSpeed=100});
	pros::delay(1000);
	driveToFrontDistanceMm(440, 100); // TODO: update if rear distance sensor is added



	// chassis.moveToPoint(42.0, 53, 1573); // node 14
	pros::delay(1000);
	chassis.setPose(42, 53, chassis.getPose().theta+4.77);
	chassis.setPose(42, 53, chassis.getPose().theta+4.77);





	pros::delay(50);
	chassis.turnToHeading(90, 1120);






	chassis.moveToPoint(23, 53, 1000, {.forwards = false, .maxSpeed=100}, false); //node 15
	scoreHigh();
	pros::delay(2500); 
	chassis.waitUntil(11.940754);


	// initial match, top left score
	
	chassis.turnToHeading(90, 461, {}, false); //prev89
	setMatchLoader(true);
	scoreHigh();
	chassis.moveToPoint(47.76, 53, 1518, {.maxSpeed=100}, false); //prey56 //node 16?? ///current 48
	chassis.turnToHeading(93, 500);

	//top left matchload
	chassis.moveToPoint(65.52, 52, 1000, {.maxSpeed = 50}, false); //prev 5 //node 17
	pros::delay(300);
	chassis.moveToPoint(65.52, 52, 1700, {.maxSpeed = 20}, false); //prev 5 //node 17

	chassis.turnToHeading(90.0, 461);
	chassis.moveToPoint(23, 53, 1500, {.forwards = false, .maxSpeed=100}, false); //node 18 //scoring on long goal
	chassis.waitUntil(32.81013);



	chassis.setPose(23, 53, chassis.getPose().theta);


	//top left 2nd matchload score		
	setMatchLoader(false);
	stopScore();

	scoreHigh();



	pros::delay(2500);
	chassis.moveToPoint(37, 53, 1539, {.maxSpeed=110}); //node 19
	chassis.turnToHeading(180, 1204);

	chassis.moveToPoint(37, -42, 20000, {.maxSpeed = 100}, false); // ode 21
	chassis.moveToPoint(37, -42, 20000, {.maxSpeed = 100}, false); // ode 21

	pros::delay(200);
	driveToFrontDistanceMm(540);  // assumes front-mounted sensor
	chassis.setPose(40, -45, 180);

	//top right matchload
	
	chassis.turnToHeading(90, 941, {}, false);
	

	stopScore();
	setMatchLoader(true);
	scoreHigh();
	pros::delay(400);

	chassis.moveToPoint(65, -45, 1300, {.maxSpeed=50}, false); //node 22 // THIS IS THE MATCHLOAD POSITION
	pros::delay(300);
	chassis.moveToPoint(65, -45, 1700, {.maxSpeed=20}, false); 
	chassis.moveToPoint(40, -45, 2000, {.forwards = false, .maxSpeed = 80}); // ode 21 NEW NODE 23


	
	//top right finished matchload
	setMatchLoader(false);
	stopScore();
	chassis.waitUntilDone();
	pros::delay(50);
	chassis.turnToHeading(180, 1317);
	chassis.moveToPoint(33, -60, 1561);//node 24
	pros::delay(50);
	chassis.turnToHeading(270, 884);
	chassis.moveToPoint(-46, -60, 3500);//node 25
	chassis.moveToPoint(-46, -60, 3500);//node 25
	chassis.turnToHeading(0, 461);
	pros::delay(1000);
	chassis.moveToPoint(-46, -44, 1237); //node 26
	chassis.moveToPoint(-46, -44, 1237); //node 26
	

	pros::delay(1000);
	driveToFrontDistanceMm(500, 100);
	pros::delay(1000);
	chassis.setPose(-45, -47, 0);



	chassis.turnToHeading(270.0, 1112);
	chassis.moveToPoint(-23, -47, 1500, {.forwards = false}); //node 27
	//bottom right score
	scoreHigh();
	pros::delay(2500);
	// chassis.setPose(chassis.getPose().x, chassis.getPose().y, 270);
	setMatchLoader(true);
	scoreHigh();
	pros::delay(50);
	chassis.moveToPoint(-68.44, -47, 2000, {.maxSpeed=50}, false); //nodem28 //bottom right matchload
	pros::delay(3000);
	pros::delay(3000);
	chassis.moveToPoint(-51.84, -47, 1941, {.forwards = false});//node 29
	pros::delay(500);
	chassis.moveToPoint(-24.96, -47, 1663, {.forwards = false}); //node 30
	chassis.waitUntil(20.017067);
	setMatchLoader(false);
	stopScore();
	scoreHigh();
	pros::delay(2500);
	chassis.waitUntilDone();
	pros::delay(50);
	chassis.turnToHeading(268.898294, 461);
	chassis.moveToPoint(-37.44, -49, 1199); //node 31
	pros::delay(50);
	chassis.turnToHeading(320, 906);
	chassis.turnToHeading(320, 906);
	chassis.moveToPoint(-70, -17.28, 2006); //node 32
	pros::delay(50);
	chassis.turnToHeading(0, 834);
	chassis.turnToHeading(0, 834);
	chassis.moveToPoint(-70, -0.24, 1364); //node 33
}
