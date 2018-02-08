#ifndef TRIANGLES_H
#define TRIAGNELS_H

#include <SFML/Graphics.hpp>
#include <random>

struct Triangles{
    unsigned int count;
    sf::VertexArray vertex_array;
    sf::Vector2u screen_size;

    Triangles(unsigned int count, sf::Vector2u screen_size);
    void randomize_triangle(std::default_random_engine& rnd);
    int cost(sf::RenderTexture& render_texture, sf::Image& original);
};

#endif
