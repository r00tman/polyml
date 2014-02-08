#include <fstream>
#include <string>
#include <cassert>
#include "../pml_node.h"

using namespace std;
using namespace pml;

void pml_test()
{
	pml_node tree;
	tree.set_data("hi");
	assert(tree.str_data() == "hi");

	tree.add_child(new pml_node("hi"));
	assert(tree.children_count() == 1);

	ofstream out("test.pml", ios_base::binary);
	tree.write(out);
	out.close();

	pml_node tree1;
	ifstream in("test.pml", ios_base::binary);
	tree1.read(in);
	in.close();

	assert(tree == tree1);
}

int main(int argc, char* argv[])
{
	pml_test();
	return 0;
}
