#include <iostream>
#include <vector>///˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
#include <list>
#include <map>///˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜
#include <fstream>
#include <string>
#include "iostream"
#include <queue>
#include <unordered_map>

using namespace std;
class Knot{
public:
    char symbol;
    int freq;
    Knot *Left, *Right;

    Knot(Knot * L, Knot * R) {
        Left = L;
        Right = R;
    freq = L -> freq + R -> freq;
  }
   Knot() {
    Left = Right = NULL;
  }
  bool operator()(Knot* l, Knot* r)
	{   // ˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜
		return l->freq > r->freq;
	}

	void encode(Knot*, string, unordered_map<char,string>);
	void decode(Knot* , int &, string );
	void buildHuffmanTree(string text);
};/***********************************************************************/
    Knot* getKnot(char symbol, int freq, Knot* Left, Knot* Right)
{
	Knot* node = new Knot();

	node->symbol = symbol;
	node->freq = freq;
	node->Left = Left;
	node->Right = Right;

	return node;
}
void encode(Knot* root, string str,
			unordered_map<char, string> &huffmanCode)
{
	if (root == nullptr)
		return;

	// нашел листовой узел
	if (!root->Left && !root->Right) {
		huffmanCode[root->symbol] = str;
	}

	encode(root->Left, str + "0", huffmanCode);
	encode(root->Right, str + "1", huffmanCode);
}

// пройти по дереву Хаффмана и декодировать закодированную строку
void decode(Knot* root, int &index, string str)
{
	if (root == nullptr) {
		return;
	}

	// found a leaf node
	if (!root->Left && !root->Right)
	{
		cout << root->symbol;
		return;
	}

	index++;

	if (str[index] =='0')
		decode(root->Left, index, str);
	else
		decode(root->Right, index, str);
}

// Строит дерево Хаффмана и декодирует введенный текст
void buildHuffmanTree(string text)
{
	// посчитать частоту появления каждого символа
   // и сохранить его на карте
	unordered_map<char, int> freq;
	for (char ch: text) {
		freq[ch]++;
	}
    // Создаем приоритетную очередь для хранения активных узлов
   // дерево Хаффмана;
	priority_queue<Knot*, vector<Knot*>, Knot> pq;

	// Создаем конечный узел для каждого символа и добавляем его
   // в приоритетную очередь.
	for (auto pair: freq) {
		pq.push(getKnot(pair.first, pair.second, nullptr, nullptr));
	}

	// делать до тех пор, пока в очереди не будет более одного узла
	while (pq.size() != 1)
	{
		// Удаляем два узла с наивысшим приоритетом
        // (самая низкая частота) из очереди
		Knot *Left = pq.top(); pq.pop();
		Knot *Right = pq.top();	pq.pop();

		// Создаем новый внутренний узел с этими двумя узлами
        // как дочерние и с частотой, равной сумме
        // частот двух узлов. Добавьте новый узел
        // в приоритетную очередь.
		int sum = Left->freq + Right->freq;
		pq.push(getKnot('\0', sum, Left, Right));
	}

	// root хранит указатель на корень дерева Хаффмана
	Knot* root = pq.top();

	// обход дерева Хаффмана и сохранение кодов Хаффмана
    // на карте. Также печатает их
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "Huffman Codes are :\n" << '\n';
	for (auto pair: huffmanCode) {
		cout << pair.first << " " << pair.second << '\n';
	}

	cout << "\nOriginal string was :\n" << text << '\n';

	// вывести закодированную строку
	string str = "";
	for (char symbol: text) {
		str += huffmanCode[symbol];
	}

	cout << "\nEncoded string is :\n" << str << '\n';

	// снова проходим по дереву Хаффмана и на этот раз
    // декодируем закодированную строку
	int index = -1;
	cout << "\nDecoded string is: \n";
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}
}
/*********************************************************************/
 vector < bool > code; ///˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜ ˜.˜ #3
 map < char, vector < bool > > table; ///˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜ 'c' -> 0011
///˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜ #4
void Table(Knot * root) ///˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
{
  if (root -> Left != NULL) { code.push_back(0);
    Table(root -> Left);
  }
  if (root -> Right != NULL) { code.push_back(1);
    Table(root -> Right);
  }
  if (root -> Left == NULL && root -> Right == NULL) table[root -> symbol] = code;

  code.pop_back();
}

/***********                            ************/
int main(int argc, char * argv[])
{  /*
    Knot huf;
    string text = "qwerty";
    huf.buildHuffmanTree(text);*/

    ifstream fin("1.txt", ios::out | ios::binary);
    map < char, int > m; ///˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜ 1 ˜˜˜,2 ˜˜˜

    while(!fin.eof()){
        char symbol = fin.get();
        m[symbol]++;
    }

   while (!fin.eof()) ///˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ #1
   {
    char symbol = fin.get();
    m[symbol]++;
   }

  list < Knot * > t; ///˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜ Node #3

  for (map < char, int > ::iterator itr = m.begin(); itr != m.end(); ++itr) ///˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜ ˜ ˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜
  {
    cout << itr -> first << " : " << itr -> second <<"\t\n";
    Knot * p = new Knot;
    p -> symbol = itr -> first;
    p -> freq = itr -> second;
    t.push_back(p); ///t = ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
  }



  while (t.size() != 1) {
    t.sort(Knot());

    Knot * SonL = t.front();
    t.pop_front();
    Knot * SonR = t.front();
    t.pop_front();

    Knot * parent = new Knot(SonL, SonR);
    t.push_back(parent);

  }

  Knot * root = t.front();
  Table(root);

  fin.clear();
  fin.seekg(0);
cout << "Huffman binary text:\t";
  while (!fin.eof()) ///˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜ #4
  {
    char symbol = fin.get();
    vector < bool > x = table[symbol];
    cout << " ";
     for (int n = 0; n < x.size(); n++) {
      cout << x[n];
    }

  }
  cout << "\n";

  fin.clear();
  fin.seekg(0);

  ofstream g("output.txt", ios::out | ios::binary); ///#5

  int count = 0;
  char buf = 0;
  while (!fin.eof()) ///˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜  ˜˜˜˜˜˜˜ ˜˜˜.˜˜˜  ˜˜˜˜
  {
    char symbol = fin.get(); ///˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜.
    vector < bool > x = table[symbol];
    for (int n = 0; n < x.size(); n++) /// ˜˜˜˜ count ˜˜ ˜˜˜˜˜ = 8 ˜˜ ˜˜˜.˜˜˜˜˜˜˜˜˜˜ 'c'-> 10010
    {
      buf = buf | x[n] << (7 - count);
      count++;
      if (count == 8) {
        count = 0;
        g << buf;
        buf = 0;
      }
    }
  }

  fin.close();
  g.close();

  ifstream F("output.txt", ios:: in | ios::binary);
  Knot * p = root;
  count = 0;
  char byte;
  byte = F.get();
  while (!F.eof())
  {
    bool smash = byte & (1 << (7 - count));
    if (smash) p = p -> Right;
    else p = p -> Left;
    if (p -> Left == NULL && p -> Right == NULL) {
      cout << p -> symbol;
      p = root;
    }
    count++; if (count == 8) {
                count = 0;
                byte = F.get();
            }
    }

  F.close();

	return 0;
}

