bool readConfig(const char *filename, int &n, int &start, int &end, const int base, string &pwd);
bool readDictionary(const char *filename, const string pwd);
void finish(bool success, const char *pwd, const int pastTime);