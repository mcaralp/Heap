
#include "path.h"
#include "scene.h"

int main(int, char ** argv)
{
	heap::Path::init(argv[0]);

	// Compute the size of the window
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	uint32_t width  = mode.height / 2;
	uint32_t height = mode.height * (3 / 4.f);

    heap::Scene scene(width, height);

    // Start the game
    while(scene.update()) scene.draw();

    return 0;
}
