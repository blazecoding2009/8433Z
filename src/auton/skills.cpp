#include "../hardware.hpp"
#include "../helpers.hpp"
#include "auton/autons.hpp"

#include "lemlib/api.hpp"
void skills_auton() { /* CODEGEN EXPORT: LemLib */
	chassis.setPose(0, 0, 0);
	chassis.moveToPoint(
	    0, 12, 1000,
	    {
	        .forwards = true,
	        .maxSpeed = 127,
	        .minSpeed = 127,
	    }
	);
}
