/**
     * Represents the position and movement of a character or other object.
     *
     * Kinematic extends static to add the first derivative of both
     * position and orientation: velocity and rotation. Rotation
     * consists of angular velocity about the positive z axis (the
     * first derivative of orientation in the Static structure), this
     * will be altered to be a full 3D angular velocity in due course.
     */
    struct Kinematic : public Static
    {
        /**
         * The linear velocity.
         */
        Vector3 velocity;

        /**
         * The angular velocity.
         */
        double rotation;

        /**
         * Creates a new Kinematic with zeroed data.
         */
        Kinematic()
            : Static(), velocity(), rotation(0)
        {}

        /**
         * Creates a new Kinematic with the given linear components
         * and no rotation or orientation.
         *
         * @param position The position in space of the Kinematic.
         * @param velocity The linear velocity of the Kinematic.
         */
        Kinematic(const Vector3& position, const Vector3& velocity)
            : Static(position), velocity(velocity), rotation(0)
        {}

        /**
         * Creates a new Kinematic with the given static and linear
         * velocity. The Kinematic has no rotation.
         *
         * @param loc The static of the Kinematic.
         * @param velocity The linear velocity of the Kinematic.
         */
        Kinematic(const Static& loc, const Vector3& velocity)
            : Static(loc), velocity(velocity), rotation(0)
        {}

        /**
         * Creates a new Kinematic with the given static and no
         * linear or rotational velocity.
         *
         * @param loc The static of the Kinematic.
         */
        Kinematic(const Static& loc)
            : Static(loc), velocity(), rotation(0)
        {}

        /**
         * Creates a new Kinematic with the given position,
         * orientation, velocity and rotational velocity.
         *
         * @param position The position of the Kinematic.
         * @param orientation The orientation of the Kinematic.
         * @param velocity The linear velocity of the Kinematic.
         * @param avel The angular velocity of the Kinematic.
         */
        Kinematic(const Vector3& position, double orientation,
                  const Vector3& velocity, double avel)
            : Static(position, orientation),
              velocity(velocity), rotation(avel)
        {}

        /**
         * Zeros the static and velocity of this Kinematic.
         */
        void clear()
        {
            Static::clear();
            velocity.clear();
            rotation = 0.0f;
        }

        /**
         * Checks that the given Kinematic is equal to this.
         * Kinematics are equal if their statics, velocities and
         * rotations are equal.
         */
        bool operator == (const Kinematic& other) const
        {
            return position == other.position &&
                   orientation == other.orientation &&
                   velocity == other.velocity &&
                   rotation == other.rotation;
        }

        /**
         * Checks that the given Kinematic is unequal to this.
         * Kinematics are unequal if any of their statics,
         * velocities or rotations are unequal.
         */
        bool operator != (const Kinematic& other) const
        {
            return position != other.position ||
                   orientation != other.orientation ||
                   velocity != other.velocity ||
                   rotation != other.rotation;
        }

        /**
         * Checks that the given Kinematic is less than this.  A
         * Kinematic is less than another Kinematic if its position
         * along the x-axis is less than that of the other Kinematic.
         */
        bool operator < (const Kinematic& other) const
        {
            return position.x < other.position.x;
        }

        /**
         * Sets the value of this Kinematic to the given static.
         * The velocity components of the Kinematic are left
         * unchanged.
         *
         * @param other The Static to set the Kinematic to.
         */
        Kinematic& operator = (const Static& other)
        {
            orientation = other.orientation;
            position = other.position;
            return *this;
        }

        /**
         * Copies (by assignment) all the attributes of the given
         * Kinematic.
         *
         * @param other Reference to Kinematic to copy.
         */
        Kinematic& operator = (const Kinematic& other)
        {
            orientation = other.orientation;
            position = other.position;
            velocity = other.velocity;
            rotation = other.rotation;
            return *this;
        }

        /**
         * Modifies the value of this Kinematic by adding the given
         * Kinematic.  Additions are performed by component.
         */
        void operator += (const Kinematic&);

        /**
         * Modifies the value of this Kinematic by subtracting the
         * given Kinematic.  Subtractions are performed by component.
         */
        void operator -= (const Kinematic&);

        /**
         * Scales the Kinematic by the given value.  All components
         * are scaled, including rotations and orientations, this is
         * normally not what you want. To scale only the linear
         * components, use the *= operator on the position and
         * velocity components individually.
         *
         * @param f The scaling factor.
         */
        void operator *= (double f);

        /**
         * Performs a forward Euler integration of the Kinematic for
         * the given duration.  This applies the Kinematic's velocity
         * and rotation to its position and orientation.
         *
         * \note All of the integrate methods in this class are
         * designed to provide a simple mechanism for updating
         * position. They are not a substitute for a full physics
         * engine that can correctly resolve collisions and
         * constraints.
         *
         * @param duration The number of simulation seconds to
         * integrate over.
         */
        void integrate(double duration);

        /**
         * Perfoms a forward Euler integration of the Kinematic for
         * the given duration, applying the given acceleration.
         * Because the integration is Euler, all the acceleration is
         * applied to the velocity at the end of the time step.
         *
         * \note All of the integrate methods in this class are designed
         * to provide a simple mechanism for updating position. They are
         * not a substitute for a full physics engine that can correctly
         * resolve collisions and constraints.
         *
         * @param steer The acceleration to apply over the
         * integration.  @param duration The number of simulation
         * seconds to integrate over.
         */
        void integrate(const SteeringOutput& steer, double duration);

        /**
         * Perfoms a forward Euler integration of the Kinematic for
         * the given duration, applying the given acceleration and
         * drag.  Because the integration is Euler, all the
         * acceleration is applied to the velocity at the end of the
         * time step.
         *
         * \note All of the integrate methods in this class are designed
         * to provide a simple mechanism for updating position. They are
         * not a substitute for a full physics engine that can correctly
         * resolve collisions and constraints.
         *
         * @param steer The acceleration to apply over the integration.
         *
         * @param drag The isotropic drag to apply to both velocity
         * and rotation. This should be a value between 0 (complete
         * drag) and 1 (no drag).
         *
         * @param duration The number of simulation seconds to
         * integrate over.
         */
        void integrate(const SteeringOutput& steer,
                       double drag, double duration);

        /**
         * Perfoms a forward Euler integration of the Kinematic for the given
         * duration, applying the given acceleration and drag.
         * Because the integration is Euler, all the acceleration is applied to
         * the velocity at the end of the time step.
         *
         * \note All of the integrate methods in this class are designed
         * to provide a simple mechanism for updating position. They are
         * not a substitute for a full physics engine that can correctly
         * resolve collisions and constraints.
         *
         * @param steer The acceleration to apply over the integration.
         *
         * @param drag The anisotropic drag to apply. The force
         * component of the SteeringOutput is interpreted as linear drag
         * coefficients in each direction, and torque component is
         * interpreted as the rotational drag.
         *
         * @param duration The number of simulation seconds to
         * integrate over.
         */
        void integrate(const SteeringOutput& steer,
                       const SteeringOutput& drag,
                       double duration);

        /**
         * Trims the speed of the kinematic to be no more than that
         * given.
         */
        void trimMaxSpeed(double speed);

        /**
         * Sets the orientation of this static so it points along
         * its own velocity vector.
         */
        void setOrientationFromVelocity();
    };

