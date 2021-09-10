#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
constexpr int window_dimensions = 800;
constexpr int box_dimensions = 20;
constexpr int max = window_dimensions / box_dimensions;
constexpr int vertex = max * max;
using namespace sf;

typedef struct cell {
	RectangleShape box;
	int wall;
	int visited;
	int vertex;
}cell;
cell matrix[max][max];
int adj_matrix[vertex][vertex] = { 0 };
std::list<int>traverse;
int pred[vertex] = { -1 };
int path[vertex] = { 0 };
int source = 0, des = 0;

Clock cl;
Time dt;
float mx, my;
Sprite info_img;
Texture info_tex;
RectangleShape b1, b2;
int algo_select = 0;

void init(void);
void mouse_update(void);
void create_adj_mat(void);
void add_edge(int, int);
void bfs(void);
void dfs(void);
int get_path(void);
void info(void);

int main()
{
	RenderWindow window(VideoMode(window_dimensions + 300, window_dimensions), "Maze Solver", Style::Close);
	float t = 0;
	int state = 0;
	init();
	
	/*
	for (int i = 0; i < vertex; i++)
	{
		for (int j = 0; j < vertex; j++)
			std::cout << adj_matrix[i][j]<<" ";
		std::cout << std::endl;
	}	*/

	while (window.isOpen())
	{
		//dt = cl.restart();
		//t += dt.asSeconds();

		Event e;
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case Event::Closed:
				window.close();
			case Event::KeyPressed:
				if (Keyboard::isKeyPressed(Keyboard::Enter))
					if (state == 0) {
						create_adj_mat();
						state = 1;
					}
				if (Keyboard::isKeyPressed(Keyboard::R)) {
					init();
					state = 0;
				}
				break;
			default:
				break;
			}
		}

		///////////////////////

		mx = Mouse::getPosition(window).x;
		my = Mouse::getPosition(window).y;

		info();

		//states updating
		if (state == 0)
			mouse_update();
			
		if (state == 1)
		{
			if(algo_select == 0)
				bfs();
			else if(algo_select == 1)
				dfs();
			state = 2;
		}
		if (state == 2 && traverse.empty() == 1)
		{
			int length = get_path();
			for (int k = 0; k < length; k++)
				for (int i = 0; i < max; i++)
					for (int j = 0; j < max; j++)
						if (matrix[i][j].vertex == path[k] && path[k] != source && path[k] != des )
							matrix[i][j].box.setFillColor(Color::Yellow);
		}
		
		
		if (traverse.empty() != 1)
		{
			int x = traverse.front();
			traverse.pop_front();
			for (int i = 0; i < max; i++)
				for (int j = 0; j < max; j++)
					if (matrix[i][j].vertex == x && x != source)
						matrix[i][j].box.setFillColor(Color(190, 190, 190, 255));
			//t = 0;
		}
		
		
		

		/////////////////////////

		window.clear();

		window.draw(info_img);
		window.draw(b1);
		window.draw(b2);
		for (int i = 0; i < max; i++)
			for (int j = 0; j < max; j++)
				window.draw(matrix[i][j].box);

		window.display();
	}
}


void init(void)
{
	int count = 0;
	for (int i = 0; i < max; i++)
	{
		for (int j = 0; j < max; j++)
		{
			matrix[i][j].box.setSize(Vector2f(box_dimensions - 2, box_dimensions - 2));
			matrix[i][j].box.setFillColor(Color(92, 92, 92, 255));
			matrix[i][j].box.setOutlineThickness(2.f);
			matrix[i][j].box.setOutlineColor(Color::Black);
			matrix[i][j].box.setPosition(i * box_dimensions, j * box_dimensions);
			matrix[i][j].wall = 0;
			matrix[i][j].visited = 0;
			matrix[i][j].vertex = count;
			count++;
		}
	}

	for (int i = 0; i < vertex; i++)
	{
		path[i] = 0;
		pred[i] = -1;
		for (int j = 0; j < vertex; j++)
			adj_matrix[i][j] = 0;
	}

	info_tex.loadFromFile("info.png");
	info_img.setTexture(info_tex);
	info_img.setPosition(window_dimensions, 40);

	b1.setSize(Vector2f(12, 12));
	b1.setOutlineThickness(2.f);
	b1.setOutlineColor(Color(92, 92, 92, 255));
	b1.setPosition(window_dimensions + 82, 40 + 215);
	b1.setFillColor(Color::Red);
	b2.setSize(Vector2f(12, 12));
	b2.setOutlineThickness(2.f);
	b2.setFillColor(Color::Black);
	b2.setOutlineColor(Color(92, 92, 92, 255));
	b2.setPosition(window_dimensions + 82, 40 + 243);
}

void create_adj_mat()
{
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

void add_edge(int a, int b)
{
	
	if (b < 0 || b > vertex - 1)
		return;
	//std::cout << a << " " << b << std::endl;
	adj_matrix[a][b] = 1;
	adj_matrix[b][a] = 1;
}

void bfs()
{
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

		traverse.push_back(x);
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

void dfs()
{
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

int get_path()
{
	int k = 0, i = des;
	while (pred[i] != -1)
	{
		path[k++] = i;
		i = pred[i];
	}
	path[k++] = i;
	return k;
}

void mouse_update()
{
	for (int i = 0; i < max; i++)
	{
		for (int j = 0; j < max; j++)
		{
			int hot = mx > matrix[i][j].box.getPosition().x && mx < matrix[i][j].box.getPosition().x + box_dimensions
				&& my > matrix[i][j].box.getPosition().y && my < matrix[i][j].box.getPosition().y + box_dimensions;

			if (hot && Keyboard::isKeyPressed(Keyboard::Key::S))
			{
				source = matrix[i][j].vertex;
				matrix[i][j].box.setFillColor(Color::Red);
			}
			if (hot && Keyboard::isKeyPressed(Keyboard::Key::D))
			{
				des = matrix[i][j].vertex;
				matrix[i][j].box.setFillColor(Color::Green);
			}

			if (hot && Mouse::isButtonPressed(Mouse::Button::Left))
			{
				matrix[i][j].wall = 1;
				matrix[i][j].box.setFillColor(Color::Black);
			}

			if (hot && Mouse::isButtonPressed(Mouse::Button::Right))
			{
				matrix[i][j].wall = 0;
				matrix[i][j].box.setFillColor(Color(92, 92, 92, 255));
			}
		}
	}

}

void info(void)
{
	//for select buttons
	int h1 = mx > b1.getPosition().x && mx < b1.getPosition().x + b1.getGlobalBounds().width
		&& my > b1.getPosition().y && my < b1.getPosition().y + b1.getGlobalBounds().height;
	int h2 = mx > b2.getPosition().x && mx < b2.getPosition().x + b2.getGlobalBounds().width
		&& my > b2.getPosition().y && my < b2.getPosition().y + b2.getGlobalBounds().height;

	if (h1 && Mouse::isButtonPressed(Mouse::Button::Left)) {
		algo_select = 0;
		b1.setFillColor(Color::Red);
		b2.setFillColor(Color::Black);
	}
	if (h2 && Mouse::isButtonPressed(Mouse::Button::Left)) {
		algo_select = 1;
		b2.setFillColor(Color::Red);
		b1.setFillColor(Color::Black);
	}

}