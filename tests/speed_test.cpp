#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <sys/timeb.h>
#include "../pml_node.h"

using namespace pml;

void speed_pml_test()
{
	pml_node tree;
	for (int i = 0; i < 1000000; i++)
	{
		char buffer[100];
		_itoa_s(i, buffer, 100, 10);
		pml_node *c = new pml_node(std::string(buffer));
		tree.add_child(c);
	}

	timeb beg, end;
	ftime(&beg);
	std::ofstream out("test.pml", std::ios_base::binary);
	tree.write(out);
	out.close();
	ftime(&end);
	std::cerr << "writing time:" << (end.time-beg.time)+end.millitm/1000.0-beg.millitm/1000.0 << " seconds" << std::endl;

	ftime(&beg);
	pml_node tree1;
	std::ifstream in("test.pml", std::ios_base::binary);
	tree1.read(in);
	in.close();
	ftime(&end);
	std::cerr << "reading time:" << (end.time-beg.time)+end.millitm/1000.0-beg.millitm/1000.0 << " seconds" << std::endl;

	assert(tree == tree1);
}

int main(int argc, char* argv[])
{
	speed_pml_test();
	return 0;
}