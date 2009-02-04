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
#include <stdlib.h>
#include <aicore/aicore.h>

//#include <functional>
//#include <algorithm>
//#include <float.h>
#include <assert.h>

namespace aicore {

//#include "include/steerutils.h"

    /**
     * An inline function calculating the determinant of 3 column vectors.
     */
    inline real det(const Vector3& v1, const Vector3& v2, const Vector3& v3)
    {
        return v1.x * v2.y * v3.z - v1.x * v3.y * v2.z - v2.x * v1.y * v3.z
             + v2.x * v3.y * v1.z + v3.x * v1.y * v2.z - v3.x * v2.y * v1.z;
    }

    /*
     * Returns the distance of point p from line (g, v), where v is
     * the orienting vector and g is a point on the line.
     */
    inline real distanceFromLine(const Vector3& g, const Vector3& v,
                                  const Vector3& p)
    {
        // Solution taken from http://mathworld.wolfram.com/
        Vector3 c  = g; c -= p;
        real  t  = c * v / v.squareMagnitude();
        Vector3 vt = v; vt *= t;
        c += vt;
        return c.magnitude();
    }

    /*
     * Returns a vector perpendicular to the given vector. The rotation axis
     * is arbitrary, i.e. it cannot be specified by the user.
     */
    inline Vector3 getNormal(const Vector3& v,
                             bool use3dRestitution = true)
    {
        if (use3dRestitution)
        {
            if (!v.z) return Vector3(v.y, -v.x, 0);
            if (!v.y) return Vector3(v.z, 0, -v.x);
            if (!v.x) return Vector3(0, v.z, -v.y);
            return Vector3(- v.y * v.z * 2 / v.x, -v.z, -v.y);
        }
        return Vector3(v.y, -v.x, 0);
    }

    /*
        Returns the point that:
          1. Lies on a plane perpendicular to line (g, v) and passing through
             point g.
          2. Lies in the same plane as the line and another point p.
          3. Lies at a distance r from point g.
        This routine is used during docking, when the actor is downstream
        from the goal.
    */
    inline Vector3 getArchPoint(const Vector3& g, const Vector3& v,
                                const Vector3& p, real r)
    {
        // The formula is:  g + d * r / |d|
        // where            d = v x c
        // where            c = (p - g) x v
        // where 'x' is the vector product
        Vector3 d, c = p; c -= g; c %= v;
        if (c.isZero()) d = getNormal(v);
        else d = v % c;
        d *= r / d.magnitude();
        d += g;

        return d;
    }

    /*
     * Calculates the value of a custom squashing function. In order to avoid
     * calculating the exponent function, we construct our squashing function
     * by putting together two constant functions and a linear component in
     * the middle.
     * x is the value of the independent variable
     * s is the squashing factor
     * a is the tangent of the linear segment
     * The function returns values between -s and +s, exluding +- s itself.
     */
    inline real squash(real x, real s = 1, real a = 1)
    {
        if (x > 0)
            if (x < s / a) return a * x;
            else return s;
        else
            if (x > -s / a) return a * x;
            else return -s;
    }

    /*
     * Finds the smallest angle we need to add to alpha
     * to get the angle beta (or some 360^0 multiple of beta).
     */
    inline real smallestTurn(real alpha, real beta)
    {
        real f = fmodf(beta - alpha, M_2PI);
        if (f < -M_PI) return f + M_2PI;
        if (f >= M_PI) return f - M_2PI;
        return f;
    }


    Vector3 intersection(const Kinematic& k1, const Kinematic& k2)
    {
        Vector3 v1 = k1.velocity, v2 = k2.velocity;
        v1.normalise(); v2.normalise();
        Vector3 v12 = v1; v12 %= v2;
        const real v12l = v12.magnitude();
        v12 *= ((real)1.0)/v12l;
        Vector3 p(k1.position, k2.position);
        const real t1 = det(p, v2, v12) / v12l,
                    t2 = det(p, v1, v12) / v12l;
        v1 *= t1; v2 *= t2;
        p = k1.position; p += v1; p += k2.position; p += v2;
        p *= 0.5;
        return p;
    }

