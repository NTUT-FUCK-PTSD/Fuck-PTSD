#include "Settings/Window.hpp"

#include "config.hpp"

void Window::Init() {
    RowNumber =
        (Window::ColNumber
         * (double(PTSD_Config::PTSD_Config::WINDOW_HEIGHT)
            / double(PTSD_Config::PTSD_Config::WINDOW_WIDTH)));
    Scale =
        ((double(PTSD_Config::PTSD_Config::WINDOW_WIDTH) / ColNumber)
         / TileWidth);
    HalfColNumber = ColNumber / 2.0f;
    HalfRowNumber = RowNumber / 2.0f;
}

double Window::RowNumber;
double Window::Scale;
double Window::HalfColNumber;
double Window::HalfRowNumber;
