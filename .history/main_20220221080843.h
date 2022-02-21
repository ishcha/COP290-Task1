void pool(char* type, char* im, char* stride, char* om);
void fc(char* im, char* wm, char* bm, char* om);
void prob(char* type, char* iv, char* ov);
void act(char* type, char* im, char* om);
void fc_mkl(char* im, char* wm, char* bm, char* om);

void fc_pthread(char* im, char* wm, char* bm, char* om);

void fc_blas(char* im, char *wm, char* bm, char* om);
void fc(char* im, char *wm, char* bm, char* om);