    real timeToAgent(const Kinematic& actor, const Kinematic& predator,
                      real safetyMargin)
    {
        Vector3 dp(actor.position, predator.position);
        Vector3 dv(predator.velocity, actor.velocity);
        const real dp2 = dp.squareMagnitude(),
                    dv2 = dv.squareMagnitude(),
                    r2  = safetyMargin * safetyMargin;

        if (dv2 == 0)
            if (dp2 < r2) return 0;
            else return FLT_MAX;
        // Calculate the time of nearest approach
        const real dpdv = dp * dv,
                    at   = dpdv / dv2;
        if (at <= 0)
            if (dp2 < r2) return at;
            else return FLT_MAX;

        if (dp2 <= r2) return 0;

        // Calculate the square of nearest the approach distance
        const real dpdv2 = dpdv * dpdv,
                    ad2   = dp2 - dpdv2 / dv2;
        if (ad2 > r2) return FLT_MAX;

        // Actual time of collision
        if (r2 == 0) return at;
        const real delta = dpdv2 - dv2 * (dp2 - r2);

        // Numerical instability sometimes produces slightly negative deltas
        if (delta <= 0) return at;
        const real t = (dpdv - sqrtf(delta)) / dv2;
        assert(t > 0);
        return t;
    }

    // Implementation based on quaternion algebra
    void rotate(Vector3& p, real cosa, const Vector3& n)
    {
        assert(n.magnitude() == 1);
        // Calculate quaternion q(cos(a/2), n * sin(a/2))
        const real qr = sqrtf((1 + cosa) / 2);
        Vector3 q = n; q *= sqrtf((1 - cosa) / 2);
        // calculate x = q * p
        const real xr =  - q.x * p.x - q.y * p.y - q.z * p.z;
        Vector3 x(qr * p.x + q.y * p.z - q.z * p.y,
                     qr * p.y + q.z * p.x - q.x * p.z,
                     qr * p.z + q.x * p.y - q.y * p.x);
        // calculate p = x * ~q, where ~q is the conjugate of q
        p.x = -xr * q.x + x.x * qr - x.y * q.z + x.z * q.y;
            p.y = -xr * q.y + x.y * qr - x.z * q.x + x.x * q.z;
            p.z = -xr * q.z + x.z * qr - x.x * q.y + x.y * q.x;
    }

    const Kinematic* Targeter::getActor() const
    {
	if (!steering) return NULL;
	return steering->getActor();
    }


    SteerPipe::SteerPipe(Targeter *t, Kinematic *a, Actuator *r)
            :
            localTargeter(false), localActor(false),
            localActuator(false), relaxationSteps(1),
            constraints(NULL), decomposers(NULL)
    {
        setActor(a);
        setTargeter(t); // must be called after setActor()
        setActuator(r);
    }

    SteerPipe::SteerPipe(const SteerPipe& other)
    {
        targeter = other.targeter;
        localTargeter = false;
        actor = other.actor;
        localActor = false;
        actuator = other.actuator;
        localActuator = false;
        decomposers = other.decomposers;
        constraints = other.constraints;
        relaxationSteps = other.relaxationSteps;
    }

    void SteerPipe::setActor(const Kinematic *a)
    {
        if (localActor) delete actor;

        if (a)
        {
            actor = a;
            localActor = false;
        }
        else
        {
            actor = new Kinematic();
            localActor = true;
        }
        if (localTargeter) setTargeter(NULL);
    }

    void SteerPipe::setTargeter(Targeter* t)
    {
        if (localTargeter) delete targeter;

        if (t)
        {
            targeter = t;
            localTargeter = false;
        }
        else
        {
            targeter = new Targeter(actor);
            localTargeter = true;
        }
        targeter->steering = this;
    }

    void SteerPipe::setActuator(Actuator *a)
    {
        if (localActuator) delete actuator;
        if (a)
        {
            actuator = a;
            localActuator = false;
        }
        else
        {
            actuator = new Actuator();
            localActuator = true;
        }
        actuator->steering = this;
    }

    void SteerPipe::addDecomposer(Decomposer* d)
    {
        d->next = decomposers;
        decomposers = d;
        d->steering = this;
    }

    void SteerPipe::addConstraint(SteeringConstraint* c)
    {
        c->next = constraints;
        constraints = c;
        c->steering = this;
    }


