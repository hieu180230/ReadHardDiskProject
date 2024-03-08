#include "MFTEntry.h"
#include <iostream>
#include <vector>
#include "Utils.h"

MFTEntry::MFTEntry() {
	_firstSector = -1;

	_size = 0;
}

unsigned int MFTEntry::getId() {
	return _id;
}

unsigned int MFTEntry::getParentId() {
	return _parentId;
}

string MFTEntry::getName() {
	return _name;
}

string MFTEntry::getData() {
	return _data;
}

unsigned long long int MFTEntry::getSize() {
	return _size;
}

int MFTEntry::getAttributes() {
	return _attributes;
}

bool MFTEntry::isReadOnly() {
	return Utils::getBit(_attributes, PERM_READ_ONLY);
}

bool MFTEntry::isHidden() {
	return Utils::getBit(_attributes, PERM_HIDDEN);
}

bool MFTEntry::isSystem() {
	return Utils::getBit(_attributes, PERM_SYSTEM);
}

bool MFTEntry::isFile() {
	return _isFile;
}

bool MFTEntry::isFolder() {
	return !_isFile;
}

int MFTEntry::getFirstSector() {
	return _firstSector;
}

void MFTEntry::setId(unsigned int id) {
	_id = id;
}

void MFTEntry::setParentId(unsigned int parentId) {
	_parentId = parentId;
}

void MFTEntry::setName(string name) {
	_name = name;
}

void MFTEntry::setData(string data) {
	_data = data;
}
void MFTEntry::setSize(unsigned long long int  size) {
	_size = size;
}

void MFTEntry::setAttributes(int attributes) {
	_attributes = attributes;
}

void MFTEntry::setIsFile(bool isFile) {
	_isFile = isFile;
}

void MFTEntry::setFirstSector(int firstSector) {
	_firstSector = firstSector;
}

void MFTEntry::printInfo(int number) {
	cout << " [" << number << "] ";
	if (_isFile) cout << "File: ";
	else cout << "Folder: ";
	cout << _name << endl;
	
	cout << "     Attributes: ";
	if (isReadOnly()) cout << "read-only ";
	if (isHidden()) cout << "hidden ";
	if (isSystem()) cout << "system ";
	cout << endl;

	if (_isFile) {
		cout << "     Size: " << Utils::formatSize(_size) << endl;
	}
	cout << "     Data: ";
	if (_firstSector == -1) {
		cout << "resident" << endl;
	}
	else {
		cout << "non-resident (sector " << _firstSector << ")" << endl;
	}
}

bool MFTEntry::isTXT() {
	return this->_name.find(".txt") != std::string::npos;
}
