#include "Board.h"

BoardFactoryBase* BoardFactories::Find(const char* name) {
	for(iterator it = begin(); it != end(); ++it){
		if (strcmp((*it)->GetName(), name) == 0) return &**it;
	}
	return NULL;
}
BoardFactoryBase* BoardFactories::Find(int modelNum){
	for (iterator it = begin(); it != end(); ++it) {
		if ((*it)->GetModelNumber() == modelNum) return &**it;
	}
	return NULL;
}


BoardFactories Boards::factories;

BoardBase* Boards::Create(const char* name, int boardId) {
	BoardFactoryBase* f = factories.Find(name);
	if (!f) return NULL;
	BoardBase* b = f->Create(boardId);
	push_back(b);
	return b;
}
BoardBase* Boards::Create(int modelNum, int boardId) {
	BoardFactoryBase* f = factories.Find(modelNum);
	if (!f) return NULL;
	BoardBase* b = f->Create(boardId);
	push_back(b);
	return b;
}

BoardFactories::BoardFactories() {
	push_back(new BOARD_FACTORY(B1M));
	push_back(new BOARD_FACTORY(B1F));
}
