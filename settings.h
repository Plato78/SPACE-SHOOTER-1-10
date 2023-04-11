#pragma once
#include "SFML/Graphics.hpp"

const float WINDOW_WIDTH = 800;
const float WINDOW_HEIGHT = 1000;
const std::string WINDOW_TITLE = "SFML Space Shooter P33122";
const float FPS = 60.f;

const std::string IMAGES_FOLDER = "images\\";

const std::string PLAYER_FILE_NAME = "playerShip2_red.png";
const float PLAYER_SPEED = 10.f;
const int INITIAL_PLAYER_HP = 100;
const int FIRE_COOLDOWN = 200;

const int METEOR_TYPES_QTY = 8;
const size_t METEOR_QTY = 20;

const std::string RES_FOLDER = "res\\";
const std::string FONT_FILE_NAME = "ds-digib.ttf";
const size_t CHAR_SIZE = 32;

const std::string LASER_FILE_NAME = "laserRed03.png";

const float BONUS_SPEED = 10.f;
const int BONUS_RANGE = 10000;
const int BONUS_CHANCE = 500;

const std::string MULTI_LASER_BONUS_FILE_NAME = "things_gold.png";
