#ifndef HISTOGRAMEQUALIZER_H
#define HISTOGRAMEQUALIZER_H

#include <histogram.h>

class HistogramEqualizer
{

private:
    vectorx accumulativeValues;
    vectorx functionValues;
    vectorx lookUpTable;
    double sum;
    void obtainSum(vectorx vectorHistogram);
public:
    HistogramEqualizer();
    vectorx getAccumulativeValues();
    vectorx getFunctionValues();
    vectorx getLookUpTable();
    double getSum();

    void setAccumulativeValues(vectorx accumulativeValues);
    void setFunctionValues(vectorx functionValues);
    void setLookUpTable(vectorx lookUpTable);
    void setSum(double sum);


    Image applyEqulizer(Image& image);


};

#endif // HISTOGRAMEQUALIZER_H