    void SteerPipe::run()
    {
        const Vector3& v = actor->velocity;
        speed2 = v.squareMagnitude();
        speed  = sqrtf(speed2);
        orientation.x = cosf(actor->orientation);
        orientation.y = sinf(actor->orientation);

        targeter->run();
        currentGoal = *targeter->getGoal();

        // run decomposers
        Decomposer * decomp = decomposers;
        while (decomp != NULL)
        {
            decomp->run();
            decomp = decomp->next;
        }

        // Constraint satisfaction algorithm. Works by gradually expanding the
        // "no-go" angle in front of the actor.
        Kinematic leftGoal, rightGoal = *actor, previousGoal = currentGoal;
        real leftSine = 0, rightSine = 0, currentSine = 0;
        real priority = 0;
        while (true)
        {
            bool violation = false, refinement = false;
            SteeringConstraint * constraint = constraints;
            while (constraint != NULL)
            {
                if (constraint->priority < priority) continue;
                constraint->violated = false;
                constraint->run();
                if (constraint->violated)
                {
                    const Kinematic& sg = constraint->suggestedGoal;
                    const Vector3 w(actor->position, sg.position);
                    real normFactor = sqrtf((v.x * v.x + v.y * v.y)
                                           * (w.x * w.x + w.y * w.y));
                    real sine, cosine;
                    if (normFactor) {
                        sine = (v.x * w.y - v.y * w.x) / normFactor;
                        cosine = (v.x * w.x + v.y * w.y) / normFactor;
                    } else {
                        sine = cosine = 0;
                    }

                    if (cosine < 0)
                    {   // make the sine monotonic
                        if (sine > 0) {
                            sine += 2 * (1 - sine);
                        } else {
                            sine -= 2 * (1 + sine);
                        }
                    }

                    if (constraint->priority > priority)
                    {   // ignore earlier constraints
                        leftGoal.clear(); rightGoal = *actor;
                        leftSine = rightSine = currentSine = 0;
                        priority = constraint->priority;
                    }

                    if (sine > leftSine) {
                        leftSine = sine; leftGoal = sg; refinement = true;
                    } else if (sine < rightSine) {
                        rightSine = sine; rightGoal = sg; refinement = true;
                    }
                    violation = true;
                }

                constraint = constraint->next;
            }
            if (!violation) break;
            if (refinement)
            {
                // Choose the smaller of the two no go angles for the
                // next pass.
                if (!rightSine || leftSine && leftSine < -rightSine)
                {
                    currentGoal = leftGoal; currentSine = leftSine;
                }
                else
                {
                    currentGoal = rightGoal; currentSine = rightSine;
                }
                previousGoal = currentGoal;
                continue;
            }

            // If the goal hasn't changed some constraint must be
            // firing even though its suggested goal has already been
            // taken into account.
            if (currentGoal == previousGoal) break;

            // This side didn't yield a workable solution. Try the
            // other.  But first check if we haven't done that
            // already.
            if (-currentSine > leftSine || -currentSine < rightSine)
            {
                constraintDeadlock();
                break;
            }

            if (currentSine == leftSine)
            {
                currentGoal = rightGoal; currentSine = rightSine;
            }
            else
            {
                currentGoal = leftGoal; currentSine = leftSine;
            }
        }
        actuator->run();
    }


    /**
     * Approximates the turning arc by two linear sections for
     * collision detection.  Returns the apex (midpoint) in the first
     * argument, and if the agent is going too fast, the second
     * argument is also filled with the projected end point.
     *
     * @param pt Pseudo target - Kinematic to write the apex of the
     * turning arc.
     *
     * @param pg Pseudo goal - Kinematic to write the end point of the
     * turning arc.
     *
     * @param steering the SteerPipe object which performs the
     * calculation
     *
     * @returns the time after which the actor will theoretically
     * reach the apex.
     */
    static inline real wayPoint(Kinematic& pt, Kinematic& pg,
                                 const SteerPipe* steering)
    {
        const Kinematic& a = *steering->getActor();
        const Kinematic& g = steering->currentGoal;
        const Vector3 a2g(a.position, g.position);
        real stopTime = 0;
        if (steering->getSpeed() && !a2g.isZero())
        {
            // Calculate component of actor's velocity perpendicular to a2g
            Vector3 vPara = a.velocity;
            vPara *= vPara * a2g / (steering->getSpeed() * a2g.magnitude());
            const Vector3 vPerp(vPara, a.velocity);

            // Calculate time required to reduce perpendicular
            // component of velocity to zero, assuming all
            // deceleration goes towards this.
            stopTime = vPerp.magnitude() /
                steering->getActuator()->maxAcceleration;

            // Calculate how far we will travel along actor's current
            // velocity vector in stopTime and hence set pseudoTarget
            // to this point.
            pt.position = a.velocity;
            pt.position *= stopTime;
            pt.position += a.position;
        }
        else pt.position = a.position;
        pt.velocity = g.position;
        pt.velocity -= pt.position;

        if (!pt.velocity.isZero()) {
            pt.velocity.setMagnitude(steering->getSpeed());
        }

        pg = g;
        return stopTime;
    }

