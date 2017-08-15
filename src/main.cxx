
#include "scene.h"

int main()
{
    heap::Scene scene;

    while(scene.update()) scene.draw();

    return 0;
}
