// Lunar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once
#include <iostream>
#include "Scene.h"
#include "Scene0.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "SceneManager.h"

void main()
{
    auto sceneManager = new SceneManager();
    sceneManager->Initialize("Main", 1280, 720);
   // sceneManager->AddScene(new Scene0());
    sceneManager->AddScene(new Scene2());
    sceneManager->AddScene(new Scene3());
    sceneManager->AddScene(new Scene4());
    sceneManager->AddScene(new Scene2());
    sceneManager->Run(0);
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
