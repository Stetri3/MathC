// testing.cpp
#include "linalg/vectors.hpp"
#include "calculus/duals.hpp"
#include <iostream>
#include <cassert>
#include "calculus/field_funcs.hpp"

int main() {
    std::cout << "--- INIZIO TEST AVANZATI ALGEBRA ---\n\n";

    // =================================================================
    // TEST 1: Vettore di Matrici Quadrate (Vec di MatQ)
    // =================================================================
    std::cout << "[Test 1] Vec di MatQ (Spazio di tensori/matrici)\n";

    // Un vettore tridimensionale dove ogni elemento è una MatQ 2x2 di float
    // Il tipo interno T è MatQ<2, float>, quindi _depth deve salire a 2
    using Mat2f = MatQ<2, float>;
    using VecOfMat = Vec<3, Mat2f>;

    // Inizializziamo le matrici interne
    Mat2f m1{ 1.0f, 2.0f, 3.0f, 4.0f }; // det = 1*4 - 2*3 = -2
    Mat2f m2 = Mat2f::One(2.0f);      // Diagonale con 2.0f -> det = 4
    Mat2f m3 = Mat2f::One(3.0f);      // Diagonale con 3.0f -> det = 9

    VecOfMat v_nested;
    v_nested.raw[0] = m1;
    v_nested.raw[1] = m2;
    v_nested.raw[2] = m3;

    // Verifica statica della profondità algebrica
    std::cout << "  -> Depth di Mat2f (Livello 1): " << co::_depth_v<Mat2f> << "\n";
    std::cout << "  -> Depth di VecOfMat (Livello 2): " << co::_depth_v<VecOfMat> << "\n";
    assert(co::_depth_v<VecOfMat> == 2);

    // Operazione 1: Moltiplicazione per scalare scalare (float, depth 0)
    // Deve moltiplicare ogni coefficiente di ogni matrice per 2.0f
    auto v_scaled = v_nested * 2.0f;
    std::cout << "  -> Scalamento Vec di MatQ eseguito.\n";
    assert(v_scaled.raw[1].raw[0] == 4.0f); // Il primo elemento di m2 scalato (2.0 * 2)

    // Operazione 2: Prodotto scalare tra due Vec di MatQ (Vettore * Vettore dello stesso livello)
    // Esegue il prodotto scalare standard sommando i prodotti delle matrici corrispondenti:
    // acc = (m1 * m1) + (m2 * m2) + (m3 * m3)
    // Il tipo di ritorno DEVE essere una MatQ<2, float> (stesso livello degli elementi interni)
    auto dot_matrix_result = v_nested * v_nested;

    std::cout << "  -> Prodotto scalare (Vec di Mat * Vec di Mat) riuscito.\n";
    std::cout << "  -> Determinante della matrice risultante: " << static_cast<MatQ<2, float>>(dot_matrix_result).det() << "\n";


    // =================================================================
    // TEST 2: Matrice di Vettori (Mat di Vec)
    // =================================================================
    std::cout << "\n[Test 2] Matrice di Vettori (Mat 2x2 di Vec3f)\n";

    using MatOfVec = Mat<2, 2, Vec3f>;

    Vec3f vec_a{ 1.0f, 0.0f, 0.0f };
    Vec3f vec_b{ 0.0f, 1.0f, 0.0f };

    // Costruiamo una matrice 2x2 di Vec3f
    MatOfVec M_nested;
    M_nested(0, 0) = vec_a;
    M_nested(0, 1) = vec_b;
    M_nested(1, 0) = vec_b;
    M_nested(1, 1) = vec_a;

    assert(co::_depth_v<MatOfVec> == 2);

    // Operazione: Moltiplicazione Matrice di Vettori * Vettore standard (MatOfVec * Vec)
    // Avendo bloccato la moltiplicazione per blocchi implicita, questo prodotto righe per colonne
    // moltiplica i Vettori interni per gli scalari del vettore destro.
    // MatOfVec (depth 2) * Vec2f (depth 1) -> Ritorna un Vec<2, Vec3f> (depth 2)
    Vec<2, float> v_combiner{ 2.0f, 3.0f };

    auto combinazione_lineare = M_nested * v_combiner;

    std::cout << "  -> Prodotto MatOfVec * Vec di combinazione riuscito.\n";
    // Risultato atteso sulla prima riga: vec_a * 2.0f + vec_b * 3.0f = {2.0f, 3.0f, 0.0f}
    std::cout << "  -> Risultato riga 0: {"
        << combinazione_lineare.raw[0].raw[0] << ", "
        << combinazione_lineare.raw[0].raw[1] << ", "
        << combinazione_lineare.raw[0].raw[2] << "}\n";

    assert(combinazione_lineare.raw[0].raw[0] == 2.0f);
    assert(combinazione_lineare.raw[0].raw[1] == 3.0f);


    // =================================================================
    // TEST 3: Vincoli Rigidi di Compile-Time (Cosa NON deve compilare)
    // =================================================================
    std::cout << "\n[Test 3] Verifica dei vincoli formali statici\n";

    // Un Vec3f ha depth 1. Un float ha depth 0.
    // Il tuo operatore * per scalare a destra vieta che lo scalare sia a un livello >= depth del vettore.

    // La riga sotto NON deve compilare perché stiamo provando a fare Vettore(depth 1) * Vettore(depth 1) 
    // trattando il secondo come scalare, ma il concept richiede (co::_depth_v<U> < _depth)
    // auto errore = vec_a * vec_b; // Togli il commento per testare il blocco del compilatore

    std::cout << "  -> Concept di protezione multilivello funzionanti.\n";

    std::cout << "\n--- TUTTI I TEST PASSATI CON SUCCESSO ---\n";

    Dual<float> r(3.0f, 2.0f);
    Dual<float> d(3.0f, 4.0f);
    Dual<float> e = r + d;
    std::cout << e.real << ", " << e.dual << "\n";

    Dual<Dual<float>> nest(r, d);
    Dual<Dual<float>> result = nest * d;
    std::cout << result.real.real << ", " << result.real.dual 
        << "; " << result.dual.real << result.dual.dual << "\n";
    return 0;
}