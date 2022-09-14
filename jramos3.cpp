#include <iostream>

class OtherCar
{
    private:
    int xPosition;
    int yPosition;
    int velocity;
    public:
    // add data regarding car sprites
    // tie the car position to the street
};

enum Direction
{
    Left,
    Right,
}

void car_motion(Direction direction, vec & position)
{
    // add code relating to movement of the camera (W, A, S, D)
    // this might work with cameraPosition[0]
    switch (direction) {
        case (Left):
            position[0] -= 1.0f;
        case (Right):
            position[0] += 1.0f;
    }
}

void accelerate(float & velocity)
{
    // change the velocity
    // can this work with cameraPosition[2]?
    velocity += 1.0f;
}

void decelerate(float & velocity)
{
    // lower the velocity
    velocity -= 1.0f;
}

void apply_velocity(int vel, vec & position)
{
    position[2] += vel;
}

void show_name_jr3()
{
    std::cout << "jramos3" << std::endl;
}

