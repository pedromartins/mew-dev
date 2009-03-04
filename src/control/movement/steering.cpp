/*
 * Defines the behaviour classes used for steering.
 *
 * Part of the Artificial Intelligence for Games system.
 *
 * Copyright (c) Ian Millington 2003-2006. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */

#include "../include/movement/steering.h"

namespace mew {
namespace movement {

    void Seek::getSteering(SteeringOutput* output) const
    {
        // First work out the direction
        output->linear = *target;
        output->linear -= character->position;

        // If there is no direction, do nothing
        if (output->linear.squareMagnitude() > 0)
        {
            output->linear.normalise();
            output->linear *= maxAcceleration;
        }
    }

    void Flee::getSteering(SteeringOutput* output) const
    {
        // First work out the direction
        output->linear = character->position;
        output->linear -= *target;

        // If there is no direction, do nothing
        if (output->linear.squareMagnitude() > 0)
        {
            output->linear.normalise();
            output->linear *= maxAcceleration;
        }
    }

};
}; // end of namespace
