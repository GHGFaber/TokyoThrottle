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
    Right
};

void car_motion(Direction direction, float & position)
{
    // add code relating to movement of the camera (W, A, S, D)
    // this might work with cameraPosition[0]
    switch (direction) {
        case (Left):
            position -= 1.0f;
        case (Right):
            position += 1.0f;
    }
}

void accelerate(float & velocity)
{
    // change the velocity
    // can this work with cameraPosition[2]?
    // velocity += 0.1f;
}

void decelerate(float & velocity)
{
    // lower the velocity
    // velocity -= 0.1f;
}

void apply_velocity(int vel, float & position)
{
    position += vel;
}

void show_name_jr3()
{
    std::cout << "Jarl Ramos / Geoffrey De Palme" << std::endl;
}