    void AvoidAgentConstraint::calcResolution(const Kinematic* actor,
                                              real margin, real)
    {
        // Predator's position at nearest approach time
        Vector3 prediction = agent->velocity; prediction *= time;
        prediction += agent->position;
        suggestedGoal.position  = prediction;
        suggestedGoal.position -= actor->position;

        // If prediction is behind, place suggested goal on other side of us.
        if (suggestedGoal.position * actor->velocity < 0) {
            suggestedGoal.position *= -1;
        } else {
            // Otherwise place suggested goal on other side of our path.
            const real sgl = suggestedGoal.position.magnitude();
            suggestedGoal.position %= actor->velocity;
            const real sina = suggestedGoal.position.magnitude()
                             / steering->getSpeed() / sgl;

            // But, if prediction is roughly ahead, turn right.
            if (fabsf(sina) < .1f)
                 suggestedGoal.position = getNormal(actor->velocity);
            else suggestedGoal.position %= actor->velocity;
        }

        suggestedGoal.position.setMagnitude(margin);
        suggestedGoal.position += prediction;
        suggestedGoal.velocity = suggestedGoal.position;
        suggestedGoal.velocity -= actor->position;
        suggestedGoal.velocity.setMagnitude(steering->getActuator()->maxSpeed);
        suggestedGoal.orientation = atan2f(
            suggestedGoal.velocity.y, suggestedGoal.velocity.x);
    }

    void AvoidAgentConstraint::run()
    {
        const Kinematic *actor = steering->getActor();
        #ifndef _DEBUG
            Kinematic pt1, pt2;
        #endif
        if (inertial)
        {
            const real tOffset = wayPoint(pt1, pt2, steering);
            time = timeToAgent(*actor, *agent, safetyMargin);
            if (time < tOffset)
            {
                violated = true;
                calcResolution(actor, safetyMargin);
            }
            else
            {   // Move the agent forward by tOffset
                Kinematic pseudoAgent(agent->velocity, agent->velocity);
                pseudoAgent.position *= tOffset;
                pseudoAgent.position += agent->position;
                time = timeToAgent(pt1, pseudoAgent, safetyMargin);
                if (time <
                    pt1.position.distance(steering->currentGoal.position)
                    / steering->getSpeed())
                {
                    violated = true;
                    time += tOffset;
                    calcResolution(&pt1, safetyMargin, tOffset);
                }
            }
        }
        else
        {
            const Kinematic *currentGoal = &steering->currentGoal;
            pt1 = *actor;
            pt1.velocity  = currentGoal->position;
            pt1.velocity -= pt1.position;
            pt1.velocity.setMagnitude(steering->getSpeed());
            time = timeToAgent(pt1, *agent, safetyMargin);
            if (time < pt1.position.distance(steering->currentGoal.position)
                                           / steering->getSpeed())
            {
                violated = true;
                calcResolution(&pt1, safetyMargin);
            }
        }
    }

    // These parameters could be made member of
    // AvoidPredatorConstraint if it proves necessary to tune them on
    // case-by-case basis. For now, let's not complicate the API or
    // give our IP away.

    /**
     * The safetyMargin is increased by distance to agent scaled by
     * this parameter, i.e. the actual margin used by the constraint
     * is safetyMargin + |d - safetyMargin| * distanceScale.  The
     * default value is 0.
     */
    const real distanceScale = .5f;

    /**
     * When it comes to generating the suggested goal, the margin
     * adjusted by the distanceScale is scaled again by avoidScale.
     */
    const real avoidScale = 2;

