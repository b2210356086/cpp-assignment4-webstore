webstore:main
	g++ main.o tree_rb.o tree_avl.o -o webstore -std=c++11
main:tree_avl tree_rb
	g++ -c main.cpp -o main.o -std=c++11
tree_avl:
	g++ -c tree_avl.cpp -o tree_avl.o -std=c++11
tree_rb:
	g++ -c tree_rb.cpp -o tree_rb.o -std=c++11