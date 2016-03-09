#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Identity {
	string name;
	int ID;
};

bool compareByLength(const Identity &a, const Identity &b)
{
	return a.ID < b.ID;
}

int main(int argc, char** argv) {

	vector<Identity> ID_vec;
	Identity i;
	i.name = "Nelson";
	i.ID = 5;
	ID_vec.push_back(i);

	Identity j;
	j.name = "jason";
	j.ID = 2;
	ID_vec.push_back(j);

	i.name = "Kelvin";
	i.ID = 1;
	ID_vec.push_back(i);
	ID_vec.push_back({ "Peter",6 });
	ID_vec.push_back({ "John",3 });
	ID_vec.push_back({ "Alice",9 });
	ID_vec.push_back({ "Frankie",7 });
	ID_vec.push_back({ "Susan",4 });

	sort(ID_vec.begin(), ID_vec.end(), compareByLength);



	cout << "Size: " << ID_vec.size()<<endl;
	cout << "Capacity: " << ID_vec.capacity() << endl;
	cout << "first: " << ID_vec[0].name<<endl;
	cout << "Second: " << ID_vec[1].name<<endl;
	cout << "Third: " << ID_vec[2].name<<endl;
	cout << "Forth: " << ID_vec[3].name;

	return EXIT_SUCCESS;
}
