#include "Visualization.h"

void Visualization::create_adj_mat() {

	for (int i = 0; i < max; i++)
	{
		for (int j = 0; j < max; j++)
		{
			if (matrix[i][j].wall == 0)
			{
				if (j + 1 < max && matrix[i][j + 1].wall == 0)
					add_edge(matrix[i][j].vertex, matrix[i][j + 1].vertex);
				if (j - 1 > 0 && matrix[i][j - 1].wall == 0)
					add_edge(matrix[i][j].vertex, matrix[i][j - 1].vertex);
				if (i + 1 < max && matrix[i + 1][j].wall == 0)
					add_edge(matrix[i][j].vertex, matrix[i + 1][j].vertex);
				if (i - 1 > 0 && matrix[i - 1][j].wall == 0)
					add_edge(matrix[i][j].vertex, matrix[i - 1][j].vertex);
			}

		}
	}
}

void Visualization::add_edge(int a, int b) {

	if (b < 0 || b > vertex - 1)
		return;
	//std::cout << a << " " << b << std::endl;
	adj_matrix[a][b] = 1;
	adj_matrix[b][a] = 1;
}

void Visualization::bfs() {

	std::list<int> queue;
	bool visited[vertex] = { false };

	visited[source] = true;
	queue.push_back(source);

	while (queue.empty() != 1)
	{
		int x = queue.front();

		if (x == des) {
			pred[source] = -1;
			return;
		}

		//traverse.push_back(x);
		//std::cout << x << " ";
		queue.pop_front();

		for (int i = 0; i < vertex; i++)
		{
			if (adj_matrix[x][i] == 1 && visited[i] == false)
			{
				visited[i] = true;
				queue.push_back(i);
				pred[i] = x;
			}
		}
	}
}

void Visualization::dfs() {

	int i;
	std::list<int> stack;
	bool visited[vertex] = { false };

	stack.push_back(source);
	visited[source] = true;
	traverse.push_back(source);
	pred[source] = -1;

	while (stack.empty() != 1)
	{
		int x = stack.back();

		for (i = 0; i < vertex; i++)
		{
			if (adj_matrix[x][i] == 1 && visited[i] == false)
			{
				stack.push_back(i);
				pred[i] = x;
				traverse.push_back(stack.back());
				visited[i] = true;
				if (i == des)
					return;
				break;
			}
		}
		if (i == vertex)
			stack.pop_back();
	}
}

int Visualization::get_path() {

	int k = 0, i = des;
	while (pred[i] != -1)
	{
		path[k++] = i;
		i = pred[i];
	}
	path[k++] = i;
	return k;
}

void Visualization::init(void) {

	//adj_matrix.resize(vertex);
	map.loadFromFile("Images/Map.png");
	spriteMapTex.loadFromFile("Images/newMap.png");
	spriteMap.setTexture(spriteMapTex);

	int count = 0;
	for (int i = 0; i < max; i++) {
		for (int j = 0; j < max; j++) {
			matrix[i][j].box.setSize(sf::Vector2f(box_dimensions - 2, box_dimensions - 2));
			matrix[i][j].box.setOutlineThickness(2.f);
			matrix[i][j].box.setOutlineColor(sf::Color::Black);
			matrix[i][j].box.setPosition(i * box_dimensions, j * box_dimensions);
			
			unsigned int boxPixlX = i * box_dimensions + 10;
			unsigned int boxPixlY = j * box_dimensions + 10;
			//std::cout << boxPixlX << " " << boxPixlY << "\n";
			if (map.getPixel(boxPixlX, boxPixlY) == sf::Color::White) {
				matrix[i][j].box.setFillColor(sf::Color(92, 92, 92, 255));
				matrix[i][j].wall = 0;	//no wall
			}
			else 
			{
				matrix[i][j].box.setFillColor(sf::Color::Black);
				matrix[i][j].wall = 1;	//set wall
			}

			matrix[i][j].visited = 0;
			matrix[i][j].vertex = count;
			count++;
		}
	}

	for (int i = 0; i < vertex; i++) {
		path[i] = 0;
		pred[i] = -1;
		for (int j = 0; j < vertex; j++)
			adj_matrix[i][j] = 0;
	}

	

}

void Visualization::mouse_update(sf::Vector2i mousePos) {

	for (int i = 0; i < max; i++)
	{
		for (int j = 0; j < max; j++)
		{
			int hot = mousePos.x > matrix[i][j].box.getPosition().x && mousePos.x < matrix[i][j].box.getPosition().x + box_dimensions
				&& mousePos.y > matrix[i][j].box.getPosition().y && mousePos.y < matrix[i][j].box.getPosition().y + box_dimensions;

			if (hot && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			{
				source = matrix[i][j].vertex;
				matrix[i][j].box.setFillColor(sf::Color::Red);
			}
			if (hot && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				des = matrix[i][j].vertex;
				matrix[i][j].box.setFillColor(sf::Color::Green);
			}

			if (hot && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				matrix[i][j].wall = 1;
				matrix[i][j].box.setFillColor(sf::Color::Black);
			}

			if (hot && sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			{
				matrix[i][j].wall = 0;
				matrix[i][j].box.setFillColor(sf::Color(92, 92, 92, 255));
			}
		}
	}

}