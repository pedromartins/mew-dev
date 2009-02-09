/*
 * Defines the pipeline steering system.
 *
 * Part of the Artificial Intelligence for Games system.
 *
 * Copyright (c) Ian Millington 2003-2006. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */

/**
 * @file
 *
 * Holds the pipeline steering system.
 */
#ifndef AICORE_STEERPIPE_H
#define AICORE_STEERPIPE_H

// Defines NULL
#include <stdlib.h>

namespace aicore
{

    /**
     * Generates goals in the form of a kinematic (position,
     * orientation, velocity and rotation) that can be sought by the
     * steering system.  This class can be used as is, to specify the
     * target, or it may be extended to provide more sophisticated
     * targeting behaviour.  Targeters are intended to work only when
     * installed in a SteerPipe class.
     */
    class Targeter
    {
        friend class SteerPipe;

    protected:

        /**
         * Pointer to the SteerPipe class, where details about the actor and
         * the goal are stored. This is set by the SteerPipe class when the
         * targeter is installed.
         */
        const SteerPipe* steering;

        /**
         * Pointer to the generated goal. This pointer is returned by
         * the inline function getGoal.
         */
        const Kinematic* goal;

    public:

        /**
         * Creates a new targeter seeking the given goal.
         */
        Targeter(const Kinematic* g)
                :
                steering(NULL),
                goal(g)
        {}

        /**
         * Gets the goal to the given kinematic.
         */
        virtual void setGoal(const Kinematic* g)
        {
            goal = g;
        }

        /**
         * Gets the current goal for this targeter. For efficiency,
         * this method is inline and cannot be overloaded. The pointer
         * stored in this class can be set when the targeter receives
         * execution time (in the normal manner, through its run
         * function), or by calling setGoal explicitly.
         *
         * @returns The current goal, always the pointer stored in the
         * goal member.
         */
        const Kinematic* getGoal() const
        {
            return goal;
        }

        /**
         * Returns the kinematick of the agent's actor.
         */
        const Kinematic* getActor() const;

        /**
         * Runs the targeter. The default implementation does nothing,
         * because the goal is assumed to be explicit.
         */
        virtual void run() {};
    };

    /**
     * Decomposes a target to an immediate target (subgoal). For
     * example, a planning decomposer takes a target position to move
     * to, produces a plan to get there from the current location, and
     * returns a subgoal at the first node of the plan. This class
     * should be extended to provide the needed decomposition.
     * Decomposers are intended to work only when installed in a
     * SteerPipe class.
     */
    class Decomposer
    {
        friend class SteerPipe;

    protected:

        /**
         * Pointer to the SteerPipe class, where details about the actor and
         * the goal are stored. This is set by the SteerPipe class when the
         * decomposer is installed.
         */
        SteerPipe* steering;

    public:

        /**
         * Decomposers can be structured in a list. This points to the
         * next item.
         */
        Decomposer * next;

        /**
         * Creates a new decomposer.
         */
        Decomposer() : steering(NULL) {}

        /**
         * Runs the decomposer.
         */
        virtual void run() = 0;
    };


    /**
     * Constrains what the steering system can do in order to achieve
     * its goals. It is provided with the actor and goal (or subgoal,
     * if it has been decomposed), and can register a corrective
     * action that should be taken to avoid violating the constraint.
     * Constraints are intended to work only when installed in a
     * SteerPipe class.
     */
    class SteeringConstraint
    {
        friend class SteerPipe;

    protected:

        /**
         * Pointer to the SteerPipe class, where details about the
         * actor and the goal are stored. This is set by the SteerPipe
         * class when the constraint is added to it.
         */
        const SteerPipe* steering;

    public:

        /**
         * Steering constraints can be held in a list. This points to
         * the next item in the list.
         */
        SteeringConstraint * next;

        /**
         * True if the constraint is or is about about to be
         * violated. In such case the time member gives the time
         * remaining until the violation occurs and suggestedGoal
         * specifies the suggested evasive action.
         */
        bool violated;

