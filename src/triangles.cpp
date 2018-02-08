#include <cmath>
#include "triangles.h"

Triangles::Triangles(unsigned int triangle_count, sf::Vector2u size) {
    count = triangle_count;
    screen_size = size;

    vertex_array = sf::VertexArray(sf::Triangles, count*3);
}

void Triangles::randomize_triangle(std::default_random_engine& rnd) {
    std::uniform_int_distribution<int> chooser(0, count - 1);
    std::uniform_int_distribution<sf::Uint8> color_space(0, 255);
    std::uniform_real_distribution<float> x_space(0, screen_size.x);
    std::uniform_real_distribution<float> y_space(0, screen_size.y);

    int i = chooser(rnd);
    sf::Color color(color_space(rnd), color_space(rnd), color_space(rnd), color_space(rnd));

    for(int vertex = 0; vertex < 3; ++vertex){
        vertex_array[i*3 + vertex].position = sf::Vector2f(x_space(rnd), y_space(rnd));
        vertex_array[i*3 + vertex].color = color;
    }
}

int Triangles::cost(sf::RenderTexture& render_texture, sf::Image& original){
    render_texture.clear();
    render_texture.draw(vertex_array);

    sf::Image image = render_texture.getTexture().copyToImage();
    auto i = image.getPixelsPtr();
    auto o = original.getPixelsPtr();
    auto end = i + (screen_size.x + screen_size.y * 4);
    int cost = 0;
    while(i!=end){
        cost += std::abs((int)*i - (int)*o);

        ++i;
        ++o;
    }

    return cost;
}
