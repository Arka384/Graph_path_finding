#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

constexpr int box_dimensions = 20;
constexpr int max = 600 / box_dimensions;
constexpr int vertex = max * max;

typedef struct cell {
	sf::RectangleShape box;
	int wall;
	int visited;
	int vertex;
}cell;

class Visualization
{
private:

public:
	cell matrix[max][max];
	int adj_matrix[vertex][vertex] = { 0 };
	//std::vector<std::vector<int>> adj_matrix(vertex, std::vector<int>(vertex));
	std::list<int>traverse;
	int pred[vertex] = { -1 };
	int path[vertex] = { 0 };
	int source = 0, des = 0;

	sf::Image map;
	sf::Sprite spriteMap;
	sf::Texture spriteMapTex;

	void create_adj_mat(void);
	void add_edge(int, int);
	void bfs(void);
	void dfs(void);
	int get_path(void);
	void init(void);
	void mouse_update(sf::Vector2i mousePos);

};

