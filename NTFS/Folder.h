#pragma once
#include "AbstractFile.h"

class Folder : public AbstractFile {
private:
	std::vector<AbstractFile*> context;
public:
	Folder() : AbstractFile() {}
	~Folder() {
		for (auto p : context) {
			delete p;
			p = nullptr;
		}
	}

	void add(AbstractFile* f) {
		if (f != nullptr) {
			context.push_back(f);
		}
	}

	std::vector<AbstractFile*>& getContext() { return this->context; }
};