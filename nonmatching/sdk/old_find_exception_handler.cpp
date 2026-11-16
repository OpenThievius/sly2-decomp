extern "C" {
struct ExceptionEntry {
    unsigned int start;
    unsigned int end;
    unsigned int handler;
};

unsigned int old_find_exception_handler(unsigned int pc, struct ExceptionEntry *table) {
    unsigned int result;
    int entryIndex = 0;
    int bestIndex = -1;
    struct ExceptionEntry *entry;
    unsigned int entryStart;

    if (table != 0) {
      if (table->start != 0xFFFFFFFF) {
        entry = table;
        do {
            entryStart = entry->start;
            if (pc >= entryStart && pc < entry->end) {
                if (bestIndex == -1 ||
                    (table[bestIndex].end >= entry->end && entryStart >= table[bestIndex].start)) {
                    bestIndex = entryIndex;
                }
            } else if (bestIndex != -1 && pc < entryStart) {
                break;
            }
            entry++;
            entryIndex++;
        } while (entry->start != 0xFFFFFFFF);
      }
    }
    if (bestIndex != -1) {
        { result = table[bestIndex].handler; goto done; }
    }
    { result = 0; goto done; }
done:
    return result;
}
}
