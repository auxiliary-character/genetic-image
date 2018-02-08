#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>
#include <iostream>
#include "options.h"
#include "triangles.h"

int main(int argc, char** argv) {
    Options options = get_options(argc, argv);
    std::cout << "Threads: " << options.threads << std::endl;
    std::cout << "In: " << options.in_file << std::endl;

    sf::Image image;
    if(!image.loadFromFile(options.in_file)){
        std::cerr << "Can't load image file!" << std::endl;
        return 1;
    }

    sf::Vector2u image_size = image.getSize();
    sf::RenderWindow window(sf::VideoMode(image_size.x, image_size.y), "Genetic Image");
    sf::RenderTexture render_texture;
    if(!render_texture.create(image_size.x, image_size.y)){
        std::cerr << "Can't create render texture!" <<std::endl;
        return 1;
    }

    int seed = std::chrono::system_clock::now().time_since_epoch().count();

    auto engine = std::default_random_engine(seed);
    Triangles triangles(50, image_size);

    int current_cost = triangles.cost(render_texture, image);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        Triangles mutation = triangles;
        mutation.randomize_triangle(engine);
        int cost = mutation.cost(render_texture, image);
        if(cost < current_cost){
            triangles = mutation;
            current_cost = cost;
            std::cout << "Cost: " << current_cost << std::endl;
        }
        window.clear();
        window.draw(triangles.vertex_array);
        window.display();
    }

    return 0;
}
