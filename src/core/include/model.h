/*
 * model.h
 *
 * Holds some basic interfacing classes with which more complicated models can be drawn.
 *
 *  Created on: 16-Feb-2009
 *      Author: Hok Shun Poon
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "core.h"
#include <string>

using namespace std;

class IModel;

/**
 * Entity
 *
 * An Entity is a signficiant, named object inside a particular model.
 *
 * For an entity to be significant, *typically* it has to have at least one of the following:
 *  * a geometric shape when looking top-down
 *  * a particular colour
 *  * a location within the working confines of the IModel that contains the entity.
 *  * a height function that maps any arbitrary location on the model to a height-cost.
 *    This height-cost is calculated by the heightFunction();
 *
 * Extensions of Entity allow them to contain any amount and/or any degree of further information
 * required, such as an image, or special cognitive information.
 *
 * Virtual IEntities, such as waypoints or goal zones on the IModel could be created by the
 * perception system to add information into the model.
 *
 * Unknown Entities may be created, with certain observable characteristics. These characteristics
 * may refine over time with more sensor input. Once enough information is gathered,
 * the UnknownEntity may well be replaced with something much more well-known; this is the art of
 * cognition.
 *
 * Notice that one particular entity is very special; and that is the sole Robot entity.
 * The robot's got its own way of using the model and its sensors to update its own position, orientation,
 * velocity and accelerations in the model. The robot object itself is treated as an Entity
 * within the Model. This allows smooth interoperability between the logical robot and the
 * model, reducing complexity of the system as a whole.
 * How effective the Model is at modelling the real world, depends heavily, of course, on its implementation.
 *
 */


/**
 * Geometry
 *
 * Use the geometry library!!!
 */
class Geometry {
public:

	virtual int getHeightAt();
	virtual bool isCollidingWith(const Vector2df& point) = 0;
};

/**
 * ShadingModel
 *
 * Provides the heightFunction for geometries, such that areas are filled in different
 * ways, whether it be radial fall-off or solid, or polka-dot.
 */
class ShadingModel {

};


class Entity {
public:
	Entity(string name) : name(name) {}
	virtual ~Entity();

	virtual Vector2df getPosition() = 0;

	// Calculates the
	virtual void heightFunction(const Vector2df& position) = 0;
	virtual Geometry *getGeometry() = 0;

private:
	string name;
};

/**
 * StaticEntity
 *
 * StaticEntities stay still and do not, and cannot move.
 */
class StaticEntity : public Entity {
public:
	StaticEntity(): stat() {}
	virtual ~StaticEntity() {}

	virtual Vector2df getPosition() { return stat->position ; }
	virtual float getOrientation() { return stat->orientation; }

	Static *getStatic() { return stat; }

private:
	Static *stat;
};

/**
 * KinematicEntity
 *
 * KinematicEntities have a position, an orientation, a velocity, and an acceleration
 * associated with them.
 */
class KinematicEntity : public Entity {
public:
	KinematicEntity(): kin() {}
	virtual ~KinematicEntity() {}

	virtual Vector2df getPosition() { return kin->position ; }
	virtual float getOrientation() { return kin->orientation; }
	virtual Vector2df getVelocity() { return kin->velocity; }
	virtual float getRotation() { return kin->rotation; }
	virtual Vector2df getAcceleration() { return kin->acceleration; }

	Kinematic *getKinematic() { return kin; }

private:
	Kinematic *kin;
};


class CircularEntity



/**
 * EntityHeightmapModel
 * 
 * A basic 2D model that works with certain resolution grid, and 
 *  
 */
class EntityHeightmapModel {
public:
	EntityHeightmapModel(int columns, int rows);
	virtual ~EntityHeightmapModel();
	
	virtual void registerStaticEntity(StaticEntity *static_ent);
	virtual void registerKinematicEntity(KinematicEntity *kin_ent);


	virutal void removeStaticEntity(StaticEntity *static_ent);
	virutal void removeKinematicEntity(KinematicEntity *kin_ent);
protected:
	// Updates the heightmap. Usually called after an addition of
	// an entity or  
	virtual void updateMap();


private:
	int columns;
	int height;
	int rows;
	int heightmap[][];
	
	Robot robot; // This is the robot currently holding this model.
};

#endif /* MODEL_H_ */
