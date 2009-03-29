    /**
     * SteeringOutput is a movement requested by the steering system.
     *
     * It consists of linear and angular components. The components
     * may be interpreted as forces and torques when output from a
     * full dynamic steering behaviour, or as velocity and rotation
     * when output from a kinematic steering behaviour. In the former
     * case, neither force nor torque take account of mass, and so
     * should be thought of as linear and angular acceleration.
     */
    struct SteeringOutput
    {
        /**
         * The linear component of the steering action.
         */
        Vector3 linear;

        /**
         * The angular component of the steering action.
         */
        double angular;

        /**
         * Creates a new steering action with zero linear and angular
         * changes.
         */
        SteeringOutput() : angular(0)
        {}

        /**
         * Creates a new steering action with the given linear and
         * angular changes.
         *
         * @param linear The initial linear change to give the
         * SteeringOutput.
         *
         * @param angular The initial angular change to give the
         * SteeringOutput.
         */
        SteeringOutput(const Vector3& linear, double angular = 0)
            : linear(linear), angular(angular)
        {}

        /**
         * Zeros the linear and angular changes of this steering action.
         */
        void clear()
        {
            linear.clear();
            angular = 0;
        }

        /**
         * Checks that the given steering action is equal to this.
         * SteeringOutputs are equal if their linear and angular
         * changes are equal.
         */
        bool operator == (const SteeringOutput& other) const
        {
            return linear == other.linear &&  angular == other.angular;
        }

        /**
         * Checks that the given steering action is unequal to this.
         * SteeringOutputs are unequal if either their linear or
         * angular changes are unequal.
         */
        bool operator != (const SteeringOutput& other) const
        {
            return linear != other.linear ||  angular != other.angular;
        }

		/**
		 * Returns the square of the magnitude of this steering output.
		 * This includes the angular component.
		 */
		double squareMagnitude()
		{
			return linear.squareMagnitude() + angular*angular;
		}

		/**
		* Returns the magnitude of this steering output.
		* This includes the angular component.
		 */
		double magnitude()
		{
			return double_sqrt(squareMagnitude());
		}
    };