    void AvoidPredatorConstraint::calcResolution(const Kinematic* actor,
                                                 real margin, real tOffset)
    {
        const Kinematic *currentGoal = &steering->currentGoal;

        // Predator's position at approach time
        Vector3 prediction = agent->velocity; prediction *= time;
        prediction += agent->position;
        suggestedGoal.position  = prediction;
        suggestedGoal.position -= actor->position;

        // If the prediction is in front of the actor then we place
        // the suggested goal opposite the prediction w.r.t. our path.
        if (suggestedGoal.position * actor->velocity > 0)
        {
            suggestedGoal.position %= actor->velocity;
            if (suggestedGoal.position.isZero())
                suggestedGoal.position = getNormal(actor->velocity);
            suggestedGoal.position %= actor->velocity;
            suggestedGoal.position.setMagnitude(margin * avoidScale);
            suggestedGoal.position += prediction;
        }

        // Otherwise we place it on the opposite side to the actor's
        // prediction.
        else
        {
            suggestedGoal.position  = actor->velocity;
            suggestedGoal.position *= time - tOffset;
            suggestedGoal.position += actor->position;
            suggestedGoal.position -= prediction;
            if (suggestedGoal.position.isZero())
                suggestedGoal.position = getNormal(agent->velocity);
            suggestedGoal.position.setMagnitude(margin * avoidScale);
            suggestedGoal.position += prediction;
        }
        suggestedGoal.velocity = suggestedGoal.position;
        suggestedGoal.velocity -= actor->position;
        suggestedGoal.velocity.setMagnitude(steering->getActuator()->maxSpeed);
        suggestedGoal.orientation = atan2f(
            suggestedGoal.velocity.y, suggestedGoal.velocity.x);
    }

    /*
        Based on AvoidAgentConstraint, with additional check for the predator
        targeting our current position.
    */
    void AvoidPredatorConstraint::run()
    {
        const Kinematic *actor = steering->getActor();
        const Vector3 a2p(actor->position, agent->position);
        const real margin = fabsf(a2p.magnitude() - safetyMargin)
                           * distanceScale + safetyMargin;
        #ifndef _DEBUG
            Kinematic pt1, pt2;
        #endif
        pt1 = pt2 = *actor;
        time = timeToAgent(*agent, Kinematic(actor->position), margin);
        if (time < lookAheadTime)
        {
            violated = true;
            calcResolution(actor, margin);
            return;
        }
        if (inertial)
        {
            const real tOffset = wayPoint(pt1, pt2, steering);
            time = timeToAgent(*actor, *agent, margin);
            if (time < tOffset)
            {
                violated = true;
                calcResolution(actor, margin);
            }
            else
            {   // Move the agent forward by tOffset
                Kinematic pseudoAgent(agent->velocity, agent->velocity);
                pseudoAgent.position *= tOffset;
                pseudoAgent.position += agent->position;
                time = timeToAgent(pt1, pseudoAgent, margin);
                if (time <
                    pt1.position.distance(steering->currentGoal.position)
                    / steering->getSpeed())
                {
                    violated = true;
                    time += tOffset;
                    calcResolution(&pt1, margin, tOffset);
                }
            }
        }
        else
        {
            const Kinematic *currentGoal = &steering->currentGoal;
            pt1 = *actor;
            pt1.velocity  = currentGoal->position;
            pt1.velocity -= pt1.position;
            pt1.velocity.setMagnitude(steering->getSpeed());
            time = timeToAgent(pt1, *agent, margin);
            if (time < pt1.position.distance(steering->currentGoal.position)
                                           / steering->getSpeed())
            {
                violated = true;
                calcResolution(&pt1, margin);
            }
        }
    }

    void AvoidLocationConstraint::calcResolution(const Kinematic* actor,
                                              real margin, real)
    {
        const Kinematic *currentGoal = &steering->currentGoal;
        suggestedGoal.position  = agent->position;
        suggestedGoal.position -= actor->position;

        // Place the suggested goal opposite the prediction w.r.t. our path.
        suggestedGoal.position %= actor->velocity;
        if (suggestedGoal.position.isZero())
            suggestedGoal.position = getNormal(actor->velocity);
        suggestedGoal.position %= actor->velocity;
        suggestedGoal.position.setMagnitude(margin);
        suggestedGoal.position += agent->position;
        suggestedGoal.velocity = suggestedGoal.position;
        suggestedGoal.velocity -= actor->position;
        suggestedGoal.velocity.setMagnitude(steering->getActuator()->maxSpeed);
        suggestedGoal.orientation = atan2f(
            suggestedGoal.velocity.y, suggestedGoal.velocity.x);
    }

