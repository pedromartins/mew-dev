/**
     * Represents the static of a character or other object.
     *
     * A static consists of a position and orientation. Position is
     * stored as a vector, rotation is a planar rotation about the y
     * axis. This will be altered to be a quaternion in due course.
     */
struct Static
{
        /**
         * The position in 3 space.
         */
        Vector3 position;

        /**
         * The orientation, as a euler angle in radians around the
         * positive y axis (i.e. up) from the positive z axis.
         */
        double orientation;

        /**
         * Creates a new static with a 0 position and orientation.
         */
        Static() : orientation(0.0f)
        {}

        /**
         * Creates a static at the given position with no rotation.
         */
        Static(const Vector3& position)
            : position(position), orientation(0.0f)
        {}

        /**
         * Creates a static with the given position and orientation.
         */
        Static(const Vector3& position, double orientation)
            : position(position), orientation(orientation)
        {}

        /**
         * Creates a static with the position vector given as
         * components and the given orientation.
         */
        Static(double x, double y, double z, double orientation)
            : position(x, y, z), orientation(orientation)
        {}

        /**
         * Assignment operator.
         */
        Static& operator = (const Static& other)
        {
            position = other.position;
            orientation = other.orientation;
            return *this;
        }

        /**
         * Zeros the position and orientation.
         */
        void clear()
        {
            position.clear();
            orientation = 0.0f;
        }

        /**
         * Checks that the given static is equal to this. Statics
         * are equal if their positions and orientations are equal.
         */
        bool operator == (const Static& other) const
        {
            return position == other.position &&
                orientation == other.orientation;
        }

        /**
         * Checks that the given static is unequal to
         * this. Statics are unequal if either their positions or
         * orientations are unequal.
         */
        bool operator != (const Static& other) const
        {
            return position != other.position ||
                orientation != other.orientation;
        }

        /**
         * Perfoms a forward Euler integration of the Kinematic for
         * the given duration, applying the given steering velocity
         * and rotation.
         *
         * \note All of the integrate methods in this class are designed
         * to provide a simple mechanism for updating position. They are
         * not a substitute for a full physics engine that can correctly
         * resolve collisions and constraints.
         *
         * @param steer The velocity to apply over the integration.
         *
         * @param duration The number of simulation seconds to
         * integrate over.
         */
        void integrate(const SteeringOutput& steer, double duration);

        /**
         * Sets the orientation of this static so it points along
         * the given velocity vector.
         */
        void setOrientationFromVelocity(const Vector3& velocity);

        /**
         * Returns a unit vector in the direction of the current
         * orientation.
         */
        Vector3 getOrientationAsVector() const;

        /**
         * Fills the passed matrix with the Static's transformation.
        void retrieveTM(Matrix& m);
         */
    };