        /**
         * The suggested goal to head for to avoid violating this
         * constraint.  Subclasses should write to this variable each
         * time they receive their processing budget (through the run
         * function in the normal way).
         */
        Kinematic suggestedGoal;

        /**
         * Time left until the constaint is violated, if no corrective
         * action is taken. If no constraint is detected then this
         * should be set to FLT_MAX or any value greater than
         * lookAheadTime. The constraint resolution algorithm in the
         * SteerPipe class picks the constraint with the highest
         * priority, then the lowest time.  Subclasses should write to
         * this variable each time this they receives their processing
         * budget (through the run function in the normal way).
         */
        real time;

        /**
         * The priority of this constraint. The constraint resolution
         * algorithm in the SteerPipe class picks the constraint with
         * the highest priority, then the lowest time (see above). The
         * default priority is zero.
         */
        real priority;

        /**
         * If this parameter is true then the constraint checks for
         * collisions in two stages: first with agent's path projected
         * along current velocity, up to the apex of the turning arc,
         * and second from the apex to the current goal. If the
         * parameter is false then the constraint checks for
         * collisions between the current position and the goal.  The
         * default value is true.
         */
        bool inertial;

        /**
         * Creates a new constraint.
         */
        SteeringConstraint()
                :
                steering(NULL), violated(false),
                priority(0), inertial(true)
        {}

        /**
         * Runs the constraint.
         */
        virtual void run() = 0;

    };

    /**
     * Tries to ensure the agent stays clear of another moving agent.
     * The assumption is that the other agent's agenda is not to chase
     * us, i.e. this constraint should be used for controlling groups
     * of neutral agents. See also AvoidLocationConstraint and
     * AvoidPredatorConstraint.
     */
    class AvoidAgentConstraint : public SteeringConstraint
    {
    protected:

        /**
         * Function calculating the suggested goal when a collision is
         * detected.
         *
         * @param actor The position and course from which collisions
         * were probed.
         *
         * @param margin The current safety margin (can be different
         * from safetyMargin)
         *
         * @param tOffset The time offset by which the actor has been
         * moved before probing.
         *
         * The result is written directly to the suggestedGoal member
         * variable.  The time member variable is not altered. The
         * caller must set it to the appropriate value before calling
         * this method.
         */
        virtual void calcResolution(const Kinematic* actor, real margin,
                                    real tOffset = 0);
    public:

        /**
         * The agent being avoided. Can be changed freely at runtime.
         */
        const Kinematic* agent;

        /**
         * The minimum distance from the location that the constraint
         * will tolerate. This parameter can be changed freely at
         * runtime. The default value is 1.
         */
        real safetyMargin;

        /**
         * Creates a new avoid agent constraint to avoid the given
         * kinematic.
         */
        AvoidAgentConstraint(Kinematic* a = NULL)
                :
                SteeringConstraint(),
                agent(a),
                safetyMargin(1)
        {}

        /**
         * Runs the constraint.
         */
        virtual void run();
    };

    /**
     * Will try to ensure the agent stays clear of a moving agent who
     * is likely to be chasing it. See also AvoidLocationConstraint
     * and AvoidAgentConstraint.
     */
    class AvoidPredatorConstraint : public AvoidAgentConstraint
    {
    protected:

        /**
         * See AvoidAgentConstraint::calcResolution().
         */
        void calcResolution(const Kinematic*, real, real = 0);

    public:
        /**
         * The time which the constraint should look ahead for
         * violations.
         *
         * Any violation which happens further ahead than this time
         * will be ignored. The default value is 1.
         */
        real lookAheadTime;

        /**
         * Creates a new constraint to avoid the given predator.
         */
        AvoidPredatorConstraint(Kinematic* predator = NULL)
                :
                AvoidAgentConstraint(predator),
                lookAheadTime(1)
        {}

        /**
         * Runs the constraint.
         */
        void run();
    };

    /**
     * Tries to ensure the agent stays clear of a static
     * location. Treats all passed kinematics as stationary objects.
     */
    class AvoidLocationConstraint : public AvoidAgentConstraint
    {
    protected:

