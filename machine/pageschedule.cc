#include "machine.h"
#include "system.h"

#ifdef LAB4

void TranslationEntryScheduler::SetStart(TranslationEntry *entry) {
	start = entry;
	return;
}


// FIFO translation entry scheduler

EntryFifo::EntryFifo(char *debugname = "scheduler") {
	list = new List;
	name = debugname;
}

EntryFifo::~EntryFifo() {
	delete list;
}

TranslationEntry* EntryFifo::Replace() {
	TranslationEntry *entry = this->Remove();
	ASSERT(entry);
	this->Insert(entry);
	return entry;
}

TranslationEntry* EntryFifo::Remove() {
	TranslationEntry *entry = list->Remove();
	if (entry) DEBUG('r', "%s remove index %d, vpn %d, ppn %d\n", name, entry-start, entry->virtualPage, entry->physicalPage);
	return entry;
}

void EntryFifo::Remove(TranslationEntry *entry) {
	list->Remove((void*)entry);
	entry->valid = false;
	DEBUG('r', "%s remove index %d, vpn %d, ppn %d\n", name, entry-start, entry->virtualPage, entry->physicalPage);
	return;
}

void EntryFifo::Insert(TranslationEntry *entry) {
	DEBUG('r', "%s insert index %d, vpn %d, ppn %d\n", name, entry-start, entry->virtualPage, entry->physicalPage);
	list->Append((void*)entry);
	return;
}

void EntryFifo::Use(TranslationEntry *entry) {
	DEBUG('r', "%s use index %d, vpn %d, ppn %d\n", name, entry-start, entry->virtualPage, entry->physicalPage);
	entry->use = true;
	return;
}

void EntryFifo::Dirty(TranslationEntry *entry) {
	DEBUG('r', "%s write index %d, vpn %d, ppn %d\n", name, entry-start, entry->virtualPage, entry->physicalPage);
	entry->dirty = true;
	return;
}

// LRU translation entry scheduler

EntryLru::EntryLru(char *debugname = "scheduler") {
	list = new List;
	name = debugname;
}

EntryLru::~EntryLru() {
	delete list;
}

TranslationEntry* EntryLru::Replace() {
	TranslationEntry *entry = this->Remove();
	ASSERT(entry);
	this->Insert(entry);
	return entry;
}


TranslationEntry* EntryLru::Remove() {
	TranslationEntry *entry = list->Remove();
	if (entry) DEBUG('r', "%s remove index %d, vpn %d, ppn %d\n", name, entry-start, entry->virtualPage, entry->physicalPage);
	return entry;
}

void EntryLru::Remove(TranslationEntry *entry) {
	list->Remove((void*)entry);
	entry->valid = false;
	DEBUG('r', "%s remove index %d, vpn %d, ppn %d\n", name, entry-start, entry->virtualPage, entry->physicalPage);
	return;
}


void EntryLru::Insert(TranslationEntry *entry) {
	DEBUG('r', "%s insert index %d, vpn %d, ppn %d\n", name, entry-start, entry->virtualPage, entry->physicalPage);
	list->Append((void*)entry);
	return;
}

void EntryLru::Use(TranslationEntry *entry) {
	DEBUG('r', "%s use index %d, vpn %d, ppn %d\n", name, entry-start, entry->virtualPage, entry->physicalPage);
	entry->use = true;
	list->Remove(entry);
	list->Append(entry);
	return;
}

void EntryLru::Dirty(TranslationEntry *entry) {
	DEBUG('r', "%s write index %d, vpn %d, ppn %d\n", name, entry-start, entry->virtualPage, entry->physicalPage);
	entry->dirty = true;
	list->Remove(entry);
	list->Append(entry);
}


// TLB Clock scheduler

EntryClock::EntryClock(char *debugname = "scheduler") {
	list = new List;
	name = debugname;
}

EntryClock::~EntryClock() {
	delete list;
}

TranslationEntry* EntryClock::Replace() {
	TranslationEntry *entry = this->Remove();
	ASSERT(entry);
	this->Insert(entry);
	return entry;
}


TranslationEntry* EntryClock::Remove() {
	TranslationEntry *entry = list->Remove();
	while (entry && (entry->clockDirty || entry->clockUse)) {
		if (entry->clockDirty && entry->clockUse) {
			entry->clockUse = false;
		}
		else {
			entry->clockDirty = false;
			entry->clockUse = false;
		}
		list->Append(entry);
		entry = list->Remove();
	}

	if (entry) DEBUG('r', "%s remove index %d, vpn %d, ppn %d\n", name, entry-start, entry->virtualPage, entry->physicalPage);
	return entry;
}

void EntryClock::Remove(TranslationEntry *entry) {
	list->Remove((void*)entry);
	entry->valid = false;
	DEBUG('r', "%s remove index %d, vpn %d, ppn %d\n", name, entry-start, entry->virtualPage, entry->physicalPage);
	return;
}

void EntryClock::Insert(TranslationEntry *entry) {
	DEBUG('r', "%s insert index %d, vpn %d, ppn %d\n", name, entry-start, entry->virtualPage, entry->physicalPage);
	list->Append((void*)entry);
	entry->clockDirty = false;
	entry->clockUse = false;
	return;
}

void EntryClock::Use(TranslationEntry *entry) {
	DEBUG('r', "%s use index %d, vpn %d, ppn %d\n", name, entry-start, entry->virtualPage, entry->physicalPage);
	entry->use = true;
	entry->clockUse = true;
	return;
}

void EntryClock::Dirty(TranslationEntry *entry) {
	DEBUG('r', "%s write index %d, vpn %d, ppn %d\n", name, entry-start, entry->virtualPage, entry->physicalPage);
	entry->dirty = true;
	entry->clockDirty = true;
}

#endif