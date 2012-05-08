#ifndef THRESHOLDING_H
#define THRESHOLDING_H

#include "histogram.h"

class Thresholding{
        private:
                int threshold;
                vectorx lookUpTable;

        public:
                Thresholding();
                int getThreshold();
                vectorx getLookUpTable();
                void setThreshold(int threshold);
                void setLookUpTable(vectorx lookUpTable);


                Image applyDosPicos(Image& image);
                Image applyOtsu(Image& image);
                Image applyIsodata(Image& image);

                Image createThresholdImage(Image& image, int threshold);
                matrix createThresholdImage(matrix& grayScale, int level, int threshold);

};

#endif // THRESHOLDING_H
