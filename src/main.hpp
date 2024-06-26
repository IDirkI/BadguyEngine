#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <stdio.h>
#include <queue>

#include <eigen3/Eigen/Dense>
#include <SDL2/SDL.h>

#include "../include/Structures/Shapes/Rectangle.hpp"
#include "../include/Structures/Shapes/Plane.hpp"
#include "../include/Structures/Shapes/Triangle.hpp"
#include "../include/Structures/Shapes/Shape.hpp"
#include "../include/Structures/Polygon.hpp"
#include "../include/Camera.hpp"
#include "../include/Draw.hpp"

using std::cout;
using std::endl;
using std::queue;

using Eigen::Vector2d;
using Eigen::Vector3d;

/* ##### Function Headers ##### */
void update(double, Draw*, queue<Shape *> *);
bool input();

#endif