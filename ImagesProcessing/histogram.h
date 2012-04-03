#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "image.h"

using namespace std;

typedef vector<double> vectorx;


class Histogram{
        private:
                vectorx histogram;
        public:
                Histogram();
                Histogram(Image& image);
                vectorx getHistogram();
                Image getImageHistogram();
                void setHistogram(vectorx histogram);
};

#endif // HISTOGRAM_H
