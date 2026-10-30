#include "../data/window.hpp"

int main(int argc, char* argv[]){
    int window_height = 600;
    int window_width = 900;
    const char* window_name = "Engine";

    Window window = Window(window_height, window_width, window_name);
    window.Open();
}