        /**
         * See AvoidAgentConstraint::calcResolution().
         */
        void calcResolution(const Kinematic*, real, real = 0);

    public:

        /**
         * Constructor.
         */
        AvoidLocationConstraint(Kinematic* location = NULL)
                :
                AvoidAgentConstraint(location)
        {}

        /**
         * Runs the constraint.
         */
        void run();
    };

    /**
     *  This class is an interface to a collision detector.  It should
     *  be overridden to implement a specific collision detector.  A
     *  function needing a collision detector should create an
     *  instance of this interface.
     */
    class CollisionDetector
    {
    public:

        /**
         * Interface to the collision detection engine. The user must
         * provide it when instantiating some of the behaviours.
         *
         * @param current The current kinematic state of the agent
         * @param target The agent's target
         * @param collisionPoint A pointer to a structure into which the
         * coordinates of the collision point should be entered.
         * @param collisionNormal A pointer to a structure into which the
         * vector normal to the collision surface should be entered.
         *
         * @return False if no collision is detected.
         */
        virtual bool detectCollisions(const Kinematic& current,
                                      const Kinematic& target,
                                      Vector3* collisionPoint,
                                      Vector3* collisionNormal) = 0;
    };

    /**
     * Attempts to steer clear of obstacles. Requires a collision detector
     * as defined above.
     */
    class AvoidWallsConstraint : public SteeringConstraint
    {
    protected:

        CollisionDetector *collisionDetector;

        /**
         * Function calculating the suggested goal when a collision is
         * detected.
         *
         * @param actor The position and course from which
         * collisions were probed.
         *
         * The result is written directly to the suggestedGoal member
         * variable.  The time member variable is not altered. The
         * caller must set it to the appropriate value before calling
         * this method.
         */
        virtual void calcResolution(const Kinematic* actor);

    public:

        /**
         * This flag indicates whether or not to perform 3d collision
         * resolution.  It defaults to true.
         */
        bool use3dRestitution;

        /**
         * Distance from the wall that the constraint will try to keep
         * at.  Default value is 1.
         */
        real safetyMargin;

        /**
         * The distance by which the tip of the collision vector
         * (normal to the wall) is shifted along the wall to produce
         * the correction vector.
         */
        real shift;

        /**
         * The absolute velocity of the suggested goal. If this value
         * is negative then the current actor speed is used. Default
         * value is -1.
         */
        real goalSpeed;

        /**
         * Collision point and normal vector returned by the collision
         * detector.
         */
        mutable Vector3 cp, cv;

        /**
         * Constructor.
         *
         * @param d Pointer to an instance of CollisionDetector.
         */
        AvoidWallsConstraint(CollisionDetector *d)
                :
                SteeringConstraint(),
                collisionDetector(d),
                use3dRestitution(true),
                safetyMargin(1),
                shift(1),
                goalSpeed(-1)
        {}

        /**
         * Set the collision detector currently in use by this constraint.
         *
         * @param cd Pointer to the collision detector to use.
         */
        void setCollisionDetector(CollisionDetector *cd)
        {
            collisionDetector = cd;
        }

        /**
         * Runs the constraint.
         */
        void run();
    };

    /**
     * Actuators generate forcess and torques that are required to
     * achieve the current goal state from the current actor
     * state. The default behaviour is to generate forces to move
     * towards the goal and align the orientation with the goal
     * kinematic, as well as adjust the target speed to match the goal
     * kinematic. The goal velocity direction is ignored.
     */
    class Actuator
    {
        friend class SteerPipe;

    protected:

        /**
         * Pointer to the SteerPipe class, where details about the
         * actor and the goal are stored. This is set by the SteerPipe
         * class when the actuator is added to it.
         */
        SteerPipe* steering;

        /**
         * The steering output which the actuator updates.
         */
        SteeringOutput* steer;

        /**
         * True if the steering output was created and should be
         * destroyed by this instance.
         */
        bool localSteer;