    void AvoidLocationConstraint::run()
    {
        #ifndef _DEBUG
            Kinematic pt1, pt2;
        #endif
        const Kinematic *actor = steering->getActor(),
                        *currentGoal = &steering->currentGoal;
        Vector3 a2p = agent->position; a2p -= actor->position;
        const real margin = fabsf(a2p.magnitude() - safetyMargin)
                           * distanceScale + safetyMargin;
        const Kinematic location(agent->position);
        if (inertial)
        {
            const real tOffset = wayPoint(pt1, pt2, steering);
            time = timeToAgent(*actor, location, margin);
            if (time < tOffset)
            {
                violated = true;
                calcResolution(actor, safetyMargin);
            }
            else
            {
                time = timeToAgent(pt1, location, margin);
                if (time <
                    pt1.position.distance(steering->currentGoal.position)
                    / steering->getSpeed())
                {
                    violated = true;
                    time += tOffset;
                    calcResolution(&pt1, margin, tOffset);
                }
            }
        }
        else
        {
            pt1 = *actor;
            pt1.velocity  = currentGoal->position;
            pt1.velocity -= pt1.position;
            pt1.velocity.setMagnitude(steering->getSpeed());
            time = timeToAgent(pt1, location, margin);
            if (time < pt1.position.distance(steering->currentGoal.position)
                                           / steering->getSpeed())
            {
                violated = true;
                calcResolution(&pt1, margin);
            }
        }
    }

    void AvoidWallsConstraint::run()
    {
        if (!steering->getSpeed()) return;
        #ifndef _DEBUG
            Kinematic pt1, pt2;
        #endif

        const Kinematic *actor = steering->getActor(),
                        *currentGoal = &steering->currentGoal;
        if (inertial)
        {
            const real tOffset = wayPoint(pt1, pt2, steering);
            if (collisionDetector->detectCollisions(*actor, pt1, &cp, &cv))
            {
                violated = true;
                Vector3 p2c = cp; p2c -= actor->position;
                time = p2c.magnitude() / steering->getSpeed();
                calcResolution(actor);
            }
            else if (collisionDetector->detectCollisions(pt1, *currentGoal,
                                                         &cp, &cv))
            {
                violated = true;
                Vector3 p2c = cp; p2c -= pt1.position;
                time = p2c.magnitude() / steering->getSpeed() + tOffset;
                calcResolution(&pt1);
            }
        }
        else if (collisionDetector->detectCollisions(*actor, *currentGoal,
                                                     &cp, &cv))
        {
            violated = true;
            pt1 = *actor;
            pt1.velocity  = currentGoal->position;
            pt1.velocity -= pt1.position;
            pt1.velocity.setMagnitude(steering->getSpeed());
            Vector3 p2c = cp; p2c -= pt1.position;
            time = p2c.magnitude() / steering->getSpeed();
            calcResolution(&pt1);
        }
    }

    void AvoidWallsConstraint::calcResolution(const Kinematic* actor)
    {
        if (!actor) actor = steering->getActor();

        // Set the suggestedGoal to: cp + cv * safetyMargin + cvT *
        // shift, where cvT is the vector normal to cv lying in the
        // same plane as actor's velocity. First find the vector
        // perpendicular to the plane in which cv and actor's velocity
        // lie.
        Vector3 cvT = cv, a = actor->velocity;
        a %= cv; cvT %= a;
        if (!use3dRestitution) cvT.z = 0;
        real cvTl = cvT.magnitude();

        // nasty case when collision is head-on
        if (!cvTl)
        {
            cvT = getNormal(actor->velocity, use3dRestitution);
            cvTl = cvT.magnitude();
            assert(cvTl && "cvT must not be zero");
        }
        cv.setMagnitude(safetyMargin);
        suggestedGoal.position = cp;
        suggestedGoal.position += cv;

        cvT *= shift / cvTl;
        suggestedGoal.position += cvT;
        suggestedGoal.velocity = cvT;
        if (goalSpeed < 0)
            suggestedGoal.velocity *= steering->getSpeed() / shift;
        else
            suggestedGoal.velocity *= goalSpeed / shift;
        suggestedGoal.orientation = atan2f(
            suggestedGoal.position.y - actor->position.y,
            suggestedGoal.position.x - actor->position.x);
    }

