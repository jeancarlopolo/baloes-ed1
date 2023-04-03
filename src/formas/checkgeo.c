#include "checkgeo.h"

bool checkPontoCirculo(double x, double y,
                       double r, double cx, double cy)
{
    // Calcula a distância do ponto ao centro do círculo
    // Se a distância for menor ou igual ao raio, o ponto está dentro do círculo
    // Se a distância for maior que o raio, o ponto está fora do círculo
    double dx = x - cx;
    double dy = y - cy;
    return dx * dx + dy * dy <= r * r;
}

bool checkPontoRetangulo(double x, double y,
                         double w, double h, double rx, double ry)
{
    // O ponto está dentro do retângulo se x >= rx e x <= rx + w
    // e y >= ry e y <= ry + h
    // Ou seja, se x e y estiverem dentro dos limites do retângulo
    return x >= rx && x <= rx + w && y >= ry && y <= ry + h;
}

bool checkRetanguloCirculo(double x, double y, double w, double h,
                           double cx, double cy, double r)
{
    // Verifica se algum dos pontos do retângulo está dentro do círculo
    bool result = checkPontoCirculo(x, y, r, cx, cy);
    result |= checkPontoCirculo(x + w, y, r, cx, cy);
    result |= checkPontoCirculo(x, y + h, r, cx, cy);
    result |= checkPontoCirculo(x + w, y + h, r, cx, cy);

    // Verifica se algum dos lados do retângulo intersecta o círculo
    result |= checkLinhaCirculo(x, y, x + w, y, cx, cy, r);
    result |= checkLinhaCirculo(x + w, y, x + w, y + h, cx, cy, r);
    result |= checkLinhaCirculo(x + w, y + h, x, y + h, cx, cy, r);
    result |= checkLinhaCirculo(x, y + h, x, y, cx, cy, r);
    return result;
}

// Verifica se o círculo está dentro do retângulo
bool checkCirculoRetangulo(double cx, double cy, double r,
                           double x, double y, double w, double h)
{
    bool result = checkPontoRetangulo(cx, cy, w, h, x, y);
    result |= checkRetanguloCirculo(x, y, w, h, cx, cy, r);
    return result;
}

// Verifica se a linha está dentro do círculo
bool checkLinhaCirculo(double x1, double y1, double x2, double y2,
                       double cx, double cy, double r)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    double a = dx * dx + dy * dy;
    double b = 2 * (dx * (x1 - cx) + dy * (y1 - cy));
    double c = cx * cx + cy * cy;
    c += x1 * x1 + y1 * y1;
    c -= 2 * (cx * x1 + cy * y1);
    c -= r * r;
    double bb4ac = b * b - 4 * a * c; // b^2 - 4ac
    if (bb4ac < 0)                    // Se não houver raízes reais, a linha não intersecta o círculo
        return false;
    double mu1 = (-b + sqrt(bb4ac)) / (2 * a); // (-b +- sqrt(b^2 - 4ac)) / 2a
    double mu2 = (-b - sqrt(bb4ac)) / (2 * a); // (-b +- sqrt(b^2 - 4ac)) / 2a
    return (mu1 >= 0 && mu1 <= 1) || (mu2 >= 0 && mu2 <= 1);
}

bool checkLinhaLinha(double x1, double y1, double x2, double y2,
                     double x3, double y3, double x4, double y4)
{
    // Verifica se a linha intersecta a linha utilizando o algoritmo de segmentos de reta
    double dx12 = x2 - x1;
    double dy12 = y2 - y1;
    double dx34 = x4 - x3;
    double dy34 = y4 - y3;
    double denominator = (dy12 * dx34 - dx12 * dy34);
    if (denominator == 0)
        return false;
    double dx31 = x1 - x3;
    double dy31 = y1 - y3;
    double numerator1 = (dy12 * dx31 - dx12 * dy31);
    double numerator2 = (dy34 * dx31 - dx34 * dy31);
    double mu1 = numerator1 / denominator;
    double mu2 = numerator2 / denominator;
    return (mu1 >= 0 && mu1 <= 1) && (mu2 >= 0 && mu2 <= 1);
}

