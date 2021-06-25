#include "pch.h"
#include "../Project1/grafo.h"
#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

class GrafoTest : public ::testing::Test {
	
protected:
	
	virtual void SetUp() {
		
	}
		
	virtual void TearDown() {
		
		// Code here will be called immediately after each test
			
		// (right before the destructor).
			
	}
	
};

//Determina si encuentra un nodo. Probando para no dirigido
TEST_F(GrafoTest, SinodoExiste) {

	grafo g;
	string inicio = "a";
	string fin = "b";
	ASSERT_FALSE(g.nodoExiste(inicio));

	g = grafo(inicio, 0);
	ASSERT_TRUE(g.nodoExiste(inicio));

	g.insertarNodo(fin);
	g.insertarArco(inicio, fin, 10);

	ASSERT_TRUE(g.nodoExiste(fin));

	g.borrarNodo(inicio);
	ASSERT_FALSE(g.nodoExiste(inicio));

	g.borrarNodo(fin);
	ASSERT_FALSE(g.nodoExiste(fin));

}

//Determina si encuentra un nodo. Probando para no dirigido
TEST_F(GrafoTest, arcos) {

	grafo g;
	string inicio = "a";
	string fin = "b";
	

	g = grafo(inicio, 0);
	g.insertarNodo(fin);
	g.insertarArco(inicio, fin, 10);


	ASSERT_TRUE(g.arcoExiste(inicio, fin));
	ASSERT_TRUE(g.arcoExiste(fin, inicio));

	ASSERT_TRUE(g.nodoTieneConexion(inicio));

	g.borrarArco(inicio, fin);
	ASSERT_FALSE(g.arcoExiste(inicio, fin));

	ASSERT_ANY_THROW(g.borrarArco(fin, inicio));  //Debe dar excepcion porque ese arco ya se borro

	ASSERT_FALSE(g.nodoTieneConexion(inicio));

}





//Determina si encuentra un nodo. Probando para no dirigido
TEST_F(GrafoTest, nodoTieneConexion) {

	grafo g;
	string inicio = "a";
	ASSERT_FALSE(g.nodoExiste(inicio));

	g = grafo(inicio, 0);
	ASSERT_TRUE(g.nodoExiste(inicio));

}


//Errores al insertar y borrar Nodos. Probando para no dirigido
TEST_F(GrafoTest, nodosExepciones) {

	grafo g;
	
	g = grafo("a", 0);

	g.insertarNodo("b");
	g.insertarNodo("c");
	g.insertarNodo("d");
	g.insertarNodo("e");
	g.insertarNodo("f");
	g.insertarNodo("g");
	g.insertarNodo("h");

	g.insertarArco("a", "b", 16);
	g.insertarArco("b", "c", 2);
	g.insertarArco("a", "c", 10);
	g.insertarArco("a", "d", 5);


	ASSERT_ANY_THROW(g.insertarNodo("c"));
	
	g.borrarNodo("c");
	ASSERT_FALSE(g.nodoExiste("c"));

	g.insertarNodo("c");
	ASSERT_FALSE(g.arcoExiste("b", "c"));

}





//Probando que el algoritmo acepte bien datos de entrada. Probando para no dirigido
TEST_F(GrafoTest, algoritmoDErrores) {

	grafo g;


	//Creo grafo
	g = grafo("a", 0);

	g.insertarNodo("b");
	g.insertarNodo("c");
	g.insertarNodo("d");
	g.insertarNodo("e");
	g.insertarNodo("f");
	g.insertarNodo("g");
	g.insertarNodo("h");

	g.insertarArco("a", "b", 16);
	g.insertarArco("b", "c", 2);
	g.insertarArco("a", "c", 10);
	g.insertarArco("a", "d", 5);
	g.insertarArco("c", "d", 4);
	g.insertarArco("b", "g", 6);
	g.insertarArco("b", "f", 4);
	g.insertarArco("c", "f", 12);
	g.insertarArco("c", "e", 10);
	g.insertarArco("d", "e", 15);
	g.insertarArco("g", "h", 7);
	g.insertarArco("f", "g", 8);
	g.insertarArco("f", "h", 16);
	g.insertarArco("f", "e", 3);
	g.insertarArco("e", "h", 5);

	string nodoI = "a";
	string nodoD = "z"; //nodo que no existe
	string fin;


	ASSERT_FALSE(g.algoritmoD(nodoI, nodoD)); //devulve falso, no se puede

	



}


//Probando un caso. Probando para no dirigido (FICHERO DE TESTO D1.TXT)

TEST_F(GrafoTest, algoritmoDjCaso1) {

	grafo g;


	//Creo grafo
	g = grafo("a", 0);

	g.insertarNodo("b");
	g.insertarNodo("c");
	g.insertarNodo("d");
	g.insertarNodo("e");
	g.insertarNodo("f");
	g.insertarNodo("g");
	g.insertarNodo("h");

	g.insertarArco("a", "b", 16);
	g.insertarArco("b", "c", 2);
	g.insertarArco("a", "c", 10);
	g.insertarArco("a", "d", 5);
	g.insertarArco("c", "d", 4);
	g.insertarArco("b", "g", 6);
	g.insertarArco("b", "f", 4);
	g.insertarArco("c", "f", 12);
	g.insertarArco("c", "e", 10);
	g.insertarArco("d", "e", 15);
	g.insertarArco("g", "h", 7);
	g.insertarArco("f", "g", 8);
	g.insertarArco("f", "h", 16);
	g.insertarArco("f", "e", 3);
	g.insertarArco("e", "h", 5);

	string nodoI = "a";
	string nodoD = "h";
	string fin;



	ASSERT_TRUE(g.algoritmoD(nodoI, nodoD));

	list<string> l = g.caminoOptimo();
	for (auto const& elem : l) {
		fin += elem;
	}
	ASSERT_EQ(fin, "adcbfeh");



}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}