    public:

        /**
         * The maximum acceleration (as output in the steer member)
         * that an agent is allowed to apply. Default is 1 distance
         * unit per second per second.  It assumes the agent has a
         * mass of 1 unit.
         */
        real maxAcceleration;

        /**
         * The maximum speed the agent is allowed to do.
         * The default value is 1;
         */
        real maxSpeed;

        /**
         * The maximum angular acceleration (as output in the steer
         * member) that an agent is allowed to apply. Default is 1
         * radian per second per second.  It assumes the agent has a
         * moment of inertia of 1 unit.
         */
        real maxAngular;

        /**
         * The maximum rotation the agent is allowed to do.
         * The default value is 1;
         */
        real maxRotation;

        /**
         * Controls how aggressive the steering is at turning. The
         * higher this value the sharper the turning will be. Allowed
         * range [0, oo). Default value 1.
         */
        real angularSharpness;

        /**
         * Controls how aggressive the steering is. The higher this
         * value the sharper the transition between accelerating and
         * braking. Allowed range [0, oo). Default value 1.
         */
        real sharpness;

        /**
         * Creates a new actuator.
         *
         * @param steer Pointer to a steer object. If this is NULL
         * then a default object will be created.
         */
        Actuator(SteeringOutput* steer = NULL);

        /**
         * Copy constructor.
         */
        Actuator(const Actuator& other);

        /**
         * Sets the steer instance used to output steering actions to
         * take. If the given steer is null or no steer is given, then
         * a new local steer is used, otherwise the given steer is
         * considered non-local.
         */
        void setSteeringOutput(SteeringOutput* steer = NULL);

        /**
         * Gets the current steering output.
         */
        SteeringOutput* getSteeringOutput() const
        {
            return steer;
        }

        /**
         * Returns the steering object owning this actuator.
         */
        const SteerPipe* getSteering() const
        {
            return steering;
        }

        /**
         * Sets the steer force and torque to the values required to
         * achieve the current goal.
         */
        void run();
    };

    /**
     * The steering system, uses a targeter, an actuator and an
     * optional set of decomposers and constraints, to create steering
     * outputs to guide an agent to its goal. See the user guide for a
     * detailed discussion of the steering algorithm.
     */
    class SteerPipe
    {
    protected:

        /**
         * The targeter used to generate the top level goal.
         */
        Targeter* targeter;

        /**
         * True if the targeter was created and should be destroyed by
         * this instance.
         */
        bool localTargeter;

        /**
         * The actor that is doing the steering.
         */
        const Kinematic* actor;

        /**
         * True if the actor was created by the constructor and should
         * be destroyed by this instance.
         */
        bool localActor;

        /**
         * The actuator used for generating output
         */
        Actuator* actuator;

        /**
         * True if the actuator was created by the constructor and
         * should be destroyed by this instance.
         */
        bool localActuator;

        /**
         * A list of decomposers.
         */
        Decomposer * decomposers;

        /**
         * A list of constraints.
         */
        SteeringConstraint * constraints;

        /**
         * The current speed.
         *
         * The current speed, squared speed and orientation vector of
         * the actor are recalculated at the beginning
         * of each invocation of the run method, so that subcomponents
         * do not need to perform the same calculations. If a subclass
         * overrides the run method it must compute these values as
         * well, as many standard constraints depend on them being up
         * to date. The x and y components of the orientation vector
         * are cosine and sine of the actor's orientation
         * respectively; the z component is always zero.
         */
        real speed;

        /**
         * The current speed squared.
         *
         * The current speed, squared speed and orientation vector of
         * the actor are recalculated at the beginning
         * of each invocation of the run method, so that subcomponents
         * do not need to perform the same calculations. If a subclass
         * overrides the run method it must compute these values as
         * well, as many standard constraints depend on them being up
         * to date. The x and y components of the orientation vector
         * are cosine and sine of the actor's orientation
         * respectively; the z component is always zero.
         */
        real speed2;