// Verifica se a linha está dentro do retângulo
bool checkLinhaRetangulo(double x1, double y1, double x2, double y2,
                         double rx, double ry, double w, double h)
{
    // Verifica se a linha intersecta algum dos lados do retângulo
    bool result = checkLinhaLinha(x1, y1, x2, y2, rx, ry, rx + w, ry);
    result |= checkLinhaLinha(x1, y1, x2, y2, rx + w, ry, rx + w, ry + h);
    result |= checkLinhaLinha(x1, y1, x2, y2, rx + w, ry + h, rx, ry + h);
    result |= checkLinhaLinha(x1, y1, x2, y2, rx, ry + h, rx, ry);

    // Verifica se a linha está dentro do retângulo sem estar intersectando nenhum dos lados
    if (!result)
        result = checkPontoRetangulo(x1, y1, w, h, rx, ry) ||
                 checkPontoRetangulo(x2, y2, w, h, rx, ry);
    return result;
}

// Verifica se o círculo está dentro do círculo
bool checkCirculoCirculo(double x1, double y1, double r1,
                         double x2, double y2, double r2)
{
    // Calcula a distância entre os centros dos círculos
    // Se a distância for menor ou igual a soma dos raios, os círculos estão colidindo
    // Se a distância for maior que a soma dos raios, os círculos não estão colidindo
    double dx = x1 - x2;
    double dy = y1 - y2;
    return dx * dx + dy * dy <= (r1 + r2) * (r1 + r2);
}

// Verifica se o retângulo está dentro do retângulo
bool checkRetanguloRetangulo(double x1, double y1, double w1, double h1,
                             double x2, double y2, double w2, double h2)
{
    // QUAISQUER CASOS COM UM VÉRTICE DO RETÂNGULO 1 DENTRO DO RETÂNGULO 2
    // Verifica se o retângulo 1 está dentro do retângulo 2
    bool result = checkPontoRetangulo(x1, y1, w2, h2, x2, y2);
    result |= checkPontoRetangulo(x1 + w1, y1, w2, h2, x2, y2);
    result |= checkPontoRetangulo(x1, y1 + h1, w2, h2, x2, y2);
    result |= checkPontoRetangulo(x1 + w1, y1 + h1, w2, h2, x2, y2);

    // Verifica se o retângulo 2 está dentro do retângulo 1
    result |= checkPontoRetangulo(x2, y2, w1, h1, x1, y1);
    result |= checkPontoRetangulo(x2 + w2, y2, w1, h1, x1, y1);
    result |= checkPontoRetangulo(x2, y2 + h2, w1, h1, x1, y1);
    result |= checkPontoRetangulo(x2 + w2, y2 + h2, w1, h1, x1, y1);

    // CASOS EM QUE PARECE UM + OS DOIS RETÂNGULOS
    // Verifica se os lados horizontais do retângulo 1 colidem com os lados verticais do retângulo 2
    result |= checkLinhaLinha(x1, y1, x1 + w1, y1, x2, y2, x2, y2 + h2);
    result |= checkLinhaLinha(x1, y1, x1 + w1, y1, x2 + w2, y2, x2 + w2, y2 + h2);
    result |= checkLinhaLinha(x1, y1 + h1, x1 + w1, y1 + h1, x2, y2, x2, y2 + h2);
    result |= checkLinhaLinha(x1, y1 + h1, x1 + w1, y1 + h1, x2 + w2, y2, x2 + w2, y2 + h2);

    // Verifica se os lados verticais do retângulo 1 colidem com os lados horizontais do retângulo 2
    result |= checkLinhaLinha(x1, y1, x1, y1 + h1, x2, y2, x2 + w2, y2);
    result |= checkLinhaLinha(x1, y1, x1, y1 + h1, x2, y2 + h2, x2 + w2, y2 + h2);
    result |= checkLinhaLinha(x1 + w1, y1, x1 + w1, y1 + h1, x2, y2, x2 + w2, y2);
    result |= checkLinhaLinha(x1 + w1, y1, x1 + w1, y1 + h1, x2, y2 + h2, x2 + w2, y2 + h2);
    return result;
}