typedef struct{
int label;
float prob;
}pred_t;

extern pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred); // audiofeatures is the file name containing the dfeatures