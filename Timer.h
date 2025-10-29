#pragma once
#include <chrono>
#include <iostream>

struct Timer
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start,end;
    std::chrono::duration<float> duration;
    
    Timer() //constructor
        : start(std::chrono::high_resolution_clock::now())  // Initialize start in the initialization list
    {
    }

    ~Timer() //destructor
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end-start;
        float ms = duration.count()*1000.0f;
        std::cout << "Speedle time " << ms << " ms" << std::endl;
    }
};