    Actuator::Actuator(SteeringOutput *s)
            :
            steering(NULL),
            localSteer(false), maxAcceleration(1),
            maxSpeed(1), maxAngular(1), maxRotation(1),
            angularSharpness(1), sharpness(1)
    {
        setSteeringOutput(s);
    }

    Actuator::Actuator(const Actuator& other)
    {
        steering = other.steering;
        steer = other.steer;
        localSteer = false; // Steering output created by other
        maxAcceleration = other.maxAcceleration;
        maxSpeed = other.maxSpeed;
        maxAngular = other.maxAngular;
        maxRotation = other.maxRotation;
        angularSharpness = other.angularSharpness;
        sharpness = other.sharpness;
    }

    void Actuator::setSteeringOutput(SteeringOutput *s)
    {
        if (localSteer) steer;
        if (s)
        {
            steer = s;
            localSteer = false;
        }
        else
        {
            steer = new SteeringOutput();
            localSteer = true;
        }
    }

    void Actuator::run()
    {
        const Kinematic *currentGoal = &steering->currentGoal,
                        *actor = steering->getActor();
        // vector from current position to current goal
        Vector3 p2g = currentGoal->position; p2g -= actor->position;
        const real d2 = p2g.squareMagnitude(),
                    maxAcceleration2 = maxAcceleration * maxAcceleration;

        if (d2 > 0)
        {
            const real d = sqrtf(d2);
            p2g *= ((real)1.0/d); // p2g is now unit magnitude

            // vParallel and vNormal are component vectors of the
            // actor's velocity where vParallel is in the direction
            // from the actor towards the goal, and vNormal is normal
            // to vParallel.
            const real vP = actor->velocity * p2g;
            Vector3 vParallel = p2g; vParallel *= vP;
            Vector3 vNormal = actor->velocity; vNormal -= vParallel;

            // Apply centripetal linear equal to -vNormal
            steer->linear = vNormal;
            steer->linear *= -1;

            // Calculate the magnitude of propelling linear, after centripetal
            // linear is subtracted from maxAcceleration.
            const real vN2 = vNormal.squareMagnitude(),
                        fP2 = maxAcceleration2 - vN2;

            // If the centripetal takes all our acceleration budget,
            // then just crop it.
            if (fP2 < 0) {
                steer->linear *= maxAcceleration / sqrtf(vN2);
            } else {
                // Calculate the braking/acceleration distance
                const real gP = currentGoal->velocity * p2g,
                    brakingDistance = (d * maxAcceleration * 2 + vP*vP - gP*gP)
                                    /  maxAcceleration / 4;

                // apply a smoothing function around the speed summit
                p2g *= squash(d - brakingDistance, sqrtf(fP2), sharpness);
                steer->linear += p2g;
            }
        }
        else
        {   // if we are on target then adjust speed to match goal speed.
            steer->linear = currentGoal->velocity;
            steer->linear -= actor->velocity;
            real linear2 = steer->linear.squareMagnitude();
            // If the linear is too big then crop it.
            if (linear2 > maxAcceleration2)
                steer->linear *= maxAcceleration / sqrtf(linear2);
        }

        // Check if we are not breaking the speed limit
        if (steering->getSpeed() > maxSpeed)
        {
            const real dp = steer->linear * actor->velocity;
            if (dp > 0)
            {
                // remove the forward-pointing component of steer linear
                steer->linear -= actor->velocity *
                    (dp / steering->getSpeed2());
            }
        }

        // Calculate the angle we need to turn to point us in the desired
        // direction.
        const real dAngle = smallestTurn(actor->orientation,
                                          currentGoal->orientation);

        // Calculate the angle we will turn through when accelerating to our
        // target rotation.
        real brakingAngle = (fabsf(dAngle) * maxAngular * 2 +
                              actor->rotation * actor->rotation -
                              currentGoal->rotation * currentGoal->rotation) /
                              maxAngular / 4;

        if(dAngle < 0) brakingAngle *= -1;

        // apply a smoothing function around the speed summit
        steer->angular = squash(dAngle - brakingAngle,
                               maxAngular,
                               angularSharpness);

        // If we are rotating faster than we currently are allowed and
        // the new angular will make us accelerate even faster, then
        // set the angular to zero.
        if(fabsf(actor->rotation) >= maxRotation &&
           actor->rotation * steer->angular > 0)
        {
            steer->angular = 0;
        }
    }

} // end of namespace
