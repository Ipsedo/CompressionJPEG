//
// Created by samuel on 28/12/18.
//

#include "quantization.h"
#include <math.h>

std::vector<std::vector<double>> quantize(std::vector<std::vector<double>> F, std::vector<std::vector<double>> Q) {
    std::vector<std::vector<double>> res;

    for (int u = 0; u < F.size(); u++) {
        std::vector<double> line;
        for (int v = 0; v < F[u].size(); v++) {
            line.push_back(round(F[u][v] / Q[u][v]));
        }
        res.push_back(line);
    }

    return res;
}