        /**
         * The current orientation vector.
         *
         * The current speed, squared speed and orientation vector of
         * the actor are recalculated at the beginning
         * of each invocation of the run method, so that subcomponents
         * do not need to perform the same calculations. If a subclass
         * overrides the run method it must compute these values as
         * well, as many standard constraints depend on them being up
         * to date. The x and y components of the orientation vector
         * are cosine and sine of the actor's orientation
         * respectively; the z component is always zero.
         */
        Vector3 orientation;

        /**
         * Called when constraints could not be resolved after a
         * number of passes through the list. The maximum number of
         * passes is specified by the relaxationSteps member
         * variable. If in the last pass at least one constraint still
         * triggers then this method is called as a special measure to
         * resolve the deadlock. The default action is to do nothing,
         * but the client application may for instance invoke a
         * planner here.
         */
        virtual void constraintDeadlock()
        {
        }

    public:

        /**
         * The current goal or subgoal being sought.
         */
        Kinematic currentGoal;

        /**
         * The maximum number of passes through the constraint list.
         * See the constraintDeadlock() method for more details.  The
         * default value is 1.
         */
        int relaxationSteps;

        /**
         * Creates a new steering system. If no targeter is given then
         * the default targeter will create its own target at the
         * origin, which will never change.
         *
         * @param targeter Pointer to a Targeter object generating
         * targets for this steering object. If equal to NULL, a
         * default Targeter is created.
         *
         * @param actor Pointer to a Kinematic object describing the
         * agent being controlled. If equal to NULL, a default actor
         * object is created.
         *
         * @param actuator Pointer to an Actuator object which
         * generates output forces. If equal to NULL, a default
         * inertial actuator is created.
         */
        SteerPipe(Targeter* targeter = NULL, Kinematic* actor = NULL,
            Actuator* actuator = NULL);

        /**
         * Creates a copy of the given steering system. This shares
         * all data with the given steering, making targeter, actor
         * and steer non-local.
         */
        SteerPipe(const SteerPipe&);

        /**
         * Destroys the steering system, along with any non-local
         * components.
         */
        virtual ~SteerPipe()
        {}

        /**
         * Sets the actor to be the given kinematic. If the given
         * kinematic is null or no kinematic is given, it creates a
         * new, local, kinematic.  If the given kinematic is non null,
         * it is considered non-local.
         */
        void setActor(const Kinematic* kinematic=NULL);

        /**
         * Gets the current actor.
         */
        const Kinematic* getActor() const
        {
            return actor;
        }

        /**
         * Returns the current speed of the actor.
         */
        real getSpeed() const
        {
            return speed;
        }

        /**
         * Returns the current squared speed of the actor.
         */
        real getSpeed2() const
        {
            return speed2;
        }

        /**
         * Returns the current orientation of the actor as a
         * normalised vector in the XY plane, i.e. x =
         * cos(orientation), y = sin(orientation), and z = 0.
         */
        const Vector3& getOrientation() const
        {
            return orientation;
        }

        /**
         * Sets the targeter used to generate top level goals. If no
         * targeter is given, or the targeter is null, then a new
         * targeter is created, otherwise the given targeter is
         * considered to be non-local.
         */
        void setTargeter(Targeter* targeter = NULL);

        Targeter* getTargeter() const
        {
            return targeter;
        }

        /**
         * Changes the current actuator.
         */
        void setActuator(Actuator* actuator = NULL);

        /**
         * Returns the current actuator.
         */
        Actuator* getActuator() const
        {
            return actuator;
        }

        /**
         * Adds the given decomposer to the steering pipeline.
         */
        void addDecomposer(Decomposer* decomposer);

        /**
         * Adds the given constraint to the steering pipeline.
         */
        void addConstraint(SteeringConstraint* steering);

        /**
         * Runs the steering system. When this function returns, the
         * steering output can be retrieved from getSteeringOutput (or
         * by holding a pointer to the steer structure in which it is
         * written).
         */
        void run();
    };

}; // end of namespace

#endif // AICORE_STEERPIPR_H
