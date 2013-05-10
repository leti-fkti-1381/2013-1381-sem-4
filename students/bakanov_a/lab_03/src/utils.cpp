#include "include/utils.h"
#include <iostream>

// Инициализация статических членов класса Node.
int Node::mSize = 0;
int** Node::cMatrix = 0;
int** Node::dMatrix = 0;

// При создании, элементы массива order в узле инициализируются -1.
Node::Node() {
	order = new int [Node::mSize];
	for (int i = 0; i < Node::mSize; ++i)
		order[i] = -1;
}

Node::Node(const Node& node) {
	order = new int [Node::mSize];
	for (int i = 0; i < Node::mSize; ++i)
		order[i] = node.order[i];
}

Node::~Node() {
	delete [] order;
	order = 0;
}

std::string numToStr (int n) {
	std::stringstream ss;
	ss << n;
	return ss.str();
}

std::string numToChar (int n) {
	char c = 'a';
	c += n;
	return std::string (1, c);
}

std::string solve (int** cMatrix, int** dMatrix, int mSize) {
	// Инициализируем статические поля класса Node
	Node::cMatrix = cMatrix;
	Node::dMatrix = dMatrix;
	Node::mSize = mSize;
	// Создаем корневой узел дерева
	Node root;
	// Создаем указатель на узел, хранящий текущий минимум.
	Node* minNode = 0;
	// Запускаем шарманку.
	processNode( &root, minNode, mSize );
	
	// Формируем результат
	std::string result = "";
	for (int i = 0; i < Node::mSize; ++i)
		result += numToStr( i ) + "\t";
	result += "\n";
	for (int i = 0; i < Node::mSize; ++i)
		result += numToChar( minNode->order[i] ) + "\t";
	result += "\n\n";
	result += "sum = " + numToStr( minNode->sum ) + "\n";

	return result;
}

int calculateSum (int* order) {
	int sum = 0;
	// Проходимся по order
	for (int i = 0; i < Node::mSize && order[i] >= 0; ++i) {
		int a = order[i];
		for (int j = i + 1; j < Node::mSize && order[j] >= 0; ++j) {
			int b = order[j];
			sum += Node::cMatrix[a][b] * Node::dMatrix[i][j];
		}
	}
	return sum;
}

void processNode (Node* node, Node*& minNode, int freeCellsCount) {
	// Сосчитаем сумму в текущем узле.
	node->sum = calculateSum( node->order );
	// Если она окажется больше минимального значения, что эту ветвь можно
	// не рассматривать и сразу вернуться.
	if (minNode && node->sum > minNode->sum && freeCellsCount > 0) {
		// Данный вывод вставлен для демонстрации. На матрицах 4x4 он не работает,
		// потому что там слишком мало вариантов, а вот уже на 6x6 работа
		// видна - некоторые ветви режутся.
		std::cout << "skip [ " << node->sum << " > " << minNode->sum << " ]\n";
		return;
	}
	// Если в node.order нет свободных ячеек, значит мы достигли конечного узла
	// дерева и нужно проверить сумму в текущем узле, вдруг она меньше текущего
	// минимума.
	if (freeCellsCount == 0) {
		// Если это самая левая ветвь дерева, то узел, хранящий текущий минимум
		// еще не определен и указатель на него равен 0.
		if (minNode == 0) {
			// Соответсвенно мы и становимся этим самым узлом.
			minNode = node;
		}
		// Иначе, нужно сравнить суммы узлов. Если сумма текущего узла окажется
		// меньше текущего минимума, то нужно переопределить ссылку minNode.
		else if (node->sum < minNode->sum) {
			minNode = node;
		}
		// Иначе мы ничего не обновляем, и просто возвращаеся из этого узла.
		else
			return;
	}
	
	// Иначе у нас еще есть место для расположения плат по незанятым ячейкам.
	// Воспользуемся этим шансом.
	else {
		// Необходимо создать у текущего узла детей и наполнить их содержанием.
		// Давайте узнаем какие платы еще не помещены в ячейки.
		std::set<int> plates;
		for (int i = 0; i < Node::mSize; ++i)
			plates.insert( i );
		for (int i = 0; i < Node::mSize && node->order[i] >= 0; ++i)
			plates.erase( node->order[i] );
		// А теперь создадим дочерние узлы. (Помним, что в set элементы уже
		// отсортированы по возрастанию если проходить итератором от begin до end)
		std::set<int>::iterator it = plates.begin();
		for ( ; it != plates.end(); ++it) {
			Node newNode;
			// Проинициализируем newNode.order
			for (int i = 0; i < Node::mSize && node->order[i] >= 0; ++i)
				newNode.order[i] = node->order[i];
			// Дописываем плату
			newNode.order[ Node::mSize - freeCellsCount ] = *it;
			
			// Узел создан, сохраним его в детях текущего узла
			node->children.push_back( newNode );
		}
		
		// А вот теперь самое интересное. Запускаем обход только что созданных
		// детей.
		for (unsigned int i = 0; i < node->children.size(); ++i) {
			processNode( &(node->children[i]), minNode, freeCellsCount - 1);
		}
